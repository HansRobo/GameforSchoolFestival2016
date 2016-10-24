#include"Scenes.h"
#include"Alert.h"
char Action::str[ACTION_NUM][10] = {
	"直進",
	"後進",
	"探索",
	"右折",
	"左折",
	"弾壱",
	"弾弐",
};
void gameMainLoop() {
	stage.stage[stage.current_stage].loop();
	DrawCircle(stage.stage[0].me.pos, 30, YELLOW, false);

}


void editMeLoop() {

	debug.Print("stage:%d", stage.current_stage);
	DrawFormatString(120, 50, YELLOW, "未使用ポイント : %d", manager.point);
	DrawFormatString(160,100,WHITE,"ATK : %d",stage.stage[stage.current_stage].me.attack_point);
	DrawFormatString(160, 140, WHITE, "SPD : %d", stage.stage[stage.current_stage].me.speed_point);
	DrawFormatString(160, 180, WHITE, "HP : %d", stage.stage[stage.current_stage].me.hp_point);

	float scale = 15.0f;
	Vector2D atk, spd, hp,center;
	center = VGet(200, 400);
	atk = spd = hp = center;
	atk += VGet(0.0f, -1.0f)*stage.stage[stage.current_stage].me.attack_point*scale;
	spd += VGet(0.866f, 0.5f)*stage.stage[stage.current_stage].me.speed_point*scale;
	hp += VGet(-0.866f, 0.5f)*stage.stage[stage.current_stage].me.hp_point*scale;

	DrawLine(center,center+VGet(0,-1)*scale*10,GRAY);
	DrawLine(center, center + VGet(0.866f, 0.5f)*scale * 10, GRAY);
	DrawLine(center, center + VGet(-0.866f, 0.5f)*scale * 10, GRAY);

	DrawLine(atk,spd,YELLOW);
	DrawLine(hp, spd, YELLOW);
	DrawLine(atk, hp, YELLOW);

	DrawCircle(atk,3,YELLOW,true);
	DrawCircle(spd, 3, YELLOW, true);
	DrawCircle(hp, 3, YELLOW, true);




	//////////////////////////////////////////////

	debug.Print("select:%d",manager.selected_unit);
	manager.selectType();
	manager.sort();

	//draw
	for (int i = 0; i < manager.action_num;i++) {
		manager.action_array[i].draw(i,manager.action_array[i].num);
	}

}
void upATK() {
	if(manager.point > 0){
		manager.point--;
		stage.stage[stage.current_stage].me.attack_point++;
	}
}
void downATK(){
	if (stage.stage[stage.current_stage].me.attack_point > 0) {
		manager.point++;
		stage.stage[stage.current_stage].me.attack_point--;
	}
}
void upSPD() {
	if (manager.point > 0) {
		manager.point--;
		stage.stage[stage.current_stage].me.speed_point++;
	}
}
void downSPD() {
	if (stage.stage[stage.current_stage].me.speed_point > 0) {
		manager.point++;
		stage.stage[stage.current_stage].me.speed_point--;
	}
}
void upHP() {
	if (manager.point > 0) {
		manager.point--;
		stage.stage[stage.current_stage].me.hp_point++;
	}
}
void downHP() {
	if (stage.stage[stage.current_stage].me.hp_point > 0) {
		manager.point++;
		stage.stage[stage.current_stage].me.hp_point--;
	}
}

void reload() {
	stage.load();
}


void titleLoop() {
	//DrawBox(0, 0, 900, 600, WHITE, true);
	int unit = 30;
	
	for (int i = 0; i <= 900 / unit;i++) {
		
		for (int j = 0; j <= 600 / unit;j++) {
			float r = 5.0f + 4.7f*sin((float)(System.GetFrame() + ((i + j) * 8)) / 40.0f);
			DrawCircleAA(unit*i, unit*j ,r,100, GetColor(128, 128, 128), true);
		}
	}
	if (Event.key.GetDown(Event.key.RETURN)) {
		
	}
}


void stageSelectLoop() {
	int wheel_rot = GetMouseWheelRotVol();
	debug.Print("stage:%d", stage.current_stage);
	float d_rad = (0.3f/(float)stage.animation_time)-(0.3f/(float)stage.animation_time)*abs((float)stage.count-(float)(stage.animation_time/2.0f))/ (float)(stage.animation_time / 2.0f);
	if (stage.transition_mode == 1) {
		if (stage.animation_time <= stage.count) {
			stage.transition_mode = 0;
		}
		else {
			stage.base_rad += d_rad;
			stage.count++;
		}
	}
	else if (stage.transition_mode == 2) {
		if (stage.animation_time <= stage.count) {
			stage.transition_mode = 0;
		}
		else {
			stage.base_rad -= d_rad;
			stage.count++;
		}
	}
	else {
		if (Event.key.GetPush(Event.key.UP)|| wheel_rot > 0 ) {
			if (stage.current_stage + 1 < STAGE_NUM) {
				stage.current_stage++;
				stage.transition_mode = 2;
				stage.count = 0;
			}
		}else if (Event.key.GetPush(Event.key.DOWN) || wheel_rot < 0 ) {
			if (stage.current_stage - 1 >= 0) {
				stage.current_stage--;
				stage.transition_mode = 1;
				stage.count = 0;
			}
		}
	}
	DrawCircleAA(-800,600,1030,100,GetColor(255,255,55),true);
	DrawCircleAA(-800, 530, 950, 100, GetColor(0,0, 0), true);
	Vector2D c = VGet(-800,565);
	debug.Print("base:%f",stage.base_rad);
	for (int i = 0; i < STAGE_NUM;i++) {
		float rad = -(i)*0.15f - stage.base_rad;
		DrawCircleAA(c.x + 990.0f*cos(rad),c.y + 990.0f*sin(rad),60*powf(((1.57f - abs(rad))/1.57f),1.5f),100,YELLOW,true);
		DrawCircleAA(c.x + 990.0f*cos(rad), c.y + 990.0f*sin(rad), 52 * powf(((1.57f - abs(rad)) / 1.57f),1.5f), 100, BLACK, true);
		DrawCircleAA(c.x + 990.0f*cos(rad), c.y + 990.0f*sin(rad), 50 * powf(((1.57f - abs(rad)) / 1.57f),1.5f), 100, WHITE, true);
		DrawFormatStringToHandle(c.x + 990.0f*cos(rad) + 100, c.y + 990.0f*sin(rad) - 20, GetColor(255, 255, 255), font_l, "STAGE %d", i + 1);
	}
	//if (stage.transition_mode == 0) {
		int brightness = (int)( (255.0f)*powf(abs((float)stage.count - (float)(stage.animation_time / 2.0f)) / (float)(stage.animation_time / 2.0f),2.0f));
		int col = GetColor(brightness,brightness,brightness);
		DrawLineAA(250,530,290,560,col,3.0f);
		DrawLineAA(290, 560,500,560, col, 3.0f);
		DrawLineAA(275, 550, 490, 550, col, 3.0f);

		DrawLineAA(500, 480, 550, 530, col, 3.0f);
		DrawLineAA(270, 480, 500, 480, col, 3.0f);
		

	//}
}

void gameStart() {
	int front_num = 0;
	for (int i = 0; i < manager.action_num;i++) {
		for (int j = 0; j < manager.action_num;j++) {
			if(manager.action_array[j].num == i){
				if (manager.action_array[j].is_valid && manager.action_array[j].type != -1) {
					stage.stage[stage.current_stage].me.action[front_num].action_mode = manager.action_array[j].type;
					front_num++;
					break;
				}
			}
		}
	}
	stage.stage[stage.current_stage].me.setActionNum(front_num);


	if (front_num == 0) {
		stage.load();
		sprintf(sk_alert.str,"コマンドが空です。最低１つは指定してください");
		sk_alert.count = 60;
		sk_alert.message();
	}
	else {
		Game.AddChild(&game_main);
	}
}

void editStart() {
	manager.reset();
	
	manager.load();
	manager.action_num = stage.stage[stage.current_stage].max_action_num;
	
	Game.AddChild(&edit_me);
}