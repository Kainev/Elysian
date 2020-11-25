#include <Elysian.h>
#include "Elysian/Core/Application.h"
#include "Elysian/ECS/ComponentPattern.h"
#include "Elysian/ECS/Scene.h"
//#include "Elysian/Core/Profiler.h"

#include "PhysicsSystem.h"
#include "Elysian/ECS/ComponentTemplate.h"

struct Health
{
	float health = 1.f;
};

struct Input
{
	bool w = false;
	bool s = false;
};

struct Fire
{
	bool on_fire = false;
};

struct Mesh
{
	int mesh = 0;
};

struct Transform
{
	float x = 0.f;
	float y = 0.f;
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
	Elysian::Scene scene;

	auto static_mesh_template = scene.preregister_entity_definition<Health, Input, Fire>();

	{
		//PROFILE_SCOPE("CREATE");
		for (int i = 0; i < 4000; i++)
			scene.create_entity(static_mesh_template);
	}


	
	//auto pattern2 = Elysian::component_bitset<Health, Input, Fire>();
	//auto pattern3 = Elysian::component_bitset<Health, Input>();
	//auto pattern4 = Elysian::component_bitset(Elysian::component_type<Health>(), Elysian::component_type<Input>(), Elysian::component_type<Fire>());

	//

	//ELYSIAN_INFO("{} {}", (pattern1 == pattern2), (pattern1 == pattern4));

	return 0;
}