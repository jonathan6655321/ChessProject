//
// Created by Jonathan on 7/18/2017.
//

#include "GameBoard.h"
#include "Pieces.h"
#include "consoleRendering.h"
#include "Moves.h"

int main( int argc, char **argv )
{
    GameBoard gameBoard;
    initGame(&gameBoard, White);
    printBoard(&gameBoard,White);

    printf("\n\n");
    movePiece('1','A', '4','E', &gameBoard);
    printBoard(&gameBoard,White);

    printLegalMovesForAllPieces(&gameBoard);


}