#include <GyverPortal.h>
#include <string>


void build() {
	GP.BUILD_BEGIN(700);
	GP.THEME(GP_LIGHT);

	GP.NAV_TABS_LINKS("/,/cfg,", "Home,Config");

 	if (ui.uri() == "/cfg") {

    // ===================== CFG =====================

		GP_MAKE_FORM(
			"/cfg", "SAVE",
			GP_MAKE_BLOCK_TAB(
				"WIFI",
				GP_MAKE_BOX(GP.LABEL("SSID: "); GP.TEXT("ssid", "SSID", data.ssid));
				GP_MAKE_BOX(GP.LABEL("Pass: "); GP.TEXT("pass", "Pass", data.pass));
			);
		);
	} else {

		GP.UPDATE("flows,currTemp,currTurn,targetTemp,turnSld,wifi");

		// ===================== HOME =====================

		GP_MAKE_BLOCK_TAB(
			"CONNECTION",
			GP.LABEL("WiFi mode: ");
			GP.LABEL_BLOCK(WiFi.getMode() == WIFI_AP ? "AP" : "STA"); GP.BREAK(); GP.BREAK();
		);

		GP_MAKE_BLOCK_TAB(
			"Settings",
			GP.LABEL("target temp");
			GP.SLIDER("target", data.targetTemp, 15, 60, 1); GP.BREAK();
		);

		GP_MAKE_BLOCK_TAB(
			"Manual",
			GP.LABEL("manually");
			GP.SWITCH("isManual", data.isManual); GP.BREAK();
			GP.LABEL("turn");
			GP.SLIDER("turnSld", waterFaucet.read(), 0, 180, 1, 0, GP_GREEN, !data.isManual); GP.BREAK();
		);

		GP_MAKE_BLOCK_TAB(
			"data",
			GP.LABEL("current temp: ");
			GP.LABEL_BLOCK((String) tempController.currentIntTemp, "currTemp"); GP.BREAK(); GP.BREAK();
			GP.LABEL("water flows: ");
			GP.LED("flows", isWaterFlows); GP.BREAK(); GP.BREAK();
			GP.LABEL("povorot: ");
			GP.LABEL_BLOCK((String) waterFaucet.read(), "currTurn"); GP.BREAK(); GP.BREAK();
			GP.LABEL("target temp: ");
			GP.LABEL_BLOCK((String) mixer.targetTemp, "targetTemp"); GP.BREAK(); GP.BREAK();
			GP.LABEL("wifi: ");
			GP.LABEL_BLOCK((String) wifiSignal, "wifi"); GP.BREAK(); GP.BREAK();
		);
	}

	GP.BUILD_END();
}
