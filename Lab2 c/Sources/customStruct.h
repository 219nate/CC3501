/*
 * customStruct.h
 *
 *  Created on: Aug 7, 2016
 *      Author: Corey
 */

#ifndef SOURCES_CUSTOMSTRUCT_H_
#define SOURCES_CUSTOMSTRUCT_H_

// ----- CUSTOM DATA TYPES ----- //
// Custom data type to manage the I2C data
typedef struct {
  volatile bool dataReceivedFlg; // Set True by the interrupt if data is received
  volatile bool dataTransmittedFlg; // Set True by the interrupt if data has been set
  LDD_TDeviceData *handle; // Pointer to the device handle
} MMA8451_TDataState;

#endif /* SOURCES_CUSTOMSTRUCT_H_ */
