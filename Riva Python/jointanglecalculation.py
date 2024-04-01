import ikpy
from ikpy.chain import Chain
import numpy as np

# Define URDF file path and active links mask
urdf_path = "arm_urdf.urdf"
active_links_mask = [False, True, True, True, True, True, True]

# Create the arm chain from the URDF file
arm_chain = Chain.from_urdf_file(urdf_path, active_links_mask=active_links_mask)

def calculate_joint_angles(x, y, z):
    # Define the target position as a numpy array
    target_position = np.array([x, y, z])

    # Calculate the inverse kinematics to get the joint angles
    joint_angles = arm_chain.inverse_kinematics(target_position)
    
    return joint_angles

# Example usage:
x = 0.1  # Desired x-coordinate
y = 0.2  # Desired y-coordinate
z = 0.3  # Desired z-coordinate

joint_angles = calculate_joint_angles(x, y, z)
print("Joint angles:", joint_angles)
