#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
#define BLYNK_PRINT Serial

#define BT1 D1
 
char auth[] = "iIcNPaXXLN2yGjbQhZj0QmTVrNWBxm9o";
char ssid[] = "";
char pass[] = "";

WidgetLED BT1Blynk(V10);

void setup()
{
  Serial.begin(9600);

  pinMode(BT1,OUTPUT); 

  Blynk.begin(auth, "KIB_2.4G", "nongshin");
}
BLYNK_CONNECTED() { 
  Blynk.syncVirtual(V1); 

}
void loop()
{
  Blynk.run();
}
BLYNK_WRITE(V1){ 
  Serial.println(param.asInt()); 
    if (param.asInt()){ 
        digitalWrite(BT1, LOW); 
        BT1Blynk.on();
    } else {
        digitalWrite(BT1, HIGH); 
         BT1Blynk.off();
    }
}
