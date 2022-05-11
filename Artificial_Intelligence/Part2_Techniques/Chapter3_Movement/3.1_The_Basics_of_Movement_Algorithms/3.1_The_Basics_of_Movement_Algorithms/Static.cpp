#include <stdio.h>
#include <Windows.h>
#include <assert.h>

#include "Vector3D.h"


typedef Vector3D Vector2_5D;
struct Static {
	Vector2_5D position;	// a 2D vector
	float orientation;	// a single float value
};
struct SteeringOut {
	Vector2_5D linear;	// a 2 or 3D vector
	float angular;		// a single float value
};
struct Kinematic {
	Vector2_5D position;	// a 2 or 3D vector
	float orientation;	// a single float value
	//Vector2_5D velocity;	// another 2 or 3D vector
	//float rotation;		// a single float value
	void update(SteeringOut steering, float time) {
		// Update the postion and orientation
		position += velocity * time +
					0.5f * steering.linear * time * time;
		orientation += rotation * time + 
						0.5f * steering.angular * time * time;
		
		// and the velocity and rotation
		velocity += steering.linear * time;
		rotation += steering.angular * time;
	}
};

#ifndef UNIT_TEST
int main() {
	printf("\rHello World\n");
	Kinematic kinematic{};
	SteeringOut steering{0.5, 0.6};
	kinematic.update(steering, 20);
	return 0;
}
#endif // !UNIT_TEST
