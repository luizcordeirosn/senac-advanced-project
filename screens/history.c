#include "raylib.h"
#include "game.h"

char text[600] = "The galactic invaders, in their great \"wisdom,\" decided to use random words as shields for their ships. But the cunning warrior from Senac, the fastest typist in the galaxy, is ready to stop them! With fingers faster than lasers and inhuman keyboard dexterity, he defends Earth from the most absurd threat in the universe: an intergalactic typing combat!";
int pos_x = 1280;
int scroll_speed = 350.0f;

void DrawHistory(Texture2D background, Font myfont) {
    ClearBackground(BLACK);
    DrawTexture(background, 0, 0, WHITE);
    DrawRectangle(0, (720/2 - 50), 1280, 100, WHITE);
    DrawTextEx(GetFontDefault(), text, (Vector2) {pos_x, (720/2 - 10)}, 30, 5, BLACK);

    DrawTextEx(GetFontDefault(), "Press ENTER to skip...", (Vector2) {50, (720/2 + 70)}, 30, 5, WHITE);
}

void UpdateHistory() {
    pos_x -= GetFrameTime() * scroll_speed;
    if (IsKeyPressed(KEY_ENTER)) {
        currentScreen = GAMEPLAY;
    }
}