/***
Filename: h3lis200dl_reg.h
Authors: Michael Woldu & Konstantinos Sosopoulos
Origin Date: 20/3/2021
Module Version Number: 1.0
Compiler version used to compile the code: Atmel Studio v7.0.1931
Description: This header file contains the addresses of all the registers of the H3LIS200DL accelerometer module.
***/

#ifndef H3LIS200DL_REG
#define H3LIS200DL_REG

#define H3LIS200DL_ADDRESS (0x19 << 1) //page 18 from the data sheet (0b0011001)
#define WHO_AM_I 0x0F 
#define CTRL_REG1 0x20 
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24
#define HP_FILTER_RESET 0x25
#define REFERENCE 0x26
#define STATUS_REG 0x27
#define OUT_X 0x29
#define OUT_Y 0x2B
#define OUT_Z 0x2D
#define INT1_CFG 0x30
#define INT1_SRC 0x31
#define INT1_THS 0x32
#define INT1_DURATION 0x33
#define INT2_CFG 0x34
#define INT2_SRC 0x35
#define INT2_THS 0x36
#define INT2_DURATION 0x37


#endif
