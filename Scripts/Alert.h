#pragma once
#include"Suken.h"
#include"Manager.h"


class Alert {
private:
	CScene *parent;
public:
	Alert() {
		parent = nullptr;
	}
	void message() {
		parent = (Game.GetCurrentScene());
		Game.GetCurrentScene()->AddChild(&alert);

	}
	void loop() {
		if (Event.key.GetDown(Event.key.RETURN) || Event.LMouse.GetRelease(0,0,0,0) ) {
			parent->RemoveChild();
		}
		
	}
	char str[256];


};

void alertLoop();

extern Alert sk_alert;

class TitleManager {
public:
	bool is_transition;
};

