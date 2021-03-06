/*
 * DriverDual595.h
 *
 *  Created on: 2012-9-4
 *      Author: agu
 */

#ifndef DRIVERDUAL595_H_
#define DRIVERDUAL595_H_

#include "Arduino.h"
#include "PinWrite.h"
#include "DotMatrix.h"

#define DUAL595_WIDTH	24

class Driver_Dual595
{
public:

	Driver_Dual595(uint8_t pin_col, uint8_t pin_row, uint8_t pin_sh, uint8_t pin_st, uint8_t pin_oe);
	virtual ~Driver_Dual595();
	void display() const;
	DotMatrix & getDotMatrix();

	void setBrightness(byte brightness=0x70);
	void setScanSpan(byte scan_span= 0xa0);

private:

	DotMatrix _dm;

	const uint8_t _pin_col;
	const uint8_t _pin_row;
	const uint8_t _pin_sh;
	const uint8_t _pin_st;
	const uint8_t _pin_oe;

	uint16_t _scan_span;

	inline void shiftLatch() const;
	inline void shiftClock() const;
};

const uint8_t PROGMEM DUAL595_ROW_ADDRESS[] =
{
	24, 30, 36, 42,
	48, 54, 60, 66,
	51, 57, 63, 69,
	0, 6, 12, 18,
	3, 9, 15, 21,
	27, 33, 39, 45,
};

#endif /* DRIVERDUAL595_H_ */
