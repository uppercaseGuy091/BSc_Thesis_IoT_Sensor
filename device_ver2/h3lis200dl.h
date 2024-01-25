/***
Filename: h3lis200dl.h
Authors: Michael Woldu & Konstantinos Sosopoulos
Origin Date: 20/3/2021
Module Version Number: 2.0
Compiler version used to compile the code: Atmel Studio v7.0.1931
Description: This header file contains the definitions of functions from h3lis200dl.c file for the H3LIS200DL accelerometer module.
***/

#ifndef H3LIS200DL
#define H3LIS200DL

//configure important settings in h3lis200dl
void h3lis200dl_init(void);

void h3lis200dl_read_ALL(int8_t* buff);

void h3lis200dl_read_X(uint8_t* buff);
void h3lis200dl_read_Y(uint8_t* buff);
void h3lis200dl_read_Z(uint8_t* buff);


#endif