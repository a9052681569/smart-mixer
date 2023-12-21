
int turn = 0;

void action() {

	if (ui.update()) {
		ui.updateBool("flows", isWaterFlows);
		ui.updateInt("currTemp", tempController.currentIntTemp);
		ui.updateInt("currTurn", waterFaucet.read());
		ui.updateInt("turnSld", waterFaucet.read());
		ui.updateInt("targetTemp", mixer.targetTemp);
		ui.updateString("wifi", wifiSignal);
	}

	if (ui.form()) {
		if (ui.form("/cfg")) {
			eemem.update();
			ui.copyStr("ssid", data.ssid);
			ui.copyStr("pass", data.pass);
		}
	}

	if (ui.clickInt("target", data.targetTemp)) {
		ui.updateInt("targetTemp", mixer.targetTemp);
	}

	if (ui.clickInt("turnSld", turn)) {
		Serial.println(turn);
		waterFaucet.setTargetAngle(turn);
	}

	ui.copyBool("isManual", data.isManual);
}
