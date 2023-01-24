/*
 * init.h
 *
 *  Created on: 5 juin 2019
 *      Author: stage
 */

#ifndef SRC_INIT_H_
#define SRC_INIT_H_

#include "xparameters.h"
#include "xuartps.h"
#include "xil_printf.h"
#include <stdio.h>
#include "xgpiops.h"
#include "action_CT.h"

XUartPs Uart_Ps;		/* The instance of the UART Driver */
XGpioPs_Config  *ConfigPtrPS;
XGpioPs  mio_emio;

void init ();
int UartPsHelloWorldExample(u16 DeviceId);
int init_gpio_o ();

#endif /* SRC_INIT_H_ */
