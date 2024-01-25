/***
Filename: iam_20830.c
Authors: Michael Woldu & Konstantinos Sosopoulos
Origin Date: 20/3/2021
Module Version Number: 2.0
Compiler version used to compile the code: Atmel Studio v7.0.1931
Description: This file contains code to initialize and read values from the IAM-20830 gyroscope module. 
***/

#include <inttypes.h>
#include <stdint.h>
#include "i2c.h"
#include "iam_20380_reg.h"
#include "iam_20380.h"
#define I2C_WRITE   0

void iam20380_init(void);
void iam20380_read_gyro_X(uint8_t * buff);
void iam20380_read_gyro_Y(uint8_t * buff);
void iam20380_read_gyro_Z(uint8_t * buff);


void iam20380_init(void){
	
	i2c_write_byte(IAM20380_ADDRESS, GYRO_CONFIG, 0x1A); //0 for DLPF, rsvd, 2000 dps, enable x, y, z self-test
	
	//i2c_write_byte(IAM20380_ADDRESS, FIFO_EN, 0xF0); //rsvd, FIFO enable for x, y, z, temp
	//i2c_write_byte(IAM20380_ADDRESS, USER_CTRL, 0x00); //rsvd, enable FIFO, rsvd, not disable i2c, rsvd, not reset FIFO, rsvd, reset gyro digital paths
	
	i2c_write_byte(IAM20380_ADDRESS, PWR_MGMT_1, 0x09); //don't reset device, sleep mode off, rsvd, standby mode, disable temperature sensor, full gyro performance
	i2c_write_byte(IAM20380_ADDRESS, PWR_MGMT_2, 0x00); //rsvd, enable x, y, z gyro
	
	i2c_start(IAM20380_ADDRESS + I2C_WRITE);

}


//read gyro X, Y, Z all at once, high- & low-8-bits combined
//return int16_t (signed) in buff
//buff must have at least 3 available places
void iam20380_read_gyro_ALL(int16_t * buff){
	
	uint8_t tmp[2];

	iam20380_read_gyro_X(tmp);
	buff[0] = (tmp[0]<<8)|(tmp[1]);
	iam20380_read_gyro_Y(tmp);
	buff[1] = (tmp[0]<<8)|(tmp[1]);
	iam20380_read_gyro_Z(tmp);
	buff[2] = (tmp[0]<<8)|(tmp[1]);
}




//read gyro X, high- & low-8-bits separated, high first
//buff must have at least 2 available places
void iam20380_read_gyro_X(uint8_t * buff){

	i2c_read_byte(IAM20380_ADDRESS, GYRO_XOUT_H, buff);
	i2c_read_byte(IAM20380_ADDRESS, GYRO_XOUT_L, buff+1);
}

//read gyro Y, high- & low-8-bits separated, high first
//buff must have at least 2 available places
void iam20380_read_gyro_Y(uint8_t * buff){

	i2c_read_byte(IAM20380_ADDRESS, GYRO_YOUT_H, buff);
	i2c_read_byte(IAM20380_ADDRESS, GYRO_YOUT_L, buff+1);
}

//read gyro Z, high- & low-8-bits separated, high first
//buff must have at least 2 available places
void iam20380_read_gyro_Z(uint8_t * buff){

	i2c_read_byte(IAM20380_ADDRESS, GYRO_ZOUT_H, buff);
	i2c_read_byte(IAM20380_ADDRESS, GYRO_ZOUT_L, buff+1);
}