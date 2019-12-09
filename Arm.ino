#include <IRremote.h>
#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;

int RECV_PIN = 9;
IRrecv irrecv(RECV_PIN);
decode_results results;

int degree = 10 ;

void setup() {
  // put your setup code here, to run once:

  //IR remote
  Serial.begin(19200);
  Serial.println("Startup");
  irrecv.enableIRIn();
  //irrecv.blink13(true);

  servo1.attach(3);
  servo2.attach(5);
  servo3.attach(7);

  servo1.write(70);
  servo2.write(0);
  servo3.write(80);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (irrecv.decode(&results)) {
    Serial.println(results.value);

    // results.value = key_value;
    if (results.value == 551508645) {
      servo1.write(70);
      servo2.write(0);  // (ok) to pick up items
      delay(500);
    }

    if (results.value == 551506605) {
      servo1.write(135);
      servo2.write(45); // (home) to release items
      delay(500);
    }

    if (results.value == 551512725) {
      degree -= 20 ;
      servo3.write(degree); // (up) to return to original 0
      delay(250);
    }

    if (results.value == 551545365) {
      degree += 20;
      servo3.write(degree); // (down) to return to bottom 180
      delay(250);
    }

    
    irrecv.resume();
  }
}
