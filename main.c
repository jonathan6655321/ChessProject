////
//// Created by Jonathan on 7/18/2017.
////
#include <stdlib.h>
#include <string.h>
#include "CommandLineGame.h"
// TODO:#include "Gui/mainGui.h"

int main(int argc, char **argv) {
	if (argc == 2 && strcmp("-g", argv[1]) == 0) {
		return 0;//TODO:MainGuiLoop();
	} else {
		return commandLineGameLoop();
	}
}
