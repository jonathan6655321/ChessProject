CC = gcc
OBJS = main.o CommandLineGame.o mainGui.o Game.o consoleRendering.o GameBoard.o Pieces.o ArrayUtils.o Moves.o MiniMax.o XmlUtils.o Parser.o  GuiManager.o  GameWindow.o  GameBoardControl.o  SDLHelperFunctions.o  MainWindow.o  LoadGameWindow.o  NewGameWindow.o

EXEC = chessprog
CC_COMP_FLAG = -g -std=c99 -Wall -Wextra \
-Werror -pedantic-errors
SDL_COMP_FLAG = -I/usr/local/lib/sdl_2.0.5/include/SDL2 -D_REENTRANT
SDL_LIB = -L/usr/local/lib/sdl_2.0.5/lib -Wl,-rpath,/usr/local/lib/sdl_2.0.5/lib -Wl,--enable-new-dtags -lSDL2 -lSDL2main

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(SDL_LIB) -o $@
main.o: main.c Gui/mainGui.h CommandLineGame.h 
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
CommandLineGame.o: CommandLineGame.c CommandLineGame.h Game.h Parser.h Messages.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
Game.o: Game.c Game.h consoleRendering.h Moves.h GameBoard.h MiniMax.h constants.h XmlUtils.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
consoleRendering.o: consoleRendering.c consoleRendering.h GameBoard.h Pieces.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
GameBoard.o: GameBoard.c GameBoard.h Pieces.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
Pieces.o: Pieces.c Pieces.h constants.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
Moves.o: Moves.c Moves.h GameBoard.h consoleRendering.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
MiniMax.o: MiniMax.c MiniMax.h GameBoard.h Moves.h Pieces.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
ArrayUtils.o: ArrayUtils.c ArrayUtils.h constants.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
XmlUtils.o: XmlUtils.c XmlUtils.h Pieces.h GameBoard.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
Parser.o: Parser.c Parser.h Game.h CommandLineCommands.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
mainGui.o: Gui/mainGui.c Gui/mainGui.h Gui/GuiManager.h Gui/Events.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c Gui/$*.c
GuiManager.o: Gui/GuiManager.c Gui/GuiManager.h Gui/Events.h Gui/GameWindow.h Gui/MainWindow.h Gui/LoadGameWindow.h Gui/NewGameWindow.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c Gui/$*.c
GameWindow.o: Gui/GameWindow.c Gui/GameWindow.h Gui/Events.h Gui/GameBoardControl.h Gui/Constants.h Gui/SDLHelperFunctions.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c Gui/$*.c
GameBoardControl.o: Gui/GameBoardControl.c Gui/GameBoardControl.h Gui/Events.h Gui/SDLHelperFunctions.h Gui/Constants.h Game.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c Gui/$*.c
SDLHelperFunctions.o: Gui/SDLHelperFunctions.c Gui/SDLHelperFunctions.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c Gui/$*.c
MainWindow.o: Gui/MainWindow.c Gui/MainWindow.h Gui/Events.h Gui/Constants.h Gui/SDLHelperFunctions.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c Gui/$*.c
LoadGameWindow.o: Gui/LoadGameWindow.c Gui/LoadGameWindow.h Gui/Events.h Gui/Constants.h Gui/SDLHelperFunctions.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c Gui/$*.c
NewGameWindow.o: Gui/NewGameWindow.c Gui/NewGameWindow.h Gui/Events.h Gui/Constants.h Gui/SDLHelperFunctions.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c Gui/$*.c
clean:
	rm -f $(OBJS) $(EXEC)