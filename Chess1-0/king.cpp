#include "king.h"

King::King(int type, int x, int y)
{
    st = new Step(x, y);
    this->type = type;
    if(type < 6)
        filename = "C:\\Users\\Jarvis\\Documents\\Chess1-0\\blackKing.png";
    if(type >= 6)
        filename = "C:\\Users\\Jarvis\\Documents\\Chess1-0\\whiteKing.png";
    int i = x, t = y;
    ++i;
    if(i < 8)
    {
        Step st1(i, t);
        ++t;
        free_step.push_back(st1);
        if(t < 8)
        {
            Step st2(i, t);
            Step st3(x, t);
            free_step.push_back(st3);
            free_step.push_back(st2);

        }
        t -= 2;
        if(t >= 0)
        {
            Step st4(i, t);
            Step st5(x, t);
            free_step.push_back(st5);
            free_step.push_back(st4);
        }
        t = y;

    }

    i -= 2;

    if(i >= 0)
    {
        Step st1(i, t);
        ++t;
        free_step.push_back(st1);
        if(t < 8)
        {
            Step st1(i, t);
            free_step.push_back(st1);
        }
        t -= 2;
        if(t >= 0)
        {
            Step st2(i, t);
            free_step.push_back(st2);
        }
        t = y;

    }




}
