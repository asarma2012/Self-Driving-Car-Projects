import serial
import re
ser = serial.Serial('/dev/ttyUSB0', 9600)
ser.write(b'S') # Requsting to send data

while(1):
  ser.write(b'S') # Requsting to send data
  if(ser.in_waiting > 0):
      line = ser.readline().decode('utf-8')
      value = re.findall('\d+', line )
      print(str(value[0]) + " cm")
      break