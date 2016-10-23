#pragma once
#include"Suken.h"
#include"Manager.h"
using namespace std;
enum AI_ACTION {
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
	Action() {
		action_mode = -1;
	}
	int action_mode;
	static char str[ACTION_NUM][10];
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
	void setParam(int _action_num, int _hp) {
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
		if (System.GetFrame() % ACTION_INTERVAL == 0) {
			count++;
			doAction(count);
		}

		DrawCircle(pos, 20, RED, true);
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
		Vector2D target = search_target - pos;
		direction = atan2f(target.y, target.x);
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
	Vector2D VGetRTheta(float r, float theta) {
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

class ActionUnit {
public:
	ActionUnit() {
		type = -1;
		num = -1;
		pos = VGet(0.0f, 0.0f);
		is_valid = false;
	}
	void draw(int i, int _pos) {
		
		DrawBox(pos.x, pos.y, pos.x + size.x, pos.y + size.y, GetColor(128, 128, 255), false);
		//for (int i = 0; i < 30;i++) {
		//	DrawBox(pos.x+i, pos.y+i, pos.x + size.x-i, pos.y + size.y-i, GetColor(255.0f*((float)i/30.0f) , 255.0f*((float)i / 30.0f), 255), false);
		//}
		if (is_valid) {
			const TCHAR *sss = Action::str[type];
			//DrawCenterString((int)(pos.x + size.x / 2.0f),(int)( pos.y + 20.0f), (int)GetColor(255,255,0), "%s", sss);
			DxLib::DrawString((int)(pos.x + size.x / 2.0f) - GetDrawStringWidth(sss, strlen(sss)) / 2, (int)(pos.y + 20.0f), sss, YELLOW);
			DrawCenterString((int)(pos.x + size.x / 2.0f), (int)(pos.y + 120.0f), GetColor(255,255,0), "%d", _pos);
		}
	}
	void reset() {
		is_valid = false;
	}
	int type;
	Vector2D pos;
	const Vector2D size = Vector2D(60.0f, 60.0f);
	Vector2D anchor = Vector2D(450, 250);
	const int space = 70;
	int num;
	void setPos() {
		pos = anchor + VGet(num*space, 0);
	}
	void setNum(int _num) {
		num = _num;
	}
	void setType(int _type) {
		type = _type;
		if (_type != -1) {
			is_valid = true;
		}
		else {
			is_valid = false;
		}
	}
	bool is_valid;
};

class MeManager {
public:
	MeManager() {
		action_num = 0;
		action_array = nullptr;
		selected_unit = -1;
	}
	void load() {
		FILE *fp = fopen("Assets_Y68/Data/spec.txt", "r");
		if (fp != NULL) {
			fscanf(fp, "%d", &point);
			fscanf(fp, "%d", &action_num);
			action_array = new ActionUnit[action_num];

			for (int i = 0; i < action_num; i++) {
				action_array[i].setNum(i);
				action_array[i].setPos();
			}
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
			MessageBox(GetMainWindowHandle(), "データの読み込みに失敗しました", "警告", MB_OK);
			System.Escape();
		}
	}

	void reset() {
		if (action_array != nullptr) {
			delete action_array;
			action_array = nullptr;
		}
		action_num = 0;
		for (int i = 0; i < ACTION_NUM; i++) {
			is_action_locked[i] = true;
		}
		point = 0;
		selected_unit = -1;
	}
	void sort() {
		if (selected_unit == -1) {
			for (int i = 0; i < action_num; i++) {
				Vector2D vertex1 = action_array[i].pos;
				Vector2D vertex2 = action_array[i].pos + action_array[i].size;
				if (Event.LMouse.GetClick(vertex1.x, vertex1.y, vertex2.x, vertex2.y)) {
					selected_unit = i;
					break;
				}
			}
		}
		else {
			Vector2D vertex1 = action_array[selected_unit].pos;
			Vector2D vertex2 = action_array[selected_unit].pos + action_array[selected_unit].size;

			if (Event.LMouse.GetInput()) {


				int distance = 1000;
				int nearest = -1;
				for (int i = 0; i < action_num; i++) {
					int center = action_array[0].anchor.x + i*action_array[0].space + action_array[0].size.x / 2;
					if (distance > abs(Event.LMouse.GetX() - center)) {
						distance = abs(Event.LMouse.GetX() - center);
						nearest = i;
					}
				}
				debug.Print("nearest:%d", nearest);
				if (nearest != action_array[selected_unit].num && nearest != -1) {
					for (int i = 0; i < action_num; i++) {
						if (action_array[i].num == nearest) {
							int temp = action_array[i].num;
							action_array[i].setNum(action_array[selected_unit].num);
							action_array[i].setPos();
							action_array[selected_unit].setNum(temp);

						}
					}

				}

				action_array[selected_unit].pos = VGet(Event.LMouse.GetX() - action_array[0].size.x / 2, Event.LMouse.GetY() - action_array[0].size.x / 2);
			}
			else {
				for (int i = 0; i < action_num; i++) {
					action_array[i].setPos();
				}
				selected_unit = -1;

				debug.Print("EXIT!");
			}


		}
		for (int i = 0; i < action_num; i++) {
			Vector2D vertex1 = action_array[i].pos;
			Vector2D vertex2 = action_array[i].pos + action_array[i].size;
			if (Event.RMouse.GetClick(vertex1.x, vertex1.y, vertex2.x, vertex2.y)) {
				action_array[i].reset();
				break;
			}
		}
	}

	void selectType() {
		debug.Print("黄色いボタンを");
		debug.Print("青い四角へ");
		debug.Print("ドラッグ＆ドロップ");
		debug.Print("してください");
		Vector2D size = VGet(50.0f,50.0f);
		int space = 60;
		Vector2D left_top = VGet(380,400);

		for (int i = 0; i < ACTION_NUM;i++) {
			DrawBox(left_top.x + space*i, left_top.y, left_top.x + space*i + size.x, left_top.y + size.y , YELLOW , false);
			DxLib::DrawString(left_top.x + space*i + size.x/2.0f - GetDrawStringWidth(Action::str[i], strlen(Action::str[i])) / 2, left_top.y + size.y / 2.0f -10.0f, Action::str[i], YELLOW);
			
		}
		debug.Print("type : %d",selected_type);
		if (selected_type == -1) {
			for (int i = 0; i < ACTION_NUM; i++) {
				if (Event.LMouse.GetClick(left_top.x + space*i, left_top.y  , left_top.x + space*i + size.x, left_top.y + size.y)) {
					selected_type = i;
					break;
				}
			}
		}
		else {
			if (!Event.LMouse.GetPreInput()) {
				selected_type = -1;
			}
			else {
				for (int i = 0; i < action_num; i++) {
					Vector2D vertex1 = action_array[i].pos;
					Vector2D vertex2 = action_array[i].pos + action_array[i].size;
					if (Event.LMouse.GetRelease(vertex1.x, vertex1.y, vertex2.x, vertex2.y)) {
						
						action_array[i].setType(selected_type);
						selected_type = -1;
						break;
					}
				}
			}

		}
		
	}
		int selected_type;
	int point;
	bool is_action_locked[ACTION_NUM];
	int action_num;
	int selected_unit;
	ActionUnit *action_array;


};