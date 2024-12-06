from controller import Robot
import cv2
import numpy as np

# Inisialisasi robot
robot = Robot()
time_step = int(robot.getBasicTimeStep())

# Inisialisasi kamera
camera = robot.getDevice('camera')
camera.enable(time_step)

# Inisialisasi motor
left_motor = robot.getDevice('left wheel motor')
right_motor = robot.getDevice('right wheel motor')

# Fungsi untuk menggerakkan robot
def move_robot(left_speed, right_speed):
    left_motor.setVelocity(left_speed)
    right_motor.setVelocity(right_speed)

while robot.step(time_step) != -1:
    # Ambil gambar dari kamera
    image = camera.getImage()
    width = camera.getWidth()
    height = camera.getHeight()

    # Konversi gambar ke format numpy
    img = np.frombuffer(image, np.uint8).reshape((height, width, 4))
    img = cv2.cvtColor(img, cv2.COLOR_RGBA2BGR)

    # Mengubah gambar ke HSV
    hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

    # Mendefinisikan rentang warna untuk objek yang ingin dilacak
    lower_color = np.array([0, 120, 70])  # Ganti dengan rentang warna yang sesuai
    upper_color = np.array([10, 255, 255])
    mask = cv2.inRange(hsv, lower_color, upper_color)

    # Mencari kontur
    contours, _ = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    if contours:
        # Mengambil kontur terbesar
        largest_contour = max(contours, key=cv2.contourArea)
        M = cv2.moments(largest_contour)
        if M['m00'] != 0:
            cX = int(M['m10'] / M['m00'])
            cY = int(M['m01'] / M['m00'])

            # Menggerakkan robot berdasarkan posisi objek
            if cX < width // 3:
                move_robot(-1, 1)  # Belok kiri
            elif cX > 2 * width // 3:
                move_robot(1, -1)  # Belok kanan
            else:
                move_robot(1, 1)  # Maju
        else:
            move_robot(0, 0)  # Berhenti
    else:
        move_robot(0, 0)  # Berhenti
