# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 1.5.1)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(Joystick_posicao_x_y C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

pico_add_library(example_lwip_http_util NOFLAG)
target_sources(example_lwip_http_util INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/example_http_client_util.c
        )
pico_mirrored_target_link_libraries(example_lwip_http_util INTERFACE
        pico_lwip_http
        pico_lwip_mbedtls
        pico_mbedtls
        )
target_include_directories(example_lwip_http_util INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}
        )


# Add executable. Default name is the project name, version 0.1

add_executable(Joystick_posicao_x_y Joystick_posicao_x_y.c )
set(WIFI_SSID "Silva") # Nome da sua rede wifi
set(WIFI_PASSWORD "a1l9v7r8o") # Senha da rede wifi
target_compile_definitions(Joystick_posicao_x_y PRIVATE
        WIFI_SSID=\"${WIFI_SSID}\"
        WIFI_PASSWORD=\"${WIFI_PASSWORD}\"
        )

pico_set_program_name(Joystick_posicao_x_y "Joystick_posicao_x_y")
pico_set_program_version(Joystick_posicao_x_y "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(Joystick_posicao_x_y 0)
pico_enable_stdio_usb(Joystick_posicao_x_y 1)

# Add the standard library to the build
target_link_libraries(Joystick_posicao_x_y
        pico_stdlib
        pico_cyw43_arch_lwip_threadsafe_background
        example_lwip_http_util
        hardware_adc  
        )

# Add the standard include files to the build
target_include_directories(Joystick_posicao_x_y PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/..
)

# Add any user requested libraries
target_link_libraries(Joystick_posicao_x_y 
        
        )

pico_add_extra_outputs(Joystick_posicao_x_y)
