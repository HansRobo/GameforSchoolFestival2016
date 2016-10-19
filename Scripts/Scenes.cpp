#include"Scenes.h"

void gameMainLoop() {
	stage.stage[stage.current_stage].loop();
	DrawCircle(stage.stage[0].me.pos, 30, YELLOW, false);

}


void editMeLoop() {
	DrawFormatString(70, 50, YELLOW, "未使用ポイント : %d", manager.point);
	DrawFormatString(110,100,WHITE,"ATK : %d",stage.stage[stage.current_stage].me.attack_point);
	DrawFormatString(110, 140, WHITE, "SPD : %d", stage.stage[stage.current_stage].me.speed_point);
	DrawFormatString(110, 180, WHITE, "HP : %d", stage.stage[stage.current_stage].me.hp_point);

	float scale = 30.0f;
	Vector2D atk, spd, hp,center;
	center = VGet(550, 350);
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

	DrawCircle(atk,10,YELLOW,true);
	DrawCircle(spd, 10, YELLOW, true);
	DrawCircle(hp, 10, YELLOW, true);
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