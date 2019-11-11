#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
 
int pos = 0;    // variable to store the servo position 
int on = 0;

const int trigPin = 11;
const int echoPin = 12;

// defines variables
long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication

  myservo.attach(13);
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance= duration*0.034/2;
  
  // Turning the light
  if(distance <= 10){
    if( on ){
      myservo.write(180);
      delay(500); 
    }
    else{
      myservo.write(-180);
      delay(500);
    }

    myservo.write(90);
    delay(500);

    Serial.print(on);
    on = !on;
    
  }

}
