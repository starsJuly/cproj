#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<assert.h>
#include "../../3.1_The_Basics_of_Movement_Algorithms/3.1_The_Basics_of_Movement_Algorithms/Vector3D.h"


class SteeringOut {
public:
	Vector3D linear;
	float angular;
};

class Kinematic {
public:
	Vector3D position;
	float orientation;
	Vector3D velocity;
	float rotation;
	// Holds maximum speed
	float maxSpeed;
	void update(SteeringOut &steering, float time) {
		position += velocity * time;
		orientation += rotation * time;

		velocity += steering.linear * time;
		rotation += steering.angular * time;

		// Check for speeding and clip
		if (velocity.length() > maxSpeed) {
			velocity.normalize();
			velocity *= maxSpeed;
		}
	}
};


class Seek {
public:
	Kinematic &character;
	Kinematic &target;
	float maxAcceleration;
	void getSteering(SteeringOut &steering) {
		steering.linear = target.position -
						  character.position;
		
		steering.linear.normalize();
		steering.linear *= maxAcceleration;

		steering.angular = 0;
	}
};

class Flee {
public:
	Kinematic &character;
	Kinematic &target;
	float maxAcceleration;
	void getSteering(SteeringOut& steering) {
		steering.linear = character.position -
			target.position;

		steering.linear.normalize();
		steering.linear *= maxAcceleration;

		steering.angular = 0;
	}
};

#define SpreadVector3D(_sv3d_vec) (_sv3d_vec).x, (_sv3d_vec).y, (_sv3d_vec).z

inline void PrintKinematic(Kinematic &kinematic) {
	printf( "{ { %-6.2f , %-.2f , %-6.2f } , %-4.2f , { %-6.2f , %-.2f , %-6.2f } , %-4.2f , %-4.2f }\n", 
			SpreadVector3D(kinematic.position), kinematic.orientation, 
			SpreadVector3D(kinematic.velocity), kinematic.rotation, kinematic.maxSpeed );
}

//#define NoRedirect

int main(int argc, char**argv) {

#ifndef NoRedirect
	if (!freopen("output.txt", "w", stdout) || !freopen("output.txt", "w", stderr)) {
		printf( "Open failed: %s\n", strerror(errno) );
	}
#endif

	SteeringOut steering{ {-1.0f, -1.0f, -1.0f}, 0.0f };
	Kinematic character	= { {0, 0, 0}, 1.5f, {0, 0, 0}, 0, 4 },
			  target	= { {6, 0, 8}, 0.0f, {0, 0, 0}, 0, 0 };
	Seek behavior{ character , target , 2 };
	

	int frame = 0;

	do {
		printf("[%-4d]\n", frame);
		PrintKinematic(character);
		PrintKinematic(target);
		if (++frame > 100) break;
		behavior.getSteering(steering);
		behavior.character.update(steering, 1.0f);
	} while (1);

	return 0;
}
