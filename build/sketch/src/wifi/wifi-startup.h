#line 1 "c:\\Users\\79052\\Desktop\\arduino\\smart-mixer-v4\\src\\wifi\\wifi-startup.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "../ui/actions.h"
#include "../ui/webFace.h"

#define AP_SSID "mixer"
#define CONNECT_TIMEOUT 10000

uint32_t blinkTmr = millis();
bool isBlink = false;

void blink() {
	if (isBlink) {
		if(millis() - blinkTmr >= 100) {
			digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
			blinkTmr = millis();
		}
	} else {
		digitalWrite(LED_BUILTIN, 1);
	}
}

void startupWifi() {
	EEPROM.begin(eemem.blockSize());
	eemem.begin(0, 'b');

	WiFi.mode(WIFI_AP_STA);

	isBlink = true;

	Serial.println(String("Connecting ") + data.ssid + ", " + data.pass);
	WiFi.begin(data.ssid, data.pass);
	uint32_t tmr = millis();
	bool fail = false;
	while (WiFi.status() != WL_CONNECTED) {
		if (millis() - tmr >= CONNECT_TIMEOUT) {
			fail = 1;
			break;
		}
		
		Serial.print(".");
		// да, delay, мы ждем подключения вифи, ничего вычислять не нужно
		delay(500);

		blink();
	}

	WiFi.softAP(AP_SSID, NULL, 1);

	if (fail) {
		
		Serial.println("Fail! AP mode");
		Serial.println(WiFi.softAPIP());
	} else {
		Serial.println(WiFi.localIP());
		isBlink = false;
	}

  	// WiFi.mode(WIFI_AP);
	// WiFi.softAP(AP_SSID);

	ui.start("Smart Mixer");
	ui.attachBuild(build);
	ui.attach(action);
	ui.enableOTA();
}