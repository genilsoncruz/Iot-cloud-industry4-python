import serial
import time

# ==========================
# CONFIGURAÇÃO SERIAL
# ==========================

ser = serial.Serial(
    port='/dev/serial0',
    baudrate=9600,
    timeout=1
)

# ==========================
# COMANDO MODBUS
# ==========================

read_co2 = bytes([
    0xFE,
    0x04,
    0x00,
    0x03,
    0x00,
    0x01,
    0xD5,
    0xC5
])

print("Sensor CO2 SC8/S8 inicializado...")

try:

    while True:

        ser.reset_input_buffer()

        ser.write(read_co2)

        print("\nComando enviado...")

        time.sleep(1)

        response = ser.read(7)

        if len(response) == 7:

            high = response[3]
            low = response[4]

            co2_ppm = (high << 8) | low

            print(f"CO2 Level: {co2_ppm} ppm")

            print("Resposta HEX:")
            print(response.hex())

        else:

            print("Aguardando dados do sensor...")
            print(f"Bytes recebidos: {len(response)}")

        time.sleep(5)

except KeyboardInterrupt:

    print("\nPrograma encerrado")

    ser.close()
