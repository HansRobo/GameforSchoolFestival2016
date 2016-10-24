#pragma once
#include"Suken.h"
#define STAGE_NUM (5)

#define ACTION_INTERVAL (8) 

#define TURN_RAD (1.57f)

#define VELOCITY (40.0f)

class Stage;
class StageManager;
class Agent;
class MeManager;

extern StageManager stage;
extern CScene title, game_main, edit_me,alert;
extern MeManager manager;

extern int font_l;