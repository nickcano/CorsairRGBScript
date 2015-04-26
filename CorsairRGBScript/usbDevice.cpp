#include "usbDevice.h"

#include "libusb\libusb.h"

#ifdef _DEBUG
#pragma comment(lib, "libusb\\libusb-1.0d.lib")
#else
#pragma comment(lib, "libusb\\libusb-1.0.lib")
#endif

libusb_context *usbDevice::ctxt = NULL;

usbDevice::usbDevice(libusb_device_handle* deviceHandle)
{
	this->deviceHandle = deviceHandle;
}

usbDevice::~usbDevice(void)
{
	libusb_release_interface(this->deviceHandle, 0);
	libusb_close(this->deviceHandle);
}

bool usbDevice::controlTransfer(uint8_t requestType, uint8_t request, uint16_t value, uint16_t index, unsigned char *data, uint16_t length, unsigned int timeout)
{
	auto error = libusb_control_transfer(this->deviceHandle, requestType, request, value, index, data, length, timeout);
	if (error == 0 || error == 0x40)
		return true;

	printf("Failed to constrol transfer (libusb error: %s).\n", libusb_error_name(error));
	return false;
}

void usbDevice::cleanup()
{
	libusb_exit(usbDevice::ctxt);
	usbDevice::ctxt = NULL;
}


//TODO: need to figure out how to properly clean up memory allocated by libusb
std::shared_ptr<usbDevice> usbDevice::getByVendorProductIdentifier(uint16_t vendor, uint16_t id)
{
	if (usbDevice::ctxt == NULL)
	{
		auto error = libusb_init(&ctxt);
		if (error != 0)
		{
			printf("Failed to initialize libusb: %d\n", error);
			return nullptr;
		}
	}


	libusb_device **deviceList;

	auto deviceCount = libusb_get_device_list(usbDevice::ctxt, &deviceList);
	if (deviceCount == 0)
		return nullptr;

	struct libusb_device_descriptor deviceDescriptor;
	for (unsigned int i = 0; i < (unsigned int)deviceCount; i++)
	{
		ZeroMemory(&deviceDescriptor, sizeof(deviceDescriptor));

		auto error = libusb_get_device_descriptor(deviceList[i], &deviceDescriptor);
		if (error == 0)
		{
			if (deviceDescriptor.idVendor == vendor && deviceDescriptor.idProduct == id)
			{
				struct libusb_device_handle *deviceHandle;
				error = libusb_open(deviceList[i], &deviceHandle);
				if (error == 0)
				{
					error = libusb_claim_interface(deviceHandle, 3);
					if(error == 0)
						return std::shared_ptr<usbDevice>(new usbDevice(deviceHandle));
					else
						printf("USB interface claim failed with error %d :(\n", libusb_error_name(error));
				}
				else
					printf("Failed to open device (libusb error: %s).\n", libusb_error_name(error));

				return nullptr;
			}
		}
		else
		{
			printf("Failed to get device description (libusb error: %s).\n", libusb_error_name(error));
		}
	}

	return nullptr;
}