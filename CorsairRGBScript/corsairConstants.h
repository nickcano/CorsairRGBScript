#pragma once
#include <stdint.h>


struct corsairLightColor
{
	unsigned char r, g, b;

	static uint8_t normalize(uint8_t color)
	{
		static const float multiplier = 7.0f / 255.0f;
		auto result = (unsigned char)(multiplier * (float)color);

		if (result > 7) result = 7;
		return 7 - result;
	}
};

const unsigned int CORSAIR_MAX_KEYS = 144;
const unsigned int CORSAIR_RGB_VENDOR_ID = 0x1B1C;
const unsigned int CORSAIR_K70RGB_PRODUCT_ID = 0x1B13;
const unsigned int CORSAIR_K95RGB_PRODUCT_ID = 0x1B11;