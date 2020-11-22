#ifndef _SERIAL_H
#define _SERIAL_H

int configure_serial(int device);
int open_serial(const char * device_name);
int read_message(int serial_port, char * data, int buffer_size);
int send_message(int serial_port, const char * data, int buffer_size);

#endif  // _SERIAL_H
