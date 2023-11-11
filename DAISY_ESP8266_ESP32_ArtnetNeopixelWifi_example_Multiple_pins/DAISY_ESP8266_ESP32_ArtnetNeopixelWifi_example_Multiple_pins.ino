/*
This example will receive multiple universes via Artnet and control a strip of ws2811 leds via 
Adafruit's NeoPixel library: https://github.com/adafruit/Adafruit_NeoPixel
Changed and Edited by mAr$hA//
Educational use only
This example may be copied under the terms of the MIT license, see the LICENSE file for details
*/

// This code can be used on any ESP8266/ESP32 based microcontroller with WIFI modules. -mAr$hA//

/* Suggestion: For ESP8266, based on the web search for good performance it can handle up to 3 pins for data output with total 1536 LEDs total.
However, I strongly suggest up to 2 pins (especially GPIO1(TX) and GOPI2(D4) instead of 3 with stable performance with up to 1024 leds. 
For ESP32, you can use as many pins as you want, for good performance I suggest 4 pins out total with up to 2048 LEDs total.
*/ 
#include <ArtnetWifi.h>
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

//Wifi settings
const char* ssid = "Lucignorant69"; //Your WIFI name
const char* password = "Whz19961005?"; //WIFI's password

// Neopixel settings
const int numLeds1 = 96; //total numbers of your LEDs for the first output
const int numLeds2 = 98; // total numbers of your LEDs for the second output
const int Lucignorant1 = numLeds1 * 3; // Total number of channels for the first pin you want to receive (1 led = 3 channels, which means RGB)
const int Licignorant2 = numLeds2 * 3; // Total number of channels for the second pin you want to receive (1 led = 3 channels, which means RGB)
const byte dataPin1 = 1;
const byte dataPin2 = 2;

Adafruit_NeoPixel leds1 = Adafruit_NeoPixel(numLeds1, dataPin1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel leds2 = Adafruit_NeoPixel(numLeds2, dataPin2, NEO_GRB + NEO_KHZ800);
// Add more instances if you have more LED strips

// Artnet settings
ArtnetWifi artnet;
const int startUniverse1 = 0; // first pin output universe (In Resolume Arena it starts as 0)
const int startUniverse2 = 2;// CHANGE FOR YOUR SETUP most software this is 1. (Depends on your set up, one universe has 512 channels total and it will handle up to 170 LEDs per universe, the rest of two channels will be not used for RGB data)

// Check if we got all universes, changed by mAr$hA// from Artnet/Neopixel WIFI Example
const int maxUniverses = (Lucignorant1 / 512 + ((Lucignorant1 % 512) ? 1 : 0)) + (Licignorant2 / 512 + ((Licignorant2 % 512) ? 1 : 0)) ;
bool universesReceived[maxUniverses];
bool sendFrame = 1;
int previousDataLength1 = 0;
int previousDataLength2 = 0;

// connect to wifi – returns true if successful or false if not
bool ConnectWifi(void)
{
  bool state = true;
  int i = 0;

  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");
  
  // Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20){
      state = false;
      break;
    }
    i++;
  }
  if (state){
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("");
    Serial.println("Connection failed.");
  }
  
  return state;
}

void initTest()
{
  for (int i = 0 ; i < numLeds1 ; i++)
    leds1.setPixelColor(i, 127, 0, 0);
  leds1.show();
  delay(500);
  for (int i = 0 ; i < numLeds1; i++)
    leds1.setPixelColor(i, 0, 127, 0);
  leds1.show();
  delay(500);
  for (int i = 0 ; i < numLeds1; i++)
    leds1.setPixelColor(i, 0, 0, 127);
  leds1.show();
  delay(500);
  for (int i = 0 ; i < numLeds1; i++)
    leds1.setPixelColor(i, 0, 0, 0);
  leds1.show();
}

void onDmxFrame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data)
{
    sendFrame = 1;
    // set brightness of the whole strips 
    if (universe == 15)
    {
        leds1.setBrightness(data[0]);
        leds1.show();
        leds2.setBrightness(data[0]);
        leds2.show();
        // Add more if you have more LED strips
    }

    // Handle universes for each strip
    if (universe >= startUniverse1 && universe < startUniverse1 + maxUniverses) {
        int stripIndex = universe - startUniverse1;
        for (int i = 0; i < length / 3; i++)
        {
            int led = i + stripIndex * (previousDataLength1 / 3);
            if (led < numLeds1)
                leds1.setPixelColor(led, data[i * 3], data[i * 3 + 1], data[i * 3 + 2]);
        }
        previousDataLength1 = length;
        leds1.show();
    }
    else if (universe >= startUniverse2 && universe < startUniverse2 + maxUniverses) {
        int stripIndex = universe - startUniverse2;
        for (int i = 0; i < length / 3; i++)
        {
            int led = i + stripIndex * (previousDataLength2 / 3);
            if (led < numLeds2)
                leds2.setPixelColor(led, data[i * 3], data[i * 3 + 1], data[i * 3 + 2]);
        }
        previousDataLength2 = length;
        leds2.show();
    }
    // Add more conditions for additional LED strips
}


void setup()
{
  Serial.begin(9600);
  ConnectWifi();
  artnet.begin();
  leds1.begin();
  leds2.begin();
  initTest();

  // this will be called for each packet received
  artnet.setArtDmxCallback(onDmxFrame);
}

void loop()
{
  // we call the read function inside the loop
  artnet.read();
}