#pragma once

#include "Constants.h"
#include <stdbool.h>
#include <stdlib.h>

struct GameConfig {
	size_t level;
	char *player1Name, *player2Name;
	size_t computer1Hardness, computer2Hardness;
};

struct GameBoard {
  int noCols;
  int activeRow, activeCol;

  bool singleRow, solvedFirstRow;

	int *board[2];
};

typedef enum ControlDirection (*PlayerSelectionFunc)(struct GameBoard board);
typedef size_t (*PlayerDrawAmount)(struct GameBoard board);

void init(void);
void ResetGameConfig(struct GameConfig *cfg);
void GameEngine();
