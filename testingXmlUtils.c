////
//// Created by Jonathan on 9/11/2017.
////
//
//#include "GameBoard.h"
//#include "XmlUtils.h"
//#include "consoleRendering.h"
//
//int main(int argc, char **argv )
//{
//    GameBoard gameBoard;
//    initGame(&gameBoard, White);
//    Player player = Player1;
//    int gameMode = 1;
//    int dif = 1;
//    Color color = White;
//
//    printf("BEFORE:\n\n");
//    printBoard(&gameBoard,White);
//    saveGameToFile(&gameBoard, player, gameMode, dif, color, FILE_1_PATH);
//
//
//
//    GameBoard newGameBoard;
//    int newGameMode;
//    Player newPlayer;
//    int newDif;
//    Color newColor;
//    loadGameFromFile(&newGameBoard, &newPlayer, &newGameMode, &newDif, &newColor, FILE_1_PATH);
//
//    printf("\n\nAFTER:\n");
//    printf("players turn: %d\n", newPlayer);
//    printf("game mode: %d\n", newGameMode);
//    printf("difficulty: %d\n", newDif);
//    printf("color: %c\n", newColor);
//    printBoard(&gameBoard, White);
//
//    return 1;
//}