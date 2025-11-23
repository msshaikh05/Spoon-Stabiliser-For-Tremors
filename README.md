# Arduino-Based-Spoon-Stabiliser-For-Tremor-Assistance

This is a mini project we made to experiment with stabilizing a spoon or platform
using an MPU6050 sensor and two servo motors as our mini project.  
The idea is simple: the MPU6050 reads the roll and pitch angles, and the servos move in
the opposite direction to keep the spoon as stable as possible.

This is *not* a medical device — it’s just a prototype that can help reduce tremors
while eating or holding small objects.

---

## ✨ Features
- MPU6050 reads roll & pitch
- Complementary filter for smoother angles
- Two-servo stabilization platform
- Adjustable angle range
- Works on Arduino UNO or Nano

---

## 🛠️ Hardware Required
- Arduino UNO / Nano  
- MPU6050 (GY-521)  
- 2x Servo motors (SG90 or MG90S)  
- Breadboard + jumper wires  
- 5V battery pack or power bank  
- Optional: spoon mount / 3D-printed platform

---

## 🔌 Wiring Diagram (Text Description)

**MPU6050 → Arduino UNO**
- VCC → 5V  
- GND → GND  
- SDA → A4  
- SCL → A5  

**Servos**
- Servo 1 signal → Pin 9  
- Servo 2 signal → Pin 10  
- Servo VCC → 5V external supply  
- Servo GND → Arduino GND (must be common)

---

## 🧠 How It Works
The MPU6050 gives raw accelerometer and gyro values.  
The code mixes both using a complementary filter:

- Gyro → smooth short-term motion  
- Accelerometer → long-term angle correction  

This gives a clean estimate of roll and pitch angles.  
Servos then move in the opposite direction to stabilize the platform.

---

## 📂 Code
All project code is inside the `code/` folder.

---

## ▶️ Getting Started
1. Install Arduino IDE  
2. Add the Servo library (built-in)  
3. Connect the MPU6050 and servos  
4. Upload the `.ino` file  
5. Power the servos using an external 5V supply  
6. Test the stabilization by tilting the board

---

## ⚠️ Note
This is just a mini project and not a medical-certified stabilizer.  
It can assist with tremors, but accuracy depends on servo speed, mounting,  
and sensor quality.

---

## 📜 License
This project is open-source under the MIT License.
Feel free to modify and improve it.
