#pragma once
#include "Constants.h"
#include "Game.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32) || defined(__MINGW32__) || defined(__CYGWIN__)

#include <Windows.h>
#include <conio.h>

#else

#include <termios.h>
#include <unistd.h>

#endif

// Menus
enum MainMenuSelection MainMenuPrinter(void);
struct GameConfig GameConfiguration(enum MainMenuSelection gameType);

// Game
void GameBoardDrawer(const struct GameBoard *board, int stagedDraw);
void WinScreen(const struct GameBoard *board);

// Game drawer helpers
void FillScreen(const struct GameBoard *board,
                char screen[SCREEN_HEIGHT][SCREEN_WDITH]);
void ClearBoardScreen(char screen[SCREEN_HEIGHT][SCREEN_WDITH]);

// Helper functions
void ClearScreen(void);
char NonCanonicalGetChar();
void CrossPlatformSleep(int amount);
void SetBackgroundColorWhite(char c);
