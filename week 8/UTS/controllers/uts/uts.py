from controller import Robot

# Initialize the robot instance
robot = Robot()

# Set the time step of the simulation
timestep = int(robot.getBasicTimeStep())

# Retrieve the left and right motors (names adjusted to match the .wbt file)
left_motor = robot.getDevice("Motor_1")
right_motor = robot.getDevice("Motor_2")

# Set the motors to infinite position mode (for continuous rotation)
left_motor.setPosition(float("inf"))
right_motor.setPosition(float("inf"))

# Initialize motor speeds to ensure movement
left_motor.setVelocity(2.0)  # Try a higher initial speed for testing
right_motor.setVelocity(2.0)  # Try a higher initial speed for testing

# Control variables for dynamic movement adjustments
default_speed = 1.0
turning_speed = 0.10

# Main loop to run the simulation
while robot.step(timestep) != -1:
    # Example movement control
    left_speed = default_speed
    right_speed = default_speed

    # Set the motor velocities based on calculated speeds
    left_motor.setVelocity(left_speed)
    right_motor.setVelocity(right_speed)

    # If sensors or additional control logic are added, integrate them here.

# Cleanup code (if necessary) can go here
