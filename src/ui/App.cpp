#ifndef REWINDCHESS_APP_CPP
#define REWINDCHESS_APP_CPP
#include "../core/Game.cpp"
#include "raylib.h"
#include <stdexcept>
using namespace std;

class App {
public:
    int run() {
        InitWindow(720, 360, "RewindChess - architecture prototype");
        if (!IsWindowReady()) throw runtime_error("Could not open the window.");
        SetTargetFPS(60);
        Game game;
        while (!WindowShouldClose()) {
            BeginDrawing();
            ClearBackground({246, 243, 235, 255});
            DrawText("RewindChess / Week 1", 40, 45, 32, {27, 30, 47, 255});
            DrawText(game.statusText().c_str(), 40, 110, 20, {53, 119, 94, 255});
            DrawText("Square, Piece, Move, State and Game are defined.", 40, 160, 20, DARKGRAY);
            DrawText("GUI library and compiler are connected.", 40, 205, 20, DARKGRAY);
            DrawText("Close the window or press Esc to exit.", 40, 275, 18, DARKGRAY);
            EndDrawing();
        }
        CloseWindow();
        return 0;
    }
};
#endif
