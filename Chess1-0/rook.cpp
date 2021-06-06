#include "rook.h"

Rook::Rook(int type, int x, int y)
{
    st = new Step(x, y);
    this->type = type;
    if(type < 6)
        filename = "C:\\Users\\Jarvis\\Documents\\Chess1-0\\blackRook.png";
    if(type >= 6)
        filename = "C:\\Users\\Jarvis\\Documents\\Chess1-0\\whiteRook.png";

}
