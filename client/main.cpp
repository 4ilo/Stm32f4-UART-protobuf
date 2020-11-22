#include <iostream>
#include <cstring>
#include <sstream>
#include <string>
#include <unistd.h>

#include "serial.h"
#include "proto/leds.pb.h"

int main()
{
    char led;
    int status;
    char buffer[265];
    int serial_port = 0;
    LedStatus_Led value;
    LedStatus led_status;

    // Open serial port
    serial_port = open_serial("/dev/ttyUSB0");
    configure_serial(serial_port);

    std::cout << "[R,G,B,O][0,1]" << std::endl;

    while(true) {
        std::cout << "Cmd: ";
        std::cin >> led;

        if (led == 'q') {
            break;
        }

        std::cin >> status;

        switch (status) {
            case 0:
                value = LedStatus_Led_OFF;
                break;
            case 1:
                value = LedStatus_Led_ON;
                break;
            default:
                break;
        }

        switch (led) {
            case 'R':
                led_status.set_ledred(value);
                break;
            case 'G':
                led_status.set_ledgreen(value);
                break;
            case 'B':
                led_status.set_ledblue(value);
                break;
            case 'O':
                led_status.set_ledorange(value);
                break;
        }

        // Serialize protobuf and send over serial
        std::stringstream stream_buffer;
        stream_buffer.rdbuf()->pubsetbuf(buffer, sizeof(buffer));

        led_status.SerializeToOstream(&stream_buffer);
        stream_buffer << '\0';

        send_message(serial_port, buffer, sizeof(buffer));

        // Read response over serial
        int length = read_message(serial_port, buffer, sizeof(buffer));

        // Decode protobuf
        std::stringstream input_buffer;
        input_buffer.rdbuf()->pubsetbuf(&buffer[1], length);

        led_status.ParseFromIstream(&input_buffer);

        std::cout << "Response: " << std::endl;
        std::cout << led_status.DebugString() << std::endl;
    }

    std::cout << "Stopping" << std::endl;
    close(serial_port);
    return 0;
}
