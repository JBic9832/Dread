#include "Application.h"
#include "Logger.h"
#include "Event/EventSystem.h"

extern Dread::Application* CreateApplication(Dread::EventSystem&);

int main() {
	Dread::Logger::Init();
	DREAD_CORE_ERROR("Hello from Core!");
	int a = 5;
	DREAD_INFO("Hello from Client! {0}", a);

	Dread::EventSystem e;
	auto app = CreateApplication(e);

	app->Run();
	delete app;
	return 0;
}
