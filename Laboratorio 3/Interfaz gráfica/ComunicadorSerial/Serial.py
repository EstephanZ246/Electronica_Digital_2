import serial
import serial.tools.list_ports as lp
import serial.tools.list_ports_osx as lpx
from thread_with_trace import thread_with_trace
from PyQt5 import QtWidgets
import sys
# import os
from Adafruit_IO import Client, RequestError, Feed

ADAFRUIT_IO_KEY = "aio_OCPh472nNkpjEjTlsEy4ZDOd0x8i"
ADAFRUIT_IO_USERNAME = "EstephanZ246"
aio = Client(ADAFRUIT_IO_USERNAME, ADAFRUIT_IO_KEY)

class Serial(object):

    def getPorts(self):
        
        # print (os.name)
        
        return list(lp.comports())

    def connect(self, port: str, p1: QtWidgets.QLabel, p2: QtWidgets.QLabel):
        try:
            self.serialCon = serial.Serial(port=port, baudrate=9600, bytesize=8, timeout=5,
                                           stopbits=serial.STOPBITS_ONE)
            self.read(p1, p2)
        except:
            pass

    def read(self, p1: QtWidgets.QLabel, p2: QtWidgets.QLabel):
        
        
        def threadF():
            while (True):
                if (self.serialCon.in_waiting > 0):
                    serialString = self.serialCon.readline()
                    message = serialString.decode('ascii')

                    try:
                        data = eval(message)
                        p1.setText(f'Pot1: {data[0]}V')
                        p2.setText(f'Pot2: {data[1]}V')
                        #digital_feed = aio.feeds('lab5')
                        #aio.send_data(digital_feed.key, data[0])
                        
                        #value = int(data[0])
                    except:
                        pass

        self.threadRead = thread_with_trace(target=threadF)
        self.threadRead.start()

    def send(self, text: str):
        if self.serialCon:
            self.serialCon.write(bytes(text, 'ascii'))

    def disconnect(self):
        if self.serialCon and self.threadRead:
            self.threadRead.kill()
            self.serialCon.close()
            sys.exit(0)
