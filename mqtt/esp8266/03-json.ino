/**
 For this particular example you could use following model with JSON params preconfigured: 
    https://github.com/rightech/ric-examples/blob/master/mqtt/.ric-models/03-json.json
 Note that: 
    @node `json`        - only must have (although you could rename all the nodes as you like)
    @node `server-info` - for connectivity debug
    @node `mqtt-last`   - for mqtt publish debug
*/

#include "EspMQTTClient.h" /* https://github.com/plapointe6/EspMQTTClient */
#include "ArduinoJson.h" /* https://github.com/bblanchon/ArduinoJson */

#define PUB_DELAY (5 * 1000) /* 5 seconds */

EspMQTTClient client(
  "<wifi-ssid>",
  "<wifi-password>",

  "sandbox.rightech.io",
  "<ric-mqtt-client-id>"
);

void setup() {
  Serial.begin(9600);  
}

void onConnectionEstablished() {
  Serial.println("connected");
}

long last = 0;
void publishTemperature() {
  long now = millis();
  if (client.isConnected() && (now - last > PUB_DELAY)) {
    String payload;
    StaticJsonDocument<200> doc;
    doc["temperature"] = random(20, 30);
    doc["humidity"] = random(40, 90);
    serializeJson(doc, payload);

    client.publish("base/state", payload);
    last = now;
  }
}

void loop() {
  client.loop();
  publishTemperature();
}
