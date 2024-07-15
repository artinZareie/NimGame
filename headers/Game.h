#pragma once

#include "Constants.h"
#include <stdbool.h>
#include <stdlib.h>

struct GameConfig {
  size_t level;
  char *player1Name, *player2Name;
  size_t computer1Hardness, computer2Hardness;
  enum MainMenuSelection gameType;
};

struct GameBoard {
  int noCols;
  int activeRow, activeCol;
  int turn;

  bool singleRow, solvedFirstRow;

  int *board[2];
  struct GameConfig cfg;
};

typedef enum ControlDirection (*PlayerSelectionFunc)(struct GameBoard board);
typedef size_t (*PlayerDrawAmount)(struct GameBoard board);

void init(void);
void ResetGameConfig(struct GameConfig *cfg);
void ResetGameBoard(struct GameBoard *board, struct GameConfig cfg);
void GameEngine(struct GameBoard board, PlayerSelectionFunc player1Sel,
                PlayerSelectionFunc player2Sel, PlayerDrawAmount player1Draw,
                PlayerDrawAmount player2Draw);
