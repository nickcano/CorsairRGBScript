#include "corsairRGBKeyboard.h"
#include "usbDevice.h"

#include <assert.h>

bool corsairRGBKeyboard::setKey(uint8_t key, uint8_t r, uint8_t g, uint8_t b)
{
	if (key >= CORSAIR_MAX_KEYS)
		return false;

	this->keyColors[key].r = corsairLightColor::normalize(r);
	this->keyColors[key].g = corsairLightColor::normalize(g);
	this->keyColors[key].b = corsairLightColor::normalize(b);

	return true;
}

bool corsairRGBKeyboard::updateKeyboard()
{
	assert(this->isValid());

	unsigned char packet[5][64] = {0};

	packet[0][0] = 0x7F;
	packet[0][1] = 0x01;
	packet[0][2] = 0x3C;

	packet[1][0] = 0x7F;
	packet[1][1] = 0x02;
	packet[1][2] = 0x3C;

	packet[2][0] = 0x7F;
	packet[2][1] = 0x03;
	packet[2][2] = 0x3C;

	packet[3][0] = 0x7F;
	packet[3][1] = 0x04;
	packet[3][2] = 0x24;

	packet[4][0] = 0x07;
	packet[4][1] = 0x27;
	packet[4][4] = 0xD8;

	for(int i = 0; i < 60; i++)
		packet[0][i+4] = this->keyColors[i*2+1].r << 4 | this->keyColors[i*2].r;

	for(int i = 0; i < 12; i++)
		packet[1][i+4] = this->keyColors[i*2+121].r << 4 | this->keyColors[i*2+120].r;

	for(int i = 0; i < 48; i++) {
		packet[1][i+16] = this->keyColors[i*2+1].g << 4 | this->keyColors[i*2].g;
	}

	for(int i = 0; i < 24; i++) {
		packet[2][i+4] = this->keyColors[i*2+97].g << 4 | this->keyColors[i*2+96].g;
	}

	for(int i = 0; i < 36; i++) {
		packet[2][i+28] = this->keyColors[i*2+1].b << 4 | this->keyColors[i*2].b;
	}

	for(int i = 0; i < 36; i++) {
		packet[3][i+4] = this->keyColors[i*2+73].b << 4 | this->keyColors[i*2+72].b;
	}


	this->device->controlTransfer(0x21, 0x09, 0x0300, 0x03, packet[0], 64);
	this->device->controlTransfer(0x21, 0x09, 0x0300, 0x03, packet[1], 64);
	this->device->controlTransfer(0x21, 0x09, 0x0300, 0x03, packet[2], 64);
	this->device->controlTransfer(0x21, 0x09, 0x0300, 0x03, packet[3], 64);
	this->device->controlTransfer(0x21, 0x09, 0x0300, 0x03, packet[4], 64);

	return true;
}