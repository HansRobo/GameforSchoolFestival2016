#pragma once
#include"Suken.h"
#include"Manager.h"
#include"Bullet.h"
using namespace std;
enum AI_ACTION {
	GO,
	BACK,
	SEARCH,
	TURN_R,
	TURN_L,
	SHOOT_1,
	SHOOT_2,
	SHOOT_3,
	ACTION_NUM
};

class Action {
public:
	Action() {
		action_mode = -1;
	}
	int action_mode;
	static char str[ACTION_NUM][10];
	static char explanation[ACTION_NUM][100];
	static char message[256];
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
		velocity = VELOCITY;
		pos = VGet(200, 200);
		direction = 0.0f;
		count = 0;
		damage = 1;
		hp_point = speed_point = attack_point = 0;
		this->action_num = 0;
		this->hp = 1;
	}
	void setParam(int _action_num, int _hp) {
		action_num = _action_num;
		hp = _hp;
	}
	void setActionNum(int num) {
		action_num = num;
		hp = hp_point;
	}
	int getActionNum() {
		return action_num;
	}
	int getDamage(Agent *agent) {
		int dam = 0;;
		if (!agent->bullet.empty()) {
			for (int i = 0; i < agent->bullet.size(); i++) {
				if(agent->bullet[i].getValid() && GetDistance(agent->bullet[i].pos, pos) < agent->bullet[i].scale*2){
					dam += agent->damage;
					agent->bullet[i].count = 0;
				}
			}
		}
		return dam;
	}
	Action action[10];
	void loop(Vector2D scrl) {
		if (System.GetFrame() % ACTION_INTERVAL == 0) {
			count++;
			doAction(count);
		}
		switch (action[count%action_num].action_mode) {
		case 0:
			pos += VGetRTheta(velocity/ACTION_INTERVAL,direction);
			break;
		case 1:
			pos -= VGetRTheta(velocity / ACTION_INTERVAL, direction);
			break;
		}
		if (!bullet.empty()) {
			checkBullet();
			for (int i = 0; i < bullet.size();i++) {
				bullet[i].loop(scrl);
			}
		}
		DrawFormatString(pos.x, pos.y - 60,M_PINK, "HP:%d", hp);
		
		DrawCenterString((int)pos.x, (int)pos.y - 40, WHITE, "mode : %d", action[count%action_num].action_mode);
	}
	bool isValid() {
		return (hp > 0);
	}
	void drawMe(Vector2D scrl) {
		float scale = 20.0f;
		int col = GetColor(50,255,50);
		for (int i = 0; i < 6;i++) {
			Vector2D s = VNorm(VGet(cos(M_PI / 3.0f*i), sin(M_PI / 3.0f*i)))*scale + pos + scrl;
			Vector2D e = VNorm(VGet(cos(M_PI / 3.0f*(i+1)), sin(M_PI / 3.0f*(i+1))))*scale + pos + scrl;
			DrawLineAA(s.x,s.y,e.x,e.y,col,3);
		}
		Vector2D v[3] = { pos,pos,pos };
		for (int i = 0; i < 3; i++) {

			//DrawTriangleAA(v[0].x,v[0].y,v[1].x,v[1].y,v[2].x,v[1].y,BLACK,true);

		}
		
	}
	void drawEnemy(Vector2D scrl) {
		DrawCircle(pos +scrl, 10, RED, true);
	}
	void checkBullet() {
		if (!bullet.empty()) {
			if (!bullet.front().getValid()) {
				bullet.pop_front();
			}
		}
		if (!bullet.empty()) {
			if (!bullet.front().getValid()) {
				checkBullet();
			}
		}
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
		case SHOOT_3:
			actionShoot3();
			break;
		default:
			break;

		}
	}

	void actionGo() {
		//pos += VGetRTheta(velocity, direction);
	}
	void actionBack() {
		//pos -= VGetRTheta(velocity, direction);
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
		Bullet temp;
		temp.count = 200;
		temp.pos = pos;
		temp.rad = direction;
		temp.velocity = 10.0f;
		bullet.push_back(temp);

	}
	void actionShoot2() {
		Bullet temp;
		temp.count = 200;
		temp.pos = pos;
		temp.rad = direction;
		temp.velocity = 10.0f;
		bullet.push_back(temp);
		temp.rad += 0.5f;
		bullet.push_back(temp);
		temp.rad -= 1.0f;
		bullet.push_back(temp);
	}
	void actionShoot3() {
		Bullet temp;
		temp.count = 200;
		temp.pos = pos;
		temp.rad = direction;
		temp.velocity = 10.0f;
		bullet.push_back(temp);

		temp.pos -= VGetRTheta(20.0f,direction);
		bullet.push_back(temp);
	}
	Vector2D VGetRTheta(float r, float theta) {
		return VGet(cos(theta), sin(theta))*r;
	}
	Vector2D VGetRTheta(float r, int theta) {
		return VGet(cos(theta*180.0f / 3.1416f), sin(theta*180.0f/3.1416f))*r;
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
	std::deque<Bullet> bullet;
	int damage;

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
		for (int i = -5; i < 5;i++) {
			DrawBox(pos.x+i, pos.y+i, pos.x + size.x-i, pos.y + size.y-i, GetColor(255.0f-255.0f*((float)abs(i)/5.0f) , 255.0f-255.0f*((float)abs(i) / 5.0f), 0.0f-0.0f*((float)abs(i) / 5.0f)), false);
		}
		if (is_valid) {
			const TCHAR *sss = Action::str[type];
			//DrawCenterString((int)(pos.x + size.x / 2.0f),(int)( pos.y + 20.0f), (int)GetColor(255,255,0), "%s", sss);
			DxLib::DrawStringToHandle((int)(pos.x + size.x / 2.0f) - GetDrawStringWidthToHandle(sss, strlen(sss),font_m) / 2, (int)(pos.y +size.y/2 -  DxLib::GetFontSizeToHandle(font_m) / 2), sss, YELLOW,font_m);
			//DrawCenterString((int)(pos.x + size.x / 2.0f), (int)(pos.y + 120.0f), GetColor(255,255,0), "%d", _pos);
		}
		else
		{
			DxLib::DrawStringToHandle((int)(pos.x + size.x / 2.0f) - GetDrawStringWidthToHandle("空", strlen("空"), font_m) / 2, (int)(pos.y + size.y / 2 - DxLib::GetFontSizeToHandle(font_m) / 2), "空", GetColor(100,100,0), font_m);
		}
	}
	void reset() {
		is_valid = false;
	}
	int type;
	Vector2D pos;
	const Vector2D size = Vector2D(50.0f, 50.0f);
	Vector2D anchor = Vector2D(450, 150);
	const int space = 60;
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
		Vector2D left_top = VGet(380,250);

		for (int i = 0; i < ACTION_NUM;i++) {
			DrawBox(left_top.x + space*i, left_top.y, left_top.x + space*i + size.x, left_top.y + size.y , YELLOW , false);
			DxLib::DrawStringToHandle(left_top.x + space*i + size.x/2.0f - GetDrawStringWidthToHandle(Action::str[i], strlen(Action::str[i]),font_m) / 2, left_top.y + size.y / 2.0f - GetFontSizeToHandle(font_m)/2, Action::str[i], YELLOW,font_m);
			if (is_action_locked[i]) {
				DrawLineAA(left_top.x + space*i, left_top.y, left_top.x + size.x + space*i, left_top.y + size.y, RED, 5.0f);
				DrawLineAA(left_top.x + space*i, left_top.y + size.y, left_top.x + size.x + space*i, left_top.y, RED, 5.0f);
			}
			
		}
		for (int i = 0; i < ACTION_NUM;i++) {
			if (Event.LMouse.GetOn(left_top.x + space*i, left_top.y, left_top.x + space*i + size.x, left_top.y + size.y)) {
				pointed_type = i;
				break;
			}
			else if (i == ACTION_NUM - 1) {
				pointed_type = -1;
			}
		}
		debug.Print("type : %d",selected_type);
		if (selected_type == -1) {
			for (int i = 0; i < ACTION_NUM; i++) {
				if (!is_action_locked[i]){
					if (Event.LMouse.GetClick(left_top.x + space*i, left_top.y, left_top.x + space*i + size.x, left_top.y + size.y)) {
						selected_type = i;
						break;
					}
					
				}
				
			}
		}
		else {
			
			DrawBox(Event.LMouse.GetX()-size.x/2, Event.LMouse.GetY() - size.y / 2, Event.LMouse.GetX() + size.x / 2, Event.LMouse.GetY() + size.y / 2,YELLOW,false);
			DxLib::DrawStringToHandle(Event.LMouse.GetX() - GetDrawStringWidthToHandle(Action::str[selected_type], strlen(Action::str[selected_type]), font_m) / 2, Event.LMouse.GetY() - GetFontSizeToHandle(font_m) / 2, Action::str[selected_type], YELLOW, font_m);
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
		Vector2D v[5];
		v[0] = VGet(350,340);
		v[1] = VGet(820,340);
		v[2] = VGet(840,360);
		v[3] = VGet(840,420);
		v[4] = VGet(350,420);
		for (int i = 0; i < 4;i++) {
			DrawLineAA(v[i].x, v[i].y, v[i + 1].x, v[i + 1].y, WHITE,3.0f);
		}
		DrawLineAA(v[4].x, v[4].y, v[0].x, v[0].y, WHITE, 3.0f);
		
		if (pointed_type != -1) {
			sprintf(Action::message,"%s",Action::explanation[pointed_type]);
		}
		else {
			sprintf(Action::message,"%s", "コマンドを上のボックスにドラッグ＆ドロップしましょう");
			
		}
		Vector2D b[6];
		b[0] = VGet(400,220);
		b[1] = VGet(475,220);
		b[2] = VGet(500,233);
		b[3] = VGet(475,245);
		b[4] = VGet(400,245);
		b[5] = VGet(375,233);
		for (int i = 0; i < 5;i++) {
			DrawLineAA(b[i].x,b[i].y,b[i+1].x,b[i+1].y,WHITE,2.0f);
		}
		DrawLineAA(b[5].x, b[5].y, b[0].x, b[0].y, WHITE, 2.0f);
		DrawStringToHandle(405,223,"コマンド",WHITE,font_m);
	
		Vector2D c[8];
		c[0] = VGet(500,233);
		c[1] = VGet(800,233);
		c[2] = VGet(820,240);
		c[3] = VGet(820,320);
		c[4] = VGet(370,320);
		c[5] = VGet(350,310);
		c[6] = VGet(350,233);
		c[7] = VGet(375,233);
		for (int i = 0; i < 7; i++) {
			DrawLineAA(c[i].x, c[i].y, c[i + 1].x, c[i + 1].y, WHITE, 2.0f);
		}
		

		for (int i = 0; i < action_num; i++) {
			Vector2D vertex1 = action_array[i].pos;
			Vector2D vertex2 = action_array[i].pos + action_array[i].size;
			if (Event.LMouse.GetOn(vertex1.x, vertex1.y, vertex2.x, vertex2.y)) {
				sprintf(Action::message,"ドラッグすることで順番を入れ替えることができます");
			}
		}

		DrawFormatStringFToHandle(360, 350, WHITE, font_m, Action::message);
		sprintf(Action::message, "");
	}
	int selected_type;
	int pointed_type;
	int point;
	bool is_action_locked[ACTION_NUM];
	int action_num;
	int selected_unit;
	ActionUnit *action_array;


};