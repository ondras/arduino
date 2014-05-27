#ifndef shapes_h
#define shapes_h

#define SHAPE_ROTATIONS	4
#define SHAPE_SIZE		4
#define SHAPE_COUNT		8

typedef int Shape[SHAPE_SIZE];
typedef Shape Shape4[SHAPE_ROTATIONS];

extern Shape4 SHAPES[SHAPE_COUNT];

#endif
