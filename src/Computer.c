#include "Computer.h"

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

int findOptimalPileStd(const struct GameBoard *board, int xsum) {

  for (int i = 0; i < board->noCols; i++)
    if ((xsum & board->board[0][i]) == xsum && board->board[0][i] != 0)
      return i;

  return -1;
}
