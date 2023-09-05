#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>

#include "Button2.h"
#include "WakeOnLan.h"

#define WIFI_SSID "test"
#define WIFI_PSK "changeme"
#define WOL_MAC_ADDRESS "01:23:45:67:89:AB"
#define BUTTON_PIN 10

WiFiUDP udp;
Button2 button(BUTTON_PIN);
WakeOnLan wol(udp);

void trigger(Button2& btn) { wol.sendMagicPacket(WOL_MAC_ADDRESS); }

void setup() {
  wol.setRepeat(3, 100);
  WiFi.begin(WIFI_SSID, WIFI_PSK);
  while (!WiFi.isConnected()) {
    delay(1000);
  }
  wol.calculateBroadcastAddress(WiFi.localIP(), WiFi.subnetMask());
  button.setClickHandler(trigger);
}

void loop() {
  // todo: ensure we are still connected to wifi
  button.loop();
}
