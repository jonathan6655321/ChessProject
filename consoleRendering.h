//
// Created by Jonathan on 7/19/2017.
//

#ifndef CHESSPROJECT_CONSOLERENDERING_H
#define CHESSPROJECT_CONSOLERENDERING_H

#include "GameBoard.h"
#include "Pieces.h"

/*
 * according to specifications in PDF
 */
void printBoard(GameBoard *gameBoard, Color player1Color);

/*
 * black -> white
 * white -> black
 */
Color getOppositeColor(Color color);

/*
 * get chars according to conventions: black is upper case
 */
char getPieceChar(Piece * piece, Color player1Color);







#endif //CHESSPROJECT_CONSOLERENDERING_H
