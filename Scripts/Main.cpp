#include "Suken.h"
#include"Stage.h"
#include"Scenes.h"
#include"Alert.h"
int font_l,font_m,font_ll;

StageManager stage;
CScene title,game_main,edit_me,stage_select,alert, game_clear, game_over;
MeManager manager;


void suken::Awake(){
	AddFontFromPath("Assets_Y68/Fonts/AozoraMinchoHeavy.ttf");
	ChangeFont("‚ ‚¨‚¼‚ç–¾’© Heavy");
	font_ll = CreateFontToHandle("‚ ‚¨‚¼‚ç–¾’© Heavy", 72, -1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4,-1,4);
	font_l = CreateFontToHandle("‚ ‚¨‚¼‚ç–¾’© Heavy",48,-1, DX_FONTTYPE_ANTIALIASING_4X4);
	font_m = CreateFontToHandle("‚ ‚¨‚¼‚ç–¾’© Heavy", 20, -1, DX_FONTTYPE_ANTIALIASING_4X4);
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_8X8);
	stage.load();
	manager.load();
	
	alert.input.AddEventListener(Event.EVERY_FRAME,alertLoop);

	title.input.AddEventListener(Event.EVERY_FRAME, titleLoop);
	title.SetButton(System.GetWindowX()/2-100,400,System.GetWindowX()/2+100,450,GetColor(128,255,128),"SELECT STAGE",BLACK,&stage_select);
	title.input.AddEventListener(Event.key.RETURN,&stage_select);
	//title.SetMusic("Assets_Y68/Music/history.mp3");

	stage_select.input.AddEventListener(Event.EVERY_FRAME, stageSelectLoop);
	stage_select.SetButton(System.GetWindowX() / 2 + 100, 450, System.GetWindowX() / 2 + 300, 500, GetColor(128, 255, 128), "SELECT STAGE", BLACK, editStart);
	stage_select.input.AddEventListener(Event.key.RETURN, editStart);
	stage_select.SetButton(System.GetWindowX() - 80, 20, System.GetWindowX() - 20, 80, GetColor(255, 255, 0), "–ß‚é", BLACK, backToTitle);
	stage_select.input.AddEventListener(Event.key.BACK, backToTitle);

	int SIHandle = MakeARGB8ColorSoftImage(100,100);
	FillSoftImage(SIHandle, 0, 0, 0, 0);
	DrawCircleSoftImage(SIHandle,50,35,25,30,30,150,128);
	DrawCircleSoftImage(SIHandle, 50, 35, 12, 0, 0, 0, 0);
	for (int i = 0; i < 100;i++) {
		for (int j = 36; j < 100;j++) {
			DrawPixelSoftImage(SIHandle,i,j,0,0,0,0);
		}
	}
	for (int i = 20; i <= 80;i++) {
		for (int j = 40; j <= 80;j++) {
			DrawPixelSoftImage(SIHandle,i,j,30,30,150,128);
		}
	}
	DrawCircleSoftImage(SIHandle, 50, 65, 7, 0, 0, 0, 0);
	for (int i = 47; i <= 53;i++) {
		for (int j = 50; j <= 65;j++) {
			DrawPixelSoftImage(SIHandle, i, j, 0, 0, 0, 0);
		}
	}
	lock = CreateGraphFromSoftImage(SIHandle);

	edit_me.input.AddEventListener(Event.EVERY_FRAME, editMeLoop);
	edit_me.SetButton( 500, 500, 700, 550, GetColor(128, 255, 128), "GAME START", BLACK, gameStart);
	//edit_me.input.AddEventListener(Event.key.RETURN, &game_main);

	int x_1 = 250;
	int x_2 = 90;
	int y = 85;
	edit_me.SetButton(x_1, y, x_1+50, y+30, YELLOW, "¨", BLACK, upATK);
	edit_me.SetButton(x_2, y, x_2+50, y+30, YELLOW, "©", BLACK, downATK);
	edit_me.SetButton(x_1, y+40, x_1 + 50, y + 70, YELLOW, "¨", BLACK, upSPD);
	edit_me.SetButton(x_2, y+40, x_2 + 50, y + 70, YELLOW, "©", BLACK, downSPD);
	edit_me.SetButton(x_1, y+80, x_1 + 50, y + 110, YELLOW, "¨", BLACK, upHP);
	edit_me.SetButton(x_2, y+80, x_2 + 50, y + 110, YELLOW, "©", BLACK, downHP);
	edit_me.SetButton(System.GetWindowX() - 80, 20, System.GetWindowX() - 20, 80, GetColor(255, 255, 0), "–ß‚é", BLACK, &stage_select);
	x_1 = 400;
	

	game_main.SetButton(System.GetWindowX()-80,20,System.GetWindowX()-20,80,GetColor(255,255,0),"–ß‚é",BLACK,&backToTitle);
	game_main.input.AddEventListener(Event.EVERY_FRAME,gameMainLoop);
	game_main.input.AddEventListener(Event.key.R, reload);
	//game_main.SetMusic("Assets_Y68/Music/wen-kamuy2.mp3");

	game_over.input.AddEventListener(Event.EVERY_FRAME,gameOverLoop);
	game_over.SetButton(System.GetWindowX() - 80, 20, System.GetWindowX() - 20, 80, GetColor(255, 255, 0), "–ß‚é", BLACK, &backToTitle);

	game_clear.input.AddEventListener(Event.EVERY_FRAME, gameClearLoop);
	game_clear.SetButton(System.GetWindowX() - 80, 20, System.GetWindowX() - 20, 80, GetColor(255, 255, 0), "–ß‚é", BLACK, &backToTitle);

	Game.AddChild(&title);

}

void suken::GameLoopEnter(){
	
}

void suken::GameLoopExit(){
	debug.Print("Hello!!!");
}