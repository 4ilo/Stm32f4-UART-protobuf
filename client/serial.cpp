#include <iostream>
#include <cstring>
#include <cerrno>

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

static void print_errno(const char * message)
{
    std::cerr << "Error " << errno << " "<< message << ": " << std::strerror(errno) << std::endl;
}

int open_serial(const char * device_name)
{
    int serial_port = 0;
    if ((serial_port = open(device_name, O_RDWR)) < 0) {
        print_errno("From opening tty");
        exit(1);
    }

    return serial_port;
}

int configure_serial(int device)
{
    struct termios tty;

    if (tcgetattr(device, &tty) != 0) {
        print_errno("From tcgetattr");
        exit(1);
    }

    tty.c_cflag &= ~PARENB;         // Disable parity
    tty.c_cflag &= ~CSTOPB;         // Disable stop bits
    tty.c_cflag |= CS8;             // 8bits/byte
    tty.c_cflag &= ~CRTSCTS;        // Disbale flow control
    tty.c_cflag |= CREAD | CLOCAL;  // ignore ctrl lines

    tty.c_lflag &= ~ICANON;         // Disable text mode (don't wait for backspaces)
    tty.c_lflag &= ~ECHO;           // Disable echo
    tty.c_lflag &= ~ECHOE;          // Disable echo ensurance
    tty.c_lflag &= ~ECHONL;         // Disable new-line echo
    tty.c_lflag &= ~ISIG;           // Disable Signal interpretion

    tty.c_iflag &= ~(IXON | IXOFF | IXANY);    // Turn off sw flow control
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL); // Disable special handling on receive

    tty.c_oflag &= ~OPOST;          // Disable special interpretion of out bytes
    tty.c_oflag &= ~ONLCR;          // Disbale conversion of \n to \n\r

    tty.c_cc[VTIME] = 10;
    tty.c_cc[VMIN] = 0;

    cfsetispeed(&tty, B115200);
    cfsetospeed(&tty, B115200);

    if (tcsetattr(device, TCSANOW, &tty) != 0) {
        print_errno("from tcsetattr");
        exit(1);
    }

    return 0;
}

int send_message(int serial_port, const char * data, int buffer_size)
{
    int len = strnlen(data, buffer_size);

    write(serial_port, &len, 1);    // Send length first
    write(serial_port, data, len);  // Send data

    return 0;
}

int read_message(int serial_port, char * data, int buffer_size)
{
    int len = 0;

    len = read(serial_port, data, buffer_size);
    data[len] = '\0';

    return len;
}

