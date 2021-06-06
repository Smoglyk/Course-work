#ifndef STEP_H
#define STEP_H

enum Figure
{
    BLACK_PAWN,
    BLACK_ROOK,
    BLACK_KNIGHT,
    BLACK_BISHOP,
    BLACK_QUEEN,
    BLACK_KING,
    WHITE_PAWN,
    WHITE_ROOK,
    WHITE_KNIGHT,
    WHITE_BISHOP,
    WHITE_QUEEN,
    WHITE_KING,
    ZERO
};

class Step
{
public:
    int x, y;
    Step();
    Step(int x, int y);
    int operator ==(Step s);
    int operator !=(Step s);
    void operator ++();
    int operator ++(int);
};

#endif // STEP_H
