/* ###################################################################
**     Filename    : main.c
**     Project     : Lab8CC3501
**     Processor   : MK20DX128VLH5
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-09-28, 14:30, # CodeGen: 0
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

#include "Cpu.h"
#include "Events.h"
#include "mqx_tasks.h"
#include "MQX1.h"
#include "SystemTimer1.h"
#include "AD1.h"
#include "AdcLdd1.h"
#include "Term1.h"
#include "Inhr1.h"
#include "ASerialLdd1.h"
#include "MMA8451Q.h"
#include "IntI2cLdd1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include "theBakersHeader.h" // The Cheekiest Include Known to Man
#include "main.h"
MessageQueue msg_queue;


LWSEM_STRUCT msg_queue_lock; // Message Lock
char startup[2]; // Char for 8bit Data Elements
word num_bytes = 0; // Needed for I2C

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
  	Term1_SendStr("CC3501 [Lab 8]\r\n"); // Print Startup
 	AD1_Calibrate(FALSE); // Calibrate the ADC
 	// Setup the I2C Communication
	startup[0] = 0x2A;
	startup[1] = 0x1;
	MMA8451Q_SendBlock(startup,2,&num_bytes);
 	Term1_SendStr("Calibrated.......\r\n"); // Print Calibrated
 	// Initialize Message Queue
 	_lwmsgq_init(&msg_queue, QUEUE_LENGTH, sizeof(Message)/sizeof(_mqx_max_type));
	// Initialise the Semaphore
	_lwsem_create(&msg_queue_lock, 1);

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
