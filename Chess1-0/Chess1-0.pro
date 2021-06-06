#-------------------------------------------------
#
# Project created by QtCreator 2021-05-26T23:08:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chess1-0
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    piece.cpp \
    board.cpp \
    bishop.cpp \
    knight.cpp \
    pawn.cpp \
    king.cpp \
    queen.cpp \
    rook.cpp \
    step.cpp

HEADERS  += mainwindow.h \
    piece.h \
    board.h \
    bishop.h \
    knight.h \
    pawn.h \
    king.h \
    queen.h \
    rook.h \
    step.h

FORMS    += mainwindow.ui
