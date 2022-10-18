#define BLYNK_TEMPLATE_ID "TMPLeqy-Y-E1"
#define BLYNK_DEVICE_NAME "Switch"
#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#define BLYNK_PRINT Serial
#define APP_DEBUG
#include "BlynkEdgent.h"

BLYNK_WRITE(V0)
{
  int val = param.asInt();
  digitalWrite(D4, !val);
  if (param.asInt()){ 
        digitalWrite(D4, LOW); 
    } else {
        digitalWrite(D4, HIGH); 
    }
}

void setup()
{
  pinMode(D4, OUTPUT);
  Serial.begin(115200);
  delay(100);

  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run();
}
