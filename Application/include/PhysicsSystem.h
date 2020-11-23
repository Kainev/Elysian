#include "Elysian/ECS/System.h"
#include <iostream>

struct Translation
{
	float x = 0.f;
	float y = 0.f;
};

class PhysicsSystem : public Elysian::System<Translation>
{
public:
	PhysicsSystem() {}
	void update(double dt) override
	{
		std::cout << "Update" << std::endl;
	}
};