#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include "Adafruit_Bluefruit_LE.h"
#include "Adafruit_BLE.h"
#include "Adafruit_ATParser.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "shims.h"

#include <avr/pgmspace.h>

// This file wraps a C++ class and exposes Swift useable interface

#define BLUEFRUIT_SPI_CS               8
#define BLUEFRUIT_SPI_IRQ              7
#define BLUEFRUIT_SPI_RST              4    // Optional but recommended, set to -1 if unused

Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

extern "C" {

	_Bool btstart() {
		return ble.begin(false);
	}

	_Bool btreset() {
		return ble.reset();
	}

	_Bool btecho(_Bool on) {
		return ble.echo(on);
	}

	// verbose mode and btinfo both rely on the serialdebug
	// mechanism which expects debug serial to be available
	// which has been commented out, find another way if it's needed
	// void btverbose(_Bool on) {
	// 	ble.verbose(on);
	// }

	// char * btinfo() {
	// 	return ble.info(on);
	// }

	_Bool btcheckminimumversion(const char * version) {
		return ble.isVersionAtLeast(version);
	}

	_Bool btfactoryreset() {
		return ble.factoryReset();
	}

	_Bool btisconnected() {
		return ble.isConnected();
	}

	_Bool btsetmode(uint8_t new_mode) {
		return ble.setMode(new_mode);
	}

	_Bool btsendcommandbuffer(const char * cmd) {
		return ble.sendCommandCheckOK(cmd);
	}

	_Bool btsendcommandfixedstring(const char * cmd) {
		return ble.sendCommandCheckOK(reinterpret_cast<const __FlashStringHelper *>(cmd));
	}

	_Bool btwaitforok() {
		return ble.waitForOK();
	}

	void btprintbuffer(const char * cmd, _Bool addNewline) {
		if (addNewline) {
			ble.println(cmd);
		} else {
			ble.print(cmd);
		}
	}

	void btprintfixedstring(const char * cmd, _Bool addNewline) {
		if (addNewline) {
			ble.println(reinterpret_cast<const __FlashStringHelper *>(cmd));
		} else {
			ble.print(reinterpret_cast<const __FlashStringHelper *>(cmd));
		}
	}

	uint16_t btavailable() {
		return ble.available();
	}

	uint16_t btread() {
		return ble.read();
	}
}