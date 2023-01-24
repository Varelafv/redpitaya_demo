/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "sleep.h"
#include "xparameters.h"
#include "xgpiops.h"
//#include "stdlib.h"
#include <string.h>
#include <math.h>

//////////////////////////////////////////////////Mes includes à moi///////////////////////////
#include "init_CT.h"
#include "reception_uart_CT.h"
#include "parse_CT.h"
#include "action_CT.h"

static u8 RecvBuffer[TEST_BUFFER_SIZE];	/* Buffer for Receiving Data */


int main()
{
	int valid ; //= 3;
	char dir  ;//= 5;
	char canal ; //= 56;
	char cmd ; //= 5;
	unsigned int value_int ;
	char *mess ;

	init_platform();

   init(); //Init from Corentin de l'uart à 115200 bauds AINSI QUE init des GPIO

   print("Rappel commmandes :\n");
   print("\t-allume LED : \t$W:G:LED,XXXX!\t avec 0000<=XXXX<=00FF \n");
//   print("\t-RESET SOFT : \t$W:G:RST!\n");
//   print("\t-nb clk (1->8) : ex : \t$W:G:NBR,5!----non instantié-----\n");
//   print("\t-Modify Period (4 digit hexa) : ex : \t$W:G:PER,XXXX!\t avec 0001<=XXXX<=FFFF \n");
//   print("\t-Modify Delay CK(2->8) (4 digit hexa) : ex : \t$W:3:DEL,A00F!\t avec 0000<=XXXX<=FFFF\n");
//   print("\t-Modify Ton CK(1->8) (4 digit hexa) : ex : \t$W:1:TON,001F!\t avec 0000<=XXXX<=FFFF\n");
//   print("-... si un pulse a un TON>=PER signal DC... PHYSIQUE OBLIGE  ;)\n\n");
//   print("-... depend AUSSI du delay appliqué sinon signal DC aussi... PHYSIQUE OBLIGE  ;)\n\n");
   print("-----------------------------------------------------------------\n\n");

   memset(RecvBuffer,0,TEST_BUFFER_SIZE);

   do {
	   reception_uart(RecvBuffer);

	   valid = parse_CP(RecvBuffer,&dir, &canal,&cmd, &value_int) ;

	   if(valid != 1){ //Seulement si une trame n est pas valide
		   print("!! NOK !!\n\r");
	   }
	   else{
		   print("OK: ");
//		   ecrire_chenillard();
		   traitement_cmd(dir,canal,cmd,value_int);
	   }

    }while(1);
    cleanup_platform();
    return 0;
}
