#include "config/Types.h"
#include "Application.h"

i32 main(i32 argc, char** argv)
{
	Application app = Application();

	app.Run();

	return EXIT_SUCCESS;
}