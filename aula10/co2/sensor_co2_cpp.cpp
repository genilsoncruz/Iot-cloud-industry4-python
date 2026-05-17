#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <cstring>

using namespace std;

int main() {

    int serial_port = open("/dev/serial0", O_RDWR);

    if (serial_port < 0) {

        cerr << "Erro abrindo serial!" << endl;
        return 1;
    }

    struct termios tty;

    memset(&tty, 0, sizeof tty);

    if (tcgetattr(serial_port, &tty) != 0) {

        cerr << "Erro no tcgetattr()" << endl;
        return 1;
    }

    cfsetospeed(&tty, B9600);
    cfsetispeed(&tty, B9600);

    tty.c_cflag |= (CLOCAL | CREAD);

    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;

    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    tty.c_iflag = 0;
    tty.c_oflag = 0;
    tty.c_lflag = 0;

    tcsetattr(serial_port, TCSANOW, &tty);

    unsigned char readCO2[] = {
        0xFE,
        0x04,
        0x00,
        0x03,
        0x00,
        0x01,
        0xD5,
        0xC5
    };

    unsigned char response[7];

    cout << "Sensor CO2 iniciado..." << endl;

    while (true) {

        tcflush(serial_port, TCIFLUSH);

        write(serial_port, readCO2, sizeof(readCO2));

        cout << "\nComando enviado..." << endl;

        sleep(1);

        int num_bytes =
            read(serial_port, &response, 7);

        if (num_bytes == 7) {

            int high = response[3];
            int low = response[4];

            int co2_ppm =
                (high << 8) | low;

            cout << "CO2: "
                 << co2_ppm
                 << " ppm"
                 << endl;

            cout << "HEX: ";

            for (int i = 0; i < 7; i++) {

                printf("%02X ", response[i]);
            }

            cout << endl;

        } else {

            cout << "Aguardando dados..."
                 << endl;

            cout << "Bytes recebidos: "
                 << num_bytes
                 << endl;
        }

        sleep(5);
    }

    close(serial_port);

    return 0;
}
