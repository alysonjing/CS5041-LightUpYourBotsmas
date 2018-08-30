#include <SoftwareSerial.h>
#include <Servo.h>
//bluetooth in/out
const int bluetoothTx = 10;
const int bluetoothRx = 11;

#define RLED 6 
#define GLED 5
#define YLED 7
#define RGBR 4
#define RGBG 3
#define RGBB 2

int count = 0;
int timer = 30;
String color;

String Command;
byte State =1;
byte Counter =0;
long LastTic;

Servo myservo;
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup() {
  bluetooth.begin(9600);
  Serial.begin(9600);
  pinMode(RGBB, OUTPUT);  // blue 2
  pinMode(RGBG, OUTPUT);  // green 3
  pinMode(RGBR, OUTPUT);  // red 4
  pinMode(RLED, OUTPUT);  //6
  pinMode(YLED, OUTPUT);  //7
  pinMode(GLED, OUTPUT);  //5
  myservo.attach(9); // attach servo signal wire to pin 9

  LastTic = millis();
  stopAll();
}
//-----------------------------------------------------------------------//
void loop() {

  if(Serial.available()){
    Command = Serial.readString();
    handleCommand();
    }
}

void handleCommand(){

  //stopAll();
  
  if(Command == "color1"){
      lightControl("red");
    }
  else if (Command == "color2"){
      lightControl("green");
    }
  else if (Command == "color3"){
      lightControl("blue");
    }
  else if (Command == "pattern1"){
      lightControl("l1");
    }  
   else if (Command == "pattern2"){
      lightControl("l2");
    }
  else if (Command == "pattern3"){
      lightControl("l3");
    }
  else if (Command == "turn1"){
      myservo.write(45);
      delay(1000);
    }
  else if (Command == "turn2"){
      myservo.write(90);
      delay(1000);
    }
  else if (Command == "turn3"){
      myservo.write(135);
      delay(1000);
    }
  else if (Command == "turn4"){
      myservo.write(180);
      delay(1000);
    }
  else if (Command == "colorS"){
      stopAll();
    }  
  else{
      Serial.println("Error!!");
    }
}

void stopAll(){
  digitalWrite(RLED, LOW);
  digitalWrite(GLED, LOW);
  digitalWrite(YLED, LOW); 
  digitalWrite(RGBR, LOW);
  digitalWrite(RGBG, LOW);
  digitalWrite(RGBB, LOW);
  }

void lightControl(String color){

    if (color == "blue") // set white led to blue
    {
      digitalWrite(2, HIGH);
      digitalWrite (3, LOW);
      digitalWrite(4, LOW);
      delay(10);
    }
    else if (color == "green") // set white led light to green
    {
      digitalWrite(2, LOW);
      digitalWrite (3, HIGH);
      digitalWrite(4, LOW);
      delay(10);
    }
    else if (color == "red") // set white led light to red
    {
      digitalWrite(2, LOW);
      digitalWrite (3, LOW);
      digitalWrite(4, HIGH);
      delay(10);
    }
    else if (color == "l3") // LED pattern #3 - turns on/ff red, green, yellow LEDs in specific order
    {
      digitalWrite(5, HIGH);
      digitalWrite(6, LOW);
      digitalWrite(7, HIGH);
          delay(200);
      digitalWrite(5, LOW);
      digitalWrite(6, HIGH);
      digitalWrite(7, HIGH);
         delay(200);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(7, LOW);
          delay(200);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      digitalWrite(7, HIGH);
          delay(200);
      digitalWrite(5, LOW);
      digitalWrite(6, HIGH);
      digitalWrite(7, LOW);
          delay(200);
      digitalWrite(5, HIGH);
      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
          delay(200);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(7, HIGH);
          delay(100);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
          delay(100);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(7, HIGH);
         delay(100);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
          delay(100);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(7, HIGH);
          delay(100);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
          delay(100);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(7, HIGH);
    }

    else if (color == "l2") // LED pattern # 2 - cyces through color spectrum with white LEDs
    {
      setColor(255,0,0);
      delay(1000);
      setColor(0,255,0);
      delay(1000);
      setColor(0,0,255);
      delay(1000);
      setColor(255,255,0);
      delay(1000);
      setColor(80,0,80);
      delay(1000);
      setColor(0,255,255);
      delay(1000);
    }

    else if (color == "l1") // patern #1 in red/green/yellow LEDs.
    {
        digitalWrite(GLED, HIGH);
        delay(timer);
        digitalWrite(RLED, HIGH);
        delay(timer);
        digitalWrite(YLED, LOW);
        delay(timer * 2);
        digitalWrite(YLED, HIGH);
        delay(timer);
        digitalWrite(RLED, HIGH);
        delay(timer);
        digitalWrite(GLED, LOW);
        delay(timer * 2);
    }
}

void setColor(int r, int g, int b){
    #ifdef COMMON_ANODE;
    r = 255 -r;
    g = 255 - g;
    b = 255 - b;

    #endif
    analogWrite(RGBR, r);
    analogWrite(RGBG, g);
    analogWrite(RGBB, b);
  }
