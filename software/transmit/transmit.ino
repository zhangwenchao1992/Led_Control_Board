/*
 * Demo
 * Author: sevenxiaoyu1992
 */

/**
 * A simple example of sending data from 1 nRF24L01 transceiver to another.
 *
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include "printf.h"
#include "RF24.h"

#define BUTTON_PIN   PD7

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

boolean oldState = HIGH;
int oldpayload =9;
int mode = 0;    // Currently-active animation mode, 0-9

// instantiate an object for the nRF24L01 transceiver
RF24 radio(9, 10); // using pin 7 for the CE pin, and pin 8 for the CSN pin

// Let these addresses be used for the pair
uint8_t address[][6] = {"1Node", "2Node"};
// It is very helpful to think of an address as a path instead of as
// an identifying device destination

// to use different addresses on a pair of radios, we need a variable to
// uniquely identify which address this radio will use to transmit
bool radioNumber = 1; // 0 uses address[0] to transmit, 1 uses address[1] to transmit

// Used to control whether this node is sending or receiving
bool role = false;  // true = TX role, false = RX role

// For this example, we'll be using a payload containing
// a single float number that will be incremented
// on every successful transmission
int payload = 0;

void setup() {

  Serial.begin(115200);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  while (!Serial) {
    // some boards need to wait to ensure access to serial over USB
  }

  // initialize the transceiver on the SPI bus
  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    while (1) {} // hold in infinite loop
  }

  // print example's introductory prompt
  Serial.println(F("RF24/examples/GettingStarted"));

  // To set the radioNumber via the Serial monitor on startup
  //Serial.println(F("Which radio is this? Enter '0' or '1'. Defaults to '0'"));
  //while (!Serial.available()) {
    // wait for user input
  //}
  //char input = Serial.parseInt();
  radioNumber == 1;
  Serial.print(F("radioNumber = "));
  Serial.println((int)radioNumber);

  // role variable is hardcoded to RX behavior, inform the user of this
  Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));

  // Set the PA Level low to try preventing power supply related problems
  // because these examples are likely run with nodes in close proximity to
  // each other.
  radio.setPALevel(RF24_PA_LOW);  // RF24_PA_MAX is default.

  // save on transmission time by setting the radio to only transmit the
  // number of bytes we need to transmit a float
  radio.setPayloadSize(sizeof(payload)); // float datatype occupies 4 bytes

  // set the TX address of the RX node into the TX pipe
  radio.openWritingPipe(address[radioNumber]);     // always uses pipe 0

  // set the RX address of the TX node into a RX pipe
  radio.openReadingPipe(1, address[!radioNumber]); // using pipe 1

  // additional setup specific to the node's role
  if (role) {
    radio.stopListening();  // put radio in TX mode
  } else {
    radio.startListening(); // put radio in RX mode
  }

  // For debugging info
  // printf_begin();             // needed only once for printing details
  // radio.printDetails();       // (smaller) function that prints raw register values
  // radio.printPrettyDetails(); // (larger) function that prints human readable data

} // setup

void loop() {

  // Get current button state.
  boolean newState = digitalRead(BUTTON_PIN);

  // Check if state changed from high to low (button press).
  if((newState == LOW) && (oldState == HIGH)) {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still low after debounce.
    newState = digitalRead(BUTTON_PIN);
    if(newState == LOW) {      // Yes, still low
      if(++mode > 8) mode = 0; // Advance to next mode, wrap around after #8
      switch(mode) {           // Start the new animation...
        case 0:
          display.clearDisplay();
          display.setTextSize(1);             // Normal 1:1 pixel scale
          display.setTextColor(SSD1306_WHITE);        // Draw white text
          display.setCursor(0,0);             // Start at top-left corner
          display.println(F("colorMode:off"));
          display.display();
          payload=0;
          //colorWipe(strip.Color(  0,   0,   0), 10);    // Black/off
          break;
        case 1:
          display.clearDisplay();
          display.setTextSize(1);             // Normal 1:1 pixel scale
          display.setTextColor(SSD1306_WHITE);        // Draw white text
          display.setCursor(0,0);             // Start at top-left corner
          display.println(F("colorMode:wipe-red"));
          display.display();
          payload=1;
          //colorWipe(strip.Color(255,   0,   0), 10);    // Red
          break;
        case 2:
          display.clearDisplay();
          display.setTextSize(1);             // Normal 1:1 pixel scale
          display.setTextColor(SSD1306_WHITE);        // Draw white text
          display.setCursor(0,0);             // Start at top-left corner
          display.println(F("colorMode:wipe-Green"));
          display.display();
          payload=2;
          //colorWipe(strip.Color(  0, 255,   0), 10);    // Green
          break;
        case 3:
          display.clearDisplay();
          display.setTextSize(1);             // Normal 1:1 pixel scale
          display.setTextColor(SSD1306_WHITE);        // Draw white text
          display.setCursor(0,0);             // Start at top-left corner
          display.println(F("colorMode:wipe-blue"));
          display.display();
          payload=3;
          //colorWipe(strip.Color(  0,   0, 255), 10);    // Blue
          break;
        case 4:
          display.clearDisplay();
          display.setTextSize(1);             // Normal 1:1 pixel scale
          display.setTextColor(SSD1306_WHITE);        // Draw white text
          display.setCursor(0,0);             // Start at top-left corner
          display.println(F("colorMode:wipe-white"));
          display.display();
          payload=4;
          //theaterChase(strip.Color(127, 127, 127), 10); // White
          break;
        case 5:
          display.clearDisplay();
          display.setTextSize(1);             // Normal 1:1 pixel scale
          display.setTextColor(SSD1306_WHITE);        // Draw white text
          display.setCursor(0,0);             // Start at top-left corner
          display.println(F("colorMode:tc-red"));
          display.display();
          payload=5;
          //theaterChase(strip.Color(127,   0,   0), 10); // Red
          break;
        case 6:
          display.clearDisplay();
          display.setTextSize(1);             // Normal 1:1 pixel scale
          display.setTextColor(SSD1306_WHITE);        // Draw white text
          display.setCursor(0,0);             // Start at top-left corner
          display.println(F("colorMode:tc-blue"));
          display.display();
          payload=6;
          //theaterChase(strip.Color(  0,   0, 127), 10); // Blue
          break;
        case 7:
          display.clearDisplay();
          display.setTextSize(1);             // Normal 1:1 pixel scale
          display.setTextColor(SSD1306_WHITE);        // Draw white text
          display.setCursor(0,0);             // Start at top-left corner
          display.println(F("colorMode:rainbow"));
          display.display();
          payload=7;
          //rainbow(10);
          break;
        case 8:
          display.clearDisplay();
          display.setTextSize(1);             // Normal 1:1 pixel scale
          display.setTextColor(SSD1306_WHITE);        // Draw white text
          display.setCursor(0,0);             // Start at top-left corner
          display.println(F("colorMode:8"));
          display.display();
          payload=8;
          //theaterChaseRainbow(50);
          break;
      }
    }
  }

  // Set the last-read button state to the old state.
  oldState = newState;
  if(payload!=oldpayload){
    radio.stopListening();
    unsigned long start_timer = micros();                    // start the timer
    bool report = radio.write(&payload, sizeof(int));      // transmit & save the report
    unsigned long end_timer = micros();                      // end the timer

    if (report) {
      Serial.print(F("Transmission successful! "));          // payload was delivered
      Serial.print(F("Time to transmit = "));
      Serial.print(end_timer - start_timer);                 // print the timer result
      Serial.print(F(" us. Sent: "));
      Serial.println(payload);                               // print payload sent
      //payload += 1;                                       // increment float payload
    } else {
      Serial.println(F("Transmission failed or timed out")); // payload was not delivered
    }
    oldpayload = payload;
    // to make this example readable in the serial monitor
    delay(100);  // slow transmissions down by 1 second
    
    
    }


} // loop
