#include "Game.h"
#include "Constants.h"
#include "Screen.h"

void init(void) {
  enum MainMenuSelection sel = MainMenuPrinter();
  GameConfiguration(sel);
}

void ResetGameConfig(struct GameConfig *cfg) {
  cfg->level = 0;
  cfg->computer1Hardness = 0;
  cfg->computer2Hardness = 0;
  cfg->player1Name = NULL;
  cfg->player2Name = NULL;
}
