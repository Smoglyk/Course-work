#include "piece.h"

Piece::Piece()
{

}

void Piece::copy(Piece *p)
{
    type = p->type;
    filename = p->filename;
    st = p->st;
    free_step = p->free_step;
    free_attack_pawn = p->free_attack_pawn;
}

