/* ###################################################################
**     Filename    : mqx_tasks.c
**     Project     : Lab8CC3501
**     Processor   : MK20DX128VLH5
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-09-28, 14:31, # CodeGen: 1
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Contents    :
**         Task1_task - void Task1_task(uint32_t task_init_data);
**         Task2_task - void Task2_task(uint32_t task_init_data);
**         Task3_task - void Task3_task(uint32_t task_init_data);
**
** ###################################################################*/
/*!
** @file mqx_tasks.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup mqx_tasks_module mqx_tasks module documentation
**  @{
*/         
/* MODULE mqx_tasks */

#include "Cpu.h"
#include "Events.h"
#include "mqx_tasks.h"

#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */
#include "theBakersHeader.h" // The Cheekiest Include Known to Man
#include "main.h"
// Extern [Global] Variables
extern MessageQueue msg_queue;

extern LWSEM_STRUCT msg_queue_lock; // Message Lock
volatile char buffer[100]; // Buffer for Using Sprintf
volatile uint16 adc_result; // Result for the ADC Readings
extern char startup[2];
extern word num_bytes;
short int i2cbuffer[3] = {0,0,0}; // Buffer for the I2C Values [X, Y, Z]

/*
** ===================================================================
**     Event       :  Task1_task (module mqx_tasks)
**
**     Component   :  Task1 [MQXLite_task]
**     Description :
**         MQX task routine. The routine is generated into mqx_tasks.c
**         file.
**     Parameters  :
**         NAME            - DESCRIPTION
**         task_init_data  - 
**     Returns     : Nothing
** ===================================================================
*/
void Task1_task(uint32_t task_init_data)
{
  int counter = 0;

  while(1) {
    counter++;

    /* Write your code here ... */
    Message msg;
    msg.msg_id = 'l';
	AD1_Measure(TRUE); // Measure the light intensity
	AD1_GetValue16(&adc_result); // 0-65535
	msg.data.light = adc_result; // Attach the Light Sensor Reading
	_lwmsgq_send(&msg_queue, (void*)&msg, LWMSGQ_SEND_BLOCK_ON_FULL);
  }
}

/*
** ===================================================================
**     Event       :  Task2_task (module mqx_tasks)
**
**     Component   :  Task2 [MQXLite_task]
**     Description :
**         MQX task routine. The routine is generated into mqx_tasks.c
**         file.
**     Parameters  :
**         NAME            - DESCRIPTION
**         task_init_data  - 
**     Returns     : Nothing
** ===================================================================
*/
void Task2_task(uint32_t task_init_data)
{
  int counter = 0;

  while(1) {
    counter++;

    /* Write your code here ... */
    Message msg;
    // Recieve the Accelerometer Data
    MMA8451Q_SendChar(0x01);
	MMA8451Q_RecvBlock(i2cbuffer,6,&num_bytes);
	// Attatch the Accelerometer Readings
	msg.msg_id = 'a';
	msg.data.accel.X = i2cbuffer[0];
	msg.data.accel.Y = i2cbuffer[1];
	msg.data.accel.Z = i2cbuffer[2];
	_time_delay_ticks(10);
	_lwmsgq_send(&msg_queue, (void*)&msg, LWMSGQ_SEND_BLOCK_ON_FULL);
  }
}

/*
** ===================================================================
**     Event       :  Task3_task (module mqx_tasks)
**
**     Component   :  Task3 [MQXLite_task]
**     Description :
**         MQX task routine. The routine is generated into mqx_tasks.c
**         file.
**     Parameters  :
**         NAME            - DESCRIPTION
**         task_init_data  - 
**     Returns     : Nothing
** ===================================================================
*/
void Task3_task(uint32_t task_init_data)
{
  int counter = 0;

  while(1) {
    counter++;
    /* Write your code here ... */
    Message msg;
    _lwmsgq_receive(&msg_queue, (void*)&msg, LWMSGQ_RECEIVE_BLOCK_ON_EMPTY, 0, NULL);
    // Get the Associated Data
    if (msg.msg_id =='l') {
    	sprintf(buffer, "ADC Reading: [%i]\r\n", msg.data.light);
    } else {
    	sprintf(buffer, "Accel Reading: [%i,%i,%i]\r\n", msg.data.accel.X, msg.data.accel.Y, msg.data.accel.Z);
    }
    Term1_SendStr(buffer);


    /*
    if (msid == 1) {
    	sprintf(buffer, "Accel Reading: [%i,%i,%i]\r\n", msg.reading1, msg.reading2, msg.reading3);
    } else {
    	sprintf(buffer, "ADC Reading: [%i]\r\n", msg.reading0);
    }
	Term1_SendStr(buffer);
	*/
  }
}

/* END mqx_tasks */

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
