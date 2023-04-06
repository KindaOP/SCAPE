#pragma once


const float DEGREE = 180 / 3.14159;


struct Vector {
	Vector(float x, float y, float z);
	Vector();
	float norm();
	Vector unit();

	Vector operator/ (float f);
	Vector& operator/= (float f);

	float x;
	float y;
	float z;
};


struct Body {
	Body(
		Vector pos,
		Vector dir,
		float d,
		Vector ax,
		float da
	);

	Vector pos;
	Vector dir;
	float d;
	Vector ax;
	float da;
};