/*
 * reception_uart.h
 *
 *  Created on: 5 juin 2019
 *      Author: stage
 */

#ifndef SRC_RECEPTION_UART_H_
#define SRC_RECEPTION_UART_H_

#define TEST_BUFFER_SIZE	100

#include <string.h>
#include "xil_printf.h"
#include "xuartps.h"
#include "action_CT.h"

XUartPs Uart_Ps;		/* The instance of the UART Driver */

void reception_uart (u8 RecvBuffer[]);

#endif /* SRC_RECEPTION_UART_H_ */
