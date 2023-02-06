#include "App.hpp"

int main(int argc, char **argv) {
    std::string path = "../assets/objects/42.obj";

    if (argc >= 3) {
        printToConsole("Too many arguments!\n"
                       "scop will be running with default 42.obj!\n"
                       "usage: ./scop path_to_obj");
    } else if (argc == 1) {
        printToConsole("Missing argument!\n"
                       "scop will be running with default 42.obj!\n"
                       "usage: ./scop path_to_obj");
    }
    else {
        path = argv[1];
    }

    App app;
    app.obj.load(path);
    app.renderLoop();

    return EXIT_SUCCESS;
}