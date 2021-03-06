/*
 *	Driver_PCD8544_Basic.h
 *	Driver_PCD8544 Class for dot-matrix printing on liquid crystal display driven by HD47780, namely 1602/1604
 *	Created on: 2012-05-30
 *
 *	library for Arduino for Dot Matrix Display, support driver by 74HC595 and 74HC138, ST7920, HD47780
 *	Author: Weihong Guan
 *	Blog: http://aguegu.net
 *	E-mail: weihong.guan@gmail.com
 *
 *	Code license: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
 *	http://creativecommons.org/licenses/by-nc-sa/3.0/
 *	source host: https://github.com/aguegu/dot-matrix
 */

#ifndef DRIVER_PCD8544_BASIC
#define DRIVER_PCD8544_BASIC

#include "Arduino.h"

#define COMMAND	false
#define DATA	true

#ifndef PIN_WRITE
#define pinSet(pin)	*portOutputRegister(digitalPinToPort(pin)) |= digitalPinToBitMask(pin)
#define pinClear(pin)	*portOutputRegister(digitalPinToPort(pin)) &= ~digitalPinToBitMask(pin)
#define pinWrite(pin, val) ( (val) ? pinSet(pin) : pinClear(pin))
#endif

class Driver_PCD8544_Basic
{

public:

	Driver_PCD8544_Basic
		(uint8_t pin_sce, uint8_t pin_rst, uint8_t pin_dc, uint8_t pin_din, uint8_t pin_sclk);
	virtual ~Driver_PCD8544_Basic();
	void init();
	void setRamAddress(byte x, byte y);

	void configureHardware(byte tc = 0x03, byte bias = 0x00, byte vop = 0x50);
	void configureDisplay(bool display_on = true, bool reverse = false);
	void configureFunction(bool active = true, bool vertical_addressing = true, bool extend_command = false);

protected:

	void sendMsbFirst(byte c, bool b);
	void sendLsbFirst(byte c, bool b);
	const static byte BYTES_PER_COLUMN = 6;
	const static byte CLOLUMN_COUNT = 84;

private:

	const uint8_t _pin_sce;
	const uint8_t _pin_rst;
	const uint8_t _pin_dc;
	const uint8_t _pin_din;
	const uint8_t _pin_sclk;
};

#endif /* DRIVER_PCD8544_H_ */
