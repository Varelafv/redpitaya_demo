/*
 * parse.c
 *
 *  Created on: 5 juin 2019
 *      Author: stage
 */

#include "parse_CT.h"


int parse_CP (u8* frame,char *dir, char *canal,char *cmd,unsigned int *value)
{
	int i=0;
	int j=0;
	char value_trame[4]; // car 4 digit attendus
	char message[30] ;
////////////////////////////////////////////Traitement début de trame////////////////////////////////////////////////
	while(frame[i]!='$')
	{
		i++;
		if(i==10)
			return NOK;
	}
	i++;

////////////////////////////////////////////Traitement Read Write////////////////////////////////////////////////
	if(frame[i]=='W')
		*dir = W;
	else {
		if(frame[i]=='R')
			*dir = R;
		else
			return NOK;
	}
	i++;

////////////////////////////////////////////Traitement séparation////////////////////////////////////////////////
	if(frame[i]!=':')
		return NOK;
	i++;

////////////////////////////////////////////Traitement numéro signal////////////////////////////////////////////////
	if(frame[i]>='0' && frame[i]<='7'){
		//*num_signal = frame[i]-'0';
		*canal = frame[i];
	}
	else if(frame[i] == 'G'){
		*canal = 'G';	//codage pouvant être amélioré avec opérateur OU
	}
	else{
		return NOK;
	}
	i++;

////////////////////////////////////////////Traitement séparation////////////////////////////////////////////////
	if(frame[i]!=':'){
		return NOK;
	}
	i++;

////////////////////////////////////////////Traitement parametre à modifier///////////////////////////////////////////
	if(frame[i]=='N'&& frame[i+1]=='B' && frame[i+2]=='R')
		*cmd=NBR ;
	else if(frame[i]=='R'&& frame[i+1]=='S'&& frame[i+2]=='T')
		*cmd=RST ;
	else if(frame[i]=='T'&& frame[i+1]=='O'&& frame[i+2]=='N')
		*cmd=TON;
	else if(frame[i]=='P'&& frame[i+1]=='E'&& frame[i+2]=='R')
		*cmd = PER;
	else if(frame[i]=='D'&& frame[i+1]=='E'&& frame[i+2]=='L')
		*cmd = DEL;
	else if(frame[i]=='L'&& frame[i+1]=='E'&& frame[i+2]=='D')
		*cmd = LED;
	else
		return NOK;
	i+=3;

////////////////////////////////////////////Traitement cmd////////////////////////////////////////////////
	// selon Write ou Read
	if(*dir==W)
	{
		if(*cmd==RST) {
			if(frame[i]=='!')
				return OK;
			else
				return NOK;
		}
		else {
			if(frame[i] != ',')			//Traitement séparation
			return NOK;
			i++;
		}

		if(*cmd==NBR) {
			if(frame[i]>='0' && frame[i]<='7')
				*value = frame[i]-'0';
			else
				return NOK;
			i++;
			if(frame[i]=='!')
				return OK;
			else
				return NOK;
		}

		if(*cmd==PER || *cmd==TON || *cmd==DEL || *cmd==LED) {
			*value=0;

			for (j=0 ; j<4 ; j++){
				if(frame[i]>='0' && frame[i]<='9')
					value_trame[j]= frame[i++]-'0';
				else
					return NOK;
			}


				*value=value_trame[3]+16*value_trame[2]+256*value_trame[1]+4096*value_trame[0];
	//			sprintf(message, "   \tapres parse_value : value : 0x%x \n ", *value ) ; // si on veut que message non tronqué il faut 3 espaces avant le début de la chaine ...
	//			print(message) ;

				//		  pour convertir valeur ascii en hexa
				//			char nombre_repr[] = "0x1234";
				//		    char *pc = nombre_repr;
				//		    char *p_end = NULL;
				//
				//		    unsigned int nombre = strtoul(pc, &p_end, 16);
				//
				//		    if (pc != p_end)
				//		    {
				//		        printf("La valeur du nombre est %x\n", nombre);
				//		    }
		} // fin du if du dir==W

		// que ce soit R ou W la trame finit par un !

		if(frame[i]=='!')	//attention qd je mets des print avant, le i s'incrémente et ne voit plus le '!' !! bizarrerie du print !!
			return OK;
		else
			return NOK;
	}

	return NOK;
}






