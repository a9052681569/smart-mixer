void fastTicksTask() {
	ui.tick();
	eemem.tick();

	tempController.tick();
	waterFaucet.myTick();
	mixer.tick(tempController.currentIntTemp, tempController.tempChangeSpeed, data.targetTemp);

	int8_t signal = WiFi.RSSI();

	if (signal < -80) {
		wifiSignal = "pizda";
	} else if (signal < -60) {
		wifiSignal = "takoe";
	} else if (signal < -50) {
		wifiSignal = "pokatit";
	} else {
		wifiSignal = "zaebis";
	}
	
	// Serial.print("wifi: ");
	// Serial.println(signal);	
	Serial.print("spid: ");
	Serial.println(tempController.tempChangeSpeed);
}

void caclFaucetDataTask() {
	if (isWaterFlows) {
		mixer.turnTick();
	}
}

void calcWaterFlowTask() {
	uint32_t pulse = pulseIn(D5, HIGH, 200000);

	uint8_t waterSpeed;

	if (pulse) {
		waterSpeed = uint8_t(1000000 / (15 * pulse));
	} else {
		waterSpeed = 0;
	}

	isWaterFlows = waterSpeed;
}


void makeWarmer(int turnPercent) {
	// что-то делаем только если вода течет и кран докрутился до целевого положения
	if (isWaterFlows && !data.isManual) {
		waterFaucet.decreaseTarget(turnPercent);
	}
}

void makeColder(int turnPercent) {
	// что-то делаем только если вода течет и кран докрутился до целевого положения
	if (isWaterFlows && !data.isManual) {
		waterFaucet.increaceTarget(turnPercent);
	}
}