#pragma once
#include "geometry.h"
#include <memory>


const int SLICES = 20;
const int STACKS = 20;


void drawGround(int nw=10, int nh=10);
void drawPoint(Vector position, double size);


class Enemy {
public:
	Enemy(Body body);
	virtual ~Enemy() = default;

	virtual void draw() = 0;
	
	void step();

protected:
	Body body;
};


class Snowman : public Enemy {
public:
	Snowman(Body body, double r, double h);
	~Snowman() override = default;

	void draw() override;

private:
	double r;
	double h;
};


class Armageddon : public Enemy {
public:
	Armageddon(Body body, double ri, double ro);
	~Armageddon() override = default;

	void draw() override;

private:
	double ri;
	double ro;
};
