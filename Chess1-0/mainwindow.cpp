#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //ui->setupUi(this);
    b = new Board();
    connect(b, &Board::my_signal, this, &MainWindow::printBoard);
    connect(b, &Board::new_signal, this, &MainWindow::printWiner);
    b->setSceneRect(0, 0, 500, 500);
    QGraphicsPixmapItem* item1 = b->addPixmap(QPixmap("C:\\Users\\Jarvis\\Documents\\Chess1-0\\chess.png"));
    item1->setOffset(0, 0);
    for(int i = 0; i < 8; i++)
    {
        for(int y = 0; y < 8; y++)
        {
            if(b->piece[i][y].type != ZERO)
            {
                QGraphicsPixmapItem* item2 = b->addPixmap(b->piece[i][y].filename);
                item2->setOffset((b->piece[i][y].st->x*62.5) + 14,(b->piece[i][y].st->y*62.5) + 13);
            }
        }
    }
    view.setScene(b);
    view.show();
}

void MainWindow::printBoard()
{
    b->clear();
    QGraphicsPixmapItem* item1 = b->addPixmap(QPixmap("C:\\Users\\Jarvis\\Documents\\Chess1-0\\chess.png"));
    item1->setOffset(0, 0);
    for(int i = 0; i < 8; i++)
    {
        for(int y = 0; y < 8; y++)
        {
            if(b->piece[i][y].type != ZERO)
            {
                QGraphicsPixmapItem* item2 = b->addPixmap(b->piece[i][y].filename);
                item2->setOffset((b->piece[i][y].st->x*62.5) + 14,(b->piece[i][y].st->y*62.5) + 13);
            }
        }
    }
    view.setScene(b);
    view.show();
}

void MainWindow::printWiner()
{
    b->clear();
    if(b->win_black)
    {
        QGraphicsPixmapItem* item1 = b->addPixmap(QPixmap("C:\\Users\\Jarvis\\Documents\\Chess1-0\\black-win.jpg"));
        item1->setOffset(0, 0);
    }
    if(b->win_white)
    {
        view.resize(375, 500);
        resize(375, 500);
        QGraphicsPixmapItem* item1 = b->addPixmap(QPixmap("C:\\Users\\Jarvis\\Documents\\Chess1-0\\white-win.jpg"));
        item1->setOffset(0, 0);
    }
    view.setScene(b);
    view.show();
}

MainWindow::~MainWindow()
{
    delete b;
}
