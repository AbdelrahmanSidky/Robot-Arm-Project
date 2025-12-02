/*
 * Robot_Hand.c
 *
 * Created: 11/16/2025 1:07:04 PM
 * Author : Abd El Rahman Sidky
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL 
#include <util/delay.h>
#include <avr/interrupt.h>

#define servo0  0
#define servo1  1
#define servo2  2
#define servo3  3
#define servo4  4

#define servo0_pin  3
#define servo1_pin  4
#define servo2_pin  5
#define servo3_pin  6
#define servo4_pin  7

#define NUM_SERVO  5
volatile uint16_t servo_puls_us[5] = {1800, 1600, 1000, 1500,2500}; // pointing up
//volatile uint16_t servo_puls_us[5] = {2300, 1500, 2000, 1500,2300}; //initial position pointin out
volatile uint16_t frame_time_us = 0; // counter

volatile uint8_t servos_state = 0;

int main(void){
	DDRD |= (1 << servo1_pin) | (1 << servo2_pin) | (1 << servo3_pin)
			| (1 << servo4_pin) | (1 << servo0_pin);
	TCCR1A = 0;
	TCCR1B = (1 << WGM12) | (1 << CS11);
	OCR1A = 19; // interrupt every 10 us
	TIMSK1 = (1 << OCIE1A);
	
	sei();
	_delay_ms(700);
	while (1) {
		servo_puls_us[0] = 1800;
		_delay_ms(200);
		servo_puls_us[2] = 1500;
		_delay_ms(200);
		servo_puls_us[1] = 900;
		_delay_ms(200);
		servo_puls_us[3] = 1000;
		_delay_ms(200);
		servo_puls_us[4] = 900;
		_delay_ms(600);
		servo_puls_us[3] = 1500;
		_delay_ms(200);
		servo_puls_us[2] = 1000;
		_delay_ms(500);
		servo_puls_us[0] = 600;
		_delay_ms(400);
		servo_puls_us[4] = 2300;
		_delay_ms(200);
    }
}

ISR(TIMER1_COMPA_vect){
	if(frame_time_us == 0){
		PORTD = (1 << servo1_pin) | (1 << servo2_pin) | (1 << servo3_pin)
		        | (1 << servo4_pin) | (1 << servo0_pin);
		servos_state = 0x1f;
	}
	// servo 0
	if((servos_state & (1 << 0)) && (frame_time_us >= servo_puls_us[0])){
		PORTD &= ~(1 << servo0_pin);
		servos_state &= ~(1 << 0);
	}
	// servo 1
	if((servos_state & (1 << 1)) && (frame_time_us >= servo_puls_us[1])){
		PORTD &= ~(1 << servo1_pin);
		servos_state &= ~(1 << 1);
	}
	// servo 2
	if((servos_state & (1 << 2)) && (frame_time_us >= servo_puls_us[2])){
		PORTD &= ~(1 << servo2_pin);
		servos_state &= ~(1 << 2);
	}
	// servo 3
	if((servos_state & (1 << 3)) && (frame_time_us >= servo_puls_us[3])){
		PORTD &= ~(1 << servo3_pin);
		servos_state &= ~(1 << 3);
	}
	// servo 4
	if((servos_state & (1 << 4)) && (frame_time_us >= servo_puls_us[4])){
		PORTD &= ~(1 << servo4_pin);
		servos_state &= ~(1 << 4);
	}
	
	frame_time_us += 10; // counter +10us
	
	if(frame_time_us >= 20000){
		frame_time_us = 0;
	}
}
	






