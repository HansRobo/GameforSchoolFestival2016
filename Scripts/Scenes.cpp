#include"Scenes.h"

void gameMainLoop() {
	stage.stage[stage.current_stage].loop();
	DrawCircle(stage.stage[0].me.pos, 30, YELLOW, false);

}


void editMeLoop() {
	DrawFormatString(120, 50, YELLOW, "���g�p�|�C���g : %d", manager.point);
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

}

void stageSelectLoop() {

}