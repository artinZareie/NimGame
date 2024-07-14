#include "Screen.h"
#include "Constants.h"
#include "Game.h"
#include "Utils.h"
#include <stdio.h>

enum MainMenuSelection MainMenuPrinter(void) {
  enum MainMenuSelection selectedNum = PVPOption;
  while (true) {
    ClearScreen();

    const int messageLen = strlen(WELCOME_MESSAGE);
    const int mainmenuLen = strlen(MAINMENU_MESSAGE);

    for (int i = 0; i < SCREEN_WDITH / 2 - messageLen / 2; i++) {
      putchar(' ');
    }

    printf("%s\n\n\n", WELCOME_MESSAGE);

    printf("%s\n", MAINMENU_MESSAGE);

    for (int i = 0; i < NO_MAINMENU_OPTIONS; i++) {
      if (i == selectedNum) {
        printf("[*] %s\n", MainMenuOptionMessages[i]);
      } else {
        printf("[ ] %s\n", MainMenuOptionMessages[i]);
      }
    }

    char pressedKey = NonCanonicalGetChar();

    if (pressedKey == 'w' || pressedKey == 'W') {
      selectedNum =
          ((long long signed int)selectedNum - 1 + NO_MAINMENU_OPTIONS) %
          NO_MAINMENU_OPTIONS;
    } else if (pressedKey == 's' || pressedKey == 'S') {
      selectedNum = (selectedNum + 1) % NO_MAINMENU_OPTIONS;
    } else if (pressedKey == '\n') {
      break;
    }
  }

  printf("\n\n\nNavigating to: %s\n", MainMenuOptionMessages[selectedNum]);
  CorssPlatformSleep(1);

  return selectedNum;
}

struct GameConfig GameConfiguration(enum MainMenuSelection gameType) {
  if (gameType < 0 || gameType > CVCOption) {
    printf("Really?!");
    exit(-1);
  }

  struct GameConfig cfg;
  ResetGameConfig(&cfg);

  ClearScreen();
  printf("%s\n", CONFIGMENU_MESSAGE);

  while (true) {
    ClearScreen();
    printf("%s\n", CONFIGMENU_MESSAGE);
    printf("\n%s\n", CONFIGMENU_LEVEL_MESSAGE);

    printf("Level Difficalty:\t\t");

    printf("[#");
    for (int i = 0; i < cfg.level; i++) {
      putchar('#');
    }

    for (int i = NO_MAX_LEVELS - 1; i > cfg.level; i--)
      putchar(' ');
    putchar(']');
    printf("\t%d", (int)cfg.level + 1);

    char pressedKey = NonCanonicalGetChar();

    if (pressedKey == '\n')
      break;
    else if (pressedKey == 'd' || pressedKey == 'D') {
      cfg.level = min_int(NO_MAX_LEVELS - 1, cfg.level + 1);
    } else if (pressedKey == 'a' || pressedKey == 'A') {
      cfg.level = max_int(0, cfg.level - 1);
    }
  }

  char buff[MAX_BUFFER_SIZE];

  return cfg;
}

void ClearScreen(void) { system(CLEAN_COMMAND); }

// Since getch() is only available on windows and ncurses is not available on
// windows, I again am forced to do this...
#if defined(_WIN32) || defined(__MINGW32__) || defined(__CYGWIN__)

char NonCanonicalGetChar(void) { return getch(); }
void CorssPlatformSleep(int amount) { Sleep(amount); }

#else

// Some weird POSIX APIs:)
char NonCanonicalGetChar(void) {
  char buf = 0;
  struct termios old = {0};
  fflush(stdout);
  if (tcgetattr(0, &old) < 0)
    perror("tcsetattr()");
  old.c_lflag &= ~ICANON;
  old.c_lflag &= ~ECHO;
  old.c_cc[VMIN] = 1;
  old.c_cc[VTIME] = 0;
  if (tcsetattr(0, TCSANOW, &old) < 0)
    perror("tcsetattr ICANON");
  if (read(0, &buf, 1) < 0)
    perror("read()");
  old.c_lflag |= ICANON;
  old.c_lflag |= ECHO;
  if (tcsetattr(0, TCSADRAIN, &old) < 0)
    perror("tcsetattr ~ICANON");
  return buf;
}

void CorssPlatformSleep(int amount) { sleep(amount); }

#endif
