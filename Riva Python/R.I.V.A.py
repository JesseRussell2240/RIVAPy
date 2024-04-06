import pygame
import sys
import serial
import time

# Initialize pygame
pygame.init()


# Initialize joint angles as all 0s
joint_angles = [0, 0, 0, 0, 0, 0]


# Initialize motion values for forward/reverse, right/left, CCW, CW
motion_values = [0, 0, 0, 0]  # [forward/reverse, right/left, CCW, CW]

isParked = 0;

# Button positions and sizesgreat
button_positions = {
    "Cross": (50, 50),
    "Square": (150, 50),
    "Triangle": (250, 50),
    "Circle": (200, 100),
    "L1": (50, 150),
    "R1": (250, 150)
}

button_pressed = {button: False for button in button_positions}

# Initialize joystick
pygame.joystick.init()
if pygame.joystick.get_count() == 0:
    print("No joystick detected.")
    pygame.quit()
    sys.exit()
else:
    joystick = pygame.joystick.Joystick(0)
    joystick.init()

def send_data():
    #data = str(joint_angles[0]) + "," + str(joint_angles[1]) + "," + str(joint_angles[2]) + "," + str(joint_angles[3]) + '\n' # Generate a random string of 5 numbers
    data = isParked + ',' + ','.join(map(str, joint_angles)) + ',' + ','.join(map(str, motion_values)) + '\n'
    port.write(data.encode('utf-8'))
    
    print("Sent:", data)
    
def receive_data():
    try:
        received_data = port.readline().decode('utf-8').strip()
        print("Received:", received_data)
        return received_data
    except KeyboardInterrupt:
        print("Exiting...")
    finally:
        port.close()  # Close the serial port when done
        
        
# Main game loop
while True:
   
    
    port = serial.Serial("/dev/ttyAMA0", 9600, timeout=1)  # Open serial port

    
    # Check events
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
    
    # Get the state of the buttons from the controller
    pygame.event.pump()  # Pump the event queue to update joystick events
    for i in range(joystick.get_numbuttons()):
        button_pressed["Cross"] = joystick.get_button(0)
        button_pressed["Circle"] = joystick.get_button(1)
        button_pressed["Triangle"] = joystick.get_button(2)
        button_pressed["Square"] = joystick.get_button(3)
        button_pressed["L1"] = joystick.get_button(4)
        button_pressed["R1"] = joystick.get_button(5)

    axis_values = [joystick.get_axis(i) for i in range(6)]

    # Get the state of the axes from the controller
    for i in range(joystick.get_numaxes()):
        axis_value = joystick.get_axis(i)
        # Example: You can print out the axis values for debugging
        #print(f"Axis {i}: {axis_value}")

    # Print button states for debugging
    #print(button_pressed)
    pressed_buttons = [button for button, pressed in button_pressed.items() if pressed]
   # if pressed_buttons:
    #    print("Current Buttons:", ", ".join(pressed_buttons))
        
     # Normalize axis values to range from -1 to 1
    normalized_axes = [value for value in axis_values]  # No need to normalize as they're already in range [-1, 1]

   

    # Map axis values to discrete ranges [-1, 0, 1]
    axes_ranges = []
    for value in normalized_axes:
        if value < -0.5:
            axes_ranges.append(-1)
        elif value > 0.5:
            axes_ranges.append(1)
        else:
            axes_ranges.append(0)

    # Print ranges for debugging
  #  print("Axes ranges:", axes_ranges)
     # Map joystick axes to motion values
    motion_values[0] = int(axis_values[1] * 100)  # Forward/Reverse
    motion_values[1] = int(axis_values[0] * 100)  # Right/Left
    motion_values[2] = int(axis_values[0] * 100)  # Cw/CCW
        #j0
    if (button_pressed["Cross"] == 1):        
        if (axes_ranges[2] == 1):
            joint_angles[0] = joint_angles[0] - 1
        elif (axes_ranges[2] == 0):
            joint_angles[0] = joint_angles[0] - 0.5
        elif (axes_ranges[5] == 1):
            joint_angles[0] = joint_angles[0] + 1
        elif (axes_ranges[5] == 0):
            joint_angles[0] = joint_angles[0] + 0.5
            #over shoot protection
        if(joint_angles[0] > 110):
            joint_angles[0] = 110
        elif (joint_angles[0] < -110):
            joint_angles[0] = -110
            
            #j1
    elif (button_pressed["Square"] == 1):        
        if (axes_ranges[2] == 1):
            joint_angles[1] = joint_angles[1] - 1
        elif (axes_ranges[2] == 0):
            joint_angles[1] = joint_angles[1] - 0.5
        elif (axes_ranges[5] == 1):
            joint_angles[1] = joint_angles[1] + 1
        elif (axes_ranges[5] == 0):
            joint_angles[1] = joint_angles[1] + 0.5
                        #over shoot protection
        if(joint_angles[1] > 110):
            joint_angles[1] = 110
        elif (joint_angles[1] < -110):
            joint_angles[1] = -110
            
            #J2
    elif (button_pressed["Triangle"] == 1):        
        if (axes_ranges[2] == 1):
            joint_angles[2] = joint_angles[2] - 1
        elif (axes_ranges[2] == 0):
            joint_angles[2] = joint_angles[2] - 0.5
        elif (axes_ranges[5] == 1):
            joint_angles[2] = joint_angles[2] + 1
        elif (axes_ranges[5] == 0):
            joint_angles[2] = joint_angles[2] + 0.5
                        #over shoot protection
        if(joint_angles[2] > 110):
            joint_angles[2] = 110
        elif (joint_angles[2] < -110):
            joint_angles[2] = -110
            
                        
            #J3
    elif (button_pressed["Circle"] == 1):        
        if (axes_ranges[2] == 1):
            joint_angles[3] = joint_angles[3] - 1
        elif (axes_ranges[2] == 0):
            joint_angles[3] = joint_angles[3] - 0.5
        elif (axes_ranges[5] == 1):
            joint_angles[3] = joint_angles[3] + 1
        elif (axes_ranges[5] == 0): 
            joint_angles[3] = joint_angles[3] + 0.5
                         #over shoot protection   
        if(joint_angles[3] > 110):
            joint_angles[3] = 110
        elif (joint_angles[3] < -110):
            joint_angles[3] = -110
    
    
    if(button_pressed[R1] == 1){
        isParked = 1;
    } else {
        isParked = 0;
    }

    send_data()
   
    time.sleep(0.1)  # Wait for a bit before attempting to read
   
    
        
              
