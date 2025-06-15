const int touchPin1 = 2; // Not used directly in this code, assumes A2 and A3 are connected to touch sensors
const int touchPin2 = 3; // Not used directly in this code, assumes A2 and A3 are connected to touch sensors
int baseline1 = 0;
int baseline2 = 0;
int threshold = 20; // Adjust this value based on your sensor's sensitivity

bool touch1_active = false;
bool touch2_active = false;

void setup() {
  Serial.begin(9600); // Changed to 9600 to match Python, though 115200 is also fine if matched
  // No need for pinMode on analog pins for analogRead, but good practice if you use them for digital later
  
  // Get baselines
  delay(1000);
  baseline1 = analogRead(A2); // First sensor on A2
  baseline2 = analogRead(A3); // Second sensor on A3
  
  Serial.print("Baseline 1: ");
  Serial.println(baseline1);
  Serial.print("Baseline 2: ");
  Serial.println(baseline2);
}

void loop() {
  // Read both sensors
  int sensorValue1 = analogRead(A2);
  int sensorValue2 = analogRead(A3);
  
  int difference1 = abs(sensorValue1 - baseline1);
  int difference2 = abs(sensorValue2 - baseline2);
  
  // DEBUG: Always show sensor readings (you might want to remove this for production to reduce serial traffic)
  // Serial.print("Sensor1: ");
  // Serial.print(sensorValue1);
  // Serial.print(" (diff: ");
  // Serial.print(difference1);
  // Serial.print(") | Sensor2: ");
  // Serial.print(sensorValue2);
  // Serial.print(" (diff: ");
  // Serial.print(difference2);
  // Serial.println(")");
  
  // Handle first touch sensor
  if (difference1 > threshold) {
    if (!touch1_active) {
      Serial.println("TOUCH1");
      touch1_active = true;
    }
  } else {
    if (touch1_active) {
      Serial.println("RELEASE1");
      touch1_active = false;
    }
  }
  
  // Handle second touch sensor
  if (difference2 > threshold) {
    if (!touch2_active) {
      Serial.println("TOUCH2");
      touch2_active = true;
    }
  } else {
    if (touch2_active) {
      Serial.println("RELEASE2");
      touch2_active = false;
    }
  }
  
  // NO DELAY HERE! This makes the loop run as fast as possible, ensuring quick response.
}