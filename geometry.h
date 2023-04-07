#pragma once
#include <iostream>


const double PI = 3.14159;
const double R2D = 180 / PI;
const double D2R = 1 / R2D;
const double GY = -0.0002;


struct Vector {
	Vector(double x, double y, double z);
	Vector();
	double norm() const;
	Vector unit() const;
	Vector rotate(Vector a, double deg) const;
	
	Vector operator+ (Vector v) const;
	Vector& operator+= (Vector v);
	Vector operator- (Vector v) const;
	Vector& operator-= (Vector v);
	Vector operator* (double f) const;
	Vector& operator*= (double f);
	Vector operator/ (double f) const;
	Vector& operator/= (double f);
	Vector operator- () const;

	double x;
	double y;
	double z;
};


std::ostream& operator<< (std::ostream& s, Vector v);


Vector operator* (double f, Vector v);
double dot(Vector v1, Vector v2);
Vector cross(Vector v1, Vector v2);


struct Body {
	Body(
		Vector pos,
		Vector dir,
		double dp,
		Vector rot,
		double deg,
		double da
	);

	Vector pos;
	Vector dir;
	double dp;
	Vector rot;
	double deg;
	double da;
};