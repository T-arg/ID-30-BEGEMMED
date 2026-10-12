/*
  Begemmed: https://t-arg.github.io/ID-30-BEGEMMED/

  Arduboy version 2.0:  https://github.com/T-arg/ID-30-BEGEMMED

  MADE by TEAM a.r.g. : https://t-arg.github.io/

  2015 - JO3RI

  2026 - MUSIC and SOUND EFFECTS - JO3RI

  Game License: MIT : https://opensource.org/licenses/MIT

*/

//determine the game
#define GAME_ID 30

#include "globals.h"
#include "menu.h"
#include "game.h"
#include "stage.h"


typedef void (*FunctionPointer) ();
const FunctionPointer PROGMEM  mainGameLoop[] = {
  stateMenuIntro,
  stateMenuMain,
  stateMenuHelp,
  stateMenuPlay,
  stateMenuInfo,
  stateMenuSoundfx,
  stateMenuJbox,
  stateGamePlaying,
  stateGamePause,
  stateGameOver,
};

void setup()
{
  arduboy.boot();
  arduboy.audio.begin();
  arduboy.setFrameRate(60);
  arduboy.initRandomSeed();
}

void loop() {
  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();
  arduboy.clear();
  musicUpdate();
  ((FunctionPointer) pgm_read_word (&mainGameLoop[gameState]))();
  arduboy.display();
}




