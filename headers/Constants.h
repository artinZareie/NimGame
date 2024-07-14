#pragma once
#include <stdlib.h>

extern const int MAX_PIECES;

extern const int SCREEN_WDITH;
extern const int SCREEN_HEIGHT;

extern const int MAX_FRAME_RATE;
extern const size_t MAX_BUFFER_SIZE;

extern const char *const APP_NAME;
extern const char *const WELCOME_MESSAGE;
extern const char *const MAINMENU_MESSAGE;
extern const char *const MAINMENU_ERROR_MESSAGE;

extern const char *const CONFIGMENU_MESSAGE;
extern const char *const CONFIGMENU_LEVEL_MESSAGE;
extern const char *const CONFIGMENU_PLAYER1_NAME_MESSAGE;
extern const char *const CONFIGMENU_PLAYER2_NAME_MESSAGE;
extern const char *const CONFIGMENU_PLAYER1_MESSAGE;
extern const char *const CONFIGMENU_PLAYER2_MESSAGE;

extern const char *const PVP_MESSAGE;
extern const char *const PVF_MESSAGE;
extern const char *const PVC_MESSAGE;
extern const char *const CVC_MESSAGE;
extern const char *const LOAD_GAME_MESSAGE;

extern const char *const MENU_SELECTOR;

extern const char *const CLEAN_COMMAND;

// Enums
enum MainMenuSelection {
  PVPOption,
  PVFOption,
  PVCOption,
  CVCOption,
  LoadGameOption
};

enum ControlDirection { UpDir, LeftDir, DownDir, RightDir, Done };

extern const size_t NO_MAINMENU_OPTIONS;
extern const char *const MainMenuOptionMessages[5];

extern const size_t NO_MAX_LEVELS;
extern const size_t NO_COMPUTER_LEVELS;
extern const char *const ComputerLevelMessages[3];
