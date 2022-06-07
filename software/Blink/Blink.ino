#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define RGB1    A0 // On Trinket or Gemma, suggest changing this to 1
#define RGB2    A1 // On Trinket or Gemma, suggest changing this to 1
#define RGB3    A2 // On Trinket or Gemma, suggest changing this to 1

const int analogInPin = A6;  // Analog input pin that the potentiometer is attached to
int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS1 1 // Popular NeoPixel ring size
#define NUMPIXELS2 1 // Popular NeoPixel ring size
#define NUMPIXELS3 1 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels1(NUMPIXELS1, RGB1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2(NUMPIXELS2, RGB2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels3(NUMPIXELS3, RGB3, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 100 // Time (in milliseconds) to pause between pixels
/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/
#define LedPin1 PD3
#define LedPin2 PD4
#define LedPin3 PD5
#define LedPin4 PD6
#define LedPin5 PD7
#define LedPin6 8
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.
pixels1.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
pixels2.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
pixels3.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
pixels1.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)  
pixels2.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255) 
pixels3.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255) 

  pinMode(LedPin1, OUTPUT);
  pinMode(LedPin2, OUTPUT);
  pinMode(LedPin3, OUTPUT);
  pinMode(LedPin4, OUTPUT);
  pinMode(LedPin5, OUTPUT);
  pinMode(LedPin6, OUTPUT);
  
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  sensorValue = analogRead(analogInPin);
  outputValue = map(sensorValue, 0, 725, 0, 100);
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t BatValue = ");
  Serial.println(outputValue);

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(2);
    
  pixels1.clear(); // Set all pixel colors to 'off'
  pixels2.clear(); // Set all pixel colors to 'off'
  pixels3.clear(); // Set all pixel colors to 'off'
  for(int i=0; i<NUMPIXELS1; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels1.setPixelColor(i, pixels1.Color(0, 50, 0));

    pixels1.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
  }
  for(int i=0; i<NUMPIXELS2; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels2.setPixelColor(i, pixels2.Color(50, 0, 0));

    pixels2.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
  }
  for(int i=0; i<NUMPIXELS3; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels3.setPixelColor(i, pixels3.Color(0, 0, 50));

    pixels3.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
  }
  digitalWrite(LedPin1, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LedPin2, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LedPin3, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LedPin4, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LedPin5, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LedPin6, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(LedPin1, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LedPin2, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LedPin3, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LedPin4, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LedPin5, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LedPin6, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(100);  
  digitalWrite(LedPin1, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LedPin2, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LedPin3, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LedPin4, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LedPin5, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LedPin6, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(100); 
  digitalWrite(LedPin1, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LedPin2, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LedPin3, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LedPin4, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LedPin5, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LedPin6, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(100); 
  digitalWrite(LedPin1, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LedPin2, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LedPin3, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LedPin4, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LedPin5, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LedPin6, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(100); 
  digitalWrite(LedPin1, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LedPin2, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LedPin3, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LedPin4, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LedPin5, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LedPin6, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100); 
  for(int i=0; i<NUMPIXELS1; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels1.setPixelColor(i, pixels1.Color(0, 0, 0));

    pixels1.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
  }
  for(int i=0; i<NUMPIXELS2; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels2.setPixelColor(i, pixels2.Color(0, 0, 0));

    pixels2.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
  }
  for(int i=0; i<NUMPIXELS3; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels3.setPixelColor(i, pixels3.Color(0, 0, 0));

    pixels3.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
  }
}
