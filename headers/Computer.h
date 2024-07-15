#pragma once

#include "Game.h"
#include "Utils.h"

int CalculateGraundy(const struct GameBoard *board, bool onlyFirst);
struct IntPair findOptimalPileStd(const struct GameBoard *board, int xsum);
struct IntPair findOptimalPileMisere(const struct GameBoard *board, int xsum);
