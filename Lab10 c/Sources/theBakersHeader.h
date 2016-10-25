/*
 * theBakersHeader.h
 *
 *  Created on: Sep 27, 2016
 *      Author: Corey
 */

#ifndef SOURCES_THEBAKERSHEADER_H_
#define SOURCES_THEBAKERSHEADER_H_
#include "MQX1.h"
// Structure For the Recieved Data
typedef struct {
	char msg_id;
	union {
		uint_16 light;
		struct __attribute__((packed)) {
			int X;
			int Y;
			int Z;
		} accel;
	} data;
} Message;



#endif /* SOURCES_THEBAKERSHEADER_H_ */
