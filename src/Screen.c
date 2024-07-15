#include "Screen.h"
#include "Constants.h"
#include "Game.h"
#include "Utils.h"
#include <stdio.h>
#include <string.h>

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
  cfg.gameType = gameType;

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
  if (gameType == CVCOption) {
    cfg.player1Name =
        malloc((strlen(DEFAULT_COMPUTER_NAME) + 1) * sizeof(char));
    strcpy(cfg.player1Name, DEFAULT_COMPUTER_NAME);

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
      printf("\t%d\n", (int)cfg.level + 1);
      for (int i = 0; i < SCREEN_WDITH; i++) {
        putchar('-');
      }
      putchar('\n');

      printf("%s\n", CONFIGMENU_FIRST_PLAYER_PROMPT_MESSAGE);

      printf("%s:\t\t", CONFIGMENU_COMPUTER_LEVEL_MESSAGE);

      printf("[#");
      for (int i = 0; i < cfg.computer1Hardness; i++) {
        putchar('#');
      }

      for (int i = NO_MAX_HARDNESS - 1; i > cfg.computer1Hardness; i--)
        putchar(' ');
      putchar(']');
      printf("\t%s", ComputerLevelMessages[cfg.computer1Hardness]);

      char pressedKey = NonCanonicalGetChar();

      if (pressedKey == '\n')
        break;
      else if (pressedKey == 'd' || pressedKey == 'D') {
        cfg.computer1Hardness =
            min_int(NO_MAX_HARDNESS - 1, cfg.computer1Hardness + 1);
      } else if (pressedKey == 'a' || pressedKey == 'A') {
        cfg.computer1Hardness = max_int(0, cfg.computer1Hardness - 1);
      }
    }
  } else {
    int buffLen = 0;
    buff[buffLen] = '\0';
    char currChar = '\0';

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
    printf("\t%d\n", (int)cfg.level + 1);
    for (int i = 0; i < SCREEN_WDITH; i++) {
      putchar('-');
    }
    putchar('\n');

    printf("%s\n", CONFIGMENU_FIRST_PLAYER_PROMPT_MESSAGE);

    printf("%s:\t\t", CONFIGMENU_PLAYER1_NAME_MESSAGE);
    scanf("%s", buff);

    cfg.player1Name = malloc((strlen(buff) + 1) * sizeof(char));
    strcpy(cfg.player1Name, buff);
  }

  if (gameType == PVPOption) {
    int buffLen = 0;
    buff[buffLen] = '\0';
    char currChar = '\0';

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
    printf("\t%d\n", (int)cfg.level + 1);
    for (int i = 0; i < SCREEN_WDITH; i++) {
      putchar('-');
    }
    putchar('\n');

    printf("%s\n", CONFIGMENU_FIRST_PLAYER_PROMPT_MESSAGE);

    printf("%s:\t\t%s", CONFIGMENU_PLAYER1_NAME_MESSAGE, cfg.player1Name);

    putchar('\n');
    for (int i = 0; i < SCREEN_WDITH; i++) {
      putchar('-');
    }
    putchar('\n');

    printf("%s\n", CONFIGMENU_SECOND_PLAYER_PROMPT_MESSAGE);

    printf("%s:\t\t", CONFIGMENU_PLAYER2_NAME_MESSAGE);
    scanf("%s", buff);

    cfg.player2Name = malloc((strlen(buff) + 1) * sizeof(char));
    strcpy(cfg.player2Name, buff);
  } else if (gameType == PVFOption) {
    int buffLen = 0;
    buff[buffLen] = '\0';
    char currChar = '\0';

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
    printf("\t%d\n", (int)cfg.level + 1);
    for (int i = 0; i < SCREEN_WDITH; i++) {
      putchar('-');
    }
    putchar('\n');

    printf("%s\n", CONFIGMENU_FIRST_PLAYER_PROMPT_MESSAGE);

    printf("%s:\t\t%s", CONFIGMENU_PLAYER1_NAME_MESSAGE, cfg.player1Name);

    putchar('\n');
    for (int i = 0; i < SCREEN_WDITH; i++) {
      putchar('-');
    }
    putchar('\n');

    printf("%s\n", CONFIGMENU_SECOND_PLAYER_PROMPT_MESSAGE);

    printf("%s:\t\t", CONFIGMENU_FILE_MESSAGE);
    scanf("%s", buff);

    cfg.player2Name = malloc((strlen(buff) + 1) * sizeof(char));
    strcpy(cfg.player2Name, buff);
  } else if (gameType == PVCOption) {
    cfg.player2Name =
        malloc((strlen(DEFAULT_COMPUTER_NAME) + 1) * sizeof(char));
    strcpy(cfg.player2Name, DEFAULT_COMPUTER_NAME);

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
      printf("\t%d\n", (int)cfg.level + 1);
      for (int i = 0; i < SCREEN_WDITH; i++) {
        putchar('-');
      }
      putchar('\n');

      printf("%s\n", CONFIGMENU_FIRST_PLAYER_PROMPT_MESSAGE);

      printf("%s:\t\t%s", CONFIGMENU_PLAYER1_NAME_MESSAGE, cfg.player1Name);

      putchar('\n');
      for (int i = 0; i < SCREEN_WDITH; i++) {
        putchar('-');
      }
      putchar('\n');

      printf("%s\n", CONFIGMENU_SECOND_PLAYER_PROMPT_MESSAGE);

      printf("%s:\t\t", CONFIGMENU_COMPUTER_LEVEL_MESSAGE);

      printf("[#");
      for (int i = 0; i < cfg.computer2Hardness; i++) {
        putchar('#');
      }

      for (int i = NO_MAX_HARDNESS - 1; i > cfg.computer2Hardness; i--)
        putchar(' ');
      putchar(']');
      printf("\t%s", ComputerLevelMessages[cfg.computer2Hardness]);

      char pressedKey = NonCanonicalGetChar();

      if (pressedKey == '\n')
        break;
      else if (pressedKey == 'd' || pressedKey == 'D') {
        cfg.computer1Hardness =
            min_int(NO_MAX_HARDNESS - 1, cfg.computer2Hardness + 1);
      } else if (pressedKey == 'a' || pressedKey == 'A') {
        cfg.computer1Hardness = max_int(0, cfg.computer2Hardness - 1);
      }
    }
  } else {
    cfg.player2Name =
        malloc((strlen(DEFAULT_COMPUTER_NAME) + 1) * sizeof(char));
    strcpy(cfg.player2Name, DEFAULT_COMPUTER_NAME);

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
      printf("\t%d\n", (int)cfg.level + 1);
      for (int i = 0; i < SCREEN_WDITH; i++) {
        putchar('-');
      }
      putchar('\n');

      printf("%s\n", CONFIGMENU_FIRST_PLAYER_PROMPT_MESSAGE);

      printf("%s:\t\t", CONFIGMENU_COMPUTER_LEVEL_MESSAGE);

      printf("[#");
      for (int i = 0; i < cfg.computer1Hardness; i++) {
        putchar('#');
      }

      for (int i = NO_MAX_HARDNESS - 1; i > cfg.computer1Hardness; i--)
        putchar(' ');
      putchar(']');
      printf("\t%s", ComputerLevelMessages[cfg.computer1Hardness]);

      putchar('\n');
      for (int i = 0; i < SCREEN_WDITH; i++) {
        putchar('-');
      }
      putchar('\n');

      printf("%s\n", CONFIGMENU_SECOND_PLAYER_PROMPT_MESSAGE);

      printf("%s:\t\t", CONFIGMENU_COMPUTER_LEVEL_MESSAGE);

      printf("[#");
      for (int i = 0; i < cfg.computer2Hardness; i++) {
        putchar('#');
      }

      for (int i = NO_MAX_HARDNESS - 1; i > cfg.computer2Hardness; i--)
        putchar(' ');
      putchar(']');
      printf("\t%s", ComputerLevelMessages[cfg.computer2Hardness]);

      char pressedKey = NonCanonicalGetChar();

      if (pressedKey == '\n')
        break;
      else if (pressedKey == 'd' || pressedKey == 'D') {
        cfg.computer1Hardness =
            min_int(NO_MAX_HARDNESS - 1, cfg.computer2Hardness + 1);
      } else if (pressedKey == 'a' || pressedKey == 'A') {
        cfg.computer1Hardness = max_int(0, cfg.computer2Hardness - 1);
      }
    }
  }

  return cfg;
}

void GameBoardDrawer(struct GameBoard *board) {
  ClearScreen();
  char screen[SCREEN_HEIGHT][SCREEN_WDITH];
  FillScreen(board, screen);

  int fillableCols = board->noCols * (COL_BASE_WIDTH + COL_HORIZONTAL_MARGIN);
  for (int j = 0; j <= MAX_PIECES + 1; j++) {
    for (int i = 0; i < fillableCols; i++) {
      int col = i / (COL_BASE_WIDTH + COL_VERTICAL_MARGIN);

      if (0 == board->activeRow && col == board->activeCol &&
          screen[j][i] == '#') {
        SetBackgroundColorWhite(screen[j][i]);
      } else {
        putchar(screen[j][i]);
      }
    }
    putchar('\n');
  }

  if (board->singleRow)
    return;

  for (int j = MAX_PIECES + 2; j <= 2 * MAX_PIECES + COL_VERTICAL_MARGIN + 1;
       j++) {
    for (int i = 0; i < fillableCols; i++) {
      int col = i / (COL_BASE_WIDTH + COL_VERTICAL_MARGIN);

      if (1 == board->activeRow && col == board->activeCol &&
          screen[j][i] == '#') {
        SetBackgroundColorWhite(screen[j][i]);
      } else {
        putchar(screen[j][i]);
      }
    }
    putchar('\n');
  }
}

void ClearBoardScreen(char screen[SCREEN_HEIGHT][SCREEN_WDITH]) {
  for (int i = 0; i < SCREEN_HEIGHT; i++) {
    for (int j = 0; j < SCREEN_WDITH; j++) {
      screen[i][j] = '\0';
    }
  }
}

void FillScreen(struct GameBoard *board,
                char screen[SCREEN_HEIGHT][SCREEN_WDITH]) {
  int fillableCols = board->noCols * (COL_BASE_WIDTH + COL_HORIZONTAL_MARGIN);
  ClearBoardScreen(screen);

  for (int i = 0; i < fillableCols; i++) {
    int offest = i % (COL_BASE_WIDTH + COL_HORIZONTAL_MARGIN);

    for (int j = MAX_PIECES + 1; j >= 0; j--) {
      if (j == 0) {
        screen[j][i] = ' ';
        continue;
      }

      if (offest < COL_HORIZONTAL_MARGIN) {
        screen[j][i] = ' ';
        continue;
      }

      if (j == MAX_PIECES + 1) {
        screen[j][i] = '^';
        continue;
      }

      int height = MAX_PIECES + 1 - j;
      if (height <=
              board->board[0][i / (COL_BASE_WIDTH + COL_HORIZONTAL_MARGIN)] &&
          offest >= (COL_HORIZONTAL_MARGIN + COL_WIDTH / 2) &&
          offest <= (COL_HORIZONTAL_MARGIN + COL_WIDTH)) {
        screen[j][i] = '#';
      } else {
        screen[j][i] = ' ';
      }
    }
  }

  if (!board->singleRow) {
    for (int i = 0; i < fillableCols; i++) {
      for (int j = MAX_PIECES + 2; j < MAX_PIECES + 2 + COL_VERTICAL_MARGIN;
           j++) {
        screen[j][i] = ' ';
      }
    }

    for (int i = 0; i < fillableCols; i++) {
      int offest = i % (COL_BASE_WIDTH + COL_HORIZONTAL_MARGIN);

      for (int j = MAX_PIECES + 2 + COL_VERTICAL_MARGIN;
           j <= 2 * MAX_PIECES + 1 + COL_VERTICAL_MARGIN; j++) {
        if (j == MAX_PIECES + 2 + COL_VERTICAL_MARGIN) {
          screen[j][i] = ' ';
          continue;
        }

        if (offest < COL_HORIZONTAL_MARGIN) {
          screen[j][i] = ' ';
          continue;
        }

        if (j == 2 * MAX_PIECES + 1 + COL_VERTICAL_MARGIN) {
          screen[j][i] = '^';
          continue;
        }

        int height = 2 * MAX_PIECES + COL_VERTICAL_MARGIN - j + 1;
        if (height <=
                board->board[1][i / (COL_BASE_WIDTH + COL_HORIZONTAL_MARGIN)] &&
            offest >= (COL_HORIZONTAL_MARGIN + COL_WIDTH / 2) &&
            offest <= (COL_HORIZONTAL_MARGIN + COL_WIDTH)) {
          screen[j][i] = '#';
        } else {
          screen[j][i] = ' ';
        }
      }
    }
  }
}

void ClearScreen(void) { system(CLEAN_COMMAND); }

// Since getch() is only available on windows and ncurses is not available on
// windows, I again am forced to do this...
#if defined(_WIN32) || defined(__MINGW32__) || defined(__CYGWIN__)

char NonCanonicalGetChar(void) { return getch(); }
void CorssPlatformSleep(int amount) { Sleep(amount); }
void SetBackgroundColorWhite(char c) {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
  WORD saved_attributes;

  // Save current attributes
  GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
  saved_attributes = consoleInfo.wAttributes;

  // Set background to white and foreground to black
  SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_GREEN |
                                        BACKGROUND_BLUE | FOREGROUND_RED);

  // Print the character
  putchar(c);

  // Restore original attributes
  SetConsoleTextAttribute(hConsole, saved_attributes);
}

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

void SetBackgroundColorWhite(char c) { printf("\033[47;30m%c\033[0m", c); }

#endif
