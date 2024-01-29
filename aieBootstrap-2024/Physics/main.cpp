#include "PhysicsApp.h"

int main() {
	
	// allocation
	auto app = new PhysicsApp();

	// initialise and loop
	app->run("Physics Demo", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}