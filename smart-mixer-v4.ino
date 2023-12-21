#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>
#include <EEManager.h>
#include <GyverOS.h>

#include "include.h"

/**
 * таксменеджер
 * 
 * цифра указывает возможное количество команд
*/
GyverOS<4> OS;

unsigned long lastTime = 0;

void setup() {
	Serial.begin(115200);

	pinMode(LED_BUILTIN, OUTPUT);

	startupWifi();

	// настройки крана
	waterFaucet.init(D6);

	// настройка пина датчика потока воды
	pinMode(D5, INPUT);

	mixer.init(makeWarmer, makeColder, data.targetTemp);

	// // настройки операционки
	OS.attach(0, fastTicksTask, 20);
	OS.attach(1, caclFaucetDataTask, 1000);
	OS.attach(2, calcWaterFlowTask, 20);
	OS.attach(3, sendDataTick, 300);

	// Инициализируем ESP-NOW
	initESPNow();
}

void loop() {
	OS.tick(); // вызывать как можно чаще, задачи выполняются здесь
}




