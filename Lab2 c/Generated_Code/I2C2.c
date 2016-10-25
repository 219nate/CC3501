/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : I2C2.c
**     Project     : Lab2
**     Processor   : MK20DX128VLH5
**     Component   : I2C_LDD
**     Version     : Component 01.016, Driver 01.07, CPU db: 3.00.000
**     Repository  : Kinetis
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-08-05, 21:56, # CodeGen: 0
**     Abstract    :
**          This component encapsulates the internal I2C communication
**          interface. The implementation of the interface is based
**          on the Philips I2C-bus specification version 2.0.
**          Interface features:
**          MASTER mode
**            - Multi master communication
**            - The combined format of communication possible
**              (see SendStop parameter in MasterSend/ReceiveBlock method)
**            - 7-bit slave addressing (10-bit addressing can be made as well)
**            - Acknowledge polling provided
**            - No wait state initiated when a slave device holds the SCL line low
**            - Holding of the SCL line low by slave device recognized as 'not available bus'
**            - Invalid start/stop condition detection provided
**          SLAVE mode
**            - 7-bit slave addressing
**            - General call address detection provided
**     Settings    :
**          Component name                                 : I2C2
**          I2C channel                                    : I2C0
**          Interrupt service                              : Enabled
**            Interrupt                                    : INT_I2C0
**            Interrupt priority                           : medium priority
**          Settings                                       : 
**            Mode selection                               : MASTER
**            MASTER mode                                  : Enabled
**              Initialization                             : 
**                Address mode                             : 7-bit addressing
**                Target slave address init                : 0x1D
**            SLAVE mode                                   : Disabled
**            Pins                                         : 
**              SDA pin                                    : 
**                SDA pin                                  : ADC0_SE9/TSI0_CH6/PTB1/I2C0_SDA/FTM1_CH1/FTM1_QD_PHB
**                SDA pin signal                           : 
**              SCL pin                                    : 
**                SCL pin                                  : ADC0_SE8/TSI0_CH0/PTB0/LLWU_P5/I2C0_SCL/FTM1_CH0/FTM1_QD_PHA
**                SCL pin signal                           : 
**              High drive select                          : Disabled
**              Input Glitch filter                        : 0
**            Internal frequency (multiplier factor)       : 5.24288 MHz
**            Bits 0-2 of Frequency divider register       : 000
**            Bits 3-5 of Frequency divider register       : 000
**            SCL frequency                                : 262.144 kHz
**            SDA Hold                                     : 1.335 us
**            SCL start Hold                               : 1.144 us
**            SCL stop Hold                                : 2.098 us
**            Control acknowledge bit                      : Disabled
**            Low timeout                                  : Disabled
**          Initialization                                 : 
**            Enabled in init code                         : yes
**            Auto initialization                          : no
**            Event mask                                   : 
**              OnMasterBlockSent                          : Enabled
**              OnMasterBlockReceived                      : Enabled
**              OnMasterByteReceived                       : Disabled
**              OnSlaveBlockSent                           : Disabled
**              OnSlaveBlockReceived                       : Disabled
**              OnSlaveByteReceived                        : Disabled
**              OnSlaveRxRequest                           : Disabled
**              OnSlaveTxRequest                           : Disabled
**              OnSlaveGeneralCallAddr                     : Disabled
**              OnSlaveSmBusCallAddr                       : Disabled
**              OnSlaveSmBusAlertResponse                  : Disabled
**              OnError                                    : Disabled
**          CPU clock/configuration selection              : 
**            Clock configuration 0                        : This component enabled
**            Clock configuration 1                        : This component disabled
**            Clock configuration 2                        : This component disabled
**            Clock configuration 3                        : This component disabled
**            Clock configuration 4                        : This component disabled
**            Clock configuration 5                        : This component disabled
**            Clock configuration 6                        : This component disabled
**            Clock configuration 7                        : This component disabled
**     Contents    :
**         Init               - LDD_TDeviceData* I2C2_Init(LDD_TUserData *UserDataPtr);
**         Deinit             - void I2C2_Deinit(LDD_TDeviceData *DeviceDataPtr);
**         Enable             - LDD_TError I2C2_Enable(LDD_TDeviceData *DeviceDataPtr);
**         MasterSendBlock    - LDD_TError I2C2_MasterSendBlock(LDD_TDeviceData *DeviceDataPtr, LDD_TData...
**         MasterReceiveBlock - LDD_TError I2C2_MasterReceiveBlock(LDD_TDeviceData *DeviceDataPtr, LDD_TData...
**
**     Copyright : 1997 - 2015 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file I2C2.c
** @version 01.07
** @brief
**          This component encapsulates the internal I2C communication
**          interface. The implementation of the interface is based
**          on the Philips I2C-bus specification version 2.0.
**          Interface features:
**          MASTER mode
**            - Multi master communication
**            - The combined format of communication possible
**              (see SendStop parameter in MasterSend/ReceiveBlock method)
**            - 7-bit slave addressing (10-bit addressing can be made as well)
**            - Acknowledge polling provided
**            - No wait state initiated when a slave device holds the SCL line low
**            - Holding of the SCL line low by slave device recognized as 'not available bus'
**            - Invalid start/stop condition detection provided
**          SLAVE mode
**            - 7-bit slave addressing
**            - General call address detection provided
*/         
/*!
**  @addtogroup I2C2_module I2C2 module documentation
**  @{
*/         

/* MODULE I2C2. */

#include "Events.h"
#include "I2C2.h"
#include "PORT_PDD.h"
#include "I2C_PDD.h"
/* {Default RTOS Adapter} No RTOS includes */
#include "IO_Map.h"

#ifdef __cplusplus
extern "C" {
#endif 


/* SerFlag bits */
#define MASTER_IN_PROGRES       0x01U  /* Communication is in progress (Master) */

typedef struct {
  uint8_t SerFlag;                     /* Flags for serial communication */
                                       /* Bits: 0 - Running int from TX */
  LDD_I2C_TSendStop SendStop;          /* Enable/Disable generate send stop condition after transmission */
  LDD_I2C_TSize InpLenM;               /* The counter of input bufer's content */
  uint8_t *InpPtrM;                    /* Pointer to input buffer for Master mode */
  LDD_I2C_TSize OutLenM;               /* The counter of output bufer's content */
  uint8_t *OutPtrM;                    /* Pointer to output buffer for Master mode */
  LDD_TUserData *UserData;             /* RTOS device data structure */
} I2C2_TDeviceData;

typedef I2C2_TDeviceData *I2C2_TDeviceDataPtr; /* Pointer to the device data structure. */

/* {Default RTOS Adapter} Static object used for simulation of dynamic driver memory allocation */
static I2C2_TDeviceData DeviceDataPrv__DEFAULT_RTOS_ALLOC;
/* {Default RTOS Adapter} Global variable used for passing a parameter into ISR */
static I2C2_TDeviceDataPtr INT_I2C0__DEFAULT_RTOS_ISRPARAM;

#define AVAILABLE_EVENTS_MASK (LDD_I2C_ON_MASTER_BLOCK_SENT | LDD_I2C_ON_MASTER_BLOCK_RECEIVED)

/*
** ===================================================================
**     Method      :  I2C2_Interrupt (component I2C_LDD)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes event(s) of the component.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

PE_ISR(I2C2_Interrupt)
{
  /* {Default RTOS Adapter} ISR parameter is passed through the global variable */
  I2C2_TDeviceDataPtr DeviceDataPrv = INT_I2C0__DEFAULT_RTOS_ISRPARAM;
  register uint8_t Status;             /* Temporary variable for status register */

  Status = I2C_PDD_ReadStatusReg(I2C0_BASE_PTR); /* Safe status register */
  I2C_PDD_ClearInterruptFlags(I2C0_BASE_PTR, (Status)); /* Clear interrupt flag */
  if (I2C_PDD_GetMasterMode(I2C0_BASE_PTR) == I2C_PDD_MASTER_MODE) { /* Is device in master mode? */
    if (I2C_PDD_GetTransmitMode(I2C0_BASE_PTR) == I2C_PDD_TX_DIRECTION) { /* Is device in Tx mode? */
      if ((Status & I2C_PDD_RX_ACKNOWLEDGE) != 0x00U){ /* NACK received? */
        I2C_PDD_SetMasterMode(I2C0_BASE_PTR, I2C_PDD_SLAVE_MODE); /* Switch device to slave mode (stop signal sent) */
        I2C_PDD_SetTransmitMode(I2C0_BASE_PTR, I2C_PDD_RX_DIRECTION); /* Switch to Rx mode */
        DeviceDataPrv->OutLenM = 0x00U; /* No character for sending */
        DeviceDataPrv->InpLenM = 0x00U; /* No character for reception */
        DeviceDataPrv->SerFlag &= (uint8_t)~(MASTER_IN_PROGRES); /* No character for sending or reception */
      } else {
        if (DeviceDataPrv->OutLenM != 0x00U) { /* Is any char. for transmitting? */
          DeviceDataPrv->OutLenM--;    /* Decrease number of chars for the transmit */
          I2C_PDD_WriteDataReg(I2C0_BASE_PTR, *(DeviceDataPrv->OutPtrM)++); /* Send character */
        } else {
          if (DeviceDataPrv->InpLenM != 0x00U) { /* Is any char. for reception? */
            if (DeviceDataPrv->InpLenM == 0x01U) { /* If only one char to receive */
              I2C_PDD_EnableTransmitAcknowledge(I2C0_BASE_PTR, PDD_DISABLE); /* then transmit ACK disable */
            } else {
              I2C_PDD_EnableTransmitAcknowledge(I2C0_BASE_PTR, PDD_ENABLE); /* else transmit ACK enable */
            }
            I2C_PDD_SetTransmitMode(I2C0_BASE_PTR, I2C_PDD_RX_DIRECTION); /* Switch to Rx mode */
            (void)I2C_PDD_ReadDataReg(I2C0_BASE_PTR); /* Dummy read character */
          } else {
            DeviceDataPrv->SerFlag &= (uint8_t)~(MASTER_IN_PROGRES); /* Clear flag "busy" */
            if (DeviceDataPrv->SendStop == LDD_I2C_SEND_STOP) {
              I2C_PDD_SetMasterMode(I2C0_BASE_PTR, I2C_PDD_SLAVE_MODE); /* Switch device to slave mode (stop signal sent) */
              I2C_PDD_SetTransmitMode(I2C0_BASE_PTR, I2C_PDD_RX_DIRECTION); /* Switch to Rx mode */
            }
            I2C2_OnMasterBlockSent(DeviceDataPrv->UserData); /* Invoke OnMasterBlockSent event */
          }
        }
      }
    } else {
      DeviceDataPrv->InpLenM--;        /* Decrease number of chars for the receive */
      if (DeviceDataPrv->InpLenM != 0x00U) { /* Is any char. for reception? */
        if (DeviceDataPrv->InpLenM == 0x01U) {
          I2C_PDD_EnableTransmitAcknowledge(I2C0_BASE_PTR, PDD_DISABLE); /* Transmit NACK */
        }
      } else {
        DeviceDataPrv->SerFlag &= (uint8_t)~(MASTER_IN_PROGRES); /* Clear flag "busy" */
        I2C_PDD_SetMasterMode(I2C0_BASE_PTR, I2C_PDD_SLAVE_MODE); /* If no, switch device to slave mode (stop signal sent) */
        I2C_PDD_EnableTransmitAcknowledge(I2C0_BASE_PTR, PDD_ENABLE); /* Transmit ACK */
      }
      *(DeviceDataPrv->InpPtrM)++ = I2C_PDD_ReadDataReg(I2C0_BASE_PTR); /* Receive character */
      if (DeviceDataPrv->InpLenM == 0x00U) { /* Is any char. for reception? */
        I2C2_OnMasterBlockReceived(DeviceDataPrv->UserData); /* Invoke OnMasterBlockReceived event */
      }
    }
  } else {
    if ((Status & I2C_PDD_ARBIT_LOST) != 0x00U) { /* Arbitration lost? */
      DeviceDataPrv->OutLenM = 0x00U;  /* Any character is not for sent */
      DeviceDataPrv->InpLenM = 0x00U;  /* Any character is not for reception */
      DeviceDataPrv->SendStop = LDD_I2C_SEND_STOP; /* Set variable for sending stop condition (for master mode) */
      DeviceDataPrv->SerFlag &= (uint8_t)~(MASTER_IN_PROGRES); /* Any character is not for sent or reception*/
      I2C_PDD_SetTransmitMode(I2C0_BASE_PTR, I2C_PDD_RX_DIRECTION); /* Switch to Rx mode */
    }
  }
}

/*
** ===================================================================
**     Method      :  I2C2_Init (component I2C_LDD)
*/
/*!
**     @brief
**         Initializes the device. Allocates memory for the device data
**         structure, allocates interrupt vectors and sets interrupt
**         priority, sets pin routing, sets timing, etc.
**         If the "Enable in init. code" is set to "yes" value then the
**         device is also enabled(see the description of the Enable()
**         method). In this case the Enable() method is not necessary
**         and needn't to be generated. 
**         This method can be called only once. Before the second call
**         of Init() the Deinit() must be called first.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer will be
**                           passed as an event or callback parameter.
**     @return
**                         - Pointer to the device data structure. 
*/
/* ===================================================================*/
LDD_TDeviceData* I2C2_Init(LDD_TUserData *UserDataPtr)
{
  /* Allocate HAL device structure */
  I2C2_TDeviceData *DeviceDataPrv;
  /* {Default RTOS Adapter} Driver memory allocation: Dynamic allocation is simulated by a pointer to the static object */
  DeviceDataPrv = &DeviceDataPrv__DEFAULT_RTOS_ALLOC;

  DeviceDataPrv->UserData = UserDataPtr; /* Store the RTOS device structure */

  /* Allocate interrupt vector */
  /* {Default RTOS Adapter} Set interrupt vector: IVT is static, ISR parameter is passed by the global variable */
  INT_I2C0__DEFAULT_RTOS_ISRPARAM = DeviceDataPrv;
  DeviceDataPrv->SerFlag = 0x00U;      /* Reset all flags */
  DeviceDataPrv->SendStop = LDD_I2C_SEND_STOP; /* Set variable for sending stop condition (for master mode) */
  DeviceDataPrv->InpLenM = 0x00U;      /* Set zero counter of data of reception */
  DeviceDataPrv->OutLenM = 0x00U;      /* Set zero counter of data of transmission */
  /* SIM_SCGC4: I2C0=1 */
  SIM_SCGC4 |= SIM_SCGC4_I2C0_MASK;
  /* I2C0_C1: IICEN=0,IICIE=0,MST=0,TX=0,TXAK=0,RSTA=0,WUEN=0,DMAEN=0 */
  I2C0_C1 = 0x00U;                     /* Clear control register */
  /* I2C0_S: TCF=0,IAAS=0,BUSY=0,ARBL=0,RAM=0,SRW=0,IICIF=1,RXAK=0 */
  I2C0_S = I2C_S_IICIF_MASK;           /* Clear interrupt flag */
  /* PORTB_PCR1: ISF=0,MUX=2 */
  PORTB_PCR1 = (uint32_t)((PORTB_PCR1 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_MUX(0x05)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x02)
               ));
  PORT_PDD_SetPinOpenDrain(PORTB_BASE_PTR, 0x01u, PORT_PDD_OPEN_DRAIN_ENABLE); /* Set SDA pin as open drain */
  /* PORTB_PCR0: ISF=0,MUX=2 */
  PORTB_PCR0 = (uint32_t)((PORTB_PCR0 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_MUX(0x05)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x02)
               ));
  PORT_PDD_SetPinOpenDrain(PORTB_BASE_PTR, 0x00u, PORT_PDD_OPEN_DRAIN_ENABLE); /* Set SCL pin as open drain */
  /* NVICIP11: PRI11=0x80 */
  NVICIP11 = NVIC_IP_PRI11(0x80);
  /* NVICISER0: SETENA|=0x0800 */
  NVICISER0 |= NVIC_ISER_SETENA(0x0800);
  /* I2C0_C2: GCAEN=0,ADEXT=0,HDRS=0,SBRC=0,RMEN=0,AD=0 */
  I2C0_C2 = I2C_C2_AD(0x00);
  /* I2C0_FLT: ??=0,??=0,??=0,FLT=0 */
  I2C0_FLT = I2C_FLT_FLT(0x00);        /* Set glitch filter register */
  /* I2C0_SMB: FACK=0,ALERTEN=0,SIICAEN=0,TCKSEL=0,SLTF=1,SHTF1=0,SHTF2=0,SHTF2IE=0 */
  I2C0_SMB = I2C_SMB_SLTF_MASK;
  /* I2C0_F: MULT=2,ICR=0 */
  I2C0_F = (I2C_F_MULT(0x02) | I2C_F_ICR(0x00)); /* Set prescaler bits */
  I2C_PDD_EnableDevice(I2C0_BASE_PTR, PDD_ENABLE); /* Enable device */
  I2C_PDD_EnableInterrupt(I2C0_BASE_PTR); /* Enable interrupt */
  /* Registration of the device structure */
  PE_LDD_RegisterDeviceStructure(PE_LDD_COMPONENT_I2C2_ID,DeviceDataPrv);
  return ((LDD_TDeviceData *)DeviceDataPrv); /* Return pointer to the data data structure */
}

/*
** ===================================================================
**     Method      :  I2C2_Deinit (component I2C_LDD)
*/
/*!
**     @brief
**         Deinitializes the device. Switches off the device, frees the
**         device data structure memory, interrupts vectors, etc.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
*/
/* ===================================================================*/
void I2C2_Deinit(LDD_TDeviceData *DeviceDataPtr)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */

  /* I2C0_C1: IICEN=0,IICIE=0,MST=0,TX=0,TXAK=0,RSTA=0,WUEN=0,DMAEN=0 */
  I2C0_C1 = 0x00U;                     /* Reset I2C Control register */
  /* Restoring the interrupt vector */
  /* {Default RTOS Adapter} Restore interrupt vector: IVT is static, no code is generated */
  /* Unregistration of the device structure */
  PE_LDD_UnregisterDeviceStructure(PE_LDD_COMPONENT_I2C2_ID);
  /* Deallocation of the device structure */
  /* {Default RTOS Adapter} Driver memory deallocation: Dynamic allocation is simulated, no deallocation code is generated */
  /* SIM_SCGC4: I2C0=0 */
  SIM_SCGC4 &= (uint32_t)~(uint32_t)(SIM_SCGC4_I2C0_MASK);
}

/*
** ===================================================================
**     Method      :  I2C2_Enable (component I2C_LDD)
*/
/*!
**     @brief
**         Enables I2C component. Events may be generated
**         ("DisableEvent"/"EnableEvent").
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active clock configuration
*/
/* ===================================================================*/
LDD_TError I2C2_Enable(LDD_TDeviceData *DeviceDataPtr)
{
  I2C2_TDeviceData *DeviceDataPrv = (I2C2_TDeviceData *)DeviceDataPtr;

  /* Method 'Disable' doesn't exist, therefore method 'Enable' is redundant.
   It only returns error code. */
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  I2C2_MasterSendBlock (component I2C_LDD)
*/
/*!
**     @brief
**         This method writes one (7-bit addressing) or two (10-bit
**         addressing) slave address bytes inclusive of R/W bit = 0 to
**         the I2C bus and then writes the block of characters to the
**         bus. The slave address must be specified before, by the
**         "SelectSlaveDevice" method or in component initialization
**         section, "Target slave address init" property. If the method
**         returns ERR_OK, it doesn't mean that transmission was
**         successful. The state of transmission is detectable by means
**         of events (OnMasterSendComplete or OnError). Data to be sent
**         are not copied to an internal buffer and remains in the
**         original location. Therefore the content of the buffer
**         should not be changed until the transmission is complete.
**         Event "OnMasterBlockSent"can be used to detect the end of
**         the transmission. This method is available only for the
**         MASTER or MASTER - SLAVE mode.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
**     @param
**         BufferPtr       - Pointer to the block of data
**                           to send.
**     @param
**         Size            - Size of the data block.
**     @param
**         SendStop        - Parameter for generating I2C
**                           Stop condition
**                           LDD_I2C_SEND_STOP - Stop condition is
**                           generated on end transmission.
**                           LDD_I2C_NO_SEND_STOP - Stop condition isn't
**                           generated on end transmission.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_DISABLED -  Device is disabled
**                           ERR_SPEED - This device does not work in
**                           the active clock configuration
**                           ERR_BUSY - The I2C device is now running
*/
/* ===================================================================*/
LDD_TError I2C2_MasterSendBlock(LDD_TDeviceData *DeviceDataPtr, LDD_TData *BufferPtr, LDD_I2C_TSize Size, LDD_I2C_TSendStop SendStop)
{
  I2C2_TDeviceData *DeviceDataPrv = (I2C2_TDeviceData *)DeviceDataPtr;

  if (Size == 0x00U) {                 /* Test variable Size on zero */
    return ERR_OK;                     /* If zero then OK */
  }
  if (DeviceDataPrv->SendStop == LDD_I2C_SEND_STOP) {
    if ((I2C_PDD_GetBusStatus(I2C0_BASE_PTR) == I2C_PDD_BUS_BUSY) || /* Is the bus busy? */  \
       ((DeviceDataPrv->SerFlag & MASTER_IN_PROGRES) != 0x00U) || \
       (DeviceDataPrv->OutLenM != 0x00U))  {
      return ERR_BUSY;                 /* If yes then error */
    }
  } else {
    if (((DeviceDataPrv->SerFlag & MASTER_IN_PROGRES) != 0x00U) || /* Is the bus busy? */  \
      (DeviceDataPrv->OutLenM != 0x00U))  {
      return ERR_BUSY;                 /* If yes then error */
    }
  }
  /* {Default RTOS Adapter} Critical section begin, general PE function is used */
  EnterCritical();
  DeviceDataPrv->SerFlag |= MASTER_IN_PROGRES; /* Set flag "busy" */
  DeviceDataPrv->OutPtrM = (uint8_t *)BufferPtr; /* Save pointer to data for transmitting */
  DeviceDataPrv->OutLenM = Size;       /* Set the counter of output bufer's content */
  DeviceDataPrv->SendStop = SendStop;  /* Set generating stop condition */
  I2C_PDD_SetTransmitMode(I2C0_BASE_PTR, I2C_PDD_TX_DIRECTION); /* Set TX mode */
  if (I2C_PDD_GetMasterMode(I2C0_BASE_PTR) == I2C_PDD_MASTER_MODE) { /* Is device in master mode? */
    I2C_PDD_RepeatStart(I2C0_BASE_PTR); /* If yes then repeat start cycle generated */
  } else {
    I2C_PDD_SetMasterMode(I2C0_BASE_PTR, I2C_PDD_MASTER_MODE); /* If no then start signal generated */
  }
  I2C_PDD_WriteDataReg(I2C0_BASE_PTR, 0x3AU); /* Send slave address */
  /* {Default RTOS Adapter} Critical section end, general PE function is used */
  ExitCritical();
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  I2C2_MasterReceiveBlock (component I2C_LDD)
*/
/*!
**     @brief
**         This method writes one (7-bit addressing) or two (10-bit
**         addressing) slave address bytes inclusive of R/W bit = 1 to
**         the I2C bus and then receives the block of characters from
**         the bus. The slave address must be specified before, by the
**         "SelectSlaveDevice" method or in component initialization
**         section, "Target slave address init" property. If the method
**         returns ERR_OK, it doesn't mean that reception was
**         successful. The state of reception is detectable by means of
**         events (OnMasterSendComplete  or OnError). Data to be
**         received are not copied to an internal buffer and remains in
**         the original location. Therefore the content of the buffer
**         should not be changed until the transmission is complete.
**         Event "OnMasterBlockReceived"can be used to detect the end
**         of the reception. This method is available only for the
**         MASTER or MASTER - SLAVE mode.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
**     @param
**         BufferPtr       - Pointer to a buffer where
**                           received characters will be stored.
**     @param
**         Size            - The size of the block.
**     @param
**         SendStop        - Parameter for generating I2C
**                           Stop condition
**                           LDD_I2C_SEND_STOP - Stop condition is
**                           generated on end transmission.
**                           LDD_I2C_NO_SEND_STOP - Stop condition isn't
**                           generated on end transmission.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_DISABLED -  Device is disabled
**                           ERR_SPEED - This device does not work in
**                           the active clock configuration
**                           ERR_BUSY - The master device is busy
**                           ERR_NOTAVAIL - It is not possible to
**                           receive data if general call address is set.
**                           ERR_PARAM_MODE -  Stop condition isn't
**                           possible generated on end transmission.
*/
/* ===================================================================*/
LDD_TError I2C2_MasterReceiveBlock(LDD_TDeviceData *DeviceDataPtr, LDD_TData *BufferPtr, LDD_I2C_TSize Size, LDD_I2C_TSendStop SendStop)
{
  I2C2_TDeviceData *DeviceDataPrv = (I2C2_TDeviceData *)DeviceDataPtr;

  if (Size == 0x00U) {                 /* Test variable Size on zero */
    return ERR_OK;                     /* If zero then OK */
  }
  if (SendStop == LDD_I2C_NO_SEND_STOP) { /* Test variable SendStop on supported value */
    return ERR_PARAM_MODE;             /* If not supported value then error */
  }
  if (DeviceDataPrv->SendStop == LDD_I2C_SEND_STOP) {
    if ((I2C_PDD_GetBusStatus(I2C0_BASE_PTR) == I2C_PDD_BUS_BUSY) || /* Is the bus busy? */  \
      ((DeviceDataPrv->SerFlag & MASTER_IN_PROGRES) != 0x00U) || \
      (DeviceDataPrv->InpLenM != 0x00U)) {
      return ERR_BUSY;                 /* If yes then error */
    }
  } else {
    if(((DeviceDataPrv->SerFlag & MASTER_IN_PROGRES) != 0x00U) || /* Is the bus busy? */  \
      (DeviceDataPrv->InpLenM != 0x00U)) {
      return ERR_BUSY;               /* If yes then error */
    }
  }
  /* {Default RTOS Adapter} Critical section begin, general PE function is used */
  EnterCritical();
  DeviceDataPrv->SerFlag |= MASTER_IN_PROGRES; /* Set flag "busy" */
  DeviceDataPrv->InpPtrM = (uint8_t *)BufferPtr; /* Save pointer to data for reception */
  DeviceDataPrv->InpLenM = Size;       /* Set the counter of input bufer's content */
  DeviceDataPrv->SendStop = SendStop;  /* Set generating stop condition */
  I2C_PDD_SetTransmitMode(I2C0_BASE_PTR, I2C_PDD_TX_DIRECTION); /* Set TX mode */
  if (I2C_PDD_GetMasterMode(I2C0_BASE_PTR) == I2C_PDD_MASTER_MODE) { /* Is device in master mode? */
    I2C_PDD_RepeatStart(I2C0_BASE_PTR); /* If yes then repeat start cycle generated */
  } else {
    I2C_PDD_SetMasterMode(I2C0_BASE_PTR, I2C_PDD_MASTER_MODE); /* If no then start signal generated */
  }
  I2C_PDD_WriteDataReg(I2C0_BASE_PTR, 0x3BU); /* Send slave address */
  /* {Default RTOS Adapter} Critical section end, general PE function is used */
  ExitCritical();
  return ERR_OK;                       /* OK */
}

/* END I2C2. */

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