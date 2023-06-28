#include <Adafruit_NeoPixel.h>

const int trig = 12;
const int echo = 11;
const int leftForward = 2;
const int leftBackward = 3;
const int rightForward = 4;
const int rightBackward = 5;

const int numPixels = 4;
const int pixelPin = 6;

int duration = 0;
int distance = 0;

Adafruit_NeoPixel pixels(numPixels, pixelPin, NEO_GRB + NEO_KHZ800);

void setup() 
{
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(leftForward, OUTPUT);
  pinMode(leftBackward, OUTPUT);
  pinMode(rightForward, OUTPUT);
  pinMode(rightBackward, OUTPUT);
  
  pixels.begin();
  pixels.show(); // Initialize all pixels to off
  
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(trig, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = (duration / 2)/28.5;
  Serial.println(distance);
  
  if (distance < 20) {
    // Turn left
    digitalWrite(leftForward, LOW);
    digitalWrite(leftBackward, HIGH);
    digitalWrite(rightForward, HIGH);
    digitalWrite(rightBackward, LOW);
    
    // Set NeoPixel strip to red
    for (int i = 0; i < numPixels; i++) {
      pixels.setPixelColor(i, pixels.Color(255, 0, 0));
    }
    pixels.show();
    
    delay(100);
  } else {
    // Drive forward
    digitalWrite(leftForward, HIGH);
    digitalWrite(leftBackward, LOW);
    digitalWrite(rightForward, HIGH);
    digitalWrite(rightBackward, LOW);
    
    // Set NeoPixel strip to blue
    for (int i = 0; i < numPixels; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 255));
    }
    pixels.show();
  }
}