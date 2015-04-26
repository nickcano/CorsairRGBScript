#pragma once

#include <memory>
#include <stdint.h>


struct libusb_context;

class usbDevice
{
public:
	static std::shared_ptr<usbDevice> getByVendorProductIdentifier(uint16_t vendor, uint16_t id);
	static void cleanup();

	~usbDevice(void);

	bool controlTransfer(uint8_t requestType, uint8_t request, uint16_t value, uint16_t index, unsigned char *data, uint16_t length, unsigned int timeout = 50);

private:
	static libusb_context *ctxt;
	struct libusb_device_handle *deviceHandle;


	usbDevice(libusb_device_handle* deviceHandle);

};

