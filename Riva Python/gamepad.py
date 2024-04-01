import pygame
import sys

# Initialize pygame
pygame.init()

# Set up the screen
screen_width = 400
screen_height = 200
screen = pygame.display.set_mode((screen_width, screen_height))
pygame.display.set_caption("DualShock 4 Gamepad Display")

# Colors
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)

# Button positions and sizes
button_positions = {
    "Square": (50, 50),
    "Triangle": (150, 50),
    "Circle": (250, 50),
    "Cross": (200, 100),
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

# Main game loop
while True:
    screen.fill(WHITE)
    
    # Check events
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
    
    # Get the state of the buttons from the controller
    pygame.event.pump()  # Pump the event queue to update joystick events
    for i in range(joystick.get_numbuttons()):
        button_pressed["Square"] = joystick.get_button(0)
        button_pressed["Cross"] = joystick.get_button(1)
        button_pressed["Circle"] = joystick.get_button(2)
        button_pressed["Triangle"] = joystick.get_button(3)
        button_pressed["L1"] = joystick.get_button(4)
        button_pressed["R1"] = joystick.get_button(5)

    # Get the state of the axes from the controller
    for i in range(joystick.get_numaxes()):
        axis_value = joystick.get_axis(i)
        # Example: You can print out the axis values for debugging
        print(f"Axis {i}: {axis_value}")

    # Print button states for debugging
    print(button_pressed)
    
    # Draw buttons
    for button, pos in button_positions.items():
        pygame.draw.circle(screen, BLACK if button_pressed[button] else WHITE, pos, 20)
    
    # Update the display
    pygame.display.update()
