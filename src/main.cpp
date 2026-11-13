#include "ui/App.cpp"

#include <exception>
#include <iostream>

using namespace std;

// Start the graphical application and report exceptions as console errors.
int main() {
    try {
        // App owns input handling, drawing and the window loop.
        App app;
        return app.run();
    } catch (const exception &error) {
        cerr << "RewindChess: " << error.what() << '\n';
        return 1;
    }
}
