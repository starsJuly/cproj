#include <stdio.h>
#include <assert.h>
#include "../../3.1_The_Basics_of_Movement_Algorithms/3.1_The_Basics_of_Movement_Algorithms/Vector3D.h"

Vector3D asVector(float orientation) {
	return { sin(orientation) , 0 , cos(orientation) };
}

struct Static {
	Vector3D position;
	float orientation;
};

struct KinematicSteeringOutput {
	Vector3D velocity;
	float rotation;
};

inline float random() {
	return rand() / static_cast<float>( RAND_MAX );
}
inline float randomBinomial() {
	return random() - random();
}

class KinematicWander {
public:
	Static character;
	float maxSpeed;
	float maxRotation;

	void getSteering(KinematicSteeringOutput &steering) {
		steering.velocity = maxSpeed *
			asVector(character.orientation);
		steering.rotation = randomBinomial() * maxRotation;
	}
};


int main() {
	KinematicSteeringOutput steering{};
	KinematicWander wander;
	wander.character.orientation = 0.5f;
	wander.character.position = {0.5f, 0, 0.5f};
	wander.maxSpeed = 5.f;
	wander.maxRotation = 0.75f;
	int frame = 0;
	const int max_frame = 256;
	do {
		if (frame >= max_frame) break;
		wander.getSteering(steering);
		wander.character.position += steering.velocity;
		wander.character.orientation += steering.rotation;
		printf( "--------[frame %d\t]--------\r\n", ++frame );
		printf( "character{ position{ %f %f %f } orientation %f }\r\n"
				"steering{ velocity{ %f %f %f } -length %.8f rotation %f }\n",
				wander.character.position.x, wander.character.position.y, wander.character.position.z, wander.character.orientation,
				steering.velocity.x, steering.velocity.y, steering.velocity.z, steering.velocity.length(), steering.rotation );
		
	} while (1);

	return 0;
}