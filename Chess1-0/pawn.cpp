#include "pawn.h"

Pawn::Pawn(int type, int x, int y)
{
    st = new Step(x, y);
    this->type = type;
    if(type < 6)
        filename = "C:\\Users\\Jarvis\\Documents\\Chess1-0\\blackPawn.png";
    if(type >= 6)
        filename = "C:\\Users\\Jarvis\\Documents\\Chess1-0\\whitePawn.png";
    int t = y;
    int at = x;
    if(type == BLACK_PAWN)
    {
        if(t == 1)
        {
            ++t;
            if(t < 8)
            {
                Step st1(x, t);
                Step st2(x, ++t);
                free_step.push_back(st1);
                free_step.push_back(st2);
                --at;
                --t;
                if(at >= 0 && t < 8)
                {
                    Step at1(at, t);
                    free_attack_pawn.push_back(at1);
                }
                at += 2;
                if(at < 8 && t < 8)
                {
                    Step at1(at, t);
                    free_attack_pawn.push_back(at1);
                }

            }
        }
        else
        {
            ++t;
            if(t < 8)
            {
                Step st1(x, t);
                free_step.push_back(st1);
            }
            --at;
            if(at >= 0 && t < 8)
            {
                Step at1(at, t);
                free_attack_pawn.push_back(at1);
            }
            at += 2;
            if(at < 8 && t < 8)
            {
                Step at1(at, t);
                free_attack_pawn.push_back(at1);
            }
        }


    }
    else if(type == WHITE_PAWN)
    {
        if(t == 6)
        {
            --t;
            if(t >= 0)
            {
                Step st1(x, t);
                Step st2(x, --t);
                free_step.push_back(st1);
                free_step.push_back(st2);
                --at;
                ++t;
                if(at >= 0 && t >= 0)
                {
                    Step at1(at, t);
                    free_attack_pawn.push_back(at1);
                }
                at += 2;
                if(at < 8 && t >= 0)
                {
                    Step at1(at, t);
                    free_attack_pawn.push_back(at1);
                }
            }
        }
        else
        {
            --t;
            if(t >= 0)
            {
                Step st1(x, t);
                free_step.push_back(st1);
            }
            --at;
            if(at >= 0 && t >= 0)
            {
                Step at1(at, t);
                free_attack_pawn.push_back(at1);
            }
            at += 2;
            if(at < 8 && t < 8)
            {
                Step at1(at, t);
                free_attack_pawn.push_back(at1);
            }
        }

    }


}
