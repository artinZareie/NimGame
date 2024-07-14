#pragma once
#include "Constants.h"
#include "Game.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32) || defined(__MINGW32__) || defined(__CYGWIN__)

#include <Windows.h>

#else

#include <termios.h>
#include <unistd.h>

#endif

// Menus
enum MainMenuSelection MainMenuPrinter(void);
struct GameConfig GameConfiguration(enum MainMenuSelection gameType);

// Helper functions
void ClearScreen(void);
char NonCanonicalGetChar();
void CorssPlatformSleep(int amount);
