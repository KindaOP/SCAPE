#include "geometry.h"
#include <math.h>
#include <string>
#include <sstream>
#include <iomanip>


Vector::Vector(double x, double y, double z)
	: x(x), y(y), z(z)
{}


Vector::Vector()
	: x(0), y(0), z(0)
{}


Vector Vector::operator+ (Vector v) const {
	return Vector(
		this->x + v.x,
		this->y + v.y,
		this->z + v.z
	);
}


Vector& Vector::operator+= (Vector v) {
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	return *this;
}


Vector Vector::operator- (Vector v) const {
	return Vector(
		this->x - v.x,
		this->y - v.y,
		this->z - v.z
	);
}


Vector& Vector::operator-= (Vector v) {
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	return *this;
}


Vector Vector::operator* (double f) const {
	return Vector(
		this->x * f,
		this->y * f,
		this->z * f
	);
}


Vector& Vector::operator*= (double f) {
	this->x *= f;
	this->y *= f;
	this->z *= f;
	return *this;
}


Vector Vector::operator/ (double f) const {
	return Vector(
		this->x / f,
		this->y / f,
		this->z / f
	);
}


Vector& Vector::operator/= (double f) {
	this->x /= f;
	this->y /= f;
	this->z /= f;
	return *this;
}


Vector Vector::operator- () const {
	return Vector(
		-this->x,
		-this->y,
		-this->z
	);
}


double Vector::norm() const {
	double n = 0;
	n += pow(this->x, 2);
	n += pow(this->y, 2);
	n += pow(this->z, 2);
	return sqrt(n);
}


Vector Vector::unit() const {
	return *this / this->norm();
}


Vector Vector::rotate(Vector a, double deg) const {
	const double rad = deg * D2R;
	const Vector& v = *this;
	const Vector k = a.unit();
	Vector vr;
	vr += v * cos(rad);
	vr += cross(k, v) * sin(rad);
	vr += k * dot(k, v) * (1 - cos(rad));
	return vr;
}


std::ostream& operator<< (std::ostream& s, Vector v) {
	static const int COUT_DEC = 2;
	std::stringstream ss;
	ss << "(";
	ss << std::fixed << std::setprecision(COUT_DEC) << v.x;
	ss << ", ";
	ss << std::fixed << std::setprecision(COUT_DEC) << v.y;
	ss << ", ";
	ss << std::fixed << std::setprecision(COUT_DEC) << v.z;
	ss << ")";
	std::string vecString = ss.str();
	s << vecString;
	return s;
}


Vector operator* (double f, Vector v) {
	return v * f;
}


double dot(Vector v1, Vector v2) {
	double d = 0;
	d += v1.x * v2.x;
	d += v1.y * v2.y;
	d += v1.z * v2.z;
	return d;
}


Vector cross(Vector v1, Vector v2) {
	return Vector(
		v1.y*v2.z - v1.z*v2.y,
		v1.z*v2.x - v1.x*v2.z,
		v1.x*v2.y - v1.y*v2.x
	);
}


Body::Body(
	Vector pos,
	Vector dir,
	double dp,
	Vector rot,
	double deg,
	double da
)
	: pos(pos), dir(dir), dp(dp), rot(rot), deg(deg), da(da)
{}