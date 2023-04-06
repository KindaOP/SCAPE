#include "geometry.h"
#include <math.h>


Vector::Vector(float x, float y, float z)
	: x(x), y(y), z(z)
{}


Vector::Vector()
	: x(0), y(0), z(0)
{}


Vector Vector::operator/ (float f) {
	Vector v;
	v.x = this->x / f;
	v.y = this->y / f;
	v.z = this->z / f;
	return v;
}


Vector& Vector::operator/= (float f) {
	this->x /= f;
	this->y /= f;
	this->z /= f;
	return *this;
}


float Vector::norm() {
	float n = 0;
	n += pow(this->x, 2);
	n += pow(this->y, 2);
	n += pow(this->z, 2);
	return sqrt(n);
}


Vector Vector::unit() {
	return *this / this->norm();
}


Body::Body(
	Vector pos,
	Vector dir,
	float d,
	Vector ax,
	float da
)
	: pos(pos), dir(dir), d(d), ax(ax), da(da)
{}