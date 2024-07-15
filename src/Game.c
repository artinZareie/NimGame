#include "Game.h"
#include "Constants.h"
#include "Screen.h"
#include "Utils.h"
#include <bits/posix2_lim.h>
#include <stdio.h>
#include <time.h>

void init(void) {
  srand(time(NULL));

  enum MainMenuSelection sel = MainMenuPrinter();
  if (sel != LoadGameOption) {
    struct GameConfig gameConfig = GameConfiguration(sel);
    struct GameBoard gboard;
    ResetGameBoard(&gboard, gameConfig);

    GameEngine(&gboard, HumanMoveSelector, HumanMoveSelector);
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
      board->board[1][i] = rand() % (MAX_PIECES / 2 + 1);
      if (board->board[1][i] == 0)
        board->board[1][i] = 1;
    }
  }
}

void GameEngine(struct GameBoard *board, PlayerSelectionFunc player1Sel,
                PlayerSelectionFunc player2Sel) {

  enum ControlDirection dir = 0;
  int stagedDraw = 1;
  int noActiveCols = board->noCols;

  while (true) {
    GameBoardDrawer(board, stagedDraw);
    printf("Staged Draw: %d\n", stagedDraw);
    if (board->turn == 0)
      dir = player1Sel(board);
    else
      dir = player2Sel(board);

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
        WinScreen(board);
        break;
      }

      if (!board->singleRow) {
        board->board[1][board->activeCol] += stagedDraw;
      }

      board->turn = (board->turn + 1) % 2;
    }
  }
}

enum ControlDirection HumanMoveSelector(const struct GameBoard *const board) {
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
    return Done;
    break;

  default:
    goto redo_the_input;
  }
}
