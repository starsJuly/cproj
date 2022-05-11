#include "Vector3D.h"
#include <stdio.h>
#include <assert.h>

#define Vector_assert( _va_vector, _va_x, _va_y, _va_z, _va_str ) assert((_va_vector).x == (_va_x) && (_va_vector).y == (_va_y) && (_va_vector).z == (_va_z) && _va_str )

#define Print_test( _pt_func, _pt_str ) printf("\r" #_pt_func "\t\t: " _pt_str )

#define STR_PASS "Passed"
#define STR_FAIL "Failed"

void test_Vector3D_multiply() {
	Print_test(test_Vector3D_multiply, "");
	const Vector3D v1{ 2,3,5 }, v2{ 3,5,7 };
	const float val = 2;
	Vector3D tmp{};
	tmp = v1 * val;
	Vector_assert(tmp, 4, 6, 10,  "vector * value" );
	tmp = val * v1;
	Vector_assert(tmp, 4, 6, 10,  "value * vector" );
	tmp = v1 * v2;
	Vector_assert(tmp, 6, 15, 35, "vector * vector");
	tmp = v2 * v1;
	Vector_assert(tmp, 6, 15, 35, "vector * vector");
	tmp = v1, tmp *= val;
	Vector_assert(tmp, 4, 6, 10,  "vector *= value");
	tmp = v1, tmp *= v2;
	Vector_assert(tmp, 6, 15, 35, "vector *= vector");
	tmp = v1, tmp *= (v1 * v2) * 2;
	Vector_assert(tmp, 24, 90, 350, "vector *= vector");
	tmp = v1 * v1 * v1;
	Vector_assert(tmp, 8, 27, 125, "vector * vector * vector");
	tmp = val * v1 * val;
	Vector_assert(tmp, 8, 12, 20, "value * vector * value");
	tmp = v1 * val * v1;
	Vector_assert(tmp, 8, 18, 50, "vector * value * vector");
	Print_test(test_Vector3D_multiply, STR_PASS "\n");
}

void test_Vector3D_plus() {
	Print_test(test_Vector3D_plus, "");
	const Vector3D v1{ 2,3,5 }, v2{ 3,5,7 };
	const float val = 2;
	Vector3D tmp{};
	tmp = v1 + val;
	Vector_assert(tmp, 4, 5, 7, "vector + value");
	tmp = val + v1;
	Vector_assert(tmp, 4, 5, 7, "value + vector");
	tmp = v1 + v2;
	Vector_assert(tmp, 5, 8, 12, "vector + vector");
	tmp = v2 + v1;
	Vector_assert(tmp, 5, 8, 12, "vector + vector");
	tmp = v1, tmp += val;
	Vector_assert(tmp, 4, 5, 7, "vector += value");
	tmp = v1, tmp += v2;
	Vector_assert(tmp, 5, 8, 12, "vector += vector");
	tmp = v1, tmp += (v1 + v2) + 2;
	Vector_assert(tmp, 9, 13, 19, "vector += vector");
	tmp = v1 + v1 + v1;
	Vector_assert(tmp, 6, 9, 15, "vector + vector + vector");
	tmp = val + v1 + val;
	Vector_assert(tmp, 6, 7, 9, "value + vector + value");
	tmp = v1 + val + v1;
	Vector_assert(tmp, 6, 8, 12, "vector + value + vector");
	Print_test(test_Vector3D_plus, STR_PASS "\n");
}


void test_Vector3D_subtract() {
	Print_test(test_Vector3D_subtract, "");
	const Vector3D v1{ 2,3,5 }, v2{ 3,5,7 };
	const float val = 2;
	Vector3D tmp{};
	tmp = v1 - val;
	Vector_assert(tmp, 0, 1, 3, "vector - value");
	tmp = v1 - v2;
	Vector_assert(tmp, -1, -2, -2, "vector - vector");
	tmp = v2 - v1;
	Vector_assert(tmp, 1, 2, 2, "vector - vector");
	tmp = v1, tmp -= val;
	Vector_assert(tmp, 0, 1, 3, "vector -= value");
	tmp = v1, tmp -= v2;
	Vector_assert(tmp, -1, -2, -2, "vector -= vector");
	tmp = v1, tmp -= (v1 - v2) - 2;
	Vector_assert(tmp, 5, 7, 9, "vector -= vector");
	tmp = v1 - v1 - v1;
	Vector_assert(tmp, -2, -3, -5, "vector - vector - vector");
	tmp = v1 - val - v1;
	Vector_assert(tmp, -2, -2, -2, "vector - value - vector");
	Print_test(test_Vector3D_subtract, STR_PASS "\n");
}


void test_Vector3D_divide() {
	Print_test(test_Vector3D_divide, "");
	const Vector3D v1{ 2,3,5 }, v2{ 3,5,7 };
	const float val = 2;
	Vector3D tmp{};
	//tmp = v1 / val;
	//Vector_assert(tmp, 0, 1, 3, "vector / value");
	//tmp = v1 / v2;
	//Vector_assert(tmp, /1, /2, /2, "vector / vector");
	//tmp = v2 / v1;
	//Vector_assert(tmp, 1, 2, 2, "vector / vector");
	tmp = v1, tmp /= val;
	Vector_assert(tmp, 1.0f, 1.5f, 2.5f, "vector /= value");
	/*tmp = v1, tmp /= v2;
	Vector_assert(tmp, /1, /2, /2, "vector /= vector");
	tmp = v1, tmp /= (v1 / v2) / 2;
	Vector_assert(tmp, 5, 7, 9, "vector /= vector");
	tmp = v1 / v1 / v1;
	Vector_assert(tmp, /2, /3, /5, "vector / vector / vector");
	tmp = v1 / val / v1;
	Vector_assert(tmp, /2, /2, /2, "vector / value / vector");*/
	Print_test(test_Vector3D_divide, STR_PASS "\n");
}


namespace scope {
	extern void at();
}

namespace {
	int va;
}

#define UNIT_TEST
#ifdef UNIT_TEST
int main() {
	va = 2, scope::at();
	test_Vector3D_multiply();
	test_Vector3D_plus();
	test_Vector3D_subtract();
	test_Vector3D_divide();
	return 0;
}
#endif // UNIT_TEST
