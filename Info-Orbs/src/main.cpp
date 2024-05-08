#include <Arduino.h>
#include <user.h>
#include "screenManager.h"
#include <WiFi.h>
#include <globalTime.h>
#include "widgets/clockWidget.h"
#include "widgets/weatherWidget.h"
#include <Button.h>

TFT_eSPI tft = TFT_eSPI();
ScreenManager* sm = new ScreenManager(tft); // Initialize the screen manager and the displays

// Button states
bool lastButtonOKState = HIGH;
bool lastButtonLeftState = HIGH;
bool lastButtonRightState = HIGH;

Button buttonOK(BUTTON_OK);
Button buttonLeft(BUTTON_LEFT);
Button buttonRight(BUTTON_RIGHT);


#define COUNT_OF_WIDGETS 2
ClockWidget* clockWidget; // Initialize the clock widget
WeatherWidget* weatherWidget; // Initialize the weather widget

GlobalTime* globalTime; // Initialize the global time

String connectingString{ "" };

Widget* widgets[COUNT_OF_WIDGETS];
int8_t currentWidget = 0;

void setup() {

  buttonLeft.begin();
  buttonOK.begin();
  buttonRight.begin();

  Serial.begin(115200);
  Serial.println("Starting up...");
  Serial.println("Connecting to: " + String(WIFI_SSID));

  WiFi.begin(WIFI_SSID, WIFI_PASS);

  sm = new ScreenManager(tft);
  sm->selectAllScreens();
  sm->getDisplay().fillScreen(TFT_BLACK);
  sm->reset();

  sm->selectScreen(0);
  TFT_eSPI& display = sm->getDisplay();
  display.fillScreen(TFT_BLACK);
  display.setTextSize(2);
  display.setTextColor(TFT_WHITE);
  display.drawCentreString("Connecting" + connectingString, 120, 80, 1);

  sm->selectScreen(1);
  display.fillScreen(TFT_BLACK);
  display.setTextSize(2);
  display.setTextColor(TFT_WHITE);
  display.drawCentreString("Connecting to", 120, 80, 1);
  display.drawCentreString("WiFi..", 120, 100, 1);
  display.drawCentreString(WIFI_SSID, 120, 130, 1);

  Serial.println("Connecting to WiFi..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    connectingString += ".";
    if(connectingString.length() > 3) {
      connectingString = "";
    }
    sm->selectScreen(0);
    display.fillScreen(TFT_BLACK);
    display.drawCentreString("Connecting", 120, 80, 1);
    display.drawCentreString(connectingString, 120, 100, 1);
    delay(500);
  }

  #ifdef GC9A01_DRIVER
    Serial.println("GC9A01 Driver");
  #endif
  #ifdef ILI9341_DRIVER
    Serial.println("ILI9341 Driver");
  #endif
  #ifdef WOKWI
    Serial.println("Wokwi Build");
  #endif

  sm->selectAllScreens();
  sm->getDisplay().fillScreen(TFT_GREEN);
  sm->reset();

  Serial.println();
  Serial.println("Connected to the WiFi network");
  Serial.println(WiFi.localIP());
  
   

  globalTime = GlobalTime::getInstance();

  widgets[0] = new ClockWidget(*sm);
  widgets[1] = new WeatherWidget(*sm);

  widgets[currentWidget]->setup();



}

void loop() {
  globalTime->updateTime();

  // if(buttonRight.pressed()) {
  //   Serial.println("Right button pressed");
  //   currentWidget++;
  //   currentWidget %= COUNT_OF_WIDGETS;
  //   sm->fillAllScreens(TFT_BLACK);
  //   widgets[currentWidget]->setup();
  // }
  // This is a BIG WIP

  widgets[currentWidget]->update();
  widgets[currentWidget]->draw();
  delay(100);
}