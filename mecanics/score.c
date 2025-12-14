// score.c
#include "raylib.h"
#include "game.h"

void InitScore(Score* score) {
    score->points = 0;
}

void IncreaseScore(Score* score) {
    score->points += 10;
}

void DrawScore(Score* score, Font font) {
    const char* scoreText = TextFormat("SCORE: %d", score->points);
    int textWidth = MeasureText(scoreText, 30);
    int x = GetScreenWidth() - textWidth - 10;
    int y = GetScreenHeight() - 30 - 10;

    DrawText(scoreText, x, y, 30, WHITE);
}