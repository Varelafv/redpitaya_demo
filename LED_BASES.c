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
#include "sleep.h"
#include "xparameters.h"
#include "xgpiops.h"
#include "xil_printf.h"

//PS_MIO[53:0]
#define ld0 54
#define ld1 55
#define ld2 56
#define ld7 61



int main()
{
    int i =0;
    XGpioPs_Config *ConfigPtrPS; //struct Pointeurs  -> u32 BaseAddr, ->u16 DeviceId;
    XGpioPs mio_emio ; //struct

    init_platform(); //active uart et autres periferiques

    //Verrouillage ressource matérielle 0
    ConfigPtrPS = XGpioPs_LookupConfig(0);
    if(ConfigPtrPS == NULL){
        return XST_FAILURE;
    }

    //Initialisation EMIO
    XGpioPs_CfgInitialize(&mio_emio,ConfigPtrPS, ConfigPtrPS->BaseAddr);

    //Autorization et direction EMIO
    XGpioPs_SetDirectionPin(&mio_emio,ld0, 1); //ld0 (GPIO_O[0],1=sortie
    XGpioPs_SetOutputEnablePin(&mio_emio,ld0,1);

    XGpioPs_SetDirectionPin(&mio_emio,ld1, 1);//ld1 (GPIO_O[1],1=sortie
    XGpioPs_SetOutputEnablePin(&mio_emio,ld1,1);

    XGpioPs_SetDirectionPin(&mio_emio,ld2, 1);//ld2 (GPIO_O[1],1=sortie
    XGpioPs_SetOutputEnablePin(&mio_emio,ld2,1);

    XGpioPs_SetDirectionPin(&mio_emio,ld7, 1);//ld7 (GPIO_O[1],1=sortie
    XGpioPs_SetOutputEnablePin(&mio_emio,ld7,1);

    xil_printf("Debut du test des leds.\n");
    for (i = 0;i<3;i++ ){
        XGpioPs_WritePin(&mio_emio, ld0, 0x1);
        XGpioPs_WritePin(&mio_emio, ld1, 0x0);

        usleep(500000);

        XGpioPs_WritePin(&mio_emio, ld0, 0x0);
        XGpioPs_WritePin(&mio_emio, ld1, 0x1);

        usleep(500000);

    }
    XGpioPs_WritePin(&mio_emio, ld2, 0x1);
    XGpioPs_WritePin(&mio_emio, ld7, 0x1);
    xil_printf("Fin du test des leds.\n");
    cleanup_platform();
    return 0;
}
