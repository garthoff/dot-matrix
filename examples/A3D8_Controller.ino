#include "DotMatrixTest.h"

#include "DotMatrix3D.h"
#include "Controller_A3D8.h"

extern HardwareSerial Serial;

DotMatrix3D dm(1);
Controller_A3D8 cube(dm, Serial);

void setup()
{
	//pScreen = (byte *) malloc(sizeof(byte) * length);
	Serial.begin(57600);
	cube.sendMode(Controller_A3D8_Basic::XYZ);
	cube.sendBrightness(0xff);

	dm.clear(0x00);

	for (byte i = 0; i < 4; i++)
		dm.setDot(0, 0, i);

}

void animationFlash()
{
	static byte value = 0xff;
	cube.sendGlobal(value);
	value = ~value;
}

void animationBreathe()
{
	static byte brightness = 0xff;
	static bool increase = false;

	cube.sendBrightness(increase ? ++brightness : --brightness);

	if (brightness == 0xff)
		increase = false;

	if (brightness == 0x00)
		increase = true;
}

void animationFacetScan()
{
	static byte value = 0x01;
	cube.sendGlobal(value);
	value <<= 1;
	if (value == 0x00)
		value = 0x01;
}

void animationBlockScan()
{
	static byte value = 0x00;
	value = (value << 1) + 0x01;
	cube.sendGlobal(value);
	if (value == 0xff)
		value = 0x00;
}

void animationRiseZ()
{
	dm.setMoveDirection(DotMatrix::BIT_IN_ROW_NEGA);
	dm.move(false);
	for (byte i = 0; i < random(4); i++)
	{
		byte x = random(8);
		byte z = random(8);
		dm.setDot(x, 7, z);
	}
	cube.putDM();
}

void callAnimation(void (*p)(), uint16_t span, uint16_t times, byte init_value,
		Controller_A3D8_Basic::InputMode mode)
{
	cube.sendMode(mode);
	cube.sendGlobal(init_value);
	while (times--)
	{
		(*p)();
		delay(span);
	}
}

void callAnimationInModes(void (*p)(), uint16_t span, uint16_t times,
		byte init_value)
{
	for (byte i = 0; i < 3; i++)
		callAnimation(p, span, times, init_value,
				(Controller_A3D8_Basic::InputMode) i);
}

void loop()
{
	callAnimation(animationFlash, 0xF0, 0x08, 0x00, Controller_A3D8_Basic::XYZ);
	callAnimation(animationBreathe, 0x08, 0xff * 4, 0xff,
			Controller_A3D8_Basic::XYZ);
	callAnimationInModes(animationFacetScan, 0x80, 0x08, 0x00);
	callAnimationInModes(animationBlockScan, 0x80, 0x08, 0x00);
	callAnimationInModes(animationRiseZ, 0x40, 0x60, 0x00);
}

