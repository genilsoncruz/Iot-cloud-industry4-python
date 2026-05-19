import RPi.GPIO as GPIO
import time

LED = 18
BOTAO = 17

GPIO.setmode(GPIO.BCM)

GPIO.setup(LED, GPIO.OUT)
GPIO.setup(BOTAO, GPIO.IN, pull_up_down=GPIO.PUD_UP)

try:
    while True:
        if GPIO.input(BOTAO) == GPIO.LOW:
            GPIO.output(LED, GPIO.HIGH)
        else:
            GPIO.output(LED, GPIO.LOW)

        time.sleep(0.1)

except KeyboardInterrupt:
    GPIO.cleanup()
