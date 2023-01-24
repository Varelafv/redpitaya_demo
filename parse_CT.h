/*
 * parse.h
 *
 *  Created on: 5 juin 2019
 *      Author: stage
 */

#ifndef SRC_PARSE_H_
#define SRC_PARSE_H_



#define NOK		0
#define OK		1

#define R		0
#define W		1

enum{
	RST,
	PER,
	TON,
	NBR,
	DEL,
	LED
};


#include "stdlib.h"
#include "xil_printf.h"

int parse (u8* frame,char *W_R, char *num_signal,char *param,char *value, char *en, char *nb_signaux);
int parse_CP (u8* frame,char *dir, char *canal,char *cmd,unsigned int *value) ;

#endif /* SRC_PARSE_H_ */
