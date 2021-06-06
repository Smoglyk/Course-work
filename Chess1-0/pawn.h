#ifndef PAWN_H
#define PAWN_H
#include "piece.h"


class Pawn:public Piece
{
public:
    Pawn(int type, int x, int y);
};

#endif // PAWN_H
