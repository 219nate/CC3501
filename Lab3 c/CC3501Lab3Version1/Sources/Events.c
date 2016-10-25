/* ###################################################################
 **     Filename    : Events.c
 **     Project     : CC3501Lab3Version1
 **     Processor   : MK20DX128VLH5
 **     Component   : Events
 **     Version     : Driver 01.00
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2016-08-16, 21:39, # CodeGen: 0
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
extern volatile char buffer[100];
extern volatile int buffer_index;
extern bool complete_command;
extern volatile bool UART0_flag;
extern volatile bool UART2_flag;

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
 **     Event       :  ADLightSensor_OnEnd (module Events)
 **
 **     Component   :  ADLightSensor [ADC]
 **     Description :
 **         This event is called after the measurement (which consists
 **         of <1 or more conversions>) is/are finished.
 **         The event is available only when the <Interrupt
 **         service/event> property is enabled.
 **     Parameters  : None
 **     Returns     : Nothing
 ** ===================================================================
 */
void ADLightSensor_OnEnd(void)
{
	/* Write your code here ... */
}

/*
 ** ===================================================================
 **     Event       :  ADLightSensor_OnCalibrationEnd (module Events)
 **
 **     Component   :  ADLightSensor [ADC]
 **     Description :
 **         This event is called when the calibration has been finished.
 **         User should check if the calibration pass or fail by
 **         Calibration status method./nThis event is enabled only if
 **         the <Interrupt service/event> property is enabled.
 **     Parameters  : None
 **     Returns     : Nothing
 ** ===================================================================
 */
void ADLightSensor_OnCalibrationEnd(void)
{
	/* Write your code here ... */
}

/*
 ** ===================================================================
 **     Event       :  Inhr2_OnRxChar (module Events)
 **
 **     Component   :  Inhr2 [AsynchroSerial]
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
void Inhr2_OnRxChar(void)
{
	/* Write your code here ... */
	byte c;
	TermUART0_SendStr("Message from XBee:\t");

	if (ERR_OK == Inhr2_RecvChar(&c)) {
		// If it is an enter
		if ((c == '\r') || (c == '\n')) {
			// Insert trailing null
			buffer[buffer_index] = '\0';
			complete_command = 1;
			UART2_flag = 1;

		} else if (buffer_index <= 99) {
			buffer[buffer_index] = c;
			buffer_index++;
			TermUART0_SendChar(c);
		}
	}
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
void Inhr1_OnRxChar(void)
{
	/* Write your code here ... */
	byte c;

	if (ERR_OK == Inhr1_RecvChar(&c)) {
		// If it is an enter
		if ((c == '\r') || (c == '\n')) {
			// Insert trailing null
			buffer[buffer_index] = '\0';
			complete_command = 1;
			UART0_flag = 1;

		} else if (buffer_index <= 99) {
			buffer[buffer_index] = c;
			buffer_index++;
			TermUART0_SendChar(c);
		}
	}

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
