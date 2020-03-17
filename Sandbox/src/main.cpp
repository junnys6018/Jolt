#include "Overlay.h"

class ExampleApp : public Application
{
public:
	ExampleApp()
		:Application("Sandbox")
	{
		PushOverlay(new ImGuiLayer());
	}
};

int main()
{
	ExampleApp* app = new ExampleApp();
	app->Run();

	return 0;
}