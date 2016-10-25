#include "Suken.h"
#include"Stage.h"
#include"Scenes.h"
#include"Alert.h"
int font_l,font_m;

StageManager stage;
CScene title,game_main,edit_me,stage_select,alert, game_clear, game_over;
MeManager manager;


void suken::Awake(){
	AddFontFromPath("Assets_Y68/Fonts/AozoraMinchoHeavy.ttf");
	font_l = CreateFontToHandle("Ç†Ç®ÇºÇÁñæí© Heavy",48,-1, DX_FONTTYPE_ANTIALIASING_4X4);
	font_m = CreateFontToHandle("Ç†Ç®ÇºÇÁñæí© Heavy", 20, -1, DX_FONTTYPE_ANTIALIASING_4X4);
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_8X8);
	stage.load();
	manager.load();
	
	alert.input.AddEventListener(Event.EVERY_FRAME,alertLoop);

	title.input.AddEventListener(Event.EVERY_FRAME, titleLoop);
	title.SetButton(System.GetWindowX()/2-100,400,System.GetWindowX()/2+100,450,GetColor(128,255,128),"SELECT STAGE",BLACK,&stage_select);
	title.input.AddEventListener(Event.key.RETURN,&stage_select);

	stage_select.input.AddEventListener(Event.EVERY_FRAME, stageSelectLoop);
	stage_select.SetButton(System.GetWindowX() / 2 + 100, 450, System.GetWindowX() / 2 + 300, 500, GetColor(128, 255, 128), "SELECT STAGE", BLACK, editStart);
	stage_select.input.AddEventListener(Event.key.RETURN, editStart);

	edit_me.input.AddEventListener(Event.EVERY_FRAME, editMeLoop);
	edit_me.SetButton( 500, 500, 700, 550, GetColor(128, 255, 128), "GAME START", BLACK, gameStart);
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
	

	game_main.SetButton(System.GetWindowX()-80,20,System.GetWindowX()-20,80,GetColor(255,255,0),"ñﬂÇÈ",BLACK,&backToTitle);
	game_main.input.AddEventListener(Event.EVERY_FRAME,gameMainLoop);
	game_main.input.AddEventListener(Event.key.R, reload);




	Game.AddChild(&title);

}

void suken::GameLoopEnter(){
	
}

void suken::GameLoopExit(){
	debug.Print("Hello!!!");
}