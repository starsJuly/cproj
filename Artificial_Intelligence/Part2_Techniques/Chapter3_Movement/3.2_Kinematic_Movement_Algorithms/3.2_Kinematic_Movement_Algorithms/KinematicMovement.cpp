#include <stdio.h>
#include <assert.h>
#include "../../3.1_The_Basics_of_Movement_Algorithms/3.1_The_Basics_of_Movement_Algorithms/Vector3D.h"

float getNewOrientation(float, const Vector3D*);


inline float getNewOrientation(float currentOrientation, const Vector3D* velocity) {
	// Make sure we have a velocity
	if (velocity->length() > 0)
		// Calculate orientation using an arc tangent of
		// the velocity components.
		return atan2(velocity->x, velocity->z);

	//Otherwise use the current orientaion
	else
		return currentOrientation;

}

struct Static {
	Vector3D position;
	float orientation;
};

struct SteeringOut {
	Vector3D linear;
	float angular;
};

typedef struct {
	Vector3D velocity;
	float rotation;
	bool isSatisfied;
} KinematicSteeringOut;


class KinematicSeek {
public:
	// Holds the static data for the character and target
	Static character;
	Static target;

	// Holds the maximum speed the character can travel
	float maxSpeed;

	// Holds the satisfication radius
	float radius; // radius > 0.0000625 * timeToTarget

	// Holds the time to target constant
	float timeToTarget;

	KinematicSeek();
	void getSteering(KinematicSteeringOut* steering);

};

KinematicSeek::KinematicSeek() : character{}, target{}, maxSpeed(20), radius(0.05f), timeToTarget(0.25) {};

void KinematicSeek::getSteering(KinematicSteeringOut* steering) {
	// Create the structure for output
	//KinematicSteeringOut &steering = *new KinematicSteeringOut();

	//Get the direction to the target
	steering->velocity =
		target.position - character.position;

	// Check if we're within radius
	if (steering->velocity.length() < radius)

		// We can return no steering request
		return void(steering->isSatisfied = true);

	// We need to move to our target, we'd like to
	// get there in timeToTarget seconds
	steering->velocity /= timeToTarget;

	//The velocity is along this direction, at full speed
	//steering.velocity.normalize();
	//steering.velocity *= maxSpeed;

	//If this is too fast, clip it to the max speed
	if (steering->velocity.length() > maxSpeed) {
		steering->velocity.normalize();
		steering->velocity *= maxSpeed;
	}

	//Face in the direction we want to move
	character.orientation =
		getNewOrientation(character.orientation, 
						  &steering->velocity);

	// Output the steering
	steering->rotation = 0;
	return void(steering->isSatisfied = false);
}


#define Get_Text(_text) #_text

int main() {

	const Vector3D vec{ 2, 1, 2 };
	const float orientation = 1.5f;
	const float newOrientation = getNewOrientation(1.5f, &vec);
	printf( Get_Text(vec{ 2 1 2 })" orientation:%f new orientation:%f pi/4:%f\n",
			orientation, newOrientation, 3.141592653f / 4);

	KinematicSeek kinematicSeek{};
	//const float min_radius = 0.125;
	//kinematicSeek.radius = 0.125;
	kinematicSeek.character.position = { 10, 0, 10 };
	kinematicSeek.character.orientation = atan2(1.0f, 1.0f);
	kinematicSeek.target.position = { 1300, 0 , 1400 };
	kinematicSeek.target.orientation = atan2(3.0f, 4.0f);
	kinematicSeek.maxSpeed = 20.0f;

	printf( "Start move:\n" );
	KinematicSteeringOut steering{};
	printf( "character{ position{ %f %f %f } orientation %f:%f¡ã }\n"
			"target{ position{ %f %f %f } orientation %f:%f¡ã }"
			"maxSpeed %f\n",
			kinematicSeek.character.position.x, kinematicSeek.character.position.y, kinematicSeek.character.position.z, kinematicSeek.character.orientation, ((double)kinematicSeek.character.orientation * 180 / 3.141592635),
			kinematicSeek.target.position.x, kinematicSeek.target.position.y, kinematicSeek.target.position.z, kinematicSeek.target.orientation, ((double)kinematicSeek.target.orientation * 180 / 3.141592635),
			kinematicSeek.maxSpeed );
	printf( "distance: %f\n", (kinematicSeek.character.position - kinematicSeek.target.position).length() );
	int frame = 0; double elapsed = 0;
	const float interval = 1 / 16.f;
	assert( interval < kinematicSeek.timeToTarget * 2 );
	do {
		printf( "--------[frame %d\t]---------\n", ++frame );
		kinematicSeek.getSteering(&steering);
		if (steering.isSatisfied)break;
		kinematicSeek.character.position += steering.velocity * interval;
		elapsed += interval;
		printf( "steering{ velocity{ %f %f %f } rotation %f }\n"
				"character{ position{ %f %f %f } orientation %f:%f¡ã }\n"
				"target{ position{ %f %f %f } orientation %f:%f¡ã }"
				"maxSpeed %f\n",
				steering.velocity.x, steering.velocity.y, steering.velocity.z, steering.rotation,
				kinematicSeek.character.position.x, kinematicSeek.character.position.y, kinematicSeek.character.position.z, kinematicSeek.character.orientation, ((double)kinematicSeek.character.orientation * 180 / 3.141592635),
				kinematicSeek.target.position.x, kinematicSeek.target.position.y, kinematicSeek.target.position.z, kinematicSeek.target.orientation, ((double)kinematicSeek.target.orientation * 180 / 3.141592635),
				kinematicSeek.maxSpeed );
		printf( "distance: %f\n", (kinematicSeek.character.position - kinematicSeek.target.position).length() );
	} while (1);
	printf( "End move\n" );
	printf( "elapsed time: %f\tfps: %f\tframe: %d\tinterval: %f\n", elapsed, frame/elapsed, frame, interval );

	return 0;
}