#ifndef pieces_h
#define pieces_h

const PIECE piece_o[PIECE_ROTATIONS] = {
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
};

const PIECE piece_i[PIECE_ROTATIONS] = {
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
};

const PIECE PIECES[PIECE_COUNT] = {piece_o, piece_i};

#endif