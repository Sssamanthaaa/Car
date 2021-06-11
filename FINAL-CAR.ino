#include <SoftwareSerial.h>

SoftwareSerial bluetoothSerial(3,2);

// motor one
int enA = 5;
int in1 = 6;
int in2 = 7;

// motor two
int enB = 10;
int in3 = 8;
int in4 = 9;

void setup() {
  // put your setup code here, to run once:
  pinMode(in1, OUTPUT) ;
  pinMode(in2, OUTPUT) ;
  pinMode(in3, OUTPUT) ;
  pinMode(in4, OUTPUT) ;

  //SETUP:OFF
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  
  // Start the serial connection from the Arduino to the connected Laptop/PC
  Serial.begin(9600); 
  // Start the serial connection from the Arduino to the Bluetooth module.
  bluetoothSerial.begin(9600);

}

void loop() {
  if(bluetoothSerial.available()){
    String receivedString = bluetoothSerial.readString();
    Serial.println("Received: " + receivedString);
    if (receivedString.equals("forward")) {
        // Picking "0.25" as 25% speed. The number can be anything between 0 and 1.
        moveForward(0.75f);
    } else if (receivedString.equals("brake")) {
        brake();
    }
    // TODO: Add more conditions here. For example: if receivedString equals "left", turn left.
  }
}
 
// The speed parameter should be rethought, probably.

// For now it's 0.0 to 1.0 for percent of max speed.
void moveForward(float speed) {
  Serial.println("Going forward at speed: " + String(speed, 2));
  // turn on motors going forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
 
  // if the jumper intact this won't do anything.
  int calculatedSpeed = (int) (speed * 256.0f);
  analogWrite(enA, calculatedSpeed);
  analogWrite(enB, calculatedSpeed);
 
}
 
void brake() {
  Serial.println("Braking");
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
