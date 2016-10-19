#pragma once
#include"Suken.h"
#include"Manager.h"
using namespace std;
enum AI_ACTION{
	GO,
	BACK,
	SEARCH,
	TURN_R,
	TURN_L,
	SHOOT_1,
	SHOOT_2,
	ACTION_NUM
};
class Action {
public:
	Action(){
		action_mode = -1;
	}
	int action_mode;
};

class Agent {
private:
	int count;

	int getCount() {
		return count;
	}
	int action_front;
	int action_num;
public:
	Agent() {
		action_front = 0;
		velocity = 100.0f;
		pos = VGet(200, 200);
		direction = 0.0f;
		count = 0;
	}
	void setParam(int _action_num,int _hp){
		action_num = _action_num;
		hp = _hp;
	}
	void setActionNum(int num) {
		action_num = num;
	}
	int getActionNum() {
		return action_num;
	}
	Action action[10];
	void loop() {
		if (System.GetFrame()% ACTION_INTERVAL == 0 ) {
			count++;
			doAction(count);
		}
		
		DrawCircle(pos,20,RED,true);
		DrawCenterString((int)pos.x, (int)pos.y - 40, WHITE, "mode : %d", action[count%action_num].action_mode);
	}
	void doAction(int _count) {
		int mode = _count%action_num;
		switch (action[mode].action_mode) {
		case GO:
			actionGo();
			break;
		case BACK:
			actionBack();
			break;
		case SEARCH:
			actionSearch();
			break;
		case TURN_R:
			actionTurnR();
			break;
		case TURN_L:
			actionTurnL();
			break;
		case SHOOT_1:
			actionShoot1();
			break;
		case SHOOT_2:
			actionShoot2();
			break;
		default:
			break;
		
		}
	}

	void actionGo() {
		pos += VGetRTheta(velocity, direction);
	}
	void actionBack() {
		pos -= VGetRTheta(velocity, direction);
	}
	void actionSearch() {
		Vector2D target =search_target - pos;
		direction = atan2f(target.y,target.x);
	}
	void actionTurnR() {
		direction -= TURN_RAD;
	}
	void actionTurnL() {
		direction += TURN_RAD;
	}
	void actionShoot1() {

	}
	void actionShoot2() {

	}
	Vector2D VGetRTheta(float r,float theta) {
		return VGet(cos(theta), sin(theta))*r;
	}


	Vector2D pos;
	int hp;
	float direction;
	float velocity;
	Vector2D search_target;
	bool is_action_locked[ACTION_NUM];

	int attack_point;
	int speed_point;
	int hp_point;

};


class MeManager {
public:
	MeManager() {

	}
	void load() {
		FILE *fp = fopen("Assets_Y68/Data/spec.txt", "r");
		if (fp != NULL) {
			int point_temp;
			fscanf(fp, "%d", &point_temp);
			point = point_temp;

			for (int i = 0; i < ACTION_NUM; i++) {
				int temp;
				fscanf(fp, "%d", &temp);
				if (temp == 0) {
					is_action_locked[i] = true;
				}
				else {
					is_action_locked[i] = false;
				}
			}
		}
		else {
			MessageBox(GetMainWindowHandle(), "ƒf[ƒ^‚Ì“Ç‚Ýž‚Ý‚ÉŽ¸”s‚µ‚Ü‚µ‚½","Œx",MB_OK);
			System.Escape();
		}
	}

	int point;
	bool is_action_locked[ACTION_NUM];
};