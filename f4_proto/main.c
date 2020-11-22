#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>

#include "pb_encode.h"
#include "pb_decode.h"
#include "proto/leds.pb.h"

const int pins[4] = {GPIO15, GPIO14, GPIO13, GPIO12};

void _error(void);

static void clock_setup(void)
{
    // Enable GPIO clock for LED & UART
    rcc_periph_clock_enable(RCC_GPIOD);
    rcc_periph_clock_enable(RCC_GPIOA);

    // Enable clock for UART2
    rcc_periph_clock_enable(RCC_USART2);
}

static void gpio_setup(void)
{
    // Setup GPIOD for leds
    gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO12);
    gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO13);
    gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO14);
    gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO15);

    // Setup GPIO for USART transmit
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2);
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO3);
    gpio_set_af(GPIOA, GPIO_AF7, GPIO2);
    gpio_set_af(GPIOA, GPIO_AF7, GPIO3);
}

static void usart_setup(void)
{
    // Setup USART2
    usart_set_baudrate(USART2, 115200);
    usart_set_databits(USART2, 8);
    usart_set_stopbits(USART2, USART_STOPBITS_1);
    usart_set_mode(USART2, USART_MODE_TX_RX);
    usart_set_parity(USART2, USART_PARITY_NONE);
    usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);

    usart_enable(USART2);
}

static void uart_transmit(const uint8_t * data, int16_t len)
{
    for (int16_t i = 0; i < len; i++) {
        usart_send_blocking(USART2, data[i]);
    }
}

static uint16_t uart_read_message(uint8_t * const data)
{
    uint16_t length;

    // Read the length of the message
    length = usart_recv_blocking(USART2);

    for (uint16_t i = 0; i < length; i++) {
        data[i] = usart_recv_blocking(USART2);
    }

    return length;
}

int main(void)
{
    clock_setup();
    gpio_setup();
    usart_setup();

    uint16_t length;
    uint8_t buffer[15];

    LedStatus led_status = {LedStatus_Led_OFF, LedStatus_Led_OFF, LedStatus_Led_OFF, LedStatus_Led_OFF};
    LedStatus led_request = {};

    LedStatus_Led * const request_leds[4] = {&led_request.LedBlue, &led_request.LedRed, &led_request.LedOrange, &led_request.LedGreen};
    LedStatus_Led* const status_leds[4] = {&led_status.LedBlue, &led_status.LedRed, &led_status.LedOrange, &led_status.LedGreen};

    while (1) {
        // Read message and decode protobuf
        length = uart_read_message(buffer);
        pb_istream_t istream = pb_istream_from_buffer(buffer, length);
        if (!pb_decode(&istream, LedStatus_fields, &led_request)) {
            _error();
        }

        // Enable/disable leds as requested
        for (uint8_t i = 0; i < 4; i++) {
            switch(*request_leds[i]) {
                case LedStatus_Led_ON:
                    gpio_set(GPIOD, pins[i]);
                    *status_leds[i] = LedStatus_Led_ON;
                    break;

                case LedStatus_Led_OFF:
                    gpio_clear(GPIOD, pins[i]);
                    *status_leds[i] = LedStatus_Led_OFF;
                    break;

                default:
                    break;
            }
        }

        // Encode ledstatus protobuf and send response over uart
        pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
        if (!pb_encode(&stream, LedStatus_fields, &led_status)) {
            _error();
        }

        // Send length + data
        usart_send_blocking(USART2, stream.bytes_written);
        uart_transmit(buffer, stream.bytes_written);
    }
}

void _error(void)
{
    while (1) {
        // Flash red led
        gpio_toggle(GPIOD, GPIO14);
        for (int i=0; i<1000000; i++) {
            __asm__("nop");
        }
    }
}
