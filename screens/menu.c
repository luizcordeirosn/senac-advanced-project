#include "raylib.h"
#include "game.h"
#include <string.h>

Button play, sett, cred, quit;

void SetMenu(void) {
    int btnWidth = 300;  
    int btnHeight = 50;  
    int padding = 15;    
        
    int totalMenuHeight = (4 * btnHeight) + (3 * padding);
    
    int startX = (SCREEN_WIDTH - btnWidth) / 2;
    
    int startY = ((SCREEN_HEIGHT - totalMenuHeight) / 2) + 200; 

    play = (Button) {{startX, startY, btnWidth, btnHeight}, "Jogar", RAYWHITE, BLACK};
    
    sett = (Button) {{startX, startY + (btnHeight + padding), btnWidth, btnHeight}, "Configurações", RAYWHITE, BLACK};
    
    cred = (Button) {{startX, startY + (btnHeight + padding) * 2, btnWidth, btnHeight}, "Créditos", RAYWHITE, BLACK};
    
    quit = (Button) {{startX, startY + (btnHeight + padding) * 3, btnWidth, btnHeight}, "Sair", RAYWHITE, BLACK};
}

void DrawMenu(void) {
    SetMenu();
    
    int menuFontSize = 30; 

    ClearBackground(BLACK);
    
    DrawTexturePro(background_menu,
    (Rectangle){ 0, 0, background_menu.width, background_menu.height },
    (Rectangle){ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT },
    (Vector2){ 0, 0 },
    0.0f,
    WHITE);
        
    DrawRectangleRounded(play.rec, 0.5, 10, play.rec_color);
    DrawText(play.text, (SCREEN_WIDTH - MeasureText(play.text, menuFontSize))/2, play.rec.y + (play.rec.height - menuFontSize)/2, menuFontSize, play.text_color);

    DrawRectangleRounded(sett.rec, 0.5, 10, sett.rec_color);
    DrawText(sett.text, (SCREEN_WIDTH - MeasureText(sett.text, menuFontSize))/2, sett.rec.y + (sett.rec.height - menuFontSize)/2, menuFontSize, sett.text_color);
    
    DrawRectangleRounded(cred.rec, 0.5, 10, cred.rec_color);
    DrawText(cred.text, (SCREEN_WIDTH - MeasureText(cred.text, menuFontSize))/2, cred.rec.y + (cred.rec.height - menuFontSize)/2, menuFontSize, cred.text_color);

    DrawRectangleRounded(quit.rec, 0.5, 10, quit.rec_color);
    DrawText(quit.text, (SCREEN_WIDTH - MeasureText(quit.text, menuFontSize))/2, quit.rec.y + (quit.rec.height - menuFontSize)/2, menuFontSize, quit.text_color);
    
    Vector2 mousePos = GetMousePosition();

    if (CheckCollisionPointRec(mousePos, play.rec)) {
        DrawRectangleRounded(play.rec, 0.5, 10, play.text_color);
        DrawText(play.text, (SCREEN_WIDTH - MeasureText(play.text, menuFontSize))/2, play.rec.y + (play.rec.height - menuFontSize)/2, menuFontSize, play.rec_color);
    }
    if (CheckCollisionPointRec(mousePos, sett.rec)) {
        DrawRectangleRounded(sett.rec, 0.5, 10, sett.text_color);
        DrawText(sett.text, (SCREEN_WIDTH - MeasureText(sett.text, menuFontSize))/2, sett.rec.y + (sett.rec.height - menuFontSize)/2, menuFontSize, sett.rec_color);
    }
    if (CheckCollisionPointRec(mousePos, cred.rec)) {
        DrawRectangleRounded(cred.rec, 0.5, 10, cred.text_color);
        DrawText(cred.text, (SCREEN_WIDTH - MeasureText(cred.text, menuFontSize))/2, cred.rec.y + (cred.rec.height - menuFontSize)/2, menuFontSize, cred.rec_color);
    }
    if (CheckCollisionPointRec(mousePos, quit.rec)) {
        DrawRectangleRounded(quit.rec, 0.5, 10, quit.text_color);
        DrawText(quit.text, (SCREEN_WIDTH - MeasureText(quit.text, menuFontSize))/2, quit.rec.y + (quit.rec.height - menuFontSize)/2, menuFontSize, quit.rec_color);
    }
}

void UpdateMenu(void) {
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), play.rec)) {
        PlaySound(botaoSound); // Toca o som de botão
        currentScreen = HISTORY;
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), sett.rec)) {
        PlaySound(botaoSound); // Toca o som de botão
        currentScreen = SETTINGS;
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), cred.rec)) {
        PlaySound(botaoSound); // Toca o som de botão
        currentScreen = CREDITS;
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), quit.rec)) {
        PlaySound(botaoSound); // Toca o som de botão
        currentScreen = QUIT;
    }
}
