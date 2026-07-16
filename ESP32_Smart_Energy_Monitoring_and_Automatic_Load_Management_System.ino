#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


const int voltagePin = 34;
const int currentPin = 35;

const int relayPin = 19;
const int buzzerPin = 23;

const int greenLED = 25;
const int yellowLED = 26;
const int redLED = 33;

void setup() {

  Serial.begin(115200);

  pinMode(relayPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  Wire.begin(21,22);

  if(!display.begin(SSD1306_SWITCHCAPVCC,0x3C)){
    Serial.println("OLED Failed");
    while(true);
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.display();
}

void loop() {

  int voltageRaw = analogRead(voltagePin);
  int currentRaw = analogRead(currentPin);

  float voltage = map(voltageRaw,0,4095,180,250);
  float current = map(currentRaw,0,4095,0,10);

  float power = voltage * current;

  String status;

  
  if(power < 700){

    status="NORMAL";

    digitalWrite(greenLED,HIGH);
    digitalWrite(yellowLED,LOW);
    digitalWrite(redLED,LOW);

    digitalWrite(relayPin,HIGH);

    noTone(buzzerPin);

  }

  
  else if(power>=700 && power<1200){

    status="HIGH";

    digitalWrite(greenLED,LOW);
    digitalWrite(yellowLED,HIGH);
    digitalWrite(redLED,LOW);

    digitalWrite(relayPin,HIGH);

    noTone(buzzerPin);

  }

  
  else{

    status="OVERLOAD";

    digitalWrite(greenLED,LOW);
    digitalWrite(yellowLED,LOW);
    digitalWrite(redLED,HIGH);

    digitalWrite(relayPin,LOW);

    tone(buzzerPin,1000);

  }

  Serial.println("----------------------------");
  Serial.print("Voltage : ");
  Serial.print(voltage);
  Serial.println(" V");

  Serial.print("Current : ");
  Serial.print(current);
  Serial.println(" A");

  Serial.print("Power : ");
  Serial.print(power);
  Serial.println(" W");

  Serial.print("Status : ");
  Serial.println(status);

  display.clearDisplay();

  display.setTextSize(1);

  display.setCursor(0,0);
  display.print("Voltage:");
  display.print(voltage);
  display.println("V");

  display.setCursor(0,15);
  display.print("Current:");
  display.print(current);
  display.println("A");

  display.setCursor(0,30);
  display.print("Power:");
  display.print(power);
  display.println("W");

  display.setCursor(0,50);
  display.print(status);

  display.display();

  delay(1000);

}