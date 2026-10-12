#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include "globals.h"

void stateMenuIntro()
{
  globalCounter++;
  sprites.drawSelfMasked(49, 20, T_arg, 0);
  if (globalCounter > 180)
  {
    globalCounter = 0;
    gameState = STATE_MENU_MAIN;
  }
}

void stateMenuMain()
{
  for (byte i = 0; i < 4; i++) sprites.drawSelfMasked(32 * i, 0, splashScreen, i);
  sprites.drawSelfMasked(0, 48, mainMenu, menuSelection - 2);
  sprites.drawSelfMasked(64, 48, mainMenu, menuSelection - 2 + 6);
  if (arduboy.justPressed(RIGHT_BUTTON) && (menuSelection < 5)) { menuSelection++; sfx(sfxMove); }
  if (arduboy.justPressed(LEFT_BUTTON) && (menuSelection > 2)) { menuSelection--; sfx(sfxMove); }
  if (arduboy.justPressed(A_BUTTON | B_BUTTON)) { gameState = menuSelection == 2 ? STATE_MENU_JBOX : menuSelection; sfx(sfxSelect); }
}

void stateMenuHelp()
{
  if (arduboy.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
}


void stateMenuInfo()
{
  sprites.drawSelfMasked(33, 16, title, 0);
  sprites.drawSelfMasked(37, 32, madeBy, 0);
  if (arduboy.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
}



void stateMenuSoundfx()
{
  arduboy.clear();
  for (byte i = 0; i < 4; i++) sprites.drawSelfMasked(32 * i, 0, splashScreen, i);
  sprites.drawSelfMasked(0, 48, mainMenu, 4 + arduboy.audio.enabled());
  sprites.drawSelfMasked(64, 48, mainMenu, 6 + 4 + arduboy.audio.enabled());
  if (arduboy.justPressed(RIGHT_BUTTON)) arduboy.audio.on();;
  if (arduboy.justPressed(LEFT_BUTTON)) arduboy.audio.off();
  if (arduboy.justPressed(A_BUTTON | B_BUTTON))
  {
    arduboy.audio.saveOnOff();
    gameState = STATE_MENU_MAIN;
    sfx(sfxSelect);
  }
}

// the jukebox: MUSIC (UP) and SNDFX (DOWN), LEFT = next number, RIGHT = previous number, B = play, A = stop (and leave when nothing plays)
byte jbRow = 0;
byte jbNr[2];                                  // MUSIC 0..11, SNDFX 0..8

void stateMenuJbox()
{
  sprites.drawSelfMasked(33, 4, title, 0);
  for (byte i = 0; i < 2; i++)
  {
    byte y = 28 + 16 * i;
    sprites.drawSelfMasked(35, y, jboxWords, i);
    if (jbRow != i || (arduboy.frameCount & 16))              // the selected number blinks
    {
      sprites.drawSelfMasked(78, y, numbersBig, (jbNr[i] + 1) / 10);
      sprites.drawSelfMasked(86, y, numbersBig, (jbNr[i] + 1) % 10);
    }
  }
  byte n = jbRow ? JBOX_SFX : JBOX_MUSIC;
  if (arduboy.justPressed(UP_BUTTON)) jbRow = 0;
  if (arduboy.justPressed(DOWN_BUTTON)) jbRow = 1;
  if (arduboy.justPressed(LEFT_BUTTON)) jbNr[jbRow] = (jbNr[jbRow] + 1) % n;
  if (arduboy.justPressed(RIGHT_BUTTON)) jbNr[jbRow] = (jbNr[jbRow] + n - 1) % n;
  if (arduboy.justPressed(B_BUTTON) && arduboy.audio.enabled())
  {
    if (jbRow) sfx((const uint8_t *)pgm_read_word(&sfxList[jbNr[1]]));
    else musicPlay(jbNr[0]);
  }
  if (arduboy.justPressed(A_BUTTON))
  {
    if (musicId == MUSIC_OFF) gameState = STATE_MENU_MAIN;    // nothing playing: leave, the title tune restarts
    else musicPlay(MUSIC_OFF);
  }
}


#endif
