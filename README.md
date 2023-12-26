# DAISY-MC wearable LED Outfit
## 1.Arduino IDE code
The first folder "DAISY_ESP8266_ESP32_ArtnetNeopixelWifi_example_Multiple_pins" is the code based on ArtnetWifi Neoxpixel example from "ArtnetWifi" library. Mainly change is making ESP32/8266 have multiple pins output, this example code is for 2 pins. Twchnically ESP8266 supports 3 pins output total for 512 leds per each pins, ESP32 supports 4 pins output total for 512 leds per each pins. For a good performance, I suggest using 2 pins output for ESP8266 for 1024 leds total, using 4 pins output for ESP32 for 2048 leds total.

Please Use 2.4Ghz Wifi network.

Change "ssid" and "password" to your own WIFI setup.

## 2.Customized PCB files
In "PCBs" folders has Gerber(PCB making) BOM(electronic parts on PCB) PAP(electronic parts location on PCB) foles for each generation of PCBs, they can be used for straight order on JLCPCB website.(Including PCB assembly)

## 3.3D models STL files
In "Goggle_frame_stl_files" folder, has Mark 1 and Mark 2 frames fits on each PCB files, legs file is for the goggle's legs, however, you can use stretch fabric without priting legs, I have already leave two holes on the models.

Legs design credit: Rick Guan
## 4.Performing Example
https://www.youtube.com/watch?v=V3mug2kYJig&t=621s&ab_channel=MarshallWang
