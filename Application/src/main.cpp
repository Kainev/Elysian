#include <Elysian.h>
//#include "Elysian/Core/Application.h"


class MyApplication : public Elysian::Application
{
public:
	MyApplication() {}
	~MyApplication() {}
};


int main()
{
	Elysian::initialize<MyApplication>();
	return 0;
}