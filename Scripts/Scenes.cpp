#include"Scenes.h"
#include"Alert.h"
int lock;
char Action::str[ACTION_NUM][10] = {
	"直進",
	"後進",
	"探索",
	"右折",
	"左折",
	"弾壱",
	"弾弐",
	"弾参"
};
char Action::explanation[ACTION_NUM][100] = {
	"前に進みます",
	"後ろにバックします",
	"自分に一番近い敵を見つけてその方向を向きます",
	"右に90度ターンします",
	"左に90度ターンします",
	"自分の進行方向に弾を１発撃ちます",
	"自分の進行方向に方向をずらして弾を3発ばらまきます",
	"自分の進行方向に弾を２連射します"
};
char Action::message[256] = "";

void gameMainLoop() {
	stage.stage[stage.current_stage]->loop();
	DrawCircle(stage.stage[stage.current_stage]->me.pos, 20, YELLOW, false);

	if (stage.stage[stage.current_stage]->me.hp <= 0 && game_main.sceneChild == nullptr) {
		Game.AddChild(&game_over);
	}
	int sum = 0;
	if (!stage.stage[stage.current_stage]->enemy.empty()) {
		for (int i = 0; i < stage.stage[stage.current_stage]->enemy.size(); i++) {
			if (stage.stage[stage.current_stage]->enemy[i].hp > 0) {
				sum++;
			}
		}
		if (sum == 0 && game_main.sceneChild == nullptr) {
			Game.AddChild(&game_clear);
			if ((stage.stage[stage.current_stage]->counter / 60.0f) < manager.hi_score[stage.current_stage]) {
				manager.hi_score[stage.current_stage] = stage.stage[stage.current_stage]->counter / 60.0f;
			}
			manager.save();
			stage.can_unlock_next = false;
			if (stage.current_stage +1 < STAGE_NUM) {
				if (manager.is_stage_valid[stage.current_stage + 1] == false) {
					manager.is_stage_valid[stage.current_stage + 1] = true;
					if ((stage.stage[stage.current_stage]->counter / 60.0f) < manager.hi_score[stage.current_stage]) {
						manager.hi_score[stage.current_stage] = stage.stage[stage.current_stage]->counter / 60.0f;
					}
					manager.save();
					manager.load();
					stage.can_unlock_next = true;
					
				}
			}
		}
	}
	DrawBox(0, 570, 900 * ((float)stage.stage[stage.current_stage]->me.hp / (float)stage.stage[stage.current_stage]->me.hp_point), 600, GetColor(200, 100, 100), true);

}


void editMeLoop() {

	//debug.Print("stage:%d", stage.current_stage);
	//DrawFormatString(120, 50, YELLOW, "未使用ポイント : %d", manager.point);
	//DrawFormatString(160,100,WHITE,"ATK : %d",stage.stage[stage.current_stage]->me.attack_point);
	//DrawFormatString(160, 140, WHITE, "SPD : %d", stage.stage[stage.current_stage]->me.speed_point);
	//DrawFormatString(160, 180, WHITE, "HP : %d", stage.stage[stage.current_stage]->me.hp_point);

	//float scale = 15.0f;
	//Vector2D atk, spd, hp,center;
	//center = VGet(200, 400);
	//atk = spd = hp = center;
	//atk += VGet(0.0f, -1.0f)*stage.stage[stage.current_stage]->me.attack_point*scale;
	//spd += VGet(0.866f, 0.5f)*stage.stage[stage.current_stage]->me.speed_point*scale;
	//hp += VGet(-0.866f, 0.5f)*stage.stage[stage.current_stage]->me.hp_point*scale;

	//DrawLine(center,center+VGet(0,-1)*scale*10,GRAY);
	//DrawLine(center, center + VGet(0.866f, 0.5f)*scale * 10, GRAY);
	//DrawLine(center, center + VGet(-0.866f, 0.5f)*scale * 10, GRAY);

	//DrawLine(atk,spd,YELLOW);
	//DrawLine(hp, spd, YELLOW);
	//DrawLine(atk, hp, YELLOW);

	//DrawCircle(atk,3,YELLOW,true);
	//DrawCircle(spd, 3, YELLOW, true);
	//DrawCircle(hp, 3, YELLOW, true);

	//////////////////////////////////////////////

	debug.Print("select:%d",manager.selected_unit);
	

	//draw
	for (int i = 0; i < manager.action_num; i++) {
		manager.action_array[i].draw(i, manager.action_array[i].num);
	}


	manager.selectType();
	manager.sort();




}
void upATK() {
	if(manager.point > 0){
		manager.point--;
		stage.stage[stage.current_stage]->me.attack_point++;
	}
}
void downATK(){
	if (stage.stage[stage.current_stage]->me.attack_point > 0) {
		manager.point++;
		stage.stage[stage.current_stage]->me.attack_point--;
	}
}
void upSPD() {
	if (manager.point > 0) {
		manager.point--;
		stage.stage[stage.current_stage]->me.speed_point++;
	}
}
void downSPD() {
	if (stage.stage[stage.current_stage]->me.speed_point > 0) {
		manager.point++;
		stage.stage[stage.current_stage]->me.speed_point--;
	}
}
void upHP() {
	if (manager.point > 0) {
		manager.point--;
		stage.stage[stage.current_stage]->me.hp_point++;
	}
}
void downHP() {
	if (stage.stage[stage.current_stage]->me.hp_point > 0) {
		manager.point++;
		stage.stage[stage.current_stage]->me.hp_point--;
	}
}

void reload() {
#ifdef DEBUG
	stage.load();
#endif
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

	int x = 100;
	int str_num = (int)(System.GetFrame() / 1) % 18;
	int col1 = GetColor(128, 128, 255);
	int col2 = GetColor(255, 255, 0);
	char str[18] = "the Battle of AIs";
	for (int i = 0; i < 18;i++) {
		if (i == str_num || i == 17-str_num) {
			DrawFormatStringFToHandle(x,200-GetFontSizeToHandle(font_ll),col2,font_ll,"%c",str[i]);
			x += GetDrawFormatStringWidthToHandle(font_ll,"%c",str[i]);
		}
		else
		{
			DrawFormatStringFToHandle(x, 200 - GetFontSizeToHandle(font_ll), col1, font_ll, "%c", str[i]);
			x += GetDrawFormatStringWidthToHandle(font_ll, "%c", str[i]);
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
		//stage.current_stage = (int)(stage.base_rad / -0.15f + 0.5f);
		stage.base_rad = -(stage.current_stage)*0.15f +0.05f;
		debug.Print("now:%d", stage.current_stage);

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
		else
		{
			
			
		}
	}
	DrawCircleAA(-800,600,1030,100,GetColor(255,255,55),true);
	DrawCircleAA(-800, 530, 950, 100, GetColor(0,0, 0), true);
	Vector2D c = VGet(-800,565);
	debug.Print("base:%f",stage.base_rad);
	for (int i = 0; i < STAGE_NUM; i++) {
		float rad = -(i)*0.15f - stage.base_rad;
		DrawCircleAA(c.x + 990.0f*cos(rad), c.y + 990.0f*sin(rad), 60 * powf(((1.57f - abs(rad)) / 1.57f), 1.5f), 100, YELLOW, true);
		DrawCircleAA(c.x + 990.0f*cos(rad), c.y + 990.0f*sin(rad), 52 * powf(((1.57f - abs(rad)) / 1.57f), 1.5f), 100, BLACK, true);
		DrawCircleAA(c.x + 990.0f*cos(rad), c.y + 990.0f*sin(rad), 50 * powf(((1.57f - abs(rad)) / 1.57f), 1.5f), 100, WHITE, true);
		DrawFormatStringToHandle(c.x + 990.0f*cos(rad) + 100, c.y + 990.0f*sin(rad) - 20, GetColor(255, 255, 255), font_l, "STAGE %d", i + 1);
		if (!manager.is_stage_valid[i]) {
			DrawExtendGraph(c.x + 990.0f*cos(rad) - 40 * powf(((1.57f - abs(rad)) / 1.57f), 1.5f), c.y + 990.0f*sin(rad) - 40 * powf(((1.57f - abs(rad)) / 1.57f), 1.5f), c.x + 990.0f*cos(rad) + 40 * powf(((1.57f - abs(rad)) / 1.57f), 1.5f), c.y + 990.0f*sin(rad) + 40 * powf(((1.57f - abs(rad)) / 1.57f), 1.5f), lock, true);
		}
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

		//if (Event.LMouse.GetOn(System.GetWindowX() / 2 + 180, 450, System.GetWindowX() / 2 + 380, 500)) {
			//Vector2D c = VGet(System.GetWindowX() / 2 + 280, 475);
			//float dist = GetDistance(c,VGet(Event.LMouse.GetX(),Event.LMouse.GetY()));
			/*for (int i = 50; i > 0; i-=5) {
				int cnt = (int)((System.GetFrame()+i) % 30);
				float rate = (float)cnt / 30.0f;
				float rad = (System.GetFrame() + i )%10;
				int col1 = GetColor(100 + 100*sin(rad), 100 + 100 * sin(rad), 35+35 * sin(rad));
				DrawBoxAA(System.GetWindowX() / 2 + 180 - i, 450 -i, System.GetWindowX() / 2 + 380+i, 500+i,col1,true);
			}*/
			
		//}
}

void gameStart() {
	int front_num = 0;
	for (int i = 0; i < manager.action_num;i++) {
		for (int j = 0; j < manager.action_num;j++) {
			if(manager.action_array[j].num == i){
				if (manager.action_array[j].is_valid && manager.action_array[j].type != -1) {
					stage.stage[stage.current_stage]->me.action[front_num].action_mode = manager.action_array[j].type;
					front_num++;
					break;
				}
			}
		}
	}
	stage.stage[stage.current_stage]->me.setActionNum(front_num);

	
	if (front_num == 0) {
		//stage.load();
		sprintf(sk_alert.str,"コマンドが空です。最低１つは指定してください");
		sk_alert.count = 60;
		sk_alert.message();
	}
	else {
		Game.AddChild(&game_main);
	}
}

void editStart() {
	if (manager.is_stage_valid[stage.current_stage]) {
		manager.reset();
		manager.load();
		
		stage.load();
		manager.action_num = stage.stage[stage.current_stage]->max_action_num;
		
		
		
		stage.stage[stage.current_stage]->me.hp_point = 10;
		Game.AddChild(&edit_me);
	}
	else {
		sprintf(sk_alert.str, "ロックが解除されていません");
		sk_alert.count = 60;
		sk_alert.message();
	}
}

void backToTitle() {
	sk_alert.count = 60;
	sprintf(sk_alert.str,"タイトル画面に戻ります");
	sk_alert.scene = &title;
	sk_alert.message();

}


void gameOverLoop() {
	stage.stage[stage.current_stage]->result_counter++;
	int cnt = stage.stage[stage.current_stage]->result_counter;
	int limit = 60, range = 60;
	int col;

	int cy = 180;
	int h = 60;
	int dx = 60;
	int w = 60;
	int x1 = 900 - 810 * ((float)cnt / 30.0f);
	int x2 = (810 - w) *((float)cnt / 30.0f);
	if (cnt > 30) {
		x1 = 90;
		x2 = 810 - w;
	}
	if (cnt < 60) {
		col = GetColor(200 - 200 * ((float)abs(range - cnt) / range), 30 - 30 * ((float)abs(-cnt + range) / range), 30 - 30 * ((float)abs(-cnt + range) / range));
		
	}
	else {
		col = GetColor(200, 30, 30);
		
	}

	DrawLineAA(90, 180, 170, 120, col);
	DrawLineAA(90, 180, 170, 240, col);
	DrawLineAA(170, 240, 740, 240, col);
	DrawLineAA(170, 120, 740, 120, col);
	DrawLineAA(810, 180, 740, 240, col);
	DrawLineAA(810, 180, 740, 120, col);

	DrawQuadrangleAA(x1, cy, x1 + w, cy, x1 + dx + w, cy + h, x1 + dx, cy + h, RED, true);
	DrawQuadrangleAA(x1, cy, x1 + w, cy, x1 + dx + w, cy - h, x1 + dx, cy - h, RED, true);

	DrawQuadrangleAA(x2, cy, x2 + w, cy, x2 - dx + w, cy + h, x2 - dx, cy + h, RED, true);
	DrawQuadrangleAA(x2, cy, x2 + w, cy, x2 - dx + w, cy - h, x2 - dx, cy - h, RED, true);

	DrawFormatStringFToHandle(180, 140, col, font_ll, "GAME OVER");
	
}
void gameClearLoop() {
	stage.stage[stage.current_stage]->result_counter++;
	int cnt = stage.stage[stage.current_stage]->result_counter;
	int limit = 100, range = 100;
	int col;

	int cy = 180;
	int h = 60;
	int dx = 60;
	int w = 60;
	int x1 = 900 - 890 * ((float)cnt / 30.0f);
	int x2 = (890 - w) *((float)cnt / 30.0f);
	if (cnt > 30) {
		x1 = 10;
		x2 = 890 - w;
	}
	if (cnt < range) {
		col = GetColor(255 - 255 * ((float)abs(range - cnt) / range), 255 - 255 * ((float)abs(-cnt + range) / range), 30 - 30 * ((float)abs(-cnt + range) / range));
		
	}
	else {
		col = GetColor(255, 255, 30);
		
	}
	DrawLineAA(50, 180, 120, 120, col);
	DrawLineAA(50, 180, 120, 240, col);
	DrawLineAA(120, 240, 770, 240, col);
	DrawLineAA(120, 120, 770, 120, col);
	DrawLineAA(840, 180, 770, 240, col);
	DrawLineAA(840, 180, 770, 120, col);
	
	DrawQuadrangleAA(x1, cy, x1 + w, cy, x1 + dx + w, cy + h, x1 + dx, cy + h, YELLOW, true);
	DrawQuadrangleAA(x1, cy, x1 + w, cy, x1 + dx + w, cy - h, x1 + dx, cy - h, YELLOW, true);

	DrawQuadrangleAA(x2, cy, x2 + w, cy, x2 - dx + w, cy + h, x2 - dx, cy + h, YELLOW, true);
	DrawQuadrangleAA(x2, cy, x2 + w, cy, x2 - dx + w, cy - h, x2 - dx, cy - h, YELLOW, true);

	DrawFormatStringFToHandle(100, 140, col, font_ll, "Congratulations!");

	DrawFormatStringFToHandle(100, 300, col, font_l, "残りHP　: %d / 10",stage.stage[stage.current_stage]->me.hp);
	DrawFormatStringFToHandle(100, 400, col, font_l, "クリア時間　: %.2f 秒",stage.stage[stage.current_stage]->counter/60.0f);
	if (manager.hi_score[stage.current_stage] != 10000.00f) {
		DrawFormatStringFToHandle(100, 450, col, font_l, "ハイスコア　: %.2f 秒", manager.hi_score[stage.current_stage]);
	}
	

	if (stage.can_unlock_next) {
		DrawCircleAA(60,520,35,50,col,true);
		DrawStringToHandle(55,490,"!",BLACK,font_ll);
		DrawFormatStringFToHandle(100, 500, col, font_l, "次のステージが解禁されました");
	}
}



void howLoop() {
	DrawLine(50, 40, 850, 40, WHITE, 8);
	DrawFormatStringFToHandle(380, 50,YELLOW, font_l, "遊び方");
	DrawLine(550, 60, 800, 60, WHITE, 8);
	DrawLine(550, 80, 750, 80, WHITE, 8);
	DrawLine(350, 60, 100, 60, WHITE, 8);
	DrawLine(350, 80, 150, 80, WHITE, 8);
	DrawLine(200, 100, 700, 100, WHITE, 8);

	DrawFormatStringFToHandle(50, 150, WHITE, font_m, "21XX年、戦闘は全て自動化されたAIによって行われており、戦争で人間が死ぬことはなくなった。");
	DrawFormatStringFToHandle(50, 170, WHITE, font_m, "AIの能力は日々進歩し続けているが、そんな未来においてもAIの強さというものは");
	DrawFormatStringFToHandle(50, 190, WHITE, font_m, "依然として人間であるAIの設計者に依存している。");
	DrawFormatStringFToHandle(50, 210, WHITE, font_m, "今日は君がそのAIの設計者となり、その手腕を存分に発揮してもらいたい");
	DrawFormatStringFToHandle(50, 230, WHITE, font_m, "健闘を祈る...");
	DrawBox(40,140,850,260,GetColor(150,150,0),false);

	DrawFormatStringFToHandle(70, 280, WHITE, font_m, "基本操作");
	DrawFormatStringFToHandle(100, 310, WHITE, font_m, "エンターキーで決定・進む");
	DrawFormatStringFToHandle(100, 330, WHITE, font_m, "backspaceキーで戻る");
	DrawFormatStringFToHandle(100, 350, WHITE, font_m, "その他ボタンなど");
	
	DrawFormatStringFToHandle(100, 150, WHITE, font_m, "");
	DrawFormatStringFToHandle(100, 150, WHITE, font_m, "");
	DrawFormatStringFToHandle(100, 150, WHITE, font_m, "");


}