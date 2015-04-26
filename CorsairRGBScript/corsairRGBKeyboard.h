#pragma once
#include <memory>
#include <stdint.h>

#include "corsairConstants.h"

class usbDevice;

class corsairRGBKeyboard
{
public:
	~corsairRGBKeyboard(void) {}

	bool setKey(uint8_t key, uint8_t r, uint8_t g, uint8_t b);
	bool updateKeyboard();
	bool isValid() { return (this->device != nullptr); }

protected:
	std::shared_ptr<usbDevice> device;
	corsairLightColor keyColors[CORSAIR_MAX_KEYS];

	corsairRGBKeyboard(void) {}



};

