#pragma once
#include"Suken.h"
#include"Manager.h"

class Bullet {
public:
	Bullet() {
		count = 0;
	}
	void loop() {
		count--;
		pos += VGet(cos(rad), sin(rad))*velocity;
		draw();
	}
	void draw() {
		int col = GetColor(255,255,128);
		
		DrawLineAA(pos.x + scale*cos(rad), pos.y + scale*sin(rad), pos.x + scale*cos(rad - 2.09f), pos.y + scale*sin(rad - 2.09f), col);
		DrawLineAA(pos.x + scale*cos(rad), pos.y + scale*sin(rad), pos.x + scale*cos(rad + 2.09f), pos.y + scale*sin(rad + 2.09f), col);
	}
	bool getValid() {
		return (count > 0);
	}
	Vector2D pos;
	float velocity;
	float rad;
	const float scale = 10.0f;
	int count;
	int damage;
};