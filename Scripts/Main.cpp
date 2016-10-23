#include "Suken.h"
#include"Stage.h"
#include"Scenes.h"


StageManager stage;
CScene title,game_main,edit_me,stage_select;
MeManager manager;


void suken::Awake(){
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_8X8);
	stage.load();
	manager.load();
	
	title.input.AddEventListener(Event.EVERY_FRAME, titleLoop);
	title.SetButton(System.GetWindowX()/2-100,400,System.GetWindowX()/2+100,450,GetColor(128,255,128),"SELECT STAGE",BLACK,&stage_select);
	title.input.AddEventListener(Event.key.RETURN,&stage_select);

	stage_select.input.AddEventListener(Event.EVERY_FRAME, stageSelectLoop);
	stage_select.SetButton(System.GetWindowX() / 2 - 100, 400, System.GetWindowX() / 2 + 100, 450, GetColor(128, 255, 128), "SELECT STAGE", BLACK, &edit_me);
	stage_select.input.AddEventListener(Event.key.RETURN, &edit_me);

	edit_me.input.AddEventListener(Event.EVERY_FRAME, editMeLoop);
	edit_me.SetButton( 500, 500, 700, 550, GetColor(128, 255, 128), "GAME START", BLACK, &game_main);
	//edit_me.input.AddEventListener(Event.key.RETURN, &game_main);

	int x_1 = 250;
	int x_2 = 90;
	int y = 85;
	edit_me.SetButton(x_1, y, x_1+50, y+30, YELLOW, "Å®", BLACK, upATK);
	edit_me.SetButton(x_2, y, x_2+50, y+30, YELLOW, "Å©", BLACK, downATK);
	edit_me.SetButton(x_1, y+40, x_1 + 50, y + 70, YELLOW, "Å®", BLACK, upSPD);
	edit_me.SetButton(x_2, y+40, x_2 + 50, y + 70, YELLOW, "Å©", BLACK, downSPD);
	edit_me.SetButton(x_1, y+80, x_1 + 50, y + 110, YELLOW, "Å®", BLACK, upHP);
	edit_me.SetButton(x_2, y+80, x_2 + 50, y + 110, YELLOW, "Å©", BLACK, downHP);

	x_1 = 400;
	

	game_main.SetButton(System.GetWindowX()-80,20,System.GetWindowX()-20,80,GetColor(255,255,0),"ñﬂÇÈ",BLACK,&title);
	game_main.input.AddEventListener(Event.EVERY_FRAME,gameMainLoop);
	game_main.input.AddEventListener(Event.key.R, reload);




	Game.AddChild(&title);

}

void suken::GameLoopEnter(){
	
}

void suken::GameLoopExit(){
	debug.Print("Hello!!!");
}