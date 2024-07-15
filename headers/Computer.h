#pragma once

#include "Game.h"

int CalculateGraundy(const struct GameBoard *board, bool onlyFirst);
int findOptimalPileStd(const struct GameBoard *board, int xsum);
