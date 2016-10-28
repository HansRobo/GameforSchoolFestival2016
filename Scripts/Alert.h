#pragma once
#include"Suken.h"
#include"Manager.h"


class Alert {
private:
	CScene *parent;
public:
	Alert() {
		parent = nullptr;
		count = -1;
		scene = nullptr;
	}
	void message() {
		parent = (Game.GetCurrentScene());
		Game.GetCurrentScene()->AddChild(&alert);

	}
	void loop() {
		if (count == -1) {
			if (Event.key.GetDown(Event.key.RETURN) || Event.LMouse.GetRelease(0, 0, 0, 0)) {
				parent->RemoveChild();
			}
		}
		else {
			count--;
			if (count == 0) {
				parent->RemoveChild();
				if (scene != nullptr) {
					Game.AddChild(scene);
					scene = nullptr;
				}
				count = -1;
			}
		}

		int	space = 20;
		DrawBox(System.GetWindowX() / 2 - GetDrawStringWidthToHandle(str, strlen(str), font_m) / 2 - space, System.GetWindowY() / 2 - GetFontSizeToHandle(font_m) / 2 - space,
			System.GetWindowX() / 2 + GetDrawStringWidthToHandle(str, strlen(str), font_m) / 2 + space, System.GetWindowY() / 2 + GetFontSizeToHandle(font_m) / 2 + space,
			GetColor(100,100,200),true
			);
		space -= 10;
		DrawBox(System.GetWindowX() / 2 - GetDrawStringWidthToHandle(str, strlen(str), font_m) / 2 - space, System.GetWindowY() / 2 - GetFontSizeToHandle(font_m) / 2 - space,
			System.GetWindowX() / 2 + GetDrawStringWidthToHandle(str, strlen(str), font_m) / 2 + space, System.GetWindowY() / 2 + GetFontSizeToHandle(font_m) / 2 + space,
			WHITE, true
		);
		DrawStringToHandle(System.GetWindowX()/2-GetDrawStringWidthToHandle(str,strlen(str),font_m)/2, System.GetWindowY() / 2 - GetFontSizeToHandle(font_m) / 2,str,BLACK,font_m);
	}
	char str[256];
	int count;
	CScene *scene;

};

void alertLoop();

extern Alert sk_alert;

class TitleManager {
public:
	bool is_transition;
};

