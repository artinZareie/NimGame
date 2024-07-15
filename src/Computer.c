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
    int target = val ^ xsum;

    if (target < val) {
      x.first = i;
      x.second = target;
      return x;
    }
  }

  return x;
}
