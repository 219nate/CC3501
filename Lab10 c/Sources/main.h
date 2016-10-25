/*
 * main.h
 *
 *  Created on: 4 Oct 2016
 *      Author: jc299170
 */

#ifndef SOURCES_MAIN_H_
#define SOURCES_MAIN_H_

// Message Queue
#define QUEUE_LENGTH 1
typedef struct {
	LWMSGQ_STRUCT header;
	Message msgs [QUEUE_LENGTH];
} MessageQueue;



#endif /* SOURCES_MAIN_H_ */
