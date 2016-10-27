#pragma once
#include"Agent.h"
#include"Manager.h"
using namespace std;
class Stage {
public:
	Stage() {

		result_counter = 0;
		scroll = VGet(0, 0);
	}
	void load(int stage_num) {
		enemy.clear();
		char file_name[256];
		sprintf(file_name,"Assets_Y68/Data/stage%d.txt",stage_num);
		FILE *fp = fopen(file_name, "r");
		if (fp != NULL) {
			fscanf(fp, "%d", &max_action_num);
			me.setActionNum(max_action_num);

			int enemy_num;
			fscanf(fp, "%d", &enemy_num);
			for (int i = 0; i < enemy_num; i++) {
				Agent temp;
				int x, y, action_num, hp, spd, atk;
				fscanf(fp, "%d %d", &x, &y);
				temp.pos = VGet(x, y);
				fscanf(fp, "%d %d %d", &atk, &spd, &hp);
				fscanf(fp, "%d", &action_num);
				temp.setParam(action_num, hp);
				for (int j = 0; j < action_num; j++) {
					int mode;
					fscanf(fp, "%d", &mode);
					temp.action[j].action_mode = mode;
				}
				enemy.push_back(temp);
			}
		}else{
			MessageBox(GetMainWindowHandle(), "ƒf[ƒ^‚Ì“Ç‚Ýž‚Ý‚ÉŽ¸”s‚µ‚Ü‚µ‚½","Œx", MB_OK);
			System.Escape();
		}
	}
	void controlScroll() {
		float diff_scroll = 0.02f;
		Vector2D pos = me.pos + scroll;
		scroll -= (pos - VGet(450.0f, 300.0f))*diff_scroll;
	
	}
	void drawGrid() {
		int col = GetColor(50,50,50);
		int grid_unit = 50;
		int x = scroll.x;
		int y = scroll.y;
		x %=grid_unit;
		y %= grid_unit;
		for (int i = -10; i <= 20;i++) {
			DrawLineAA(x + i*grid_unit ,0 ,x + i*grid_unit,600,col,0.5f);
			DrawLineAA(0, y + i*grid_unit, 900, y + i*grid_unit, col,0.5f);
		}
	}
	void loop() {
		drawGrid();
		actMe();
		actEnemy();
		controlScroll();
		
	}
	void actMe() {
		me.search_target = getNearestEnemyPos(me.pos);
		me.loop(scroll);
		me.drawMe(scroll);
		if (!enemy.empty()) {
			for (int i = 0;i<enemy.size();i++ ){
				me.hp -= (me.getDamage(&enemy[i]));
			}
		}
	}
	void actEnemy() {
		if(!enemy.empty()){
			for (int i = 0;i<enemy.size();i++) {
				if (enemy[i].isValid()) {
					enemy[i].search_target = me.pos;
					enemy[i].loop(scroll);
					enemy[i].drawEnemy(scroll);
					enemy[i].hp -= enemy[i].getDamage(&me);
				}
			}
		}
	}
	Vector2D getNearestEnemyPos(Vector2D _pos){
		Vector2D nearest = _pos;
		float min_distance = 100000000000.0f;

		if (!enemy.empty()) {
			for (int i = 0; i < enemy.size();i++) {
				if (enemy[i].isValid()) {
					float distance = GetSquareDistance(enemy[i].pos, _pos);
					if (distance < min_distance) {
						min_distance = distance;
						nearest = enemy[i].pos;
					}
				}
			}

		}
		return nearest;
	}
	int max_action_num;
	Agent me;
	vector<Agent> enemy;
	int result_counter;
	Vector2D scroll;
};

class StageManager {
public:
	StageManager() {
		base_rad = 0.05f;
	}
	void load() {
		for (int i = 0; i < STAGE_NUM;i++) {
			stage[i] = new Stage();
			stage[i]->load(i+1);
		}
		base_rad = 0.05f;
		transition_mode = 0;
	}
	Stage *stage[STAGE_NUM];
	int current_stage;
	int transition_mode;
	int count;
	const int animation_time = 20;
	float base_rad;
	
};

class StageSelectManager {
public:
	StageSelectManager() {

	}
};