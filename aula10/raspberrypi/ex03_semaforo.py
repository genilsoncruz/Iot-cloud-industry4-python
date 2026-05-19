import RPi.GPIO as GPIO
import time

VERDE = 18
AMARELO = 23
VERMELHO = 24

GPIO.setmode(GPIO.BCM)

GPIO.setup(VERDE, GPIO.OUT)
GPIO.setup(AMARELO, GPIO.OUT)
GPIO.setup(VERMELHO, GPIO.OUT)

try:
    while True:
        GPIO.output(VERDE, GPIO.HIGH)
        GPIO.output(AMARELO, GPIO.LOW)
        GPIO.output(VERMELHO, GPIO.LOW)
        time.sleep(5)

        GPIO.output(VERDE, GPIO.LOW)
        GPIO.output(AMARELO, GPIO.HIGH)
        time.sleep(2)

        GPIO.output(AMARELO, GPIO.LOW)
        GPIO.output(VERMELHO, GPIO.HIGH)
        time.sleep(5)

except KeyboardInterrupt:
    GPIO.cleanup()
