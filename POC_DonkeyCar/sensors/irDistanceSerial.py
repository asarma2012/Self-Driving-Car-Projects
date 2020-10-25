import serial
import re
import time

class IR_Serial():
    def __init__(self, serialConn):
        self.serialConn = serialConn

    def getDistance(self):
        value = []
        while(1):
            serialConn.write(b'S') # Requsting to send data
            time.sleep(0.2)
            if(serialConn.in_waiting > 0):
                line = serialConn.readline().decode('utf-8')
                value = re.findall('\d+', line )
                break
        return {'dist': int(value[0])} # Unit: cm

# Example Application
serialConn = serial.Serial('/dev/ttyUSB0', 9600)
ser = IR_Serial(serialConn)
while (1):
    dist = ser.getDistance()
    print(dist['dist'])
    time.sleep(0.5)