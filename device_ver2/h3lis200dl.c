/***
Filename: h3lis200dl.c
Authors: Michael Woldu & Konstantinos Sosopoulos
Origin Date: 20/3/2021
Module Version Number: 2.0
Compiler version used to compile the code: Atmel Studio v7.0.1931
Description: This file contains code to initialize and read values from the H3LIS200DL accelerometer module.
***/

#include <inttypes.h>
#include <stdint.h>
#include "i2c.h"
#include "h3lis200dl_reg.h"
#include "h3lis200dl.h"
#define I2C_WRITE   0


//configure important settings in h3lis200dl
void h3lis200dl_init(){ 
	i2c_write_byte(H3LIS200DL_ADDRESS, CTRL_REG1, 0x2F); //normal mode, output data rate at 100 Hz, x y z axes enable
	//i2c_write_byte(H3LIS200DL_ADDRESS, CTRL_REG1, 0x37); //normal mode, output data rate at 400 Hz, x y z axes enable
	//i2c_write_byte(H3LIS200DL_ADDRESS, CTRL_REG1, 0x67); //low power mode, output data rate at 1, x y z axes enable
	
	//i2c_write_byte(H3LIS200DL_ADDRESS, CTRL_REG2, 0x80); //boot bit enabled (device calibration?)
	
	i2c_write_byte(H3LIS200DL_ADDRESS, CTRL_REG4, 0x00); //scale 100g, spi 3-wire interface
	
	//i2c_write_byte(H3LIS200DL_ADDRESS, CTRL_REG5, 0x03); //low power mode, odr set from ctrl_reg1 (default value is 0)
	
	i2c_start(H3LIS200DL_ADDRESS+I2C_WRITE);

}


//read accel X, Y, Z all at once and store in int8_t buff
//buff must have at least 3 available places
void h3lis200dl_read_ALL(int8_t* buff){
	
	uint8_t tmp[2];

	h3lis200dl_read_X(tmp);
	buff[0] = (tmp[0]<<8)|(tmp[1]);
	h3lis200dl_read_Y(tmp);
	buff[1] = (tmp[0]<<8)|(tmp[1]);
	h3lis200dl_read_Z(tmp);
	buff[2] = (tmp[0]<<8)|(tmp[1]);
}


void h3lis200dl_read_X(uint8_t* buff){
	i2c_read_byte(H3LIS200DL_ADDRESS, OUT_X, buff);
}


void h3lis200dl_read_Y(uint8_t* buff){
	i2c_read_byte(H3LIS200DL_ADDRESS, OUT_Y, buff);
}


void h3lis200dl_read_Z(uint8_t* buff){
	i2c_read_byte(H3LIS200DL_ADDRESS, OUT_Z, buff); 
}


void h3lis200dl_read_who_am_i(uint8_t* buff){
	i2c_read_byte(H3LIS200DL_ADDRESS, WHO_AM_I, buff);

}
