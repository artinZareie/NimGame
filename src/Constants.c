#include "Constants.h"

const int MAX_PIECES = 10;

// I use these variables to determine what is the size of window. However, I'd
// ratehr use something like ncurses to get size of entier terminal, but this is
// not a commercial project, so I guess this is enough...
const int SCREEN_WDITH = 100;
const int SCREEN_HEIGHT = 40;

const int MAX_FRAME_RATE = 30;

const size_t MAX_BUFFER_SIZE = 32;

// String constants
const char *const APP_NAME = "Nim Game";

const char *const WELCOME_MESSAGE = "Welcome to this Nim Game Application!";
const char *const MAINMENU_MESSAGE =
    "Please select one of the following options (Navigate with WASD)";
const char *const MAINMENU_ERROR_MESSAGE =
    "Invalid selection, please try again!";

const char *const CONFIGMENU_MESSAGE =
    "Now, you are going to setup a new game!";
const char *const CONFIGMENU_LEVEL_MESSAGE =
    "Here you can edit level's difficulty";
const char *const CONFIGMENU_FIRST_PLAYER_PROMPT_MESSAGE =
    "Here you can edit first player's information.";
const char *const CONFIGMENU_SECOND_PLAYER_PROMPT_MESSAGE =
    "Here you can edit second player's information.";
const char *const CONFIGMENU_COMPUTER_LEVEL_MESSAGE =
    "Please set Computer Level";
const char *const CONFIGMENU_PLAYER1_NAME_MESSAGE =
    "Please first enter first player's name";
const char *const CONFIGMENU_PLAYER2_NAME_MESSAGE =
    "Please first enter second player's name";
const char *const CONFIGMENU_PLAYER1_MESSAGE =
    "Here you can change information of the first player";
const char *const CONFIGMENU_PLAYER2_MESSAGE =
    "Here you can change information of the second player";
const char *const CONFIGMENU_FILE_MESSAGE =
    "Please enter file name (No space is allowed in the file name)";

const char *const DEFAULT_COMPUTER_NAME = "Computer";

const char *const PVP_MESSAGE = "New game: Human vs Human";
const char *const PVF_MESSAGE = "New game: Human vs File";
const char *const PVC_MESSAGE = "New game: Human vs Computer";
const char *const CVC_MESSAGE = "New game: Computer vs Computer";
const char *const LOAD_GAME_MESSAGE = "Load Game from database";

const char *const CONGRATS_MESSAGE = "Congrats! You won";

const char *const FIRST_PLAYER_WON =
    " _____ _          _     ____  _                        __        __       "
    "   \n|  ___(_)_ __ ___| |_  |  _ \\| | __ _ _   _  ___ _ __  \\ \\      / "
    "/__  _ __  \n| |_  | | '__/ __| __| | |_) | |/ _` | | | |/ _ \\ '__|  "
    "\\ \\ /\\ / / _ \\| '_ \\ \n|  _| | | |  \\__ \\ |_  |  __/| | (_| | |_| "
    "|  __/ "
    "|      \\ V  V / (_) | | | |\n|_|   |_|_|  |___/\\__| |_|   "
    "|_|\\__,_|\\__, "
    "|\\___|_|       \\_/\\_/ \\___/|_| |_|\n                                  "
    "    "
    "|___/                                  ";
const char *const SECOND_PLAYER_WON =
    " ____                           _   ____  _                        __     "
    "   __          \n/ ___|  ___  ___ ___  _ __   __| | |  _ \\| | __ _ _   _ "
    " ___ _ __  \\ \\      / /__  _ __  \n\\___ \\ / _ \\/ __/ _ \\| '_ \\ / "
    "_` | | |_) | |/ _` | | | |/ _ \\ '__|  \\ \\ /\\ / / _ \\| '_ \\ \n ___) "
    "|  __/ (_| (_) | | | | (_| | |  __/| | (_| | |_| |  __/ |      \\ V  V / "
    "(_) | | | |\n|____/ \\___|\\___\\___/|_| |_|\\__,_| |_|   |_|\\__,_|\\__, "
    "|\\___|_|       \\_/\\_/ \\___/|_| |_|\n                                  "
    "                |___/                                  \n";

const size_t NO_MAINMENU_OPTIONS = 5;
const char *const MainMenuOptionMessages[5] = {
    PVP_MESSAGE, PVF_MESSAGE, PVC_MESSAGE, CVC_MESSAGE, LOAD_GAME_MESSAGE};

const size_t NO_MAX_HARDNESS = 3;
const size_t NO_COMPUTER_LEVELS = 3;
const char *const ComputerLevelMessages[3] = {"Easy", "Medium", "Hard"};

const size_t NO_MAX_LEVELS = 5;
const int NoColsPerLevel[5] = {3, 5, 3, 4, 5};
const bool SingleRowPerLevel[5] = {true, true, false, false, false};

const int COL_WIDTH = 2;
const int COL_BASE_WIDTH = 4;
const int COL_HORIZONTAL_MARGIN = 2;
const int COL_VERTICAL_MARGIN = 2;

// For windows, clear command is not available, since I expect that graders and
// professor are using window and I am developing this on linux, I put this
// directive here.
#if defined(_WIN32) || defined(__MINGW32__) || defined(__CYGWIN__)

const char *const CLEAN_COMMAND = "cls";

#else

const char *const CLEAN_COMMAND = "clear";

#endif
