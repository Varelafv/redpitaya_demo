#include "init_CT.h"


void init (){

	int Status;
	int Status1;

	/*
	 * Run the Hello World example , specify the the Device ID that is
	 * generated in xparameters.h
	 */
	Status = UartPsHelloWorldExample(0);
	Status1 = init_gpio_o();


	if (Status == XST_FAILURE) {
		printf("Uartps hello world Example Failed\r\n");
	}else{
		printf("Successfully ran Uartps hello world Example\r\n");
	}

	if (Status1 == XST_FAILURE) {
		printf("GPIO_o hello world Example Failed\r\n");
	}else{
		printf("Successfully ran GPIO_o hello world Example\r\n");
	}

}

int UartPsHelloWorldExample(u16 DeviceId)
{
	int Status;
	XUartPs_Config *Config;

	/*
	 * Initialize the UART driver so that it's ready to use
	 * Look up the configuration in the config table and then initialize it.
	 */
	Config = XUartPs_LookupConfig(DeviceId);
	if (NULL == Config) {
		return XST_FAILURE;
	}

	Status = XUartPs_CfgInitialize(&Uart_Ps, Config, Config->BaseAddress);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	XUartPs_SetBaudRate(&Uart_Ps, 115200);

	return XST_SUCCESS;
}

int init_gpio_o (){

	int cpt ;

    // Verrouillage ressource matérielle 0
    ConfigPtrPS = XGpioPs_LookupConfig(0);
    if (ConfigPtrPS == NULL) {
    	return XST_FAILURE;
    }

    // Initialisation EMIO
    XGpioPs_CfgInitialize(&mio_emio, ConfigPtrPS, ConfigPtrPS->BaseAddr);

    // Autorisation et direction EMIO
    for(cpt = 54; cpt<82; cpt++){		//bus gpio 28bits
        XGpioPs_SetDirectionPin(&mio_emio, cpt, 1); 	// GPIO_O[0], 1 si sortie
        XGpioPs_SetOutputEnablePin(&mio_emio, cpt, 1);
    }

//    for(cpt1 = 86; cpt1<118; cpt1++){
//        XGpioPs_SetDirectionPin(&mio_emio, cpt1, 0); 	// ld0 (GPIO_O[0], 0 = entree de la partie soft
//        XGpioPs_SetOutputEnablePin(&mio_emio, cpt1, 0);
//    }



    return 0;
}
