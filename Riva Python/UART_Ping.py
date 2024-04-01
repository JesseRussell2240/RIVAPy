import serial
import random
import time

def send_data():
    random_data = ''.join(str(random.randint(0, 9)) for _ in range(10)) + '\n' # Generate a random string of 5 numbers
    port.write(random_data.encode('utf-8'))
    
    print("Sent:", random_data)

def receive_data():
    received_data = port.readline().decode('utf-8').strip()
    print("Received:", received_data)
    return received_data

if __name__ == "__main__":
    port = serial.Serial("/dev/ttyAMA0", 9600, timeout=1)  # Open serial port

    try:
        while True:
            send_data()
            time.sleep(0.1)  # Wait for a bit before attempting to read
            received = receive_data()
            if received == "":
                print("No data received.")
            time.sleep(0.1)  # Wait before sending again
    except KeyboardInterrupt:
        print("Exiting...")
    finally:
        port.close()  # Close the serial port when done
