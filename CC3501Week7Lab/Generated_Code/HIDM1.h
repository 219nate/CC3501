/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : HIDM1.h
**     Project     : CC3501Week7Lab
**     Processor   : MK20DX128VLH5
**     Component   : FSL_USB_HID_Mouse_Device
**     Version     : Component 01.076, Driver 01.00, CPU db: 3.00.000
**     Repository  : My Components
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-09-06, 10:46, # CodeGen: 1
**     Abstract    :
**         Implements the HID Mouse USB device class.
**     Settings    :
**          Component name                                 : HIDM1
**          CPU                                            : Kinetis K20D50
**          HID Settings                                   : Enabled
**            Bus reported device                          : Nates mouse
**            Bus reported vendor                          : glensmum            
**            Message Size                                 : 4
**          Send Buffer                                    : Buffer
**          Power Options                                  : 
**            Bus Powered                                  : yes
**            Self Powered                                 : yes
**     Contents    :
**         App_Task     - byte HIDM1_App_Task(void);
**         isEnumerated - bool HIDM1_isEnumerated(void);
**         Send         - byte HIDM1_Send(byte action, signed char x, signed char y);
**         Move         - byte HIDM1_Move(signed char x, signed char y);
**         Click        - byte HIDM1_Click(byte buttonMask);
**         Deinit       - byte HIDM1_Deinit(void);
**         Init         - byte HIDM1_Init(void);
**
**     (c) Copyright Freescale, all rights reserved, 2013
**     http: www.freescale.com
**     Ported as Processor Expert component by Erich Styger, 2013-2015
**     Web       : www.mcuoneclipse.com
** ###################################################################*/
/*!
** @file HIDM1.h
** @version 01.00
** @brief
**         Implements the HID Mouse USB device class.
*/         
/*!
**  @addtogroup HIDM1_module HIDM1 module documentation
**  @{
*/         

#ifndef __HIDM1_H
#define __HIDM1_H

/* MODULE HIDM1. */

/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited beans */
#include "Tx2.h"
#include <stddef.h> /* for size_t */

#include "Cpu.h"



/* error/event codes for events */
#define HIDM1_USB_ERR_INIT            1  /* USB initialization error */
#define HIDM1_USB_ERR_DEINIT          2  /* USB deinitialization error */

/* bits for the first byte (action) of the update message */
#define HIDM1_MOUSE_LEFT    (1<<0)
#define HIDM1_MOUSE_RIGHT   (1<<1)
#define HIDM1_MOUSE_MIDDLE  (1<<2)

byte HIDM1_Init(void);
/*
** ===================================================================
**     Method      :  HIDM1_Init (component FSL_USB_HID_Mouse_Device)
**     Description :
**         Initializes the driver
**     Parameters  : None
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

byte HIDM1_App_Task(void);
/*
** ===================================================================
**     Method      :  HIDM1_App_Task (component FSL_USB_HID_Mouse_Device)
**     Description :
**         Application task to be called periodically from the main
**         task.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, returns ERR_OK if USB
**                           enumeration has been finished, error code
**                           otherwise.
** ===================================================================
*/

void HIDM1_App_Callback(byte controller_ID, byte event_type, void *val);
/*
** ===================================================================
**     Method      :  HIDM1_App_Callback (component FSL_USB_HID_Mouse_Device)
**
**     Description :
**         Method to handle class callbacks from USB
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

bool HIDM1_isEnumerated(void);
/*
** ===================================================================
**     Method      :  HIDM1_isEnumerated (component FSL_USB_HID_Mouse_Device)
**     Description :
**         Returns true if the device is enumerated
**     Parameters  : None
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

byte HIDM1_Send(byte action, signed char x, signed char y);
/*
** ===================================================================
**     Method      :  HIDM1_Send (component FSL_USB_HID_Mouse_Device)
**     Description :
**         Sends a message to the buffer. Call App_Task() periodically
**         to send the buffer.
**     Parameters  :
**         NAME            - DESCRIPTION
**         action          - Set of action bits, e.g. MOUSE_LEFT
**         x               - x offset for move
**         y               - y offset  for move
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

byte HIDM1_Move(signed char x, signed char y);
/*
** ===================================================================
**     Method      :  HIDM1_Move (component FSL_USB_HID_Mouse_Device)
**     Description :
**         Sends a mouse move
**     Parameters  :
**         NAME            - DESCRIPTION
**         x               - x move offset
**         y               - y move offset
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

byte HIDM1_Click(byte buttonMask);
/*
** ===================================================================
**     Method      :  HIDM1_Click (component FSL_USB_HID_Mouse_Device)
**     Description :
**         Sends a button press event followed by a release event.
**     Parameters  :
**         NAME            - DESCRIPTION
**         buttonMask      - mask of buttons
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

byte HIDM1_Deinit(void);
/*
** ===================================================================
**     Method      :  HIDM1_Deinit (component FSL_USB_HID_Mouse_Device)
**     Description :
**         Deinitializes the driver
**     Parameters  : None
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

/* END HIDM1. */

#endif
/* ifndef __HIDM1_H */
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
