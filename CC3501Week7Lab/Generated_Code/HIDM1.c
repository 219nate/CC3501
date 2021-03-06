/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : HIDM1.c
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
** @file HIDM1.c
** @version 01.00
** @brief
**         Implements the HID Mouse USB device class.
*/         
/*!
**  @addtogroup HIDM1_module HIDM1 module documentation
**  @{
*/         

/* MODULE HIDM1. */

#include "HIDM1.h"
#include "hidef.h"          /* for EnableInterrupts macro */
#include "derivative.h"     /* include peripheral declarations */
#include "types.h"          /* Contains User Defined Data Types */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usb_hid.h"

#define  CONTROLLER_ID     (0)   /* ID to identify USB CONTROLLER */

#define  MOUSE_BUFF_SIZE   (4)   /* report buffer size, number of bytes in message, specified in component properties */
#define  REQ_DATA_SIZE     (1)

#if (MOUSE_BUFF_SIZE<4) || (MOUSE_BUFF_SIZE>5)
  #error "Only buffer size of 4 or 5 supported!"
#endif

static uint_8 rpt_buf[MOUSE_BUFF_SIZE];     /* Mouse Event Report Buffer Key press */
static uint_8 g_app_request_params[2];      /* for get/set idle and protocol requests*/
static volatile boolean transactionOngoing = FALSE; /* flag to know if a transaction is currently ongoing */
static volatile bool mouse_init = FALSE; /* flag to indicate if mouse is enumerated */
/******************************************************************************
 *
 *    @name        USB_App_Param_Callback
 *
 *    @brief       This function handles callbacks for USB HID Class request
 *
 *    @param       request  : request type
 *    @param       value    : give report type and id
 *    @param       data     : pointer to the data
 *    @param       size     : size of the transfer
 *
 *    @return      status
 *                 USB_OK  :  if successful
 *                 else return error
 *
 *****************************************************************************
 * This function is called whenever a HID class request is received. This
 * function handles these class requests
 *****************************************************************************/
uint_8 USB_App_Param_Callback(
      uint_8 request,        /* [IN] request type */
      uint_16 value,         /* [IN] report type and ID */
      uint_16 wIndex,                 /* [IN] interface*/
      uint_8_ptr* data,      /* [OUT] pointer to the data */
      USB_PACKET_SIZE* size  /* [OUT] size of the transfer */
)
{
  uint_8 status = USB_OK;
  uint_8 index = (uint_8)((request - 2) & USB_HID_REQUEST_TYPE_MASK);
                                         /* index == 0 for get/set idle,
                                            index == 1 for get/set protocol */

  (void)wIndex; /* unused parameter */
  *size = 0;
  /* handle the class request */
  switch(request) {
    case USB_HID_GET_REPORT_REQUEST :
      *data = &rpt_buf[0]; /* point to the report to send */
      *size = MOUSE_BUFF_SIZE; /* report size */
      break;

     case USB_HID_SET_REPORT_REQUEST :
       for(index = 0; index < MOUSE_BUFF_SIZE ; index++)
       {   /* copy the report sent by the host */
         rpt_buf[index] = *(*data + index);
       }
       break;

      case USB_HID_GET_IDLE_REQUEST :
        /* point to the current idle rate */
        *data = &g_app_request_params[index];
        *size = REQ_DATA_SIZE;
        break;

      case USB_HID_SET_IDLE_REQUEST :
        /* set the idle rate sent by the host */
        g_app_request_params[index] =(uint_8)((value & MSB_MASK) >> HIGH_BYTE_SHIFT);
        break;

      case USB_HID_GET_PROTOCOL_REQUEST :
        /* point to the current protocol code
           0 = Boot Protocol
           1 = Report Protocol*/
        *data = &g_app_request_params[index];
        *size = REQ_DATA_SIZE;
        break;

      case USB_HID_SET_PROTOCOL_REQUEST :
        /* set the protocol sent by the host
           0 = Boot Protocol
           1 = Report Protocol*/
        g_app_request_params[index] = (uint_8)(value);
        break;
  }
  return status;
}
/*
** ===================================================================
**     Method      :  HIDM1_App_Callback (component FSL_USB_HID_Mouse_Device)
**
**     Description :
**         Method to handle class callbacks from USB
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void HIDM1_App_Callback(byte controller_ID, byte event_type, void *val)
{
  (void)controller_ID; /* not used */
  (void)val; /* not used */
  if((event_type == USB_APP_BUS_RESET) || (event_type == USB_APP_CONFIG_CHANGED) || (event_type==USB_APP_BUS_SUSPEND)) {
    mouse_init = FALSE;
    transactionOngoing = FALSE;
  } else if(event_type == USB_APP_ENUM_COMPLETE) {
    /* if enumeration is complete set mouse_init so that application can start */
    mouse_init = TRUE;
  } else if (event_type==USB_APP_SEND_COMPLETE && mouse_init) {
    transactionOngoing = FALSE;
  }
}

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
byte HIDM1_App_Task(void)
{
  uint32_t hidCode; /* upper 8bits are modifier, lower 8bits are hid code value */

  /* device is Kinetis K20D50 */
  USB_Class_HID_Periodic_Task(); /* call the periodic task function */
  if (!mouse_init) {
    return ERR_BUSOFF; /* bus not available, device not enumerated */
  }
  while (Tx2_Get(&hidCode)==ERR_OK) { /* send everything in the queue */
    /* send message */
    #if MOUSE_BUFF_SIZE==4
    rpt_buf[0] = (hidCode>>24)&0xFF; /* button information */
    rpt_buf[1] = (hidCode>>16)&0xFF; /* x */
    rpt_buf[2] = (hidCode>>8)&0xFF; /* y */
    rpt_buf[3] = hidCode&0xFF;
    #else
      #error "NYI"
    /*! \todo */
    #endif
    transactionOngoing = TRUE;
    if (USB_Class_HID_Send_Data(CONTROLLER_ID, HID_ENDPOINT, rpt_buf, sizeof(rpt_buf))!=USB_OK) {
      transactionOngoing = FALSE;
      return ERR_FAILED;
    }
    while(transactionOngoing) {
      /* wait until we send the next transaction */
    }
  } /* while */
  return ERR_OK;
}

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
byte HIDM1_Deinit(void)
{
  byte err;

  mouse_init = FALSE;
  transactionOngoing = FALSE;
  err = USB_Class_HID_DeInit(CONTROLLER_ID);
  if(err != USB_OK) {
    /* Error initializing USB HID Class */
    return ERR_FAILED;
  }
  return ERR_OK;
}

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
byte HIDM1_Init(void)
{
  byte err;

  mouse_init = FALSE;
  transactionOngoing =  FALSE;
  err = USB_Class_HID_Init(CONTROLLER_ID, HIDM1_App_Callback, NULL, USB_App_Param_Callback);
  if(err != USB_OK) {
    /* Error initializing USB HID Class */
    return ERR_FAILED;
  }
  return ERR_OK;
}

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
bool HIDM1_isEnumerated(void)
{
  return mouse_init;
}

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
byte HIDM1_Send(byte action, signed char x, signed char y)
{
  uint8_t status;

  if (!mouse_init) {
    return ERR_FAILED;
  }
  rpt_buf[0] = action;
  rpt_buf[1] = (uint8_t)x;
  rpt_buf[2] = (uint8_t)y;
#if MOUSE_BUFF_SIZE==4
  rpt_buf[3] = 0;
#elif MOUSE_BUFF_SIZE==5
  rpt_buf[3] = 0;
  rpt_buf[4] = 0;
#endif
  status = USB_Class_HID_Send_Data(CONTROLLER_ID,HID_ENDPOINT, rpt_buf, sizeof(rpt_buf));
  if (status != USB_OK) {
    return ERR_FAILED;
  }
  return ERR_OK;
}

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
byte HIDM1_Move(signed char x, signed char y)
{
  union {
   uint8_t bytes[4]; /*! \todo */
   uint32_t val;
  } u;

  u.val = 0;
  u.bytes[1] = x;
  u.bytes[2] = y;
  return Tx2_Put(u.val);
}

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
byte HIDM1_Click(byte buttonMask)
{
  if (Tx2_Put(((Tx2_ElementType)buttonMask)<<24)!=ERR_OK) { /* put 32bit value into buffer */
    return ERR_FAILED;
  }
  return (Tx2_Put(0)!=ERR_OK); /* send release message */
}

/* END HIDM1. */

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
