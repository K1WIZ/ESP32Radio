/* 
This is a dedicated streaming radio implemented on an ESP32 using I2S audio to a 
MAX98357 I2S amp module.  I use this to pull in my local police radio and use this as
a dedicated police receiver.  You can use it with any stream and the radio will
play mp3, m4a, and AAC+ streams.  I have implemented this with WifiManager to 
eliminate the need to hard code credentials, and make setup and moving to other 
networks easier.  Please feel free to fork it and/or submit improvements for possibly 
adding a web interface that lets you update/change stream URLs.   This radio requires 
an I2S library from: https://github.com/schreibfaul1/ESP32-audioI2S or my fork:
https://github.com/K1WIZ/ESP32-audioI2S
Enjoy!
*/

#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include "Audio.h"

#define I2S_DOUT     25
#define I2S_BCLK      27
#define I2S_LRC        26
Audio audio;

void setup() {
    WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
    Serial.begin(115200);
    
    WiFiManager wm;

    bool res;
 
    res = wm.autoConnect("RadioSetup"); 

   while (!res) {
    delay(1000);
    Serial.println(".");
   }

   audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
   audio.setVolume(100);
   audio.connecttohost("http://your.internet.stream/mount");  // Enter desired URL for streaming

}

void loop() {
    // put your main code here, to run repeatedly: 
    audio.loop();  
}
