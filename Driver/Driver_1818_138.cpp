/*
 * Driver1818138.cpp
 *
 *  Created on: 2012-5-28
 *      Author: Agu
 */

#include "Driver_1818_138.h"

Driver_1818_138::Driver_1818_138(DotMatrix & dm, uint8_t pin_62726_DS, uint8_t pin_62726_OE,
		uint8_t pin_62726_ST, uint8_t pin_62726_SH, uint8_t pin_138_A2,
		uint8_t pin_138_A1, uint8_t pin_138_A0, uint8_t pin_brightness,
		uint16_t scan_speed):
		_dm(dm),
		chip_col(pin_62726_DS, pin_62726_SH, pin_62726_ST,pin_62726_OE, pin_brightness),
		chip_row(pin_138_A2, pin_138_A1, pin_138_A0, 255)
{
	this->setBrightness();
	this->setSpeed(scan_speed);
	this->setSize();
}

Driver_1818_138::~Driver_1818_138()
{

}

void Driver_1818_138::setSpeed(uint16_t scan_span)
{
	_scan_span = scan_span;
}

void Driver_1818_138::setSize()
{
	_row_count = _dm.countRow();
	_byte_per_row = _dm.countBytePerRow();
	_word_per_row = _byte_per_row / 2;
}

void Driver_1818_138::setBrightness(byte brg)
{
	chip_col.setBrightness(brg);
}

void Driver_1818_138::setCol(byte row) const
{
	byte * p = _dm.output();
	p += _byte_per_row * row;

	chip_col.shiftSendFromLSB(p, _byte_per_row);
}

void Driver_1818_138::display(byte times) const
{
	while (times--)
	{
		for (byte r = 0; r < _row_count; r++)
		{
			this->setCol(r);

			chip_col.setOE(true);
			chip_col.shiftLatch();
			chip_row.setValue(r);
			chip_col.setOE(false);

			delayMicroseconds(_scan_span);
		}
	}
}
