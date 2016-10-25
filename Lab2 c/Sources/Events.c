/* ###################################################################
**     Filename    : Events.c
**     Project     : Lab9
**     Processor   : MK20DX128VLH5
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-09-22, 14:56, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"

#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */


extern int lineUpTo; // Line up to in serial command prompt
extern volatile char buffer[100]; // Buffer for the characters received
extern volatile int bufferIndex;
extern volatile int messageTypeRecieved;
extern volatile char recieveCharResult; // Initialize a variable to hold the character received
extern volatile int freezeInput; // Variable to determine if the input is disabled

/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MK20DX128EX5]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  AD1_OnEnd (module Events)
**
**     Component   :  AD1 [ADC]
**     Description :
**         This event is called after the measurement (which consists
**         of <1 or more conversions>) is/are finished.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AD1_OnEnd(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  AD1_OnCalibrationEnd (module Events)
**
**     Component   :  AD1 [ADC]
**     Description :
**         This event is called when the calibration has been finished.
**         User should check if the calibration pass or fail by
**         Calibration status method./nThis event is enabled only if
**         the <Interrupt service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AD1_OnCalibrationEnd(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  Inhr1_OnRxChar (module Events)
**
**     Component   :  Inhr1 [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Inhr1_OnRxChar(void) {
	recieveCharResult = RecieveChar(); // Receive the input character
	if (recieveCharResult == 0x7f) { // If a backspace is received
		if (freezeInput == 0) {
			Term1_SendChar(recieveCharResult); // Send the character to the terminal
			buffer[bufferIndex - 1] = 0x0; // 'Delete' the last character
			bufferIndex--;	// Move the index of the buffer to the left
		}
	} else if ((recieveCharResult == 0x0DU) || (recieveCharResult == 0x0AU)) { // If the enter key is pressed
		SendString("", 1); // Enter to a new line
		buffer[bufferIndex] = 0; // Add the terminate character to the end of the buffer
		bufferIndex = 0;
		messageTypeRecieved = 1;
	} else {
		if (freezeInput == 0) {
			Term1_SendChar(recieveCharResult); // Send the character to the terminal
			buffer[bufferIndex] = recieveCharResult; // Add the character to the buffer
			bufferIndex++; // Adjust the buffer index to the correct position (forward)
		}
	}

}

/*
** ===================================================================
**     Event       :  I2C2_OnMasterBlockSent (module Events)
**
**     Component   :  I2C2 [I2C_LDD]
*/
/*!
**     @brief
**         This event is called when I2C in master mode finishes the
**         transmission of the data successfully. This event is not
**         available for the SLAVE mode and if MasterSendBlock is
**         disabled. 
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void I2C2_OnMasterBlockSent(LDD_TUserData *UserDataPtr)
{
	// Update the 'transmitted' flag to TRUE to indicate the data has been transmitted
	MMA8451_TDataState *ptr = (MMA8451_TDataState*)UserDataPtr;
	ptr->dataTransmittedFlg = TRUE;
}

/*
** ===================================================================
**     Event       :  I2C2_OnMasterBlockReceived (module Events)
**
**     Component   :  I2C2 [I2C_LDD]
*/
/*!
**     @brief
**         This event is called when I2C is in master mode and finishes
**         the reception of the data successfully. This event is not
**         available for the SLAVE mode and if MasterReceiveBlock is
**         disabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void I2C2_OnMasterBlockReceived(LDD_TUserData *UserDataPtr)
{
	// Update the 'recieved' flag to TRUE to indicate the data has been recieved
	MMA8451_TDataState *ptr = (MMA8451_TDataState*)UserDataPtr;
	ptr->dataReceivedFlg = TRUE;
}

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

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
