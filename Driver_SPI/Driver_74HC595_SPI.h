/*
 * Driver_74HC595_SPI.h
 *
 *  Created on: 2012-7-16
 *      Author: Agu
 */

#ifndef DRIVER_74HC595_SPI_H_
#define DRIVER_74HC595_SPI_H_

#include "Arduino.h"
#include "SPI.h"
#include "PinWrite.h"

class Driver_74HC595_SPI
{
public:

	Driver_74HC595_SPI(SPIClass & spi, uint8_t pin_ST, uint8_t pin_OE);
	virtual ~Driver_74HC595_SPI();

	void setShiftSendMode(byte mode = LSBFIRST);
	void shiftSend(byte *p, byte length) const;
	void shiftSendRev(byte *p, byte length) const;

	void shiftLatch() const;
	void setOE(bool high) const;

protected:

	const SPIClass & _spi;

private:

	const uint8_t _pin_ST;
	const uint8_t _pin_OE;

};

#endif /* DRIVER_74HC595_SPI_H_ */
