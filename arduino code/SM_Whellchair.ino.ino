#include<SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial bluetooth(2, 3);
char data;
Servo myservo;
int a = 150, b = 150;
int pos = 0;    // variable to store the servo position

const int trigPin = 11;
const int echoPin = 12;
 int buzzer = 8;
long duration;
int distance;

void forward() {
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  analogWrite(9, a);

  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  analogWrite(10, b);
}

void   backward() {
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  analogWrite(9, a);

  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  analogWrite(10, b);
}

void right() {
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  analogWrite(9, a);

  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  analogWrite(10, b);
}
void left() {
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  analogWrite(9, a);

  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  analogWrite(10, b);
}
void stop() {
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  analogWrite(9, 0);

  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  analogWrite(10, 0);
}


void setup() {
  bluetooth.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(10, OUTPUT);

  Serial.begin(9600);
  myservo.attach(13);  // attaches the servo on pin 9 to the servo object

}

void loop() {
  if (bluetooth.available()) {
    data = bluetooth.read();
    Serial.println(data);
  }



  digitalWrite(trigPin, LOW);
  delayMicroseconds(200);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(100);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println("  CM");



  if (distance < 10) {



    myservo.write(100);              // tell servo to go to position in variable 'pos'

    backward();

    delay(200);
   stop();
tone(buzzer,300);
}
  else if (distance >= 10) {
noTone(buzzer);
    myservo.write(0);              // tell servo to go to position in variable 'pos'


    if (data == 'F')  {
      forward();
    }
    if (data == 'B' ) {
      backward();
    }
    if (data == 'L' ) {
      left();
    }
    if (data == 'R' ) {
      right();
    }
    if (data == 'S' ) {
      stop();
    }

    myservo.write(180);              // tell servo to go to position in variable 'pos'

  }
}
