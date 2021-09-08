
# Importing Libraries
import serial
import time
from Adafruit_IO import Client, RequestError, Feed
arduino = serial.Serial(port='COM6', baudrate=9600, timeout=.1)

ADAFRUIT_IO_KEY = "aio_DzXG75km3QOkUBokBFqffX5ScXCm"
ADAFRUIT_IO_USERNAME = "EstephanZ246"
aio = Client(ADAFRUIT_IO_USERNAME, ADAFRUIT_IO_KEY)

def write_read(x):
    arduino.write(bytes(x, 'utf-8'))
    time.sleep(0.05)
    data = arduino.readline()
    return data

while True:

    
    #digital_feed1 = aio.feeds('lab5')
    #digital_data = aio.receive(digital_feed1.key)

    #if len(str(digital_data.value)) == 1:
        #arduino.write(bytes(str(00), 'utf-8'))
        #arduino.write(bytes(str(digital_data.value), 'utf-8'))
                
   # elif len(str(digital_data.value)) == 2:
       # arduino.write(bytes(str(0), 'utf-8'))
        #arduino.write(bytes(str(digital_data.value), 'utf-8'))
                
    #elif len(str(digital_data.value)) == 3:
        #arduino.write(bytes(str(digital_data.value), 'utf-8'))
    
    
    
    
    
    try:
        
        #valor = (int(arduino.readline().decode('UTF-8'))) # printing the value
        valores = arduino.readline().decode('UTF-8') \
                                    .replace('(', '') \
                                    .replace(')','') \
                                    .replace('\r','') \
                                    .replace('\n','') \
                                    .split(',')
        
        
        valores = [int(n) for n in valores]
        print(valores)
        #print (valor)
        
        digital_feed = aio.feeds('temp1')
        aio.send_data(digital_feed.key, valores[0])
        
        digital_feed = aio.feeds('temp2')
        aio.send_data(digital_feed.key, valores[1])
        
        digital_feed = aio.feeds('luz1')
        aio.send_data(digital_feed.key, valores[2])
       
        digital_feed = aio.feeds('luz2')
        aio.send_data(digital_feed.key, valores[3])

        
            
    except Exception as e:
        #print(e)
        pass
    
    
    

