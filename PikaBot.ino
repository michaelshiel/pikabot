#include <SD.h>                      // need to include the SD library
#define SD_ChipSelectPin 10  //using digital pin 4 on arduino nano 328
#include <TMRpcm.h>           //  also need to include this library...

TMRpcm tmrpcm;   // create an object for use in this sketch

#include <ServoTimer2.h>  // the servo library

#define lid_servo_pin 3

ServoTimer2 lid_servo;

int pos = 0;    // variable to store the servo position

// digital pin 2 has a pushbutton attached to it. Give it a name:
int pushButton = 2;

void setup() {
  Serial.begin(9600);

  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(6, LOW); // off

  tmrpcm.speakerPin = 9; //11 on Mega, 9 on Uno, Nano, etc

  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
    Serial.println("bad");
    return;   // don't do anything more if not
  }

  Serial.println("good");
  tmrpcm.setVolume(5);
  tmrpcm.loop(1);
  tmrpcm.quality(1);

  // tmrpcm.loop(1,1);
  close_lid(false);

  tmrpcm.play("turtle.wav");
  delay(10000);
}

void sequence(void) {
  tmrpcm.play("battle.wav");
  open_lid();
  pika();
  close_lid(true);
}

void pika() {
  // put your main code here, to run repeatedly:
  //digitalWrite(6, HIGH);
  //analogWrite(6, 64);

  // 7 = direction
  // 6 = speed

  // up
  digitalWrite(7, LOW); // up
  digitalWrite(6, HIGH); // on

  delay(18000);

  // wait

  digitalWrite(6, LOW); // off
  delay(2000);

  // down

  digitalWrite(6, HIGH); // on
  digitalWrite(7, HIGH);  // down

  delay(18000);

  digitalWrite(6, LOW);  // off

  delay(2000);
}

void open_lid(void) {
  lid_servo.attach(lid_servo_pin);

  // closed -> open
  for (int i = 2300; i > 550; i -= 10) {
    lid_servo.write(i);
    delay(25);
  }

  lid_servo.detach();
}

void close_lid(bool wait) {
  lid_servo.attach(lid_servo_pin);

  if (wait) {
    // open -> closed
    for (int i = 550; i < 2300; i += 10) {
      lid_servo.write(i);
      delay(25);
    }
  } else {
    lid_servo.write(2300);
  }

  lid_servo.detach();
}

void loop()
{
  sequence();
  tmrpcm.play("turtle.wav");
  delay(10000);
}

