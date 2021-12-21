#include <Servo.h>
Servo myServo;

#define LDR1 A0
#define LDR2 A1
#define SWITCH 2 //botó

int LDR1VAL;
int LDR2VAL;

boolean OBERT = false;

void setup()
{
  pinMode(LDR1, INPUT);
  pinMode(LDR2, INPUT);
  Serial.begin(9600);
  myServo.attach(9);  // Output pin for the servo
  pinMode(SWITCH, INPUT);
  myServo.write(100); // Angle to turn to close
}

void loop()
{
  if (OBERT == false)
  {
    if (digitalRead(SWITCH) == HIGH)
    {
      OBERT = true;

      for (int angle = 100; angle > 20; angle -= 1) { // single "degree" increments
        myServo.write (angle);
        delay (15); // so we'll take 10 * 180 milliseconds = 1.8 seconds for the traverse.
      }

      Serial.println("The box is open!");
      delay (100);
    }
  }
  if (OBERT == true) {
    LDR1VAL = analogRead(LDR1);
    LDR2VAL = analogRead(LDR2);
    LDR2VAL = (0.0000015784) * (LDR2VAL) * (LDR2VAL) * (LDR2VAL) + (-0.0028135) * (LDR2VAL) * (LDR2VAL) + (2.362346) * (LDR2VAL) + (51.022); //linealitzem l'LDR2 perque es comporti igual que l'1
    Serial.println(LDR1VAL);
    Serial.println(LDR2VAL);
    Serial.println(" ");

    if ((LDR1VAL - LDR2VAL) < 40)
    {
      delay(100);
      Serial.println("The box is still open!");
      // Serial.println(knockVal);
    }
    else
    {
      OBERT = false;

      for (int angle = 20; angle < 100; angle += 1) { // single "degree" increments
        myServo.write (angle);
        delay (15); // so we'll take 10 * 180 milliseconds = 1.8 seconds for the traverse.
      }

      delay(100);
      Serial.println("The box is closing");
      // Serial.println(knockVal);
    }
  }
}
