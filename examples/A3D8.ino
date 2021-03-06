#include "DotMatrixTest.h"
#include "DotMatrix3D.h"
#include "Driver_3D8.h"

DotMatrix3D dm(1);
Driver_3D8 cube(dm, 9, 10, 17, 8, 11, 5, 4, 3);

void setup()
{
	dm.clear(0x00);
	//dm.DotMatrix::setDot(0, 0, true);
	cube.setBrightness(0xff);
	//cube.setMode(0x02);

	for (byte i = 0; i < 8; i++)
		dm.setDot(i, i, 0, true);

}

void animation_facet_scan(byte speed = 0x04)
{
	for (byte j = 0; j < 3; j++)
	{
		cube.setMode(j);
		byte i = 0;
		while (i < 8)
		{
			dm.clear(0x00);
			dm.setRect(i * 8, 0, i * 8 + 7, 7);
			cube.display(speed);
			i++;
		}
		while (i)
		{
			i--;
			dm.clear(0x00);
			dm.setRect(i * 8, 0, i * 8 + 7, 7);
			cube.display(speed);
		}
	}
}

void animation_flow(word length = 0x40, byte speed = 0x04)
{
	word counter;
	for (byte j = 0; j < 3; j++)
	{
		cube.setMode(j);
		counter = length;
		while (counter--)
		{
			for (byte i = 0; i < random(4); i++)
				dm.setDot(random(8), random(8), 7, true);
			cube.display(speed);
			dm.setMoveDirection(DotMatrix3D::Z_NEGA);
			dm.move(false);
		}
	}
}

void loop()
{
	animation_facet_scan();
	animation_flow();
	cube.display(0x08);
}
