#pragma once
#include"Suken.h"
#include"Manager.h"

class Bullet {
public:
	Bullet() {
		count = 0;
	}
	void loop(Vector2D scrl) {
		count--;
		pos += VGet(cos(rad), sin(rad))*velocity;
		draw(scrl);
	}
	void draw(Vector2D scrl) {
		if (getValid()) {
			int col = GetColor(255, 255, 128);

			DrawLineAA(pos.x + scale*cos(rad) + scrl.x, pos.y + scale*sin(rad) + scrl.y, pos.x + scale*cos(rad - 2.09f) + scrl.x, pos.y + scale*sin(rad - 2.09f) + scrl.y, col);
			DrawLineAA(pos.x + scale*cos(rad) + scrl.x, pos.y + scale*sin(rad) + scrl.y, pos.x + scale*cos(rad + 2.09f) + scrl.x, pos.y + scale*sin(rad + 2.09f) + scrl.y, col);
		}
	}
	bool getValid() {
		return (count > 0);
	}
	Vector2D pos;
	float velocity;
	float rad;
	const float scale = 5.0f;
	int count;
};