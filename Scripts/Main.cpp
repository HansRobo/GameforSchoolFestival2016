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
	edit_me.SetButton( 100, 500, 300, 550, GetColor(128, 255, 128), "GAME START", BLACK, &game_main);
	//edit_me.input.AddEventListener(Event.key.RETURN, &game_main);

	edit_me.SetButton(200, 85, 250, 115, YELLOW, "��", BLACK, upATK);
	edit_me.SetButton(40, 85, 90, 115, YELLOW, "��", BLACK, downATK);
	edit_me.SetButton(200, 125, 250, 155, YELLOW, "��", BLACK, upSPD);
	edit_me.SetButton(40, 125, 90, 155, YELLOW, "��", BLACK, downSPD);
	edit_me.SetButton(200, 165, 250, 195, YELLOW, "��", BLACK, upHP);
	edit_me.SetButton(40, 165, 90, 195, YELLOW, "��", BLACK, downHP);

	game_main.SetButton(System.GetWindowX()-80,20,System.GetWindowX()-20,80,GetColor(255,255,0),"�߂�",BLACK,&title);
	game_main.input.AddEventListener(Event.EVERY_FRAME,gameMainLoop);
	game_main.input.AddEventListener(Event.key.R, reload);




	Game.AddChild(&title);

}

void suken::GameLoopEnter(){
	
}

void suken::GameLoopExit(){
	debug.Print("Hello!!!");
}