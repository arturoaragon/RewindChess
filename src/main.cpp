#include "ui/App.cpp"

#include <exception>
#include <iostream>

using namespace std;

int main() {
    try {
        App app;
        return app.run();
    } catch (const exception &error) {
        cerr << "RewindChess: " << error.what() << '\n';
        return 1;
    }
}
