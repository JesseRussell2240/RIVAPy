import serial
import time

# Initialize serial port
port = serial.Serial("/dev/ttyAMA0", 9600, timeout=1)

# Initialize joint angles as all 0s
joint_angles = [0, 0, 0, 0, 0, 0]

# Define button mappings
button_mappings = {
    'forward': 1,
    'backward': -1,
    'right': 1,
    'left': -1,
    'joint1_inc': 1,
    'joint1_dec': -1,
    'joint2_inc': 1,
    'joint2_dec': -1,
    'joint3_inc': 1,
    'joint3_dec': -1,
    'joint4_inc': 1,
    'joint4_dec': -1,
    'joint5_inc': 1,
    'joint5_dec': -1,
    'joint6_inc': 1,
    'joint6_dec': -1
}

# Function to send data
def send_data(command, direction, angles):
    data = f"{command},{direction},{','.join(map(str, angles))}\n"
    port.write(data.encode('utf-8'))

# Function to update joint angles
def update_joint_angle(joint_index, increment):
    joint_angles[joint_index] += increment
    # Keep joint angles within -90 to 90 range
    joint_angles[joint_index] = max(-90, min(90, joint_angles[joint_index]))

# Function to read keypad input
def get_keypad_input():
    # Placeholder function for simplicity
    # Replace with actual keypad input reading logic
  #  return 'joint1_inc', button_mappings['joint1_inc']

#def get_keypad_input():
    # Placeholder function to simulate keypad input
    # Replace with actual keypad input reading logic
    
    # Simulate random button presses
    button_press = random.randint(0, 5)
    
    # Assign buttons arbitrarily for demonstration
    if button_press == 0:
        return 'forward', button_mappings['forward']
    elif button_press == 1:
        return 'backward', button_mappings['backward']
    elif button_press == 2:
        return 'right', button_mappings['right']
    elif button_press == 3:
        return 'left', button_mappings['left']
    elif button_press == 4:
        return 'joint1_inc', button_mappings['joint1_inc']
    elif button_press == 5:
        return 'joint1_dec', button_mappings['joint1_dec']

# Function to configure button mappings
def configure_button_mapping(button, action):
    if button in button_mappings:
        button_mappings[button] = action
        print(f"Button '{button}' mapped to action '{action}'.")
    else:
        print(f"Button '{button}' not found in mappings.")

# Main loop
try:
    while True:
        # Get keypad input
        button, action = get_keypad_input()

        # Update joint angle based on the button pressed
        if button.startswith('joint'):
            joint_index = int(button[5]) - 1
            update_joint_angle(joint_index, action)

        # Handle other commands (e.g., forward, backward)
        else:
            command = button_mappings.get(button, 0)  # Get command from mappings
            direction = action

            # Send data
            send_data(command, direction, joint_angles)

        # Wait before sending again
        time.sleep(0.1)

except KeyboardInterrupt:
    print("Exiting...")
finally:
    port.close()  # Close the serial port when done
