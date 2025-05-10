#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"
#include "example_http_client_util.h"

#define HOST          "192.168.18.8"
#define PORT          5000
#define INTERVALO_MS  200

// Pinos do joystick
#define JOY_X_PIN     26   // ADC0
#define JOY_Y_PIN     27   // ADC1

void adc_setup() {
    adc_init();
    // configurar GPIO26 e GPIO27 como ADC
    adc_gpio_init(JOY_X_PIN);
    adc_gpio_init(JOY_Y_PIN);
}

uint16_t read_adc_channel(uint8_t channel) {
    adc_select_input(channel);
    return adc_read();  // 0–4095
}

int main() {
    stdio_init_all();
    adc_setup();

    // Wi-Fi
    if (cyw43_arch_init()) return 1;
    cyw43_arch_enable_sta_mode();
    cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD,
                                       CYW43_AUTH_WPA2_AES_PSK, 30000);

    printf("Conectado! Iniciando loop de envio...\n");

    while (1) {
        // Lê ADC0 e ADC1
        uint16_t raw_x = read_adc_channel(0);
        uint16_t raw_y = read_adc_channel(1);

        // Normaliza para 0–100 (%)
        int pct_x = raw_x * 100 / 4095;
        int pct_y = raw_y * 100 / 4095;

        // Monta URL: /joystick?x=NN&y=MM
        char path[64];
        snprintf(path, sizeof(path),
                 "/joystick?x=%d&y=%d", pct_x, pct_y);

        EXAMPLE_HTTP_REQUEST_T req = {0};
        req.hostname   = HOST;
        req.url        = path;
        req.port       = PORT;
        req.headers_fn = http_client_header_print_fn;
        req.recv_fn    = http_client_receive_print_fn;

        printf("Enviando %s\n", path);
        http_client_request_sync(cyw43_arch_async_context(), &req);

        sleep_ms(INTERVALO_MS);
    }
    return 0;
}
