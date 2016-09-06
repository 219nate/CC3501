/* ###################################################################
**     Filename    : main.c
**     Project     : CC3501Week7Lab
**     Processor   : MK20DX128VLH5
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-09-06, 09:59, # CodeGen: 0
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
#include "USB1.h"
#include "USB0.h"
#include "HIDM1.h"
#include "Tx2.h"
#include "CS1.h"
#include "CI2C1.h"
#include "IntI2cLdd1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  USB1_Init();
  HIDM1_Init();
  Tx2_Clear();
  short int buffer[3] = {0,0,0};
  char startup[2];
  int x,y,z;
  uint16 num_bytes=0;
	// Register address we want to write to [CTRL_REG1 p.20]
	startup[0] = 0x2A;
	// Write data into the CTRL_REG1 to switch from standby mode to active mode
	startup[1] = 0x1;
	// Send the two bytes
	CI2C1_SendBlock(startup,2,&num_bytes);
	// Infinite loop to read the data
for(;;) {
	// Write register address we want to write to
	// [0x01 is used as it is the address for OUT_X_MSB and all the 5 other
	// values are in the 5 memory addresses straight after it
	CI2C1_SendChar(0x01);
	// Receive the 6 bytes from the 6 sequential register addresses
	CI2C1_RecvBlock(buffer,6,&num_bytes);
	// Extract the [X,Y,Z] values from the buffer
	x = buffer[0];
	y = buffer[1];
	z = buffer[2];
	HIDM1_Move(y/5000,x/5000);
	HIDM1_App_Task();
}


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
