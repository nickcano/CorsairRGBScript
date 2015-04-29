#pragma once
#include "corsairRGBKeyboard.h"
#include "usbDevice.h"

class corsairRGBKeyboardK95 : public corsairRGBKeyboard
{
public:
	corsairRGBKeyboardK95(void)
	{
		this->device = usbDevice::getByVendorProductIdentifier(CORSAIR_RGB_VENDOR_ID, CORSAIR_K95RGB_PRODUCT_ID);
	}
	~corsairRGBKeyboardK95(void)
	{
	}
};

