/* ###################################################################
 **     Filename    : main.c
 **     Project     : Lab9
 **     Processor   : MK20DX128VLH5
 **     Version     : Driver 01.01
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2015-09-22, 14:56, # CodeGen: 0
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
#include "ASerialLdd1.h"
#include "I2C2.h"
#include "AD1.h"
#include "AdcLdd1.h"
#include "RedLEDPWM.h"
#include "PwmLdd1.h"
#include "TU1.h"
#include "GreenLEDPWM.h"
#include "PwmLdd2.h"
#include "BlueLEDPWM.h"
#include "PwmLdd3.h"
#include "Term1.h"
#include "Inhr1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include <stdlib.h>
#include "customStruct.h"

// ----- ACCELEROMETER REGISTER ADDRESSES ----- //
// External accelerometer control register addresses
#define MMA8451_CTRL_REG_1 0x2A
// Accelerometer control register bit masks
#define MMA8451_ACTIVE_BIT_MASK 0x01
#define MMA8451_F_READ_BIT_MASK 0x02
// External accelerometer data register addresses
#define MMA8451_OUT_X_MSB 0x01
#define MMA8451_OUT_X_LSB 0x02
#define MMA8451_OUT_Y_MSB 0x03
#define MMA8451_OUT_Y_LSB 0x04
#define MMA8451_OUT_Z_MSB 0x05
#define MMA8451_OUT_Z_LSB 0x06

// ----- GLOBAL VARIABLES ----- //
volatile char buffer[100]; // Buffer for the characters received
volatile int bufferIndex = 0; // The buffer index
volatile int messageTypeRecieved; // Determines if a character is received or the enter key is pressed
volatile char recieveCharResult; // Initialize a variable to hold the character received
volatile int freezeInput = 1; // Variable to determine if the input is disabled
volatile static int8_t xyz[3]; // Variable to store the [x,y,z] reading of the accelerometer
// [XYZ] Offsets
volatile int XOffset = 0;
volatile int YOffset = 0;
volatile int ZOffset= 0;




static MMA8451_TDataState deviceData; // Defining a new MMA8451_TDataState to manage the I2C data

// ----- CUSTOM FUNCTIONS ----- //
void SendString(char *str, _Bool enterLine) { // Sends a string to the serial
	unsigned int i, len;
	Term1_SendStr(str); // Send the string to the terminal
	if (enterLine == 1) {  // Send a carriage return if required
		Term1_SendStr("\r\n");
	}
}

char RecieveChar() { // Waits for and receives user input
	byte c; // Initialize a variable to hold the input
	Term1_ReadChar(&c); // Receives the character
	return c; // Returns the inputed character
}

void WaitUntilKeyIsPressed() { // Wait until some key is pressed
	for (;;) {
		if (messageTypeRecieved == 1) { // If a key has been pressed
			messageTypeRecieved = 0;
			freezeInput = 0; // Unfreeze the user input
			break; // Break out of the infinite for loop
		}
	}
}

uint8_t ReadReg(uint8_t addr, uint8_t *data, short dataSize) {
	// Reads the values of the MMA8451 External accelerometer data register addresses
	uint8_t res;
	// Send the I2C [Slave address] plus [Register address] to the I2C bus with no stop condition
	res = I2C2_MasterSendBlock(deviceData.handle, &addr, 1U,
			LDD_I2C_NO_SEND_STOP);
	if (res != ERR_OK) { // If the data was not sent correctly return ERR_FAILED
		return ERR_FAILED;
	}
	while (!deviceData.dataTransmittedFlg) {
		// Wait until the data is sent
	}
	deviceData.dataTransmittedFlg = FALSE; // 'Reset' dataTransmittedFlg to its default state [OFF]
	// Receive the input data [1 byte] from the I2C bus and generate a stop condition to end transmission
	res = I2C2_MasterReceiveBlock(deviceData.handle, data, dataSize,
			LDD_I2C_SEND_STOP);
	if (res != ERR_OK) { // If the data was not received correctly return ERR_FAILED
		return ERR_FAILED;
	}
	while (!deviceData.dataReceivedFlg) {
		// Wait until the data is received
	}
	deviceData.dataReceivedFlg = FALSE; // 'Reset' dataReceivedFlg to its default state [OFF]
	return ERR_OK; // Return ERR_OK [Indicating no error has occurred]
}

uint8_t WriteReg(uint8_t addr, uint8_t val) {
	// Writes the values of the MMA8451 External accelerometer data register addresses
	uint8_t buf[2], res; // Variables to store the address, value and result
	buf[0] = addr;
	buf[1] = val;
	// Send the data (3 bytes with address) on the I2C bus and generate a stop condition to end transmission
	res = I2C2_MasterSendBlock(deviceData.handle, &buf, 2U, LDD_I2C_SEND_STOP);
	if (res != ERR_OK) { // If the data was not received correctly return ERR_FAILED
		return ERR_FAILED;
	}
	while (!deviceData.dataTransmittedFlg) {
		// Wait until the data is sent
	}
	deviceData.dataTransmittedFlg = FALSE; // 'Reset' dataTransmittedFlg to its default state [OFF]
	return ERR_OK; // Return ERR_OK [Indicating no error has occurred]
}

void readXYZVal() { // Reads the current [X,Y,Z] values from the accelerometer to xyz
	uint8_t res;
	deviceData.handle = I2C2_Init(&deviceData); // Initializes the I2C connection
	res = WriteReg(MMA8451_CTRL_REG_1, MMA8451_F_READ_BIT_MASK | MMA8451_ACTIVE_BIT_MASK); // Writes thr bit mask to the accelerometers register
	if (res == ERR_OK) { // If the data was succesfully written
		res = ReadReg(MMA8451_OUT_X_MSB, (uint8_t*) &xyz, 3); // Read the data [X,Y,Z] Values from the acceleromters registers
	}
	I2C2_Deinit(deviceData.handle); // Deinitializes the I2C connection
	// Apply the [X,Y,Z] Offset from Calibration
	xyz[0] += XOffset;
	xyz[1] += YOffset;
	xyz[2] += ZOffset;
}

void drawTitleToConsole() { // Draws the 'Title' to the console
	Term1_Cls(); // Clears the terminal screen
	Term1_MoveTo(1, 1); // Moves to the top left corner
	SendString("-------- Accelerometer [XYZ] Reader--------", 1); // Print a 'title'
}

void calibrateAccelerometer() { // Calibrates the accelerometer [Homes [X,Y,Z] to zero]
	drawTitleToConsole();
	SendString("Ensure Board is on a flat surface before calibration begins", 1);
	SendString("Press [Any Key] to begin auto Calibration", 1);
	WaitUntilKeyIsPressed(); // Waits until any key is pressed
	SendString("Beginning Auto Calibration...", 1);
	SendString("Calibrating...", 1);
	readXYZVal(); // Read and print the current stationary values
	sprintf(buffer, "Stationary Values [X,Y,Z] = [%i,%i,%i]", xyz[0], xyz[1], xyz[2]);
	SendString(buffer,1);
	// Apply the calibration offset
	sprintf(buffer, "Applying Calibration Offsets of [X,Y,Z] = [%i,%i,%i]", -xyz[0], -xyz[1], -xyz[2]);
	SendString(buffer,1);
	XOffset = -xyz[0];
	YOffset = -xyz[1];
	ZOffset = -xyz[2];
	SendString("",1);
	SendString("Press [Any Key] to exit Calibration", 1);
	WaitUntilKeyIsPressed(); // Waits until any key is pressed
	drawTitleToConsole();
}

void printXYZToConsole() { // Reads the [X,Y,Z] Values and prints them to the console
	Term1_MoveTo(1, 2); // Moves to the top left corner
	readXYZVal(); // Read the current [X,Y,Z] Values
	// Print the current [X,Y,Z] Values to the console
	sprintf(buffer, "X [%i]     \r\nY [%i]     \r\nZ [%i]     ", xyz[0], xyz[1], xyz[2]);
	SendString(buffer,0);
}

void turnOffLEDs() { // Turns off all of the LEDs
	RedLEDPWM_SetRatio8(0);
	GreenLEDPWM_SetRatio8(0);
	BlueLEDPWM_SetRatio8(0);
}

void driveLEDs(float calibrationFactor) { // Drives the LEDs from the current [X,Y,Z] Values
	// NOTE: Calibration factor corrosponds to [255 / the maximum accelerometer reading] -> 100% Intensity LED
	int XPWMToSet = (float)abs(xyz[0])*calibrationFactor;
	if (XPWMToSet > 255) { // If larger than 255 set to 255
		XPWMToSet = 255;
	}
	int YPWMToSet = (float)abs(xyz[1])*calibrationFactor;
	if (YPWMToSet > 255) { // If larger than 255 set to 255
		YPWMToSet = 255;
	}
	int ZPWMToSet = (float)abs(xyz[2])*calibrationFactor;
	if (ZPWMToSet > 255) { // If larger than 255 set to 255
		ZPWMToSet = 255;
	}
	RedLEDPWM_SetRatio8(XPWMToSet);
	GreenLEDPWM_SetRatio8(YPWMToSet);
	BlueLEDPWM_SetRatio8(ZPWMToSet);
}

void cheekyMessage() {
	Term1_MoveTo(1, 6);
	SendString("Fuck Bitches; Get Money; Eat Cereal #FuckThePopo" ,0);
}
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
	turnOffLEDs(); // Turns off the LEDs
	calibrateAccelerometer(); // Calibrate the accelerometer
	cheekyMessage();
	for (;;) {
		printXYZToConsole();
		driveLEDs(3);
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
