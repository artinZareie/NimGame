#include "Computer.h"
#include "Utils.h"

int CalculateGraundy(const struct GameBoard *board, bool onlyFirst) {
  int xsum = 0;

  for (int i = 0; i < board->noCols; i++) {
    int sum = board->board[0][i];

    if (!board->singleRow && !onlyFirst) {
      sum += board->board[1][i];
    }

    xsum ^= sum;
  }

  return xsum;
}

struct IntPair findOptimalPileStd(const struct GameBoard *board, int xsum) {
  struct IntPair x = {-1, -1};

  for (int i = 0; i < board->noCols; i++) {
    int val = board->board[0][i];
    if (val == 0)
      continue;

    for (int j = 0; j < val; j++) {
      int t = (xsum ^ val) ^ j;

      if (t == 0) {
        x.first = i;
        x.second = val - j;
        return x;
      }
    }
  }

  return x;
}

struct IntPair findOptimalPileMisere(const struct GameBoard *board, int xsum) {
  struct IntPair x = {-1, -1};

  int noOnes = 0;
  int idxWithOne = -1;
  int noZeros = 0;

  for (int i = 0; i < board->noCols; i++) {
    if (board->board[0][i] == 1) {
      idxWithOne = i;
      noOnes++;
    } else if (board->board[0][i] == 0) {
      noZeros++;
    }
  }

  if (xsum == 0)
    return x;

  if (noZeros + noOnes == board->noCols) {
    if (noOnes % 2 == 0) {
      return x;
    } else {
      x.first = idxWithOne;
      x.second = 1;
      return x;
    }
  }

  for (int i = 0; i < board->noCols; i++) {
    int val = board->board[0][i];
    if (val == 0)
      continue;

    for (int j = 0; j < val; j++) {
      int t = (xsum ^ val) ^ j;

      if (t == 0) {
        x.first = i;
        x.second = val - j;
        return x;
      }
    }
  }

  return x;
}
