/*
 * Driver_1818_138.h
 *
 *  Created on: 2012-5-28
 *      Author: Agu
 */

#ifndef DRIVER_1818_138_H_
#define DRIVER_1818_138_H_

#include "DotMatrix.h"
#include "Driver_TB62726.h"
#include "Driver_74HC138.h"

class Driver_1818_138
{
public:
	Driver_1818_138(DotMatrix & dm, uint8_t pin_62726_DS, uint8_t pin_62726_OE,
			uint8_t pin_62726_ST, uint8_t pin_62726_SH, uint8_t pin_138_A2,
			uint8_t pin_138_A1, uint8_t pin_138_A0, uint8_t pin_brightness,
			uint16_t scan_speed = 0x600);

	void setSpeed(uint16_t scan_span);
	void setSize();
	void setBrightness(byte brg = 0xff);

	void display(byte times = 0x01) const;

	virtual ~Driver_1818_138();

protected:

	const DotMatrix & _dm;
	Driver_TB62726 chip_col;
	Driver_74HC138 chip_row;

	word _scan_span;

	byte _row_count;
	byte _word_per_row;
	byte _byte_per_row;

	void setCol(byte row) const;
};

#endif /* DRIVER1818138_H_ */
