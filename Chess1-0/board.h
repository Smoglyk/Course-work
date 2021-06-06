#ifndef BOARD_H
#define BOARD_H
#include "piece.h"
#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "rook.h"
#include "queen.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>


class Board: public QGraphicsScene
{
    Q_OBJECT
public:
    bool win_black = false;
    bool turn_black = false;
    bool turn_white = true;
    bool step_white = false;
    bool step_black = false;
    bool win_white = false;
    int pieceAtackW[8][8];
    int pieceAtackB[8][8];
    Piece piece[8][8];
    Step* start_step;
    Step* end_step;
    Board();
    ~Board();
    void movePiece();
    void  pieceUnderAtack(bool need_pawn = false, bool need_king = true);
    int check_checkmate(int type);
    bool check_step(int type, Step* st_start, Step* st_end = nullptr, bool attack = false);
    void attackBishop(int index_x, int index_y);
    void attackRook(int index_x,int index_y);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:
    int my_signal();
    int new_signal();



};

#endif // BOARD_H
