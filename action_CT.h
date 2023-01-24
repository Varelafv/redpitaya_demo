/*
 * action.h
 *
 *  Created on: 6 juin 2019
 *      Author: stage
 */

#ifndef SRC_ACTION_H_
#define SRC_ACTION_H_

#define ON	1
#define OFF	0

#define RST_MIO 78	//gpio(24) reset_MIO <= Ctrl_MIO(0);      --reset soft
#define RD_MIO 79	//gpio(25) rd_MIO <= Ctrl_MIO(1);
#define WR_MIO 80	//gpio(26) wr_MIO <= Ctrl_MIO(2);
#define RESA_MIO 81	//gpio(27)

#define CMDWR 0x0100 //bit WR GPIO à 1

#define ADR_PER 0x04
#define ADR_TONREF 0x05
#define ADR_TON1 0x06
#define ADR_DEL1 0x07
#define ADR_LED 0x16

#include "xgpiops.h"
#include <stdio.h>

XGpioPs_Config  *ConfigPtrPS;
XGpioPs  mio_emio;
//char tab_memoire [23][31];


//void transmettre_choix (unsigned int choix);
//void transmettre_epred(unsigned int epred);
//void dec_bin_epred (unsigned int tab_bin[], unsigned int number);
//void dec_bin_choix (unsigned int tab_bin[], unsigned int number);
//void stocker_choix (unsigned int choix);
//void stocker_epred (unsigned int epred, unsigned int choix);
//void ecrire_tous_les_params (char nb_signaux);
void ecrire_chenillard(void);
void traitement_cmd(char dir,char canal,char cmd,int value_int);

#endif /* SRC_ACTION_H_ */
