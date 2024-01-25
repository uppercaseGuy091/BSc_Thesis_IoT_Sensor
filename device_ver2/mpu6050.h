/***
Filename: mpu6050.h
Authors: Unknown
Origin Date: Unknown
Module Version Number: Unknown
Compiler version used to compile the code: Atmel Studio v7.0.1931
Description: This header file contains the definitions of functions from mpu6050.c file for the MPU6050 gyroscope and accelerometer module.
***/

#ifndef MPU6050
#define MPU6050

//configure important settings in mpu6050
//subject to change application by app
void mpu6050_init(void);


// read accel X, Y, Z all at once, high- & low-8-bits combined
// return int16_t (signed) in buff
// buff must have at least 3 available places
// data sequence: (buff)-->X, (buff+1)-->Y, (buff+2)-->Z
// no error handling for too small buff
void mpu6050_read_accel_ALL(int16_t * buff);


//read accel X, Y, Z, high- & low-8-bits separated, high first
//buff must have at least 2 available places
//no error handling for too small buff

void mpu6050_read_accel_X(uint8_t * buff);
void mpu6050_read_accel_Y(uint8_t * buff);
void mpu6050_read_accel_Z(uint8_t * buff);



#endif
