#include <iostream>
#include "Application.h"

int main(int argc, char* args[])
{
    try 
    {
        Application app;
        app.init();
        app.run();
    }
    catch (const std::exception& e) 
    {
        std::cerr << "Application error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}
