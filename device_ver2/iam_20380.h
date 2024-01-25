/***
Filename: iam_20830.h
Authors: Michael Woldu & Konstantinos Sosopoulos
Origin Date: 20/3/2021
Module Version Number: 2.0
Compiler version used to compile the code: Atmel Studio v7.0.1931
Description: This header file contains the definitions of functions from iam_20830.c file for the IAM-20830 gyroscope module.
***/

#ifndef IAM_20380
#define IAM_20380

//configure important settings in iam-20830
//subject to change application by app
void iam20380_init(void);


//read gyro X, Y, Z all at once, high- & low-8-bits combined
//return int16_t (signed) in buff
//buff must have at least 3 available places
void iam20380_read_gyro_ALL(int16_t * buff);


//read gyro X, Y, Z high- & low-8-bits separated, high first
//buff must have at least 2 available places
void iam20380_read_gyro_X(uint8_t * buff);
void iam20380_read_gyro_Y(uint8_t * buff);
void iam20380_read_gyro_Z(uint8_t * buff);


#endif