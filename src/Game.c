#include "Game.h"
#include "Constants.h"
#include "Screen.h"
#include <stdio.h>
#include <time.h>

void init(void) {
  srand(time(NULL));

  enum MainMenuSelection sel = MainMenuPrinter();
  if (sel != LoadGameOption) {
    struct GameConfig gameConfig = GameConfiguration(sel);
    struct GameBoard gboard;
    ResetGameBoard(&gboard, gameConfig);

    GameBoardDrawer(&gboard);
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
