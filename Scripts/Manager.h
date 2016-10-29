#pragma once
#include"Suken.h"

#ifndef M_PI
#define M_PI (3.1416f)
#endif
#define STAGE_NUM (6)

#define ACTION_INTERVAL (8) 

#define TURN_RAD (1.57f)

#define VELOCITY (40.0f)

class Stage;
class StageManager;
class Agent;
class MeManager;

extern StageManager stage;
extern CScene title, game_main, edit_me,alert,game_clear,game_over,how;
extern MeManager manager;

extern int font_l,font_m,font_ll;
extern int lock;