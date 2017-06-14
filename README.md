# DeauthDetector
Detect deauthentication frames using an ESP8266

![esp8266 deauth detector custom build](https://raw.githubusercontent.com/spacehuhn/DeauthDetector/master/images/device.jpg)

**Support me and my projects on [Patreon!](https://www.patreon.com/spacehuhn)**  
[<img width="200" alt="Support me on Patreon" src="https://raw.githubusercontent.com/spacehuhn/DeauthDetector/master/images/patreon.png">](https://www.patreon.com/spacehuhn)  


## How it works  

If the ESP8266 detects [deauthentication or disassociation frames](https://mrncciew.com/2014/10/11/802-11-mgmt-deauth-disassociation-frames/) it will turn on its LED. That's all ¯\ (ツ)/¯.  

![blinky esp8266 deauth detector](https://raw.githubusercontent.com/spacehuhn/DeauthDetector/master/images/blink.jpg)

So this is a good and cheap way to detect a [Wi-Fi deauthentication attack](https://en.wikipedia.org/wiki/Wi-Fi_deauthentication_attack).  

## How to install it  

**You will only need to follow one of the installation methods!**

### Uploading the .bin file

Upload the `deauth_detector.bin` using the [nodemcu-flasher](https://github.com/nodemcu/nodemcu-flasher) or the [esptool](https://github.com/espressif/esptool) from Espressif.

### Using Arduino

**1** Install [Arduino](https://www.arduino.cc/en/Main/Software)  
**2** Install the [ESP8266 SDK](https://github.com/esp8266/Arduino)  
**3** Download this project and open it with Arduino
**4** Maybe customize the code:
```
#define channel 1 //the channel it should scan on (1-14)
#define channelHopping true //scan on all channels
#define maxChannel 13 //US = 11, EU = 13, Japan = 14
#define ledPin 2 //led pin ( 2 = built-in LED)
#define inverted true // invert HIGH/LOW for the LED
#define packetRate 3 //min. packets before it gets recognized as an attack

#define scanTime 500 //scan time per channel in ms
```
**5** Upload the code to your ESP8266 (don't forget to set it to the right upload settings!)

**Done**
