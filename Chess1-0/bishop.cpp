#include "bishop.h"

Bishop::Bishop(int type, int x, int y)
{
    st = new Step(x, y);
    this->type = type;
    if(type < 6)
        filename = "C:\\Users\\Jarvis\\Documents\\Chess1-0\\blackBishop.png";
    if(type >= 6)
        filename = "C:\\Users\\Jarvis\\Documents\\Chess1-0\\whiteBishop.png";

}
