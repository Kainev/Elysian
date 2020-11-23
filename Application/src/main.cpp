#include <Elysian.h>
#include "Elysian/Core/Application.h"
#include "Elysian/ECS/ComponentPattern.h"
#include "Elysian/ECS/Scene.h"
#include "Elysian/Core/Profiler.h"

#include "PhysicsSystem.h"

struct Health
{
	float health = 1.f;
};

struct Input
{
	bool w = false;
	bool s = false;
	float health = 2.f;
};

struct Fire
{
	bool on_fire = false;
	float health = 3.f;
};


class MyApplication : Elysian::Application
{
public:
	MyApplication()
	{
		
	}
	~MyApplication() {}
};


int main()
{
	Elysian::initialize<MyApplication>();
	auto pattern1 = Elysian::component_pattern<Health, Input, Fire>();

	Elysian::Scene scene;
	scene.test_func(pattern1);

	{
		PROFILE_SCOPE("CREATE");
		for (int i = 0; i < 10; i++)
			scene.create_entity<Health, Input, Fire>(pattern1);
	}


	
	//auto pattern2 = Elysian::component_pattern<Health, Input, Fire>();
	//auto pattern3 = Elysian::component_pattern<Health, Input>();
	//auto pattern4 = Elysian::component_pattern(Elysian::component_type<Health>(), Elysian::component_type<Input>(), Elysian::component_type<Fire>());

	//

	//ELYSIAN_INFO("{} {}", (pattern1 == pattern2), (pattern1 == pattern4));

	return 0;
}