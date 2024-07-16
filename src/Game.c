#include "Game.h"
#include "Computer.h"
#include "Constants.h"
#include "Screen.h"
#include "Utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

void init(void) {
  srand(time(NULL));

  enum MainMenuSelection sel = MainMenuPrinter();
  if (sel != LoadGameOption) {
    struct GameConfig gameConfig = GameConfiguration(sel);
    struct GameBoard gboard;
    struct FramesHistory gameFrames;
    ResetGameBoard(&gboard, gameConfig);

    if (sel == PVPOption) {
      gameFrames = GameEngine(&gboard, HumanMoveSelector, HumanMoveSelector);
    } else if (sel == PVCOption) {
      gameFrames = GameEngine(&gboard, HumanMoveSelector, ComputerMoveSelector);
    } else if (sel == CVCOption) {
      gameFrames =
          GameEngine(&gboard, ComputerMoveSelector, ComputerMoveSelector);
    }

    bool saveTheGame = WinScreen(&gboard);

    if (saveTheGame) {
      FILE *fd = fopen("LastGame.txt", "w+");

      fprintf(fd, "%d %d %lu\n", gameFrames.noFrames, gameFrames.cfg.gameType,
              gameFrames.cfg.level);
      fprintf(fd, "%s %s\n", gameFrames.cfg.player1Name,
              gameFrames.cfg.player2Name);
      fprintf(fd, "%lu %lu\n", gameFrames.cfg.computer1Hardness,
              gameFrames.cfg.computer2Hardness);

      fclose(fd);
    }
  }
}

void ResetGameConfig(struct GameConfig *cfg) {
  cfg->level = 0;
  cfg->computer1Hardness = 0;
  cfg->computer2Hardness = 0;
  cfg->player1Name = NULL;
  cfg->player2Name = NULL;
  cfg->gameType = 0;
}

void ResetGameBoard(struct GameBoard *board, struct GameConfig cfg) {
  board->board[0] = board->board[1] = NULL;
  board->turn = 0;
  board->cfg = cfg;
  board->noCols = NoColsPerLevel[cfg.level];
  board->activeCol = board->activeRow = 0;
  board->singleRow = SingleRowPerLevel[cfg.level];
  board->solvedFirstRow = false;

  board->board[0] = malloc((board->noCols) * sizeof(int));

  if (!board->singleRow) {
    board->board[1] = malloc((board->noCols) * sizeof(int));
  }

  for (int i = 0; i < board->noCols; i++) {
    board->board[0][i] = rand() % (MAX_PIECES / 2 + 1);
    if (board->board[0][i] == 0)
      board->board[0][i] = 1;

    if (!board->singleRow) {
      board->board[1][i] = board->board[0][i];
    }
  }
}

void ResetFrameHistory(struct FramesHistory *frames, struct GameFrame initial) {
  frames->head = malloc(sizeof(struct GameFrame));

  for (int i = 0; i < 2; i++) {
    if (initial.board[i] == NULL) {
      frames->head->board[i] = NULL;
      continue;
    }

    frames->head->board[i] = malloc((initial.noCols) * sizeof(int));
    for (int j = 0; j < initial.noCols; j++) {
      frames->head->board[i][j] = initial.board[i][j];
    }
  }

  frames->head->singleRow = initial.singleRow;
  frames->head->next = NULL;
  frames->tail = frames->head;
  frames->noFrames = 1;
}

void AddFrame(const struct GameBoard *board, struct FramesHistory *frames) {
  struct GameFrame *newFrame = malloc(sizeof(struct GameFrame));
  newFrame->noCols = board->noCols;
  newFrame->singleRow = board->singleRow;
  newFrame->turn = board->turn;

  for (int i = 0; i < 2; i++) {
    if (board->board[i] == NULL) {
      newFrame->board[i] = NULL;
      continue;
    }

    newFrame->board[i] = malloc((board->noCols) * sizeof(int));
    for (int j = 0; j < board->noCols; j++) {
      newFrame->board[i][j] = board->board[i][j];
    }
  }

  frames->tail->next = newFrame;
  frames->tail = newFrame;
  frames->noFrames++;
}

struct FramesHistory GameEngine(struct GameBoard *board,
                                PlayerSelectionFunc player1Sel,
                                PlayerSelectionFunc player2Sel) {
  enum ControlDirection dir = 0;
  int stagedDraw = 1;
  int noActiveCols = board->noCols;

  struct FramesHistory fhist;
  struct GameFrame init;
  init.singleRow = board->singleRow;
  init.noCols = board->noCols;
  init.turn = board->turn;
  fhist.cfg = board->cfg;

  for (int i = 0; i < 2; i++) {
    if (board->board[i] == NULL) {
      init.board[i] = NULL;
      continue;
    }

    init.board[i] = malloc((board->noCols) * sizeof(int));
    for (int j = 0; j < board->noCols; j++) {
      init.board[i][j] = board->board[i][j];
    }
  }
  ResetFrameHistory(&fhist, init);

  while (true) {
    GameBoardDrawer(board, stagedDraw);
    printf("Staged Draw: %d\n", stagedDraw);
    if (board->turn == 0)
      dir = player1Sel(board, stagedDraw);
    else
      dir = player2Sel(board, stagedDraw);

    if (dir == RightDir) {
      board->activeCol = (board->activeCol + 1) % board->noCols;

      while (board->board[board->activeRow][board->activeCol] == 0) {
        board->activeCol = (board->activeCol + 1) % board->noCols;
      }

      stagedDraw =
          min_int(board->board[board->activeRow][board->activeCol], stagedDraw);
    } else if (dir == LeftDir) {
      board->activeCol = (board->activeCol - 1 + board->noCols) % board->noCols;

      while (board->board[board->activeRow][board->activeCol] == 0) {
        board->activeCol =
            (board->activeCol - 1 + board->noCols) % board->noCols;
      }
      stagedDraw =
          min_int(board->board[board->activeRow][board->activeCol], stagedDraw);
    } else if (dir == IncreaseDraw) {
      stagedDraw = min_int(stagedDraw + 1,
                           board->board[board->activeRow][board->activeCol]);
    } else if (dir == DecreaseDraw) {
      stagedDraw = max_int(1, stagedDraw - 1);
    } else {
      board->board[board->activeRow][board->activeCol] -= stagedDraw;

      if (!board->singleRow) {
        board->board[1][board->activeCol] += stagedDraw;
      }

      if (board->board[board->activeRow][board->activeCol] == 0) {
        noActiveCols--;
      }

      while (noActiveCols > 0 &&
             board->board[board->activeRow][board->activeCol] == 0) {
        board->activeCol = (board->activeCol + 1) % board->noCols;
      }

      if (noActiveCols == 0 && !board->singleRow) {
        for (int i = 0; i < board->noCols; i++) {
          board->board[0][i] = board->board[1][i];
        }

        board->singleRow = true;
        noActiveCols = board->noCols;
      }

      if (noActiveCols == 0 && board->singleRow) {
        return fhist;
      }

      board->turn = (board->turn + 1) % 2;
      stagedDraw = 1;
    }
  }

  return fhist;
}

enum ControlDirection HumanMoveSelector(const struct GameBoard *const board,
                                        int staged) {
  char pressedKey;
redo_the_input:
  pressedKey = NonCanonicalGetChar();

  switch (pressedKey) {
  case 'a':
  case 'A':
    return LeftDir;
    break;

  case 'd':
  case 'D':
    return RightDir;
    break;

  case 'w':
  case 'W':
    return DecreaseDraw;
    break;

  case 's':
  case 'S':
    return IncreaseDraw;
    break;

  case '\n':
  case '\r':
    return Done;
    break;

  default:
    goto redo_the_input;
  }
}

enum ControlDirection ComputerMoveSelector(const struct GameBoard *const board,
                                           int staged) {
  int xsum = CalculateGraundy(board, false);
  int firstRowStrategy = 0;
  int moveRandomness =
      NO_MAX_HARDNESS - (board->turn == 0 ? board->cfg.computer1Hardness
                                          : board->cfg.computer2Hardness);
  int correctMove = (rand() % moveRandomness) == 0;
  if (moveRandomness == 1)
    correctMove = 1;

  CrossPlatformSleep(1);

  if (!correctMove)
    return Done;

  if (!board->singleRow && xsum != 0) {
    firstRowStrategy = 1;
  }

  if (firstRowStrategy == 0 || !board->singleRow) {
    struct IntPair opt = findOptimalPileStd(board, xsum);

    if (opt.first == -1 || opt.second == -1)
      return Done;

    if (board->activeCol > opt.first)
      return LeftDir;
    if (board->activeCol < opt.first)
      return RightDir;

    if (staged < opt.second)
      return IncreaseDraw;

    if (staged > opt.second)
      return DecreaseDraw;

    return Done;
  }

  if (firstRowStrategy == 1) {
    struct IntPair opt = findOptimalPileMisere(board, xsum);

    if (opt.first == -1 || opt.second == -1)
      return Done;

    if (board->activeCol > opt.first)
      return LeftDir;
    if (board->activeCol < opt.first)
      return RightDir;

    if (staged < opt.second)
      return IncreaseDraw;

    if (staged > opt.second)
      return DecreaseDraw;

    return Done;
  }

  return Done;
}
