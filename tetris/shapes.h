#ifndef shapes_h
#define shapes_h

#define SHAPE_ROTATIONS	4
#define SHAPE_SIZE		4
#define SHAPE_COUNT		2

typedef int Shape[SHAPE_SIZE];
typedef Shape Shape4[SHAPE_ROTATIONS];

Shape4 SHAPES[SHAPE_COUNT] = {
	{
		{
			B0000,
			B0110,
			B0110,
			B0000
		}, {
			B0000,
			B0110,
			B0110,
			B0000
		}, {
			B0000,
			B0110,
			B0110,
			B0000
		}, {
			B0000,
			B0110,
			B0110,
			B0000
		}
	}, {
		{
			B0000,
			B1111,
			B0000,
			B0000
		}, {
			B0010,
			B0010,
			B0010,
			B0010
		}, {
			B0000,
			B0000,
			B1111,
			B0000
		}, {
			B0100,
			B0100,
			B0100,
			B0100
		}
	}
};

#endif
