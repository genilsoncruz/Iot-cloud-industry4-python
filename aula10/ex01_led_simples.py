import RPi.GPIO as GPIO
import time

LED = 18

GPIO.setmode(GPIO.BCM)
GPIO.setup(LED, GPIO.OUT)

try:
    while True:
        GPIO.output(LED, GPIO.HIGH)
        print("LED ligado")
        time.sleep(1)

        GPIO.output(LED, GPIO.LOW)
        print("LED desligado")
        time.sleep(1)

except KeyboardInterrupt:
    GPIO.cleanup()
