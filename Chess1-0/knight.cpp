#include "knight.h"

Knight::Knight(int type, int x, int y)
{
    st = new Step(x, y);
    this->type = type;
    if(type < 6)
        filename = "C:\\Users\\Jarvis\\Documents\\Chess1-0\\blackKnight.png";
    if(type >= 6)
        filename = "C:\\Users\\Jarvis\\Documents\\Chess1-0\\whiteKnight.png";
    int i = x, t = y;
    ++i;
    t = y - 2;
    if(t >= 0 && i < 8)
    {
        Step st1(i, t);
        free_step.push_back(st1);
    }
    i = x - 1;
    if(t >= 0 && i >= 0)
    {
        Step st1(i, t);
        free_step.push_back(st1);
    }
    t = y + 2;
    if(t < 8 && i >= 0)
    {
        Step st1(i, t);
        free_step.push_back(st1);
    }
    i = x + 1;
    if(t < 8 && i < 8)
    {
        Step st1(i, t);
        free_step.push_back(st1);
    }
    i = x - 2;
    t = y + 1;
    if(i >= 0 && t < 8)
    {
        Step st1(i, t);
        free_step.push_back(st1);
    }
    t = y - 1;
    if(i >= 0 && t >= 0)
    {
        Step st1(i, t);
        free_step.push_back(st1);
    }
    i = x + 2;
    if(i < 8 && t >= 0)
    {
        Step st1(i, t);
        free_step.push_back(st1);
    }
    t = y + 1;
    if(i < 8 && t < 8)
    {
        Step st1(i, t);
        free_step.push_back(st1);
    }
}
