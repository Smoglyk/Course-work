#include "step.h"

Step::Step()
{

}

Step::Step(int x, int y)
{
    this->x = x;
    this->y = y;
}

int Step::operator ==(Step s)
{
    if(x == s.x && y == s.y)
        return 1;
    else
        return 0;
}

int Step::operator !=(Step s)
{
    if(x == s.x && y == s.y)
        return 0;
    else
        return 1;
}

void Step::operator ++()
{
    ++x;
    ++y;
}

int Step::operator ++(int)
{
    ++x;
    ++y;
}
