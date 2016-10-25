#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <curl/curl.h>
#define BUF_SIZE 100

int main(int argc, char *argv[])
{
    // argc is the number of command-line arguments provided to the program.
    // The first argument (argv[0]) is always the name of the program.
    if (argc < 2) {
        printf("Usage:\n");
        printf("%s /dev/ttyXXX Receive data sent over the specified serial port\n", argv[0]);
        return 1;
    }

    // Open the serial port for reading and writing.
    // Returns a file descriptor that can be used with standard Linux functions
    // read and write. See:
    //     $ man 2 read
    //     $ man 2 write
    int serial_port = open(argv[1], O_RDWR); // Blocking I/O

    // Configure the serial port
    termios tio; // termios is a struct defined in termios.h
    memset(&tio, 0, sizeof(termios)); // Zero out the tio structure
    tio.c_cflag = CS8|CLOCAL|CREAD; // Select 8 data bits
    tio.c_cc[VMIN] = 1; // Always return at least one character
    cfsetospeed(&tio, B9600); // baud rate for output
    cfsetispeed(&tio, B9600); // baud rate for input
    tcsetattr(serial_port, TCSANOW, &tio); // Apply these settings

    // Read from the serial port
    char buf [BUF_SIZE];
    char bufurl [200];
    int buf_idx = 0; // index of first empty item
    
    CURL *curl;
    CURLcode res;

    for (;;) {
        // Read one byte (blocking)
        char c;
        size_t bytes_read = read(serial_port, &c, 1);
        if (bytes_read == 0) {
            continue;
        } else if (bytes_read != 1) {
            printf("Failed to read from the serial port: \n%s\n", strerror(errno));
            return 1;
        }

        // Detect a newline
        if (c == '\n' || c == '\r') {
            if (buf_idx > 0) {
                buf[buf_idx] = 0;
                buf_idx = 0;

                /* buf now contains a complete line of text */
                printf("Received: %s\n", buf);   
                snprintf ( bufurl, 200, "http://data.sparkfun.com/input/4JqJawXy4yuwv5XmDVAL?private_key=b545ny2mzmtyMboBg685&%s", buf);
                printf("Received Mod: %s\n", bufurl);   
                curl = curl_easy_init();
                if(curl) {
                  curl_easy_setopt(curl, CURLOPT_URL, bufurl);
                  curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(bufurl));
                  res = curl_easy_perform(curl);
                  curl_easy_cleanup(curl);
                }
              
                
                
                
                
                
            }
        } else if (buf_idx < BUF_SIZE-1) { // -1 to allow room for the NULL
            // Store the result
            buf[buf_idx++] = c;
        }
    }
}
