#pragma once
#include "Suken.h"
#include"Stage.h"
#include"Manager.h"

void gameMainLoop();

void editMeLoop();
void upATK();
void downATK();
void upSPD();
void downSPD();
void upHP();
void downHP();

void reload();

void titleLoop();
void stageSelectLoop();

void gameStart();
void editStart();
void backToTitle();

void gameOverLoop();
void gameClearLoop();

void howLoop();