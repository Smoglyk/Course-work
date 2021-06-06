#include "board.h"
#include <QDebug>

Board::Board()
{
    start_step = new Step(-1, -1);
    end_step = new Step(-1, -1);

    for(int i = 0; i < 8; i++)
    {
        for(int y = 0; y < 8; y++)
            pieceAtackW[i][y] = 0;
    }

    for(int i = 0; i < 8; i++)
    {
        for(int y = 0; y < 8; y++)
            pieceAtackB[i][y] = 0;
    }

    for(int i = 0; i < 8; i++)
    {
        for(int y = 0; y < 8; y++)
        {
          Piece p;
          p.type = ZERO;
          piece[i][y] = p;
        }
    }
    Rook r1B(BLACK_ROOK, 0, 0);
    Knight kn1B(BLACK_KNIGHT, 1, 0);
    Bishop b1B(BLACK_BISHOP, 2, 0);
    Queen qB(BLACK_QUEEN, 3, 0);
    King kB(BLACK_KING, 4, 0);
    Bishop b2B(BLACK_BISHOP, 5, 0);
    Knight kn2B(BLACK_KNIGHT, 6, 0);
    Rook r2B(BLACK_ROOK, 7, 0);

    piece[0][0] = r1B;
    piece[0][1] = kn1B;
    piece[0][2] = b1B;
    piece[0][3] = qB;
    piece[0][4] = kB;
    piece[0][5] = b2B;
    piece[0][6] = kn2B;
    piece[0][7] = r2B;
    for(int i = 0; i < 8; i++)
    {
        Pawn pB(BLACK_PAWN, i, 1);
        piece[1][i] = pB;
    }

    Rook r1W(WHITE_ROOK, 0, 7);
    Knight kn1W(WHITE_KNIGHT, 1, 7);
    Bishop b1W(WHITE_BISHOP, 2, 7);
    Queen qW(WHITE_QUEEN, 3, 7);
    King kW(WHITE_KING, 4, 7);
    Bishop b2W(WHITE_BISHOP, 5, 7);
    Knight kn2W(WHITE_KNIGHT, 6, 7);
    Rook r2W(WHITE_ROOK, 7, 7);

    piece[7][0] = r1W;
    piece[7][1] = kn1W;
    piece[7][2] = b1W;
    piece[7][3] = qW;
    piece[7][4] = kW;
    piece[7][5] = b2W;
    piece[7][6] = kn2W;
    piece[7][7] = r2W;

    for(int i = 0; i < 8; i++)
    {
        Pawn pW(WHITE_PAWN, i, 6);
        piece[6][i] = pW;
    }
    pieceUnderAtack();
}

Board::~Board()
{
    delete start_step;
    delete end_step;
}



bool Board::check_step(int type, Step* st_start, Step* st_end, bool attack)
{
    if(type == WHITE_KING)
    {
        if(piece[st_start->y][st_start->x].type == WHITE_PAWN)
        {
            if(!attack)
            {
                if(piece[st_end->y][st_end->x].type == ZERO)
                {
                    Piece p_e; p_e.copy(&piece[st_end->y][st_end->x]);
                    Pawn pawn_end(WHITE_PAWN, st_end->x, st_end->y);
                    piece[st_start->y][st_start->x].type = ZERO;
                    piece[st_end->y][st_end->x] = pawn_end;
                    pieceUnderAtack();
                    for(int i = 0; i < 8; i++)
                    {
                        for(int y = 0; y < 8; y++)
                        {
                            if(pieceAtackB[i][y] == 1 && piece[i][y].type == WHITE_KING)
                            {
                                piece[st_end->y][st_end->x] = p_e;
                                piece[st_start->y][st_start->x].type = WHITE_PAWN;
                                return false;
                            }
                        }
                    }
                    piece[st_end->y][st_end->x] = p_e;
                    piece[st_start->y][st_start->x].type = WHITE_PAWN;
                    return true;
                }
                else
                    return false;
            }
            if(attack)
            {
                Piece p_e; p_e.copy(&piece[st_end->y][st_end->x]);
                Pawn pawn_end(WHITE_PAWN, st_end->x, st_end->y);
                piece[st_start->y][st_start->x].type = ZERO;
                piece[st_end->y][st_end->x] = pawn_end;
                pieceUnderAtack();
                for(int i = 0; i < 8; i++)
                {
                    for(int y = 0; y < 8; y++)
                    {
                        if(pieceAtackB[i][y] == 1 && piece[i][y].type == WHITE_KING)
                        {
                            piece[st_end->y][st_end->x] = p_e;
                            piece[st_start->y][st_start->x].type = WHITE_PAWN;
                            return false;
                        }
                    }
                }
                piece[st_end->y][st_end->x] = p_e;
                piece[st_start->y][st_start->x].type = WHITE_PAWN;
                return true;
            }
        }
        if(piece[st_start->y][st_start->x].type != WHITE_KING)
        {
            Piece p_s, p_e;
            p_e.copy(&piece[st_end->y][st_end->x]);
            p_s.copy(&piece[st_start->y][st_start->x]);
            piece[st_start->y][st_start->x].type = ZERO;
            piece[end_step->y][end_step->x] = p_s;
            pieceUnderAtack();
            for(int i = 0; i < 8; i++)
            {
                for(int y = 0; y < 8; y++)
                {
                    if(pieceAtackB[i][y] == 1 && piece[i][y].type == WHITE_KING)
                    {
                        piece[st_start->y][st_start->x].type = piece[st_end->y][st_end->x].type;
                        piece[st_end->y][st_end->x] = p_e;
                        return false;
                    }
                }
            }
            piece[st_start->y][st_start->x].type = piece[st_end->y][st_end->x].type;
            piece[st_end->y][st_end->x] = p_e;
            return true;
        }
        if(piece[st_start->y][st_start->x].type == WHITE_KING && st_end != nullptr)
        {
            pieceUnderAtack();
            for(int i = 0; i < 8; i++)
            {
                for(int y = 0; y < 8; y++)
                {
                    if(pieceAtackB[i][y] == 1 && i == st_end->y && y == st_end->x)
                    {
                        return false;
                    }
                }
            }
            return true;
        }
    }
    if(type == BLACK_KING)
    {
        if(piece[st_start->y][st_start->x].type == BLACK_PAWN)
        {
            if(!attack)
            {
                if(piece[st_end->y][st_end->x].type == ZERO)
                {
                    Piece p_e; p_e.copy(&piece[st_end->y][st_end->x]);
                    Pawn pawn_end(WHITE_PAWN, st_end->x, st_end->y);
                    piece[st_start->y][st_start->x].type = ZERO;
                    piece[st_end->y][st_end->x] = pawn_end;
                    pieceUnderAtack();
                    for(int i = 0; i < 8; i++)
                    {
                        for(int y = 0; y < 8; y++)
                        {
                            if(pieceAtackW[i][y] == 1 && piece[i][y].type == BLACK_KING)
                            {
                                piece[st_end->y][st_end->x] = p_e;
                                piece[st_start->y][st_start->x].type = BLACK_PAWN;
                                return false;
                            }
                        }
                    }
                    piece[st_end->y][st_end->x] = p_e;
                    piece[st_start->y][st_start->x].type = BLACK_PAWN;
                    return true;
                }
                else
                    return false;
            }
            if(attack)
            {
                Piece p_e; p_e.copy(&piece[st_end->y][st_end->x]);
                Pawn pawn_end(WHITE_PAWN, st_end->x, st_end->y);
                piece[st_start->y][st_start->x].type = ZERO;
                piece[st_end->y][st_end->x] = pawn_end;
                pieceUnderAtack();
                for(int i = 0; i < 8; i++)
                {
                    for(int y = 0; y < 8; y++)
                    {
                        if(pieceAtackW[i][y] == 1 && piece[i][y].type == BLACK_KING)
                        {
                            piece[st_end->y][st_end->x] = p_e;
                            piece[st_start->y][st_start->x].type = BLACK_PAWN;
                            return false;
                        }
                    }
                }
                piece[st_end->y][st_end->x] = p_e;
                piece[st_start->y][st_start->x].type = BLACK_PAWN;
                return true;
            }

        }
        if(piece[st_start->y][st_start->x].type != BLACK_KING)
        {
            Piece p_s, p_e;
            p_e.copy(&piece[st_end->y][st_end->x]);
            p_s.copy(&piece[st_start->y][st_start->x]);
            piece[st_start->y][st_start->x].type = ZERO;
            piece[end_step->y][end_step->x] = p_s;
            pieceUnderAtack();
            for(int i = 0; i < 8; i++)
            {
                for(int y = 0; y < 8; y++)
                {
                    if(pieceAtackW[i][y] == 1 && piece[i][y].type == BLACK_KING)
                    {
                        piece[st_start->y][st_start->x].type = piece[st_end->y][st_end->x].type;
                        piece[st_end->y][st_end->x] = p_e;
                        return false;
                    }
                }
            }
            piece[st_start->y][st_start->x].type = piece[st_end->y][st_end->x].type;
            piece[st_end->y][st_end->x] = p_e;
            return true;
        }
        if(piece[st_start->y][st_start->x].type == BLACK_KING && st_end != nullptr)
        {
            pieceUnderAtack();
            for(int i = 0; i < 8; i++)
            {
                for(int y = 0; y < 8; y++)
                {
                    if(pieceAtackW[i][y] == 1 && i == st_end->y && y == st_end->x)
                    {
                        return false;
                    }
                }
            }
            return true;
        }
    }
}

void Board::movePiece()
{
    if(!win_black && !win_white)
    {
        bool have_step = false;
        bool attack = false;
        if(piece[start_step->y][start_step->x].type != ZERO)
        {
            if((piece[start_step->y][start_step->x].type >= 0 && piece[start_step->y][start_step->x].type < 6) && (piece[end_step->y][end_step->x].type >= 0 && piece[end_step->y][end_step->x].type < 6))
                return;
            if((piece[start_step->y][start_step->x].type >= 6 && piece[start_step->y][start_step->x].type < 12) && (piece[end_step->y][end_step->x].type >= 6 && piece[end_step->y][end_step->x].type < 12))
                return;
            for(int i = 0; i < piece[start_step->y][start_step->x].free_step.size(); i++)
            {
                if(piece[start_step->y][start_step->x].free_step[i].x == end_step->x && piece[start_step->y][start_step->x].free_step[i].y == end_step->y)
                {
                   have_step = true;
                   break;
                }
            }
            if(piece[start_step->y][start_step->x].type == WHITE_PAWN || piece[start_step->y][start_step->x].type == BLACK_PAWN)
            {
                for(int i = 0; i < piece[start_step->y][start_step->x].free_attack_pawn.size(); i++)
                {
                    if(piece[start_step->y][start_step->x].free_attack_pawn[i].x == end_step->x && piece[start_step->y][start_step->x].free_attack_pawn[i].y == end_step->y)
                    {
                       if(piece[end_step->y][end_step->x].type != ZERO)
                       {
                           have_step = true;
                           attack = true;
                           break;
                       }
                    }
                }
            }
            if(have_step)
            {
                switch(piece[start_step->y][start_step->x].type)
                {
                    case BLACK_PAWN:
                    {
                      if(turn_black)
                      {
                          if(!check_step(BLACK_KING, start_step, end_step, attack))
                              break;
                          if(end_step->y == 7)
                          {
                              Queen queen(BLACK_QUEEN, end_step->x, end_step->y);
                              Piece p;
                              p.type = ZERO;
                              piece[start_step->y][start_step->x] = p;
                              piece[end_step->y][end_step->x] = queen;
                              pieceUnderAtack();
                              switch(check_checkmate(WHITE_KING))
                              {
                                  case 0: break;
                                  case 1: step_white = true; break;
                                  case 2: win_black = true; break;
                              }
                          }
                          else
                          {
                              Pawn pawn(BLACK_PAWN, end_step->x, end_step->y);
                              Piece p;
                              p.type = ZERO;
                              piece[start_step->y][start_step->x] = p;
                              piece[end_step->y][end_step->x] = pawn;
                              pieceUnderAtack();
                              switch(check_checkmate(WHITE_KING))
                              {
                                  case 0: break;
                                  case 1: step_white = true; break;
                                  case 2: win_black = true; break;
                              }
                          }
                          turn_white = true;
                          turn_black = false;
                      }
                      break;
                    }
                    case BLACK_ROOK:
                    {
                     if(turn_black)
                     {
                         if(!check_step(BLACK_KING, start_step, end_step))
                             break;
                         Rook rook(BLACK_ROOK, end_step->x, end_step->y);
                         Piece p;
                         p.type = ZERO;
                         piece[start_step->y][start_step->x] = p;
                         piece[end_step->y][end_step->x] = rook;
                         pieceUnderAtack();
                         switch(check_checkmate(WHITE_KING))
                         {
                             case 0: break;
                             case 1: step_white = true; break;
                             case 2: win_black = true; break;
                         }
                         turn_white = true;
                         turn_black = false;
                     }
                     break;
                    }
                    case BLACK_KNIGHT:
                    {
                      if(turn_black)
                      {
                          if(!check_step(BLACK_KING, start_step, end_step))
                              break;
                          Knight knight(BLACK_KNIGHT, end_step->x, end_step->y);
                          Piece p;
                          p.type = ZERO;
                          piece[start_step->y][start_step->x] = p;
                          piece[end_step->y][end_step->x] = knight;
                          pieceUnderAtack();
                          switch(check_checkmate(WHITE_KING))
                          {
                              case 0: break;
                              case 1: step_white = true; break;
                              case 2: win_black = true; break;
                          }
                          turn_white = true;
                          turn_black = false;
                      }
                      break;
                    }
                    case BLACK_BISHOP:
                    {
                      if(turn_black)
                      {
                          if(!check_step(BLACK_KING, start_step, end_step))
                              break;
                          Bishop bishop(BLACK_BISHOP, end_step->x, end_step->y);
                          Piece p;
                          p.type = ZERO;
                          piece[start_step->y][start_step->x] = p;
                          piece[end_step->y][end_step->x] = bishop;
                          pieceUnderAtack();
                          switch(check_checkmate(WHITE_KING))
                          {
                              case 0: break;
                              case 1: step_white = true; break;
                              case 2: win_black = true; break;
                          }
                          turn_white = true;
                          turn_black = false;
                      }
                      break;
                    }
                    case BLACK_QUEEN:
                    {
                       if(turn_black)
                       {
                           if(!check_step(BLACK_KING, start_step, end_step))
                               break;
                           Queen queen(BLACK_QUEEN, end_step->x, end_step->y);
                           Piece p;
                           p.type = ZERO;
                           piece[start_step->y][start_step->x] = p;
                           piece[end_step->y][end_step->x] = queen;
                           pieceUnderAtack();
                           switch(check_checkmate(WHITE_KING))
                           {
                               case 0: break;
                               case 1: step_white = true; break;
                               case 2: win_black = true; break;
                           }
                           turn_white = true;
                           turn_black = false;
                       }
                       break;
                    }
                    case BLACK_KING:
                    {
                      if(turn_black)
                      {
                          if(!check_step(BLACK_KING, start_step, end_step))
                              break;
                          King king(BLACK_KING, end_step->x, end_step->y);
                          Piece p;
                          p.type = ZERO;
                          piece[start_step->y][start_step->x] = p;
                          piece[end_step->y][end_step->x] = king;
                          pieceUnderAtack();
                          switch(check_checkmate(WHITE_KING))
                          {
                              case 0: break;
                              case 1: step_white = true; break;
                              case 2: win_black = true; break;
                          }
                          turn_white = true;
                          turn_black = false;
                      }
                      break;
                    }
                    case WHITE_PAWN:
                    {
                      if(turn_white)
                      {
                          if(!check_step(WHITE_KING, start_step, end_step, attack))
                              break;
                          if(end_step->y == 0)
                          {
                              Queen queen(WHITE_QUEEN, end_step->x, end_step->y);
                              Piece p;
                              p.type = ZERO;
                              piece[start_step->y][start_step->x] = p;
                              piece[end_step->y][end_step->x] = queen;
                              pieceUnderAtack();
                              switch(check_checkmate(BLACK_KING))
                              {
                                  case 0: break;
                                  case 1: step_black = true; break;
                                  case 2: win_white = true; break;
                              }
                          }
                          else
                          {
                              Pawn pawn(WHITE_PAWN, end_step->x, end_step->y);
                              Piece p;
                              p.type = ZERO;
                              piece[start_step->y][start_step->x] = p;
                              piece[end_step->y][end_step->x] = pawn;
                              pieceUnderAtack();
                              switch(check_checkmate(BLACK_KING))
                              {
                                  case 0: break;
                                  case 1: step_black = true; break;
                                  case 2: win_white = true; break;
                              }
                          }
                          turn_white = false;
                          turn_black = true;
                      }
                      break;
                    }
                    case WHITE_ROOK:
                    {
                      if(turn_white)
                      {
                          if(!check_step(WHITE_KING, start_step, end_step))
                              break;
                          Rook rook(WHITE_ROOK, end_step->x, end_step->y);
                          Piece p;
                          p.type = ZERO;
                          piece[start_step->y][start_step->x] = p;
                          piece[end_step->y][end_step->x] = rook;
                          pieceUnderAtack();
                          switch(check_checkmate(BLACK_KING))
                          {
                              case 0: break;
                              case 1: step_black = true; break;
                              case 2: win_white = true; break;
                          }
                          turn_white = false;
                          turn_black = true;
                      }
                      break;
                    }
                    case WHITE_KNIGHT:
                    {
                       if(turn_white)
                       {
                           if(!check_step(WHITE_KING, start_step, end_step))
                               break;
                           Knight knight(WHITE_KNIGHT, end_step->x, end_step->y);
                           Piece p;
                           p.type = ZERO;
                           piece[start_step->y][start_step->x] = p;
                           piece[end_step->y][end_step->x] = knight;
                           pieceUnderAtack();
                           switch(check_checkmate(BLACK_KING))
                           {
                               case 0: break;
                               case 1: step_black = true; break;
                               case 2: win_white = true; break;
                           }
                           turn_white = false;
                           turn_black = true;
                       }
                       break;
                    }
                    case WHITE_BISHOP:
                    {
                       if(turn_white)
                       {
                           if(!check_step(WHITE_KING, start_step, end_step))
                               break;
                           Bishop bishop(WHITE_BISHOP, end_step->x, end_step->y);
                           Piece p;
                           p.type = ZERO;
                           piece[start_step->y][start_step->x] = p;
                           piece[end_step->y][end_step->x] = bishop;
                           pieceUnderAtack();
                           switch(check_checkmate(BLACK_KING))
                           {
                               case 1: step_black = true; break;
                               case 2: win_white = true; break;
                           }
                           turn_white = false;
                           turn_black = true;
                       }
                       break;
                    }
                    case WHITE_QUEEN:
                    {
                       if(turn_white)
                       {
                           if(!check_step(WHITE_KING, start_step, end_step))
                               break;
                           Queen queen(WHITE_QUEEN, end_step->x, end_step->y);
                           Piece p;
                           p.type = ZERO;
                           piece[start_step->y][start_step->x] = p;
                           piece[end_step->y][end_step->x] = queen;
                           pieceUnderAtack();
                           switch(check_checkmate(BLACK_KING))
                           {
                               case 0: break;
                               case 1: step_black = true; break;
                               case 2: win_white = true; break;
                           }
                           turn_white = false;
                           turn_black = true;
                       }
                       break;
                    }
                    case WHITE_KING:
                    {
                      if(turn_white)
                      {
                          if(!check_step(WHITE_KING, start_step, end_step))
                              break;
                          King king(WHITE_KING, end_step->x, end_step->y);
                          Piece p;
                          p.type = ZERO;
                          piece[start_step->y][start_step->x] = p;
                          piece[end_step->y][end_step->x] = king;
                          pieceUnderAtack();
                          switch(check_checkmate(BLACK_KING))
                          {
                              case 0: break;
                              case 1: step_black = true; break;
                              case 2: win_white = true; break;
                          }
                          turn_white = false;
                          turn_black = true;
                      }
                      break;
                    }
                }
            }
            if(!win_black && !win_white)
                emit my_signal();
            else
                emit new_signal();
        }
    }
}

void Board::pieceUnderAtack(bool need_pawn, bool need_king)
{
    for(int i = 0; i < 8; i++)
    {
        for(int y = 0; y < 8; y++)
            pieceAtackW[i][y] = 0;
    }

    for(int i = 0; i < 8; i++)
    {
        for(int y = 0; y < 8; y++)
            pieceAtackB[i][y] = 0;
    }
    for(int i = 0; i < 8; i++)
    {
        for(int y = 0; y < 8; y++)
        {
            if(piece[i][y].type != ZERO)
            {
                int type = piece[i][y].type;   
                if(type == WHITE_KING && need_king)
                {
                    for(int v = 0; v < piece[i][y].free_step.size(); v++)
                    {
                        Step st = piece[i][y].free_step[v];
                        pieceAtackW[st.y][st.x] = 1;
                    }
                }
                if(type == WHITE_KNIGHT)
                {
                    for(int v = 0; v < piece[i][y].free_step.size(); v++)
                    {
                        Step st = piece[i][y].free_step[v];
                        pieceAtackW[st.y][st.x] = 1;
                    }
                }
                if(type == WHITE_PAWN)
                {
                    if(!need_pawn)
                    {
                        for(int v = 0; v < piece[i][y].free_attack_pawn.size(); v++)
                        {
                            Step st = piece[i][y].free_attack_pawn[v];
                            pieceAtackW[st.y][st.x] = 1;
                        }
                    }
                    if(need_pawn)
                    {
                        for(int v = 0; v < piece[i][y].free_step.size(); v++)
                        {
                            Step st = piece[i][y].free_step[v];
                            pieceAtackW[st.y][st.x] = 1;
                        }
                    }
                }
                if(type == WHITE_BISHOP)
                {
                    piece[i][y].free_step.clear();
                    attackBishop(i, y);
                    for(int v = 0; v < piece[i][y].free_step.size(); v++)
                    {
                        Step st = piece[i][y].free_step[v];
                        pieceAtackW[st.y][st.x] = 1;
                    }
                }
                if(type == WHITE_ROOK)
                {
                    piece[i][y].free_step.clear();
                    attackRook(i, y);
                    for(int v = 0; v < piece[i][y].free_step.size(); v++)
                    {
                        Step st = piece[i][y].free_step[v];
                        pieceAtackW[st.y][st.x] = 1;
                    }
                }
                if(type == WHITE_QUEEN)
                {
                    piece[i][y].free_step.clear();
                    attackBishop(i, y);
                    attackRook(i, y);
                    for(int v = 0; v < piece[i][y].free_step.size(); v++)
                    {
                        Step st = piece[i][y].free_step[v];
                        pieceAtackW[st.y][st.x] = 1;
                    }
                }
                if(type == BLACK_KING && need_king)
                {
                    for(int v = 0; v < piece[i][y].free_step.size(); v++)
                    {
                        Step st = piece[i][y].free_step[v];
                        pieceAtackB[st.y][st.x] = 1;
                    }
                }
                if(type == BLACK_KNIGHT)
                {
                    for(int v = 0; v < piece[i][y].free_step.size(); v++)
                    {
                        Step st = piece[i][y].free_step[v];
                        pieceAtackB[st.y][st.x] = 1;
                    }
                }
                if(type == BLACK_PAWN)
                {
                    if(!need_pawn)
                    {
                        for(int v = 0; v < piece[i][y].free_attack_pawn.size(); v++)
                        {
                            Step st = piece[i][y].free_attack_pawn[v];
                            pieceAtackB[st.y][st.x] = 1;
                        }
                    }
                    if(need_pawn)
                    {
                        for(int v = 0; v < piece[i][y].free_step.size(); v++)
                        {
                            Step st = piece[i][y].free_step[v];
                            pieceAtackB[st.y][st.x] = 1;
                        }
                    }
                }
                if(type == BLACK_BISHOP)
                {
                    piece[i][y].free_step.clear();
                    attackBishop(i, y);
                    for(int v = 0; v < piece[i][y].free_step.size(); v++)
                    {
                        Step st = piece[i][y].free_step[v];
                        pieceAtackB[st.y][st.x] = 1;
                    }
                }
                if(type == BLACK_ROOK)
                {
                    piece[i][y].free_step.clear();
                    attackRook(i, y);
                    int si = piece[i][y].free_step.size();
                    int vec = 0;
                    while(vec < si)
                    {
                        Step st = piece[i][y].free_step[vec];
                        pieceAtackB[st.y][st.x] = 1;
                        ++vec;
                    }
                }
                if(type == BLACK_QUEEN)
                {
                    piece[i][y].free_step.clear();
                    attackBishop(i, y);
                    attackRook(i, y);
                    for(int v = 0; v < piece[i][y].free_step.size(); v++)
                    {
                        Step st = piece[i][y].free_step[v];
                        pieceAtackB[st.y][st.x] = 1;
                    }
                }
            }
        }
    }

}

int Board::check_checkmate(int type)
{
  int s = 0;
  if(type == BLACK_KING)
  {
      Step st_kingB(-1, -1);
      pieceUnderAtack();
      for(int i = 0; i < 8; i++)
      {
          for(int y = 0; y < 8; y++)
          {
              if(pieceAtackW[i][y] == 1 && piece[i][y].type == BLACK_KING)
              {
                  s = 2;
                  st_kingB.x = y; st_kingB.y = i;
                  break;
              }
          }
      }
      if(s == 0)
          return s;
      for(int i = 0; i < piece[st_kingB.y][st_kingB.x].free_step.size(); i++)
      {
          Step st1 = piece[st_kingB.y][st_kingB.x].free_step[i];
          if(pieceAtackW[st1.y][st1.x] == 0 && piece[st1.y][st1.x].type > 5)
          {
              s = 1;
              return s;
          }
      }
      s = 1;
      for(int i = 0; i < 8; i++)
      {
          for(int y = 0; y < 8; y++)
          {
              pieceUnderAtack(true, false);
              if(pieceAtackB[i][y] == 1 && piece[i][y].type != BLACK_KING)
              {
                  int buffer = piece[i][y].type;
                  piece[i][y].type = BLACK_PAWN;
                  pieceUnderAtack();
                  for(int i = 0; i < 8; i++)
                  {
                      for(int y = 0; y < 8; y++)
                      {
                          if(pieceAtackW[i][y] == 1 && piece[i][y].type == BLACK_KING)
                          {
                              s = 2;
                              st_kingB.x = y; st_kingB.y = i;
                              break;
                          }
                      }
                  }
                  piece[i][y].type = buffer;
                  if(s == 1)
                      return s;
                  s = 1;
              }
          }
      }
      if(s == 1)
          return 2;
  }
  if(type == WHITE_KING)
  {
      Step st_kingB(-1, -1);
      pieceUnderAtack();
      for(int i = 0; i < 8; i++)
      {
          for(int y = 0; y < 8; y++)
          {
                if(pieceAtackB[i][y] == 1 && piece[i][y].type == WHITE_KING)
              {
                  s = 2;
                  st_kingB.x = y; st_kingB.y = i;
                  break;
              }
          }
      }
      if(s == 0)
          return s;
      for(int i = 0; i < piece[st_kingB.y][st_kingB.x].free_step.size(); i++)
      {
          Step st1 = piece[st_kingB.y][st_kingB.x].free_step[i];
          if(pieceAtackB[st1.y][st1.x] == 0 && piece[st1.y][st1.x].type < 6)
          {
              s = 1;
              return s;
          }
      }
      for(int i = 0; i < 8; i++)
      {
          for(int y = 0; y < 8; y++)
          {
              pieceUnderAtack(true, false);
              if(pieceAtackW[i][y] == 1 && piece[i][y].type != WHITE_KING)
              {
                  int buffer = piece[i][y].type;
                  piece[i][y].type = WHITE_PAWN;
                  pieceUnderAtack();
                  for(int i = 0; i < 8; i++)
                  {
                      for(int y = 0; y < 8; y++)
                      {
                          if(pieceAtackB[i][y] == 1 && piece[i][y].type == WHITE_KING)
                          {
                              s = 2;
                              st_kingB.x = y; st_kingB.y = i;
                              break;
                          }
                      }
                  }
                  piece[i][y].type = buffer;
                  if(s == 1)
                      return 1;
                  s = 1;
              }
          }
      }
      if(s == 1)
          return 2;
  }
}


void Board::attackBishop(int index_x, int index_y)
{
    int i = piece[index_x][index_y].st->x, t = piece[index_x][index_y].st->y;
    i--;
    t--;
    while(i >= 0 && t >= 0 )
    {

        if(piece[t][i].type == ZERO)
        {
            Step st(i, t);
            piece[index_x][index_y].free_step.push_back(st);
        }
        else
        {
            Step st(i, t);
            piece[index_x][index_y].free_step.push_back(st);
            break;
        }
        i--;
        t--;
    }
    i = piece[index_x][index_y].st->x, t = piece[index_x][index_y].st->y;
    i++;
    t--;
    while(i < 8 && t >= 0)
    {

        if(piece[t][i].type == ZERO)
        {
            Step st(i, t);
            piece[index_x][index_y].free_step.push_back(st);
        }
        else
        {
            Step st(i, t);
            piece[index_x][index_y].free_step.push_back(st);
            break;
        }
        i++;
        t--;
    }
    i = piece[index_x][index_y].st->x, t = piece[index_x][index_y].st->y;
    i--;
    t++;
    while(i >= 0 && t < 8)
    {

        if(piece[t][i].type == ZERO)
        {
            Step st(i, t);
            piece[index_x][index_y].free_step.push_back(st);
        }
        else
        {
            Step st(i, t);
            piece[index_x][index_y].free_step.push_back(st);
            break;
        }
        i--;
        t++;
    }
    i = piece[index_x][index_y].st->x, t = piece[index_x][index_y].st->y;
    i++;
    t++;
    while(i < 8 && t < 8)
    {

        if(piece[t][i].type == ZERO)
        {
            Step st(i, t);
            piece[index_x][index_y].free_step.push_back(st);

        }
        else
        {
            Step st(i, t);
            piece[index_x][index_y].free_step.push_back(st);
            break;
        }
        i++;
        t++;
    }

}

void Board::attackRook(int index_x, int index_y)
{
    int i = piece[index_x][index_y].st->x, t = piece[index_x][index_y].st->y;
    --i;
    while(i >= 0)
    {
        if(piece[index_x][i].type == ZERO)
        {
            Step st(i, index_x);
            piece[index_x][index_y].free_step.push_back(st);

        }
        else
        {
            Step st(i, index_x);
            piece[index_x][index_y].free_step.push_back(st);
            break;
        }
        --i;
    }
    i = piece[index_x][index_y].st->x, t = piece[index_x][index_y].st->y;
    ++i;
    while(i < 8)
    {

        if(piece[index_x][i].type == ZERO)
        {
            Step st(i, index_x);
            piece[index_x][index_y].free_step.push_back(st);

        }
        else
        {
            Step st(i, index_x);
            piece[index_x][index_y].free_step.push_back(st);
            break;
        }
        ++i;
    }
    i = piece[index_x][index_y].st->x, t = piece[index_x][index_y].st->y;
    ++t;
    while(t < 8)
    {

        if(piece[t][index_y].type == ZERO)
        {
            Step st(index_y, t);
            piece[index_x][index_y].free_step.push_back(st);
        }
        else
        {
            Step st(index_y, t);
            piece[index_x][index_y].free_step.push_back(st);
            break;
        }
        ++t;
    }
    i = piece[index_x][index_y].st->x, t = piece[index_x][index_y].st->y;
    --t;
    while(t >= 0)
    {

        if(piece[t][index_y].type == ZERO)
        {
            Step st(index_y, t);
            piece[index_x][index_y].free_step.push_back(st);
        }
        else
        {
            Step st(index_y, t);
            piece[index_x][index_y].free_step.push_back(st);
            break;
        }
        --t;
    }
}

void Board::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(start_step->x == -1 && start_step->y == -1)
    {
        QPointF p = event->scenePos();
        int x1 =p.x(), y1 = p.y();
        start_step->x = x1/62.5;
        start_step->y = y1/62.5;
        qDebug() << QString::number(start_step->x) + "start";
        qDebug() << QString::number(start_step->y) + "start";
    }
    else if(end_step->x == -1 && end_step->y == -1)
    {
        QPointF p = event->scenePos();
        int x1 = p.x(), y1 = p.y();
        end_step->x = x1/62.5;
        end_step->y = y1/62.5;
        qDebug() << QString::number(end_step->x) + "end";
        qDebug() << QString::number(end_step->y) + "end";
    }

    if(start_step->x != -1 && start_step->y != -1 && end_step->x != -1 && end_step->y != -1 && start_step != end_step)
    {
        movePiece();
        start_step->x = -1;
        start_step->y = -1;
        end_step->x = -1;
        end_step->y = -1;
    }

}


