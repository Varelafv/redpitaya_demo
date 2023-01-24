/*
 * action.c
 *
 *  Created on: 6 juin 2019
 *      Author: stage
 */

#include "action_CT.h"
#include "parse_CT.h"
#include "sleep.h"

void ecrire_chenillard(){
	print("!! clignote led7 !!");
	XGpioPs_WritePin(&mio_emio, RESA_MIO, 1);
	usleep(500000);
	XGpioPs_WritePin(&mio_emio, RESA_MIO, 0);
	usleep(500000);
	XGpioPs_WritePin(&mio_emio, RESA_MIO, 1);
	usleep(500000);
	XGpioPs_WritePin(&mio_emio, RESA_MIO, 0);
}

void traitement_cmd(char dir,char canal,char cmd,int value_int)
{
u32 datagpio ;
char adr_TON;
char message[100] ;

	sprintf(message, "   message décodé : dir=%c \tcanal=%c \tcmd=%c \tvalue_int=%d \n", dir, canal, cmd, value_int) ; // si on veut que message non tronqué il faut 3 espaces avant le début de la chaine ...
			print(message) ;
	if (dir==W){
		switch(cmd){
			case NBR:
			print("!! Commande non traitée pour l'instant !!\n\r");
			break ;

			case RST:
			XGpioPs_WritePin(&mio_emio, RST_MIO, ON);
			usleep(10);
			XGpioPs_WritePin(&mio_emio, RST_MIO, OFF);
			print("!! Reset soft !!\n\r");
			break ;

			case PER:
//			sprintf(message, "   dans  traitement_cmd \tvalue_int : 0x%x \n ", value_int ) ; // si on veut que message non tronqué il faut 3 espaces avant le début de la chaine ...
//			print(message) ;
			datagpio=value_int+0x10000*ADR_PER;
			XGpioPs_Write(&mio_emio, XGPIOPS_BANK2, datagpio) ;
			XGpioPs_WritePin(&mio_emio, WR_MIO, ON);
			usleep(10);
			XGpioPs_WritePin(&mio_emio, WR_MIO, OFF);
			sprintf(message, "   Modify PERIOD :\t-> adr=0x%x \t-> value=0x%x \t-> datagpio=0x%x \n", ADR_PER, value_int,datagpio) ; // si on veut que message non tronqué il faut 3 espaces avant le début de la chaine ...
			print(message) ;
			break ;

			case TON:
			if (canal=='G')
				adr_TON=ADR_TONREF;
			else										// à modifier qd plus que 2 signaux ...
				adr_TON=ADR_TON1 ;
			datagpio=value_int+0x10000*adr_TON;
			XGpioPs_Write(&mio_emio, XGPIOPS_BANK2, datagpio) ;
			XGpioPs_WritePin(&mio_emio, WR_MIO, ON);
			usleep(10);
			XGpioPs_WritePin(&mio_emio, WR_MIO, OFF);
			print("!!  Modify TON: !!\n\r");
			sprintf(message, "   Modify TON :\t-> canal=%c \t-> adr=0x%x \t-> value=0x%x \t-> datagpio=0x%x \n", canal,adr_TON, value_int,datagpio) ; // si on veut que message non tronqué il faut 3 espaces avant le début de la chaine ...
			print(message) ;
			break ;

			case DEL:
			datagpio=value_int+0x10000*ADR_DEL1;
			XGpioPs_Write(&mio_emio, XGPIOPS_BANK2, datagpio) ;// à modifier qd plus que 2 signaux ...
			XGpioPs_WritePin(&mio_emio, WR_MIO, ON);
			usleep(10);
			XGpioPs_WritePin(&mio_emio, WR_MIO, OFF);
			print("!! Modify DELAY: !!\n\r");
			break ;

			case LED:
			datagpio=value_int+0x10000*ADR_LED;
			XGpioPs_Write(&mio_emio, XGPIOPS_BANK2, datagpio) ;// à modifier qd plus que 2 signaux ...
			XGpioPs_WritePin(&mio_emio, WR_MIO, ON);
			usleep(10);
			XGpioPs_WritePin(&mio_emio, WR_MIO, OFF);
			print("!! Modify LED: !!\n\r");
			break ;

		default :
			print("!! default sur switch traitement_cmd !!\n\r");
			break ;

		}

	}
	else
		print("!! dir W uniquement permis actuellement!!\n\r");
}
