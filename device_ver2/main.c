/***
Filename: main.c
Authors: Michael Woldu & Konstantinos Sosopoulos
Origin Date: 25/2/2021
Module Version Number: 3.0
Compiler version used to compile the code: Atmel Studio v7.0.1931
Description: This file contains code to operate our device prototype version 3.
That is, reading values from the IAM-20830 and H3LIS200DL and sending them via UART.
***/


#define F_CPU 16000000UL
#define MYUBRR ( F_CPU / 16 / BaudRate ) -  1
#define BaudRate 9600
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "i2c.h"
#include "uart.h"
#include "iam_20380.h"
#include "h3lis200dl.h"

float Xgyro, Ygyro, Zgyro;
int16_t gyroBuff[3];

int16_t Xacc, Yacc, Zacc;
int8_t accBuff[3];


/******************************************************************************************************************
*Name: stringafy_and_Send                                                                                         *
*                                                                                                                 *
*Purpose: Converts an integer to a character and then sends it via UART                                           *
*										     	                                                                  *
*In data: An int16_t variable											                                          *
*								                                                                                  *
*Out data: None									                                                                  *
*                                                                                                                 *
*Calls: uart_puts(), itoa()												                                          *
*******************************************************************************************************************/
void stringafy_and_Send(int16_t num){
	
	char _buffer[7];
	itoa(num, _buffer, 10);	//conversion from integer to char
	uart_puts(_buffer);
}


/******************************************************************************************************************
*Name: stringafy                                                                                                  *
*                                                                                                                 *
*Purpose: Sends given integers via UART while putting spaces between each one                                     *
*										     	                                                                  *
*In data: 3 int16_t variables											                                          *
*								                                                                                  *
*Out data: None									                                                                  *
*                                                                                                                 *
*Calls: uart_puts(), sprintf()											                                          *
*******************************************************************************************************************/
void stringafy(int16_t x, int16_t y, int16_t z){
	
	char newString[100];
	sprintf(newString, "%i %i %i", x,y,z);
	uart_puts(newString);
}


int main(void){
	
	uart_init(UART_BAUD_SELECT(BaudRate,F_CPU));	//initialize uart communication
	iam20380_init();	//initialize gyro with chosen settings (see function in iam_20830.c)
	h3lis200dl_init();	//initialize acc with chosen settings (see function in h3lis200dl.c)
	sei();

	while(1){
		
		//uart_puts("A");
		//_delay_ms(200);
		char c = uart_getc();
		
		if (c == '1'){	//if start btn is pressed from android app
			
			while (1) {
				c=uart_getc();
				if (c== '0'){	//if stopped btn is pressed from android app
					break;
				}
				
				
				
				iam20380_read_gyro_ALL(gyroBuff);	//read gyro x, y, z axes values from the registers
				Xgyro = gyroBuff[0];	//read x axis into Xgyro
				Ygyro = gyroBuff[1];	//read y axis into Ygyro
				Zgyro = gyroBuff[2];	//read z axis into Zgyro
				
				
				/************************************************************************/
				/* H3LIS200DL accelerometer range is +-100g = 200g (200000 mg)          */
				/* Output is 8 bits -> 2^8 = 256 (256 different readings for +-100g)    */
				/* 200000mg/256 = 781.25                                                */
				/* Each time the LSB changes by 1, the value changes by 781.25mg        */
				/*						                                                */
				/* So that means that if the raw value is for example 5                 */
				/* the true value is 5*780 (as per the spec sheet) = 3900mg = 3.9g      */
				/*																		*/
				/* (raw value*780)/1000 = value in g                                    */
				/************************************************************************/
				h3lis200dl_read_X(&accBuff);	//reads x axis from acc and puts it into accBuff
				Xacc = accBuff[0];
				Xacc = (Xacc*780)/1000;
				stringafy_and_Send(Xacc);	//covert Xacc int to char and send via uart
				uart_puts(" ");
				
				h3lis200dl_read_Y(&accBuff);	//reads y axis from acc and puts it into accBuff
				Yacc = accBuff[0];
				Yacc = (Yacc*780)/1000;
				stringafy_and_Send(Yacc);	//covert Yacc int to char and send via uart
				uart_puts(" ");
				
				h3lis200dl_read_Z(&accBuff);	//reads z axis from acc and puts it into accBuff
				Zacc = accBuff[0];
				Zacc = (Zacc*780)/1000;
				stringafy_and_Send(Zacc);	//covert Zacc int to char and send via uart
				uart_puts("\n");
				
				_delay_ms(25);	//this delay is for the Android app to have time to process the acc values before going to the gyro
				
				/************************************************************************/
				/* IAM20380 Gyroscope range 2000 dps ->  16.4 LSB/dps		            */
				/* Output is 16 bits -> 8 bits High and 8 bits Low                      */
				/*																	    */
				/* To get Degrees Per Second the raw value has to be multiplied by 0.07 */
				/* (raw value*0.07) = value in dps					                    */
				/************************************************************************/
				Xgyro = Xgyro*0.07;
				Ygyro = Ygyro*0.07;
				Zgyro = Zgyro*0.07;
				
				stringafy(Xgyro,Ygyro,Zgyro);	//take x, y, z axes values from gyro and send via uart
				uart_puts("\n");

				
				//uart_puts("\n");	//the newline character is needed to print the values into Arduino Serial Plotter
				
				_delay_ms(50);
				
			}
			
		}
		
	}
	
	return 0;
}
