#ifndef VECTOR_3D_H_
#define VECTOR_3D_H
#include <iostream>
#include <math.h>

struct Vector3D {
	float x, y, z;
	float length() const;
	void normalize();
};


Vector3D operator*(const Vector3D&, float);
Vector3D operator*(float, const Vector3D&);
Vector3D operator*(const Vector3D&, const Vector3D&);
Vector3D&& operator*(Vector3D&&, float);
Vector3D&& operator*(float, Vector3D&&);
Vector3D&& operator*(Vector3D&&,const Vector3D&&);
Vector3D& operator*=(Vector3D&, float);
Vector3D& operator*=(Vector3D&, const Vector3D&);
Vector3D& operator*=(Vector3D&,const Vector3D&&);

Vector3D operator+(const Vector3D&, float);
Vector3D operator+(float,const Vector3D&);
Vector3D operator+(const Vector3D&,const Vector3D&);
Vector3D&& operator+(Vector3D&&, float);
Vector3D&& operator+(float, Vector3D&&);
Vector3D&& operator+(Vector3D&&,const Vector3D&&);
Vector3D& operator+=(Vector3D&, float);
Vector3D& operator+=(Vector3D&,const Vector3D&);
Vector3D& operator+=(Vector3D&, const Vector3D&&);

Vector3D operator-(const Vector3D&, float);
//Vector3D operator-(float, const Vector3D&);
Vector3D operator-(const Vector3D&, const Vector3D&);
Vector3D&& operator-(Vector3D&&, float);
//Vector3D&& operator-(float, Vector3D&&);
Vector3D&& operator-(Vector3D&&, const Vector3D&&);
Vector3D& operator-=(Vector3D&, float);
Vector3D& operator-=(Vector3D&,const Vector3D&);
Vector3D& operator-=(Vector3D&, const Vector3D&&);

Vector3D& operator/=(Vector3D&, float);


inline Vector3D operator*(const Vector3D& vector, float val) {
	return { vector.x * val, vector.y * val, vector.z * val };
}
inline Vector3D operator*(float val, const Vector3D& vector)
{
	return { vector.x * val, vector.y * val, vector.z * val };
}
inline Vector3D operator*(const Vector3D& vector1, const Vector3D& vector2)
{
	return { vector1.x * vector2.x,vector1.y * vector2.y,vector1.z * vector2.z };
}
inline Vector3D&& operator*(float val, Vector3D&& vector)
{
	vector.x *= val, vector.y *= val, vector.z *= val;
	return static_cast<Vector3D&&>(vector);
}
inline Vector3D&& operator*(Vector3D&& vector, float val) {
	vector.x *= val, vector.y *= val, vector.z *= val;
	return static_cast<Vector3D&&>(vector);
}
inline Vector3D&& operator*(Vector3D&& vector1, const Vector3D&& vector2) {
	vector1.x *= vector2.x, vector1.y *= vector2.y, vector1.z *= vector2.z;
	return static_cast<Vector3D&&>(vector1);
}
inline Vector3D& operator*=(Vector3D& vector, float val) {
	vector.x *= val, vector.y *= val, vector.z *= val;
	return vector;
}
inline Vector3D& operator*=(Vector3D& vector1, const Vector3D&& vector2) {
	return operator*=(vector1, vector2);
}
inline Vector3D& operator*=(Vector3D& vector1, const Vector3D& vector2) {
	vector1.x *= vector2.x, vector1.y *= vector2.y, vector1.z *= vector2.z;
	return vector1;
}


inline Vector3D operator+(const Vector3D& vector, float value)
{
	return { vector.x + value, vector.y + value, vector.z + value };
}
inline Vector3D operator+(float value, const Vector3D& vector)
{
	return { vector.x + value, vector.y + value, vector.z + value };
}
inline Vector3D operator+(const Vector3D& vector1, const Vector3D& vector2)
{
	return { vector1.x + vector2.x, vector1.y + vector2.y, vector1.z + vector2.z };
}
inline Vector3D&& operator+(float value, Vector3D&& vector)
{
	vector.x += value, vector.y += value, vector.z += value;
	return static_cast<Vector3D&&>(vector);
}
inline Vector3D&& operator+(Vector3D&& vector, float value)
{
	vector.x += value, vector.y += value, vector.z += value;
	return static_cast<Vector3D&&>(vector);
}
inline Vector3D&& operator+(Vector3D&& vector1, const Vector3D&& vector2)
{
	vector1.x += vector2.x, vector1.y += vector2.y, vector1.z += vector2.z;
	return static_cast<Vector3D&&>(vector1);
}
inline Vector3D& operator+=(Vector3D& vector, float value)
{
	vector.x += value, vector.y += value, vector.z += value;
	return vector;
}
inline Vector3D& operator+=(Vector3D& vector1, const Vector3D&& vector2)
{
	return operator+=(vector1, vector2);
}
inline Vector3D& operator+=(Vector3D& vector1, const Vector3D& vector2)
{
	vector1.x += vector2.x, vector1.y += vector2.y, vector1.z += vector2.z;
	return vector1;
}


inline Vector3D operator-(const Vector3D& vector, float value)
{
	return { vector.x - value, vector.y - value, vector.z - value };
}
inline Vector3D operator-(const Vector3D& vector1, const Vector3D& vector2)
{
	return { vector1.x - vector2.x, vector1.y - vector2.y, vector1.z - vector2.z };
}
inline Vector3D&& operator-(Vector3D&& vector, float value)
{
	vector.x -= value, vector.y -= value, vector.z -= value;
	return static_cast<Vector3D&&>(vector);
}
inline Vector3D&& operator-(Vector3D&& vector1, const Vector3D&& vector2)
{
	vector1.x -= vector2.x, vector1.y -= vector2.y, vector1.z -= vector2.z;
	return static_cast<Vector3D&&>(vector1);
}
inline Vector3D& operator-=(Vector3D& vector, float value)
{
	vector.x -= value, vector.y -= value, vector.z -= value;
	return vector;
}
inline Vector3D& operator-=(Vector3D& vector1, const Vector3D&& vector2)
{
	return operator-=(vector1, vector2);
}
inline Vector3D& operator-=(Vector3D& vector1, const Vector3D& vector2)
{
	vector1.x -= vector2.x, vector1.y -= vector2.y, vector1.z -= vector2.z;
	return vector1;
}


inline Vector3D& operator/=(Vector3D& vector, float value) {
	vector.x /= value, vector.y /= value, vector.z /= value;
	return vector;
}


inline float Vector3D::length() const {
	return  sqrt( x * x + y * y + z * z );
}

inline void Vector3D::normalize() {
	const float length = this->length();
	if (!length) return;
	x = x / length, y = y / length, z = z / length;
}

#endif // !VECTOR_3D_H_
