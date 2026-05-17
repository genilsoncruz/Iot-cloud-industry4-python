import RPi.GPIO as GPIO
import time

LED = 18

GPIO.setmode(GPIO.BCM)
GPIO.setup(LED, GPIO.OUT)

pwm = GPIO.PWM(LED, 1000)
pwm.start(0)

try:
    while True:
        for brilho in range(0, 101):
            pwm.ChangeDutyCycle(brilho)
            time.sleep(0.02)

        for brilho in range(100, -1, -1):
            pwm.ChangeDutyCycle(brilho)
            time.sleep(0.02)

except KeyboardInterrupt:
    pwm.stop()
    GPIO.cleanup()
