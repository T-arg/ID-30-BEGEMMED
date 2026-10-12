#ifndef INPUTS_H
#define INPUTS_H

#include <Arduino.h>
#include "globals.h"
#include "stage.h"

void checkInputs()
{
  int oldX = selectorXpos, oldY = selectorYpos;
  if (arduboy.justPressed(UP_BUTTON) && (modeIsSelected == false) && (selectorYpos > 0))selectorYpos--;
  if (arduboy.justPressed(DOWN_BUTTON) && (modeIsSelected == false) && (selectorYpos < PLAYFIELD_HEIGHT - 1))selectorYpos++;
  if (arduboy.justPressed(LEFT_BUTTON) && (modeIsSelected == false) && (selectorXpos > 0))selectorXpos--;
  if (arduboy.justPressed(RIGHT_BUTTON) && (modeIsSelected == false) && (selectorXpos < PLAYFIELD_WIDTH - 1))selectorXpos++;

  if (arduboy.justPressed(UP_BUTTON) && (modeIsSelected == true) && (selectorYpos > 0))switchGem(SWITCH_GEM_UP);
  if (arduboy.justPressed(DOWN_BUTTON) && (modeIsSelected == true) && (selectorYpos < PLAYFIELD_HEIGHT - 1))switchGem(SWITCH_GEM_DOWN);
  if (arduboy.justPressed(LEFT_BUTTON) && (modeIsSelected == true) && (selectorXpos > 0))switchGem(SWITCH_GEM_LEFT);
  if (arduboy.justPressed(RIGHT_BUTTON) && (modeIsSelected == true) && (selectorXpos < PLAYFIELD_WIDTH - 1))switchGem(SWITCH_GEM_RIGHT);

  if (oldX != selectorXpos || oldY != selectorYpos) sfx(sfxMove);
  if (arduboy.justPressed(B_BUTTON))
  {
    modeIsSelected = !modeIsSelected;
    sfx(modeIsSelected ? sfxSelect : sfxDeselect);
  }
  if (arduboy.justPressed(A_BUTTON))
  {
    arduboy.clear();
    gameState = STATE_GAME_PAUSE;
    sfx(sfxPause);
  }
}


#endif
