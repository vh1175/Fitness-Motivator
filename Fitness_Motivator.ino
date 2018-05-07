#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

// For the breakout, you can use any 2 or 3 pins
// These pins will also work for the 1.8" TFT shield
#define TFT_CS     10
#define TFT_RST    9  // you can also connect this to the Arduino reset
                       // in which case, set this #define pin to -1!
#define TFT_DC     8

// For 1.44" and 1.8" TFT with ST7735 use
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

//ACC and EMG variables
const int ACC = A1;
int sensorValue = 0;
const int EMG = A2;
int EMG_signal = 0;

//baseline variables
int sensorMin = 1000; //min value for movement
int EMG_threshold = 500; //threshold value for standing

void setup() {

//LED variables
pinMode(2, OUTPUT);
pinMode(3, OUTPUT);

//initialize serial comm at 115200 baud (BITalino default)
Serial.begin(115200);
Serial.print("Hello! Testing...Testing...");

// Use this initializer if you're using a 1.8" TFT
tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
Serial.println("Initialized");

uint16_t time = millis();
tft.fillScreen(ST7735_BLACK);
time = millis() - time;

//Serial.println(time, DEC);
delay(50);
}

void loop() {

//read the signal from the ACC
sensorValue = analogRead(ACC);

//Identify ACC value
if (sensorValue < sensorMin){
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(EMG, LOW);
  tft.fillScreen(ST7735_WHITE);
  tft.setRotation(3);
  tft.setCursor(10, 50);
  tft.setTextColor(ST7735_RED);
  tft.setTextSize(3);
  tft.print("Get up!!");
  delay(2000);

}
else {
  delay(10);
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(EMG, HIGH);
  EMG_signal = analogRead(EMG);
  tft.fillScreen(ST7735_WHITE);
  tft.setRotation(3);
  tft.setCursor(10, 50);
  tft.setTextColor(ST7735_BLACK);
  tft.setTextSize(3);
  tft.print("Come on!");
  delay(2000);

//identify EMG value
  if (EMG_signal > EMG_threshold){
    tft.fillScreen(ST7735_WHITE);
    tft.setRotation(3);
    tft.setCursor(10, 50);
    tft.setTextColor(ST7735_BLUE);
    tft.setTextSize(2.5);
    tft.print("Great job!");
    delay(2000);

  }
  else {
    tft.fillScreen(ST7735_WHITE);
    tft.setRotation(3);
    tft.setCursor(10, 50);
    tft.setTextColor(ST7735_GREEN);
    tft.setTextSize(2.5);
    tft.print("Get going!");
    delay(2000);


  }
}


//print readings via USB to serial monitor
Serial.print(sensorValue);
Serial.print(",");
Serial.println(EMG_signal);


//wait 5 milliseconds for stability
delay(5);

}


