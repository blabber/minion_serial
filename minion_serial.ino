#include <Servo.h> 

Servo servoUpperRight;
Servo servoUpperLeft;
Servo servoLowerRight;
Servo servoLowerLeft;

const int ledPin = 13;
boolean serialLineRead = false;
String serialLineString;

void setup() 
{
  Serial.begin(9600);
  serialLineString.reserve(16);

  pinMode(ledPin, OUTPUT);
} 

void loop() 
{ 
  if (serialLineRead) {

    digitalWrite(ledPin, LOW);

    int delim = serialLineString.indexOf(':');
    String servoId = serialLineString.substring(0, delim);
    int servoPos = serialLineString.substring(delim + 1).toInt();

    Servo actualServo;
    if (servoId.equalsIgnoreCase("ON;")) {
      Serial.println("D: Attaching servos");
      attachServos();
      serialLineString = ""; 
      serialLineRead = false;
      return;
    } 
    else if (servoId.equalsIgnoreCase("OFF;")) {
      Serial.println("D: Detaching servos");
      detachServos();
      serialLineString = ""; 
      serialLineRead = false;
      return;
    } 
    else if (servoId.equalsIgnoreCase("UR"))
      actualServo = servoUpperRight;
    else if (servoId.equalsIgnoreCase("UL"))
      actualServo = servoUpperLeft;
    else if (servoId.equalsIgnoreCase("LR"))
      actualServo = servoLowerRight;
    else if (servoId.equalsIgnoreCase("LL"))
      actualServo = servoLowerLeft;
    else {
      digitalWrite(ledPin, HIGH);

      Serial.print("E: \"");
      Serial.print(serialLineString);
      Serial.println("\"");

      serialLineString = ""; 
      serialLineRead = false;
      return;       
    }

    Serial.print("D: \"");
    Serial.print(servoId);
    Serial.print("\" -> ");
    Serial.println(servoPos);

    actualServo.write(servoPos);

    serialLineString = ""; 
    serialLineRead = false;
  }
}

void attachServos()
{
  servoUpperRight.attach(3);
  servoUpperLeft.attach(5);
  servoLowerRight.attach(6);
  servoLowerLeft.attach(9);  
}

void detachServos()
{
  servoUpperRight.detach();
  servoUpperLeft.detach();
  servoLowerRight.detach();
  servoLowerLeft.detach();  
}

void serialEvent()
{
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    serialLineString += inChar;
    if (inChar == ';')
      serialLineRead = true;
  }
}

