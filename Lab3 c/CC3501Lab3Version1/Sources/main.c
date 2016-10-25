/* ###################################################################
 **     Filename    : main.c
 **     Project     : CC3501Lab3Version1
 **     Processor   : MK20DX128VLH5
 **     Version     : Driver 01.01
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2016-08-16, 21:39, # CodeGen: 0
 **     Abstract    :
 **         Main module.
 **         This module contains user's application code.
 **     Settings    :
 **     Contents    :
 **         No public methods
 **
 ** ###################################################################*/
/*!
 ** @file main.c
 ** @version 01.01
 ** @brief
 **         Main module.
 **         This module contains user's application code.
 */
/*!
 **  @addtogroup main_module main module documentation
 **  @{
 */
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "ADLightSensor.h"
#include "AdcLdd1.h"
#include "FC321.h"
#include "RealTimeLdd1.h"
#include "TU1.h"
#include "TermUART0.h"
#include "Inhr1.h"
#include "ASerialLdd1.h"
#include "TermUART2.h"
#include "Inhr2.h"
#include "ASerialLdd2.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
/************************************* READING DATA ***************************************/
volatile char buffer[100];
volatile int buffer_index = 0;
volatile bool complete_command = 0;
volatile bool UART0_flag = 0;
volatile bool UART2_flag = 0;


char recieveChar() { // Waits for and recieves input
	byte c, err;
	int attempts;
	do {
		err = Inhr2_RecvChar(&c);
	} while (err != ERR_OK);
		return c;
}


/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
	/* Write your local variable definition here */
	/************************************* WRITING DATA ***************************************/
	uint16 lightADC = 0;
	uint16 timeval = 0;
	uint16 wait_time = 1000;		// 1000ms = 1sec
	int number = 0;

	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/

	/* Write your code here */

	//------------------------------------ WRITING DATA ----------------------------------------//
	/* SENSOR DATA
	FC321_Reset();
  	ADLightSensor_Calibrate(TRUE);

  	for(;;) {
  		FC321_GetTimeMS(&timeval);

  		if (timeval > wait_time) {
  			FC321_Reset();

  			ADLightSensor_Measure(TRUE);
  			ADLightSensor_GetValue16(&lightADC);

  			number = (int)lightADC;
  			TermUART0_SendNum(number);
  			TermUART0_SendStr("\r\n");
  		}
  	}
	 */
	ADLightSensor_Calibrate(TRUE);
	for(;;) {
		for(int i=0;i<1000000;i++) {}
		ADLightSensor_Measure(TRUE);
		ADLightSensor_GetValue16(&lightADC);
		int number = (int)lightADC;
		char* buffer[100];
		sprintf(buffer,"Light Sensor Reading: %i Fuck you XBEE\r\n", number);
		TermUART2_SendStr(buffer);
	}
	/*
	for(;;) {
			for(int i=0;i<1000000;i++) {}
			TermUART2_SendChar('k');
		}*/


	/*
	}

	//------------------------------------ READING DATA ---------------------------------------//
/*
	for(;;) {

		while (complete_command = 0) {
			//__asm__("wfi"); // Turns low power mode on
		}

		for (int i = 0; i < strlen(buffer); i++) {
			buffer[i] = '\0';
		}

		if (UART0_flag == 1) {
			TermUART0_SendStr("\r\nMsg from PUTTY");
		} else if (UART2_flag == 1) {
			TermUART0_SendStr("\r\nMsg from XBee");
		}

		complete_command = 0;
		UART0_flag = 0;
		UART2_flag = 0;
		buffer_index = 0;
	}
	 */
	/*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
 ** @}
 */
/*
 ** ###################################################################
 **
 **     This file was created by Processor Expert 10.5 [05.21]
 **     for the Freescale Kinetis series of microcontrollers.
 **
 ** ###################################################################
 */
