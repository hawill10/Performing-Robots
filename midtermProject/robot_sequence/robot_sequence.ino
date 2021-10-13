// RF24 Setup
const int CEPIN = 9;
const int CSNPIN = 10;

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(CEPIN, CSNPIN);  // CE, CSN

// Byte of array representing the address. 
// This is the address where we will send the data. 
// This should be same on the receiving side.
const byte address[6] = "10001";

// neopixel setup
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define LED_PIN A0
#define LED_COUNT 64


// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

#define PATTERN_LENGTH 21
int neoPixelPattern[PATTERN_LENGTH];
int neoPixelPos = 0;
unsigned long prevNeoPixelTime = 0;
int neoPixelInterval = 500;

// servo setup
#include <Servo.h>
Servo myservo;
int servoPos = 10;
int servoInterval = 1;
unsigned long prevServoTime = 0;
int servoUpdateInterval = 20;

//others
const int leftMotor1 = 3;
const int leftMotor2 = 4;
const int rightMotor1 = 5;
const int rightMotor2 = 6;

String prevState = "DELAY";
String state = "SEARCHING";

unsigned long moveStart = 0;
int movingTime = 1000;

int delayStart = 0;
int delayTime = 500;
String beforeDelay;

boolean sequenceStarted = false;
int repetition = 0;

int rainbowInterval = 1000;
long rainbowHue = 0;

void setup() {
  Serial.begin(115200);

  for (int i=0; i<PATTERN_LENGTH - 5; i++) {
    neoPixelPattern[i] = 8*3 + i;
  }
  neoPixelPattern[16] = 99;
  neoPixelPattern[17] = 100;
  neoPixelPattern[18] = 99;
  neoPixelPattern[19] = 100;
  neoPixelPattern[20] = 99;
  
  myservo.attach(A1);

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(10); // Set BRIGHTNESS to about 1/5 (max = 255)

  // RF24 setup
  bool retval = radio.begin();
  // Serial.println(retval);
  radio.openReadingPipe(0, address);  // Destination address 
  radio.setPALevel(RF24_PA_MIN);      // Min or max
  radio.startListening();             // sets  module as receiver
}



void loop() {
  if (radio.available()){
    int data;

    radio.read(&data, sizeof(data));

    if (data == 0x01) {
      Serial.println("button pressed");
      if (!sequenceStarted) {
        sequenceStarted = true;
      }
    }
  }

  if (sequenceStarted) {
    // Fill along the length of the strip in various colors...
    if (state == "SEARCHING") {
      //SEARCHING
      if (millis() - prevNeoPixelTime >= neoPixelInterval){
        prevNeoPixelTime = millis();
        strip.clear();
        if (neoPixelPos < PATTERN_LENGTH - 5) {
          lightUpPosition(strip.Color(255, 0, 0), 8*3 + neoPixelPos);
        }
        else if (neoPixelPattern[neoPixelPos] == 99) {
          // turn off everything
          strip.show();
        }
        else if (neoPixelPattern[neoPixelPos] == 100) {
          lightUpSection(strip.Color(255, 0, 0), 8*3, 8*5);
        }
  
        if (neoPixelPos == PATTERN_LENGTH - 1) {
          prevState = "SEARCHING";
          state = "DELAY";
        }
        
        neoPixelPos = (neoPixelPos + 1) % PATTERN_LENGTH;
      }
    }
    else if (state == "MOVING") {
      if (prevState == "DELAY"){
        prevState = "MOVING";
        moveStart = millis();
        Serial.print("reset moveStart : ");
        Serial.println(moveStart);
      }
      //motor
      Serial.println("run motor");
      analogWrite(leftMotor1, 100);
      digitalWrite(leftMotor2, LOW);
      analogWrite(rightMotor2, 100);
      digitalWrite(rightMotor1, LOW);
  
      if (millis() - moveStart >= movingTime) {
        Serial.println("Stop moving");
        analogWrite(leftMotor1, LOW);
        digitalWrite(leftMotor2, LOW);
        analogWrite(rightMotor1, LOW);
        digitalWrite(rightMotor2, LOW);
        state = "DELAY";
      }
    }
    else if (state == "DELAY") {
      if (prevState != "DELAY") {
        beforeDelay = prevState;
        prevState = "DELAY";
        delayStart = millis();
      }

      if (millis() - delayStart >= delayTime) {
        if (beforeDelay == "SEARCHING"){
          Serial.println("Searching Done");
          state = "MOVING";
        }
        else if (beforeDelay == "MOVING") {
          Serial.println("Moving Done");
          repetition++;
          if (repetition == 3) {
            servoInterval *= 5; 
            state = "FOUND";
            Serial.println("FOUND");
          }
          else {
            state = "SEARCHING";
          }
          
        }
      }
    }
    else if (state == "FOUND") {
      if (millis() - prevNeoPixelTime >= rainbowInterval) {
        rainbow(rainbowHue);
        rainbowHue += 256;
        if (rainbowHue >= 5*65536) {
          state = "SEARCHING";
          sequenceStarted =false;
          servoInterval = 1;
          servoPos = 10;
          repetition = 0;
          rainbowHue = 0;
          strip.clear();
          strip.show();
        }
      }
      
    }
    
    if (millis() - prevServoTime >= servoUpdateInterval){
      prevServoTime = millis();
      servoPos += servoInterval;
      myservo.write(servoPos);
      if (servoPos >= 150 or servoPos <= 0) {
        servoInterval *= -1;
      }
    }
  }
  

}

void rainbow(long firstPixelHue) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    // Offset pixel hue by an amount to make one full revolution of the
    // color wheel (range of 65536) along the length of the strip
    // (strip.numPixels() steps):
    int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
    // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
    // optionally add saturation and value (brightness) (each 0 to 255).
    // Here we're using just the single-argument hue variant. The result
    // is passed through strip.gamma32() to provide 'truer' colors
    // before assigning to each pixel:
    strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
  }
  strip.show();
}


void lightUpPosition(uint32_t color, int pos) {
  strip.setPixelColor(pos, color);
  strip.show();
}

void lightUpSection(uint32_t color, int low, int high) {
    for(int i=low; i<high; i++) {
      strip.setPixelColor(i, color);
    }
    strip.show();
}