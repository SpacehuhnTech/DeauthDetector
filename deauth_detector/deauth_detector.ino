#include <ESP8266WiFi.h>
#include "Mac.h"

extern "C" {
  #include "user_interface.h"
}

//===== SETTINGS =====//
#define channel 1 //the channel to start scanning (1-14)
#define channelHopping true //scan on all channels
#define maxChannel 11 //US = 11, EU = 13, Japan = 14
#define ledPin 2 //led pin ( 2 = built-in LED)
#define inverted true // invert HIGH/LOW for the LED
#define packetRate 3 //min. packets before it gets recognized as an attack

#define scanTime 500 //scan time per channel in ms

unsigned long count = 0;
unsigned long prevTime = 0;
int curChannel = channel;

void dumpPacket(uint8_t* buf, uint16_t len) {
  if(buf == nullptr || len <= 27)
    return;
    
  Mac from(buf[16],buf[17],buf[18],buf[19],buf[20],buf[21]);
  Mac to(buf[22],buf[23],buf[24],buf[25],buf[26],buf[27]);

  Serial.print("Chan ");
  Serial.println(curChannel);
  Serial.print("From ");
  from._println();
  Serial.print("To ");
  to._println();
  Serial.println();
}

void sniffer(uint8_t* buf, uint16_t len) {
  if(buf == nullptr || len <= 12 || (buf[12] != 0xA0 && buf[12] != 0xC0))
    return;
  
  count++;
  // dumpPacket(buf, len);
}

void setup() {
  Serial.begin(115200);

  wifi_set_opmode(STATION_MODE);
  wifi_promiscuous_enable(0);
  WiFi.disconnect();
  wifi_set_promiscuous_rx_cb(sniffer);
  wifi_set_channel(curChannel);
  wifi_promiscuous_enable(1);

  pinMode(ledPin, OUTPUT);
  
  Serial.println("starting!");
}

void loop() {
  unsigned long curTime = millis();
  unsigned long delta = curTime - prevTime;
  if (delta < scanTime)
    delay(scanTime - delta);

  digitalWrite(ledPin, (count >= packetRate) ^ inverted);  

  Serial.print(curChannel);
  Serial.print(": ");
  Serial.println(count);
  
  prevTime = curTime;
  count = 0;

  if(channelHopping){
    curChannel = curChannel % maxChannel + 1;
    wifi_set_channel(curChannel);
  }
}
