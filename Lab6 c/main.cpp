#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <inttypes.h>

//------------------------------------------------------------------------------
// Function prototypes
// The "static" keyword means that these functions are local to this .cpp file
// and not visible to other .cpp files in the project. Effectively, it signals
// that they are an implementation detail rather than an externally useful
// interface.
static bool init_serial(char *port);
// File descriptor for the serial port
static int serial_port = 0;

// Union to Hold RX Data
union {
	char buf [200]; // Buffer to hold the recieved bytes
	struct __attribute__((packed)) {
		uint8_t startIdentifier;
		uint8_t packetLength1;
		uint8_t packetLength2;
		uint8_t frameType;
		uint64_t longAddress;
		uint16_t shortaddress;
		uint8_t receiveOptions;
		char data[];
		uint8_t checkSum;
	} packet;
} rx;

/*
 7E 00 1C 90 00 13 A2 00 40 E6 59 F6 00 00 02 2D 32 34 37 2C 2D 31 37 36 2C 31 36 31 32 38 0A 4A
START 00 1C 90 00 13 A2 00 40 E6 59 F6 00 00 02 -VE 32 34 37 COMMA -VE 31 37 36 COMMA 31 36 31 32 38 CHECKSUM1 CHECKSUM2
START | LENGTHx2 | FRAME TYPE | 64BIT ADDRESSx8 | 16BIT ADDRESSx2 | RECIEVE OPTIONS | DATA1 | COMMA | DATA2 | COMMA | DATA 3 | CHECKSUMx2
int , int , int 
 */

static bool init_serial(char *port) {
	printf("-----------------------------------------------\n");
	printf("TheMajesticBakers L33T Sensor Pi Reader\n");
	printf("-----------------------------------------------\n");
	printf("Opening serial port %s\n", port);

	// Open the serial port for reading and writing.
	// Returns a file descriptor that can be used with standard Linux functions
	// read and write. See:
	//     $ man 2 read
	//     $ man 2 write
	serial_port = open(port, O_RDWR);
	if (serial_port == -1) {
		fprintf(stderr, "Failed to open serial port:\n%s\n", strerror(errno));
		return false;
	}

	// Configure the serial port
	termios tio; // termios is a struct defined in termios.h
	memset(&tio, 0, sizeof(termios)); // Zero out the tio structure
	tio.c_cflag = CS8; // Select 8 data bits
	tio.c_cc[VMIN] = 1; // Demand at least 1 char from every call to read(), i.e. block execution until a char is received
	cfsetospeed(&tio, B9600); // baud rate for output
	cfsetispeed(&tio, B9600); // baud rate for input
	tcsetattr(serial_port, TCSANOW, &tio); // Apply these settings

	// Done
	return true;
}

int main(int argc, char* argv[]) 
{
	// argc is the number of command-line arguments provided to the program.
	// The first argument (argv[0]) is always the name of the program.
	if (argc < 2) {
		printf("Usage:\n");
		printf("%s /dev/ttyXXX     Use the specified serial port.\n", argv[0]);
		return 1;
	}

	// Initialise the serial port
	if (!init_serial(argv[1])) {
		return 1;
	}

	// Write your code here.
	// Below is a demo showing how to receive a single character.
	int bytes_read;
	char c;
	int currentByte = 0;
	bool receivingPacket = true;
	uint16_t packetLength;
	for (;;) {
		while (receivingPacket == true){
			// Begin receiving a new data packet
			
			// This call will block (wait for a char) if tio.c_cc[VMIN] (in init_serial) is > 0.
			// See:   $ man 2 read
			bytes_read = read(serial_port, &c, 1);
			if (bytes_read < 0) {
				fprintf(stderr, "Failed to read from the serial port.\n");
				fprintf(stderr, "%s\n", strerror(errno)); // Get text representing the reason for the failure
				exit(1); // Quit the program
			} else if (c == 0x7E) {
				// Looks like the start of an XBee frame
				printf("\nStart of Data Packet Detected"); // Indicate the start of the data frame has been detected
				rx.buf[0] = c; // Write the startIdentifier byte to the buffer
				currentByte = 1; // Set the current Byte to be equal to 1
			} else if (currentByte <= 2) {
				if (currentByte != 0) {
					// Recieve the packet length
					rx.buf[currentByte] = c;
					currentByte++; // Increment currentByte
					if (currentByte == 2) {
						// Determine the packet length
						printf("\nPacket Length of [%u] Detected",(unsigned int)rx.packet.packetLength2); // Indicate the user of the packet length
					}
				}
			} else if (currentByte > 2){
				// Obtain the remainder of the data
				if (currentByte == 27) {
					// Obtaining the last byte of data
					rx.buf[currentByte] = c;
					receivingPacket = false;
					currentByte = 0;
				} else {
					// Obtain and store the data
					rx.buf[currentByte] = c;
					currentByte++;
				}
			}
		}
		// Print the recieved data
		printf("\nPacket Contents Successfully Extracted,"); 
		printf("\n%s\n", rx.packet.data);
		receivingPacket = true;
		currentByte = 0;
	}
	// Exit
	close(serial_port);
	return 0;
}