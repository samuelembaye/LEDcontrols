#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

// Define potentiometer (analog input) and LED (PWM output) pins
#define POT1 1
#define POT2 2
#define POT3 3
#define POT4 4

#define LED PB1  // Pin 9 on Arduino Uno (OC1A for PWM)
#define SWITCH1 PD2 // Digital pin 2

void uart_init() {
    // Set baud rate to 115200 (assuming 16MHz clock)
    uint16_t ubrr = 16; 
    UBRR0H = (ubrr >> 8);
    UBRR0L = ubrr;
    UCSR0B = (1 << TXEN0);  // Enable TX
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8-bit data
}

void uart_transmit(char c) {
    while (!(UCSR0A & (1 << UDRE0))); // Wait until buffer is empty
    UDR0 = c;
}

void uart_print(const char *str) {
    while (*str) {
        uart_transmit(*str++);
    }
}

void adc_init() {
    ADMUX = (1 << REFS0); // Use AVcc as reference
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Enable ADC, set prescaler to 128
}

uint16_t adc_read(uint8_t channel) {
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F); // Select channel
    ADCSRA |= (1 << ADSC); // Start conversion
    while (ADCSRA & (1 << ADSC)); // Wait for conversion to finish
    return ADC;
}

void pwm_init() {
    DDRB |= (1 << LED); // Set LED pin as output
    TCCR1A = (1 << COM1A1) | (1 << WGM11); // Fast PWM, non-inverting
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11); // Prescaler 8
    ICR1 = 255; // Set top value for 8-bit resolution
}

void pwm_write(uint8_t value) {
    OCR1A = value; // Set PWM duty cycle
}

int main() {
    adc_init();
    pwm_init();
    uart_init();
    DDRD &= ~(1 << SWITCH1); // Set switch pin as input

    while (1) {
        uint16_t input = adc_read(POT4); // Read analog value
        char buffer[10];
        itoa(input, buffer, 10);
        uart_print(buffer);
        uart_print("\n");

        pwm_write(input / 4); // Convert 10-bit ADC to 8-bit PWM

        _delay_ms(1000);
    }
}
