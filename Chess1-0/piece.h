#ifndef PIECE_H
#define PIECE_H
#include "step.h"
#include <QString>
#include <QVector>
using namespace std;

class Piece
{
public:
    int type;
    QString filename;
    Step* st;
    QVector<Step> free_step;
    QVector<Step> free_attack_pawn;
    Piece();
    void copy(Piece* p);
};

#endif // PIECE_H
