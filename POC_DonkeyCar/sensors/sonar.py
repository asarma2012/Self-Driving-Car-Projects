import RPi.GPIO as GPIO
import time

TRIG = 18
ECHO = 24

class SR04_Sonar():
	def __init__(self):
		GPIO.setmode(GPIO.BCM)
		GPIO.setup(TRIG,GPIO.OUT)
		GPIO.setup(ECHO,GPIO.IN)
		GPIO.output(TRIG, False)

	def getDistance(self):
		GPIO.output(TRIG, True)
		time.sleep(0.00001)
		GPIO.output(TRIG, False)
		start_t = 0
		end_t = 0
		while GPIO.input(ECHO)==0:
			start_t = time.time()
		while GPIO.input(ECHO)==1:
			end_t = time.time()
		return {'dist': round((end_t - start_t) * 17150, 2)} # Unit: cm

	def __del__(self):
		GPIO.cleanup()


sonar = SR04_Sonar()
while (1):
	dist = sonar.getDistance()
	print(dist['dist'])
	time.sleep(0.22)

