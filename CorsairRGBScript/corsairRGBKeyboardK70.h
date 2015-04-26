#pragma once
#include "corsairRGBKeyboard.h"
#include "usbDevice.h"

class corsairRGBKeyboardK70 : public corsairRGBKeyboard
{
public:
	corsairRGBKeyboardK70(void)
	{
		this->device = usbDevice::getByVendorProductIdentifier(CORSAIR_RGB_VENDOR_ID, CORSAIR_K70RGB_PRODUCT_ID);
	}
	~corsairRGBKeyboardK70(void)
	{
	}
};

