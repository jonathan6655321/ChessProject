//
// Created by Jonathan on 7/18/2017.
//

#include "GameBoard.h"
#include "Pieces.h"
#include "consoleRendering.h"

int main( int argc, char **argv )
{
    GameBoard gameBoard;
    initGame(&gameBoard, White);
    printBoard(&gameBoard,White);

    printf("\n\n");
    movePiece('1','A', '3','C', &gameBoard);
    printBoard(&gameBoard,White);

    printf("\n\n");
    movePiece('1','C', '4','C', &gameBoard);
    printBoard(&gameBoard,White);

    printf("\n\n");
    movePiece('8','E', '1','A', &gameBoard);
    printBoard(&gameBoard,White);

    printf("\n\n");
    movePiece('7','H', '8','C', &gameBoard);
    printBoard(&gameBoard,White);


}