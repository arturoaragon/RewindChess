#ifndef REWINDCHESS_APP_CPP
#define REWINDCHESS_APP_CPP
#include "../core/Game.cpp"
#include "raylib.h"
#include <stdexcept>
using namespace std;

const int Width = 1024, Height = 760;
const float BoardX = 40, BoardY = 115, Cell = 70;
const Color Ink{27, 30, 47, 255}, Paper{246, 243, 235, 255}, Amber{231, 170, 57, 255};
const Color BoardLight{235, 226, 205, 255}, BoardDark{119, 131, 151, 255};

class App {
public:
    int run() {
        SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
        InitWindow(Width, Height, "RewindChess - Week 2");
        if (!IsWindowReady()) throw runtime_error("Could not open the window.");
        SetExitKey(KEY_NULL);
        SetWindowMinSize(720, 540);
        SetTargetFPS(60);
        loadAssets();
        while (!WindowShouldClose()) {
            if (IsKeyPressed(KEY_ESCAPE)) clearSelection();
            if (IsWindowMinimized()) { PollInputEvents(); WaitTime(0.05); continue; }
            float scale = min(GetScreenWidth() / float(Width), GetScreenHeight() / float(Height));
            Vector2 offset{(GetScreenWidth() - Width * scale) / 2, (GetScreenHeight() - Height * scale) / 2};
            SetMouseScale(1, 1);
            Vector2 mouse = GetMousePosition();
            mouse_ = {(mouse.x - offset.x) / scale, (mouse.y - offset.y) / scale};
            click_ = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
            
            BeginDrawing();
            ClearBackground(Ink);
            BeginMode2D({offset, {0, 0}, 0, scale});
            DrawRectangle(0, 0, Width, Height, Paper);
            DrawRectangle(0, 0, Width, 76, Ink);
            text("Rewind Chess", 36, 20, 32, Amber);
            text("Week 2 / playable board prototype", 350, 28, 20, WHITE);
            drawBoard();
            drawControls();
            
            text(notice_, 40, 710, 18, MAROON);
            EndMode2D();
            EndDrawing();
        }
        unloadAssets();
        CloseWindow();
        return 0;
    }

private:
    Game game_;
    Square selected_;
    Texture2D pieces_[2][7]{};
    Font font_{};
    Vector2 mouse_{};
    bool click_ = false;
    string notice_;
    

    void loadAssets() {
        string folder = string(GetApplicationDirectory()) + "assets/";
        if (!DirectoryExists(folder.c_str())) folder = string(GetWorkingDirectory()) + "/assets/";
        font_ = LoadFontEx((folder + "fonts/AtkinsonHyperlegible-Regular.ttf").c_str(), 36, nullptr, 0);
        if (font_.texture.id == 0 || font_.texture.id == GetFontDefault().texture.id) {
            throw runtime_error("Missing interface font in assets/fonts.");
        }
        SetTextureFilter(font_.texture, TEXTURE_FILTER_BILINEAR);
        for (int side = 0; side < 2; side++) {
            string prefix = "b";
            if (side == WHITE_PLAYER) prefix = "w";
            for (int type = PAWN; type <= KING; type++) {
                string file = folder + "pieces/" + prefix + pieceLetter(type) + ".png";
                pieces_[side][type] = LoadTexture(file.c_str());
                if (!pieces_[side][type].id) throw runtime_error("Missing piece image: " + file);
                SetTextureFilter(pieces_[side][type], TEXTURE_FILTER_BILINEAR);
            }
        }
    }

    void unloadAssets() {
        UnloadFont(font_);
        for (int side = 0; side < 2; side++) {
            for (int type = PAWN; type <= KING; type++) UnloadTexture(pieces_[side][type]);
        }
    }

    void text(const string &value, float x, float y, float size, Color color = Ink) {
        DrawTextEx(font_, value.c_str(), {x, y}, size, 0, color);
    }

    bool button(Rectangle box, const string &label, bool enabled = true) {
        Color color = Amber;
        if (!enabled) color = LIGHTGRAY;
        DrawRectangleRounded(box, 0.15f, 6, color);
        text(label, box.x + 10, box.y + 8, 19);
        if (enabled && click_ && CheckCollisionPointRec(mouse_, box)) {
            click_ = false;
            return true;
        }
        return false;
    }

    void clearSelection() {
        selected_ = Square();
        
    }

    void commit(const Move &move) {
        if (!game_.play(move)) notice_ = game_.error();
        else notice_.clear();
        clearSelection();
    }

    void drawBoard() {
        const State state = game_.live();
        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                Square square(row, col);
                Rectangle tile{BoardX + col * Cell, BoardY + row * Cell, Cell, Cell};
                Color color = BoardLight;
                if ((row + col) % 2) color = BoardDark;
                DrawRectangleRec(tile, color);
                if (square.sameAs(selected_)) DrawRectangleLinesEx(tile, 4, Amber);
                Piece piece = state.at(square);
                if (!piece.empty()) {
                    Texture2D image = pieces_[piece.side][piece.type];
                    DrawTexturePro(image, {0, 0, float(image.width), float(image.height)},
                                   {tile.x + 5, tile.y + 5, Cell - 10, Cell - 10}, {0, 0}, 0, WHITE);
                }
            }
        }
        if (!click_ || false || !CheckCollisionPointRec(mouse_, {BoardX, BoardY, Cell * 8, Cell * 8})) return;
        click_ = false;
        Square target(int((mouse_.y - BoardY) / Cell), int((mouse_.x - BoardX) / Cell));
        vector<Move> moves = game_.availableMoves();
        for (int i = 0; i < int(moves.size()); i++) {
            if (moves[i].from.sameAs(selected_) && moves[i].to.sameAs(target)) {
                commit(moves[i]);
                return;
            }
        }
        Piece piece = state.at(target);
        selected_ = Square();
        if (!piece.empty() && piece.side == state.turn) selected_ = target;
        else notice_ = "Select your piece, then a valid destination.";
    }

    void drawControls() {
        text(game_.statusText(), 640, 102, 21);
        text("Click your piece, then its destination.", 640, 160, 18);
        if (button({640, 658, 340, 36}, "New game", true)) {
            game_.newGame();
            clearSelection();
            notice_.clear();
        }
    }
    
};
#endif
