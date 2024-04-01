import serial
import random
import time

def send_data():
    random_data = ''.join(str(random.randint(0, 9)) for _ in range(1))  # Generate a random string of 5 numbers
  
    
    port.write(random_data.encode('utf-8'))
   # port.write("test");
    print("Sent:", random_data)

def send_data2(character):
    
    port.write(character.encode('utf-8'))
   # port.write("test");
    print("Sent:", character)

if __name__ == "__main__":
    port = serial.Serial("/dev/serial0", 9600, timeout=1)  # Open serial port

    try:
        while True:
            send_data2('1')
            time.sleep(1)  # Wait for a bit before attempting to read
           
    except KeyboardInterrupt:
        print("Exiting...")
    finally:
        port.close()  # Close the serial port when done
