
// Created by Jonathan on 9/11/2017.
//


#include <time.h>
#include "MiniMax.h"

int main(int argc, char **argv) {

//    GameBoard gameBoard;
//    initGame(&gameBoard, White);
//    printBoard(&gameBoard, White);

//    printf("the mobility score is: %d", getMobilityScoreByPlayer(&gameBoard, Player1));

    MiniMaxMove move1;
    MiniMaxMove move2;
//
//    movePiece('8','E', '3', 'E', &gameBoard);
//    printBoard(&gameBoard,White);
//    minimax(&gameBoard,6, INT_MIN, INT_MAX, Player1, scoreFunction, &move1);
//    int fromLoc = getLocationIndexForPieceIndex(&gameBoard, move1.pieceIndex);
//    movePiece(getRowFromLocationIndex(fromLoc), getColFromLocationIndex(fromLoc),
//                  getRowFromLocationIndex(move1.toLocationIndex), getColFromLocationIndex(move1.toLocationIndex), &gameBoard);
//    printBoard(&gameBoard,White);
//    printf("done");

    for (int dif = 1; dif <=4; dif++)
    {
        GameBoard gameBoard;
        initGame(&gameBoard, White);

        int i = 0;
        while (1){
//
            if(i>200)
            {
                printf("Entered loop\n");
                break;
            }
//    for (int i = 0; i < 31; i++) {
            i++;
//            if (hasLegalMoves(Player1, &gameBoard) == FAIL) {
//                printf("Player %d has NO MOVES", Player1+1);
//            }
//            else {
//                printf("Player %d has MOVES", Player1+1);
//            }

//            printf("\nIs player 1 king threatened? %d", isKingThreatened(Player1, &gameBoard));
//            printf("\nIs player 2 king threatened? %d", isKingThreatened(Player2, &gameBoard));
            int fromLoc;
//            printf("\n********** PLAYER 1 MOVES: **************\n");

            time_t s1;
            s1 = time(NULL);

            minimax(&gameBoard, 5, INT_MIN, INT_MAX, Player1, amazingScoreFunction, &move1, 1);
            fromLoc = getLocationIndexForPieceIndex(&gameBoard, move1.pieceIndex);
            movePiece(getRowFromLocationIndex(fromLoc), getColFromLocationIndex(fromLoc),
                      getRowFromLocationIndex(move1.toLocationIndex), getColFromLocationIndex(move1.toLocationIndex),
                      &gameBoard);
//            printBoard(&gameBoard, White);

            time_t s2;
            s2 = time(NULL);

//            printf("time: %d seconds", s2 - s1);

            if(s2 - s1 > 9)
            {
                printf("\n\n!!!!!!!!!!!!!!!!!!!!!!!!! OVERTIME !!!!!!!!!!!!!!!!!!! \n\n");
//            return 0;
            }

            if (gameBoard.mapPieceIndexToLocationOnBoard[PLAYER_2_KING_INDEX] == NOT_IN_GAME) {
                printf("TURN %d\n", i);
                printf("\n$$$$$$$$$ PLAYER 1 WINS $$$$$$$$$$$$$\n");
                break;
            }

//            if (hasLegalMoves(Player2, &gameBoard) == FAIL)
//                printf("Player %d has NO MOVES", Player2+1);
//            else
//                printf("Player %d has MOVES", Player2+1);

//            printf("\nIs player 1 king threatened? %d", isKingThreatened(Player1, &gameBoard));
//            printf("\nIs player 2 king threatened? %d", isKingThreatened(Player2, &gameBoard));
//            printf("\n********** PLAYER 2 MOVES: **************\n");
            minimax(&gameBoard, dif, INT_MIN, INT_MAX, Player2, scoreFunction, &move2, 1);
            fromLoc = getLocationIndexForPieceIndex(&gameBoard, move2.pieceIndex);
            movePiece(getRowFromLocationIndex(fromLoc), getColFromLocationIndex(fromLoc),
                      getRowFromLocationIndex(move2.toLocationIndex), getColFromLocationIndex(move2.toLocationIndex),
                      &gameBoard);
//            printBoard(&gameBoard, White);

            if (gameBoard.mapPieceIndexToLocationOnBoard[PLAYER_1_KING_INDEX] == NOT_IN_GAME) {
                printf("TURN %d\n", i);
                printf("\n$$$$$$$$$ PLAYER 2 WINS $$$$$$$$$$$$$\n");
                break;
            }
        }
    }






    for(int dif = 1; dif <=4; dif++)
    {
        GameBoard gameBoard;
        initGame(&gameBoard, White);

        int i = 0;
        while (1){
//
            if(i>200)
            {
                printf("Entered loop\n");
                break;
            }
//    for (int i = 0; i < 31; i++) {
            i++;
//            if (hasLegalMoves(Player1, &gameBoard) == FAIL) {
//                printf("Player %d has NO MOVES", Player1+1);
//            }
//            else {
//                printf("Player %d has MOVES", Player1+1);
//            }

//            printf("\nIs player 1 king threatened? %d", isKingThreatened(Player1, &gameBoard));
//            printf("\nIs player 2 king threatened? %d", isKingThreatened(Player2, &gameBoard));
            int fromLoc;
//            printf("\n********** PLAYER 1 MOVES: **************\n");



            minimax(&gameBoard, dif, INT_MIN, INT_MAX, Player1, scoreFunction, &move1, 1);
            fromLoc = getLocationIndexForPieceIndex(&gameBoard, move1.pieceIndex);
            movePiece(getRowFromLocationIndex(fromLoc), getColFromLocationIndex(fromLoc),
                      getRowFromLocationIndex(move1.toLocationIndex), getColFromLocationIndex(move1.toLocationIndex),
                      &gameBoard);
//            printBoard(&gameBoard, White);



            if (gameBoard.mapPieceIndexToLocationOnBoard[PLAYER_2_KING_INDEX] == NOT_IN_GAME) {
                printf("TURN %d\n", i);
                printf("\n$$$$$$$$$ PLAYER 1 WINS $$$$$$$$$$$$$\n");
                break;
            }

//            if (hasLegalMoves(Player2, &gameBoard) == FAIL)
//                printf("Player %d has NO MOVES", Player2+1);
//            else
//                printf("Player %d has MOVES", Player2+1);

            time_t s1;
            s1 = time(NULL);
//            printf("\nIs player 1 king threatened? %d", isKingThreatened(Player1, &gameBoard));
//            printf("\nIs player 2 king threatened? %d", isKingThreatened(Player2, &gameBoard));
//            printf("\n********** PLAYER 2 MOVES: **************\n");
            minimax(&gameBoard, 5, INT_MIN, INT_MAX, Player2, amazingScoreFunction, &move2, 1);
            fromLoc = getLocationIndexForPieceIndex(&gameBoard, move2.pieceIndex);
            movePiece(getRowFromLocationIndex(fromLoc), getColFromLocationIndex(fromLoc),
                      getRowFromLocationIndex(move2.toLocationIndex), getColFromLocationIndex(move2.toLocationIndex),
                      &gameBoard);
//            printBoard(&gameBoard, White);

            time_t s2;
            s2 = time(NULL);

//            printf("time: %d seconds", s2 - s1);

            if(s2 - s1 > 9)
            {
                printf("\n\n!!!!!!!!!!!!!!!!!!!!!!!!! OVERTIME !!!!!!!!!!!!!!!!!!! \n\n");
//            return 0;
            }
            if (gameBoard.mapPieceIndexToLocationOnBoard[PLAYER_1_KING_INDEX] == NOT_IN_GAME) {
                printf("TURN %d\n", i);
                printf("\n$$$$$$$$$ PLAYER 2 WINS $$$$$$$$$$$$$\n");
                break;
            }


        }

    }



//
//    printf("\n****************************************\n");
//    printBoard(&gameBoard, White);


//    printLegalMovesForAllPieces(&gameBoard);
//
//    printf("\n\n");
//    movePiece('1','A', '4','E', &gameBoard);
//    printBoard(&gameBoard,White);
//
//    printf("\n\n");
//    movePiece('8','B', '6','C', &gameBoard);
//    printBoard(&gameBoard,White);
//
//    printf("\n\n");
//    movePiece('8','C', '3','C', &gameBoard);
//    printBoard(&gameBoard,White);
//
//
//    printLegalMovesForAllPieces(&gameBoard);

    return 0;
}
