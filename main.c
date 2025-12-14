/**
 * @file main.c
 * @brief Arquivo principal do jogo WordBrick English Type Game.
 * * Este arquivo gerencia o ciclo de vida do jogo, incluindo inicialização da janela,
 * carregamento de recursos (áudio/textura), loop principal e gerenciamento de telas.
 * * @author Equipe WordBrick
 * @date 2025
 */

#include "raylib.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================================================
// VARIÁVEIS GLOBAIS - ESTADO E ENTIDADES DO JOGO
// ============================================================================

/** @brief Define a tela atual (Menu, Gameplay, Configurações, etc). */
GameScreen currentScreen = MENU; 

/** @brief Entidade principal: o jogador. */
Player player;

/** @brief Gerenciador de lista de inimigos. */
EnemyList enemy_list;

/** @brief Lista de projéteis ativos. */
ProjectileList projectile_list = {.qty_projectiles = 0};

/** @brief Lista de power-ups ativos. */
Power_up_list power_up_list;

/** @brief Pontuação atual do jogador. */
Score score;

/** @brief Estado de digitação (LOCKED/NOTLOCKED). */
StateTyping state = NOTLOCKED; 

// ============================================================================
// VARIÁVEIS GLOBAIS - CONTROLE E UI
// ============================================================================

int paused = 0;       /**< Flag para indicar se o jogo está pausado (1) ou rodando (0). */
int font_size = 50;   /**< Tamanho base da fonte para textos de UI. */
int j = 0;            /**< Variável auxiliar de iteração. */
double time_pass;     /**< Acumulador de tempo para efeitos (ex: congelamento). */
int freeze = 0;       /**< Flag para ativar/desativar o efeito de congelamento. */

/** @brief Retângulo base usado para posicionamento de botões. */
Rectangle rec = {(SCREEN_WIDTH - 400)/2, (SCREEN_HEIGHT - 80)/2, 400, 80};

/** @brief Botão 'Voltar' usado em várias telas. */
Button back = {
    {(SCREEN_WIDTH - 33*5)/2, SCREEN_HEIGHT/2 + 250, 33*5, 50}, 
    "Voltar", 
    BLACK, 
    RAYWHITE
};

/** @brief Botão 'Menu' usado em telas de pausa/game over. */
Button back_menu = {
    {(SCREEN_WIDTH - 400)/2, (SCREEN_HEIGHT)/2 + 180, 400, 80}, 
    "Menu", 
    RAYWHITE, 
    BLACK
};

// ============================================================================
// VARIÁVEIS GLOBAIS - RECURSOS (TEXTURAS, SONS E FONTES)
// ============================================================================

Font myfont;

Sound morteSound;
Sound menuJogoSound;
Sound tiroSound;
Sound botaoSound;
Sound freezeSound;

Texture2D enemy_textures[3];
Texture2D background;
Texture2D background_history;
Texture2D background_menu;
Texture2D heart;

// ============================================================================
// PROTÓTIPOS DE FUNÇÕES LOCAIS
// ============================================================================

void UpdateDrawFrame(void); // Atualiza e desenha o quadro atual (loop gráfico)
void UpdateGame(void);      // Atualiza a lógica do jogo (movimento, física)
void LoadResources(void);   // Carrega todas as texturas e sons
void UnloadResources(void); // Descarrega recursos para liberar memória

// ============================================================================
// FUNÇÃO PRINCIPAL
// ============================================================================

/**
 * @brief Ponto de entrada do programa.
 * Inicializa a janela, áudio, carrega recursos e executa o Game Loop.
 */
int main(void)
{
    // 1. Inicialização da Janela e Áudio
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "WordBrick");
    InitAudioDevice(); 
    SetTargetFPS(60);

    // 2. Inicialização de Variáveis de Jogo
    CreatePlayer(&player);
    InitTexts(); // Carrega as palavras do dicionário
    Inicializar_power_up_list(&power_up_list);

    // 3. Carregamento de Assets (Sons, Texturas, Fontes)
    LoadResources();
    
    // 4. Game Loop (Roda até o usuário fechar a janela ou escolher Sair)
    while (!WindowShouldClose() && currentScreen != QUIT)
    {
        UpdateDrawFrame();
        UpdateGame();
    }

    // 5. Limpeza e Encerramento
    UnloadResources();
    UnloadPlayer(); // Libera memória específica do player, se houver
    
    CloseAudioDevice();
    CloseWindow();

    return 0;
}

// ============================================================================
// IMPLEMENTAÇÃO DAS FUNÇÕES
// ============================================================================

/**
 * @brief Carrega todas as texturas, sons e fontes do jogo.
 * Centraliza o carregamento para manter a main limpa.
 */
void LoadResources(void) {
    // Carregar Fontes
    myfont = LoadFont("COUR.TTF");

    // Carregar Texturas
    // Nota: Use barras normais (/) para compatibilidade cross-platform (Windows/Linux)
    background_history = LoadTexture("sprites/background_history.png");
    enemy_textures[0] = LoadTexture("sprites/inimigo1.png");
    enemy_textures[1] = LoadTexture("sprites/inimigo2.png");
    enemy_textures[2] = LoadTexture("sprites/inimigo3.png");
    background = LoadTexture("sprites/background.png");
    background_menu = LoadTexture("sprites/backgroundmenu.png");
    heart = LoadTexture("sprites/heart.png");

    // Carregar Sons
    morteSound = LoadSound("sounds/morte.mp3");
    menuJogoSound = LoadSound("sounds/menu_jogo.mp3");
    tiroSound = LoadSound("sounds/tiro.mp3");
    botaoSound = LoadSound("sounds/botao.mp3");
    freezeSound = LoadSound("sounds/freeze.mp3");
}

/**
 * @brief Libera a memória de todos os recursos carregados.
 * Deve ser chamada antes de fechar o jogo.
 */
void UnloadResources(void) {
    // Descarregar Sons
    UnloadSound(morteSound);
    UnloadSound(menuJogoSound);
    UnloadSound(tiroSound);
    UnloadSound(botaoSound);
    UnloadSound(freezeSound);
    
    // Descarregar Texturas
    UnloadEnemyTextures(); // Função específica definida em enemy.c para o array
    UnloadTexture(background);
    UnloadTexture(background_menu);
    UnloadTexture(background_history);
    UnloadTexture(heart);
    
    // Descarregar Fonte
    UnloadFont(myfont);
}

/**
 * @brief Gerencia a atualização lógica do jogo baseada na tela atual.
 * Trata input, física e transições de estado.
 */
void UpdateGame(void) {
    
    // Música de fundo em loop
    if (!IsSoundPlaying(menuJogoSound)) {
        PlaySound(menuJogoSound);
    }

    // Máquina de estados das telas
    switch (currentScreen) {
        case MENU:
            UpdateMenu();
            break;
        case GAMEPLAY:
            UpdateGameplay(&player, &enemy_list, &projectile_list, &time_pass, &freeze, &power_up_list, &score);
            break;
        case HISTORY:
            UpdateHistory();
            break;
        case PAUSE:
            UpdatePause(&player, &enemy_list, &projectile_list);
            break;
        case GAME_OVER:
            ResetGame(&player, &enemy_list, &projectile_list);
            UpdateGameOver();
            break;        
        case SETTINGS: 
            UpdateSettings(); 
            break;
        case CREDITS: 
            UpdateCredits(); 
            break;
        case QUIT: 
            break;
    }
}

/**
 * @brief Gerencia o desenho (renderização) do jogo.
 * Limpa a tela e desenha os elementos da tela atual.
 */
void UpdateDrawFrame(void) {
    BeginDrawing();

    switch (currentScreen) {
        case MENU: 
            DrawMenu();
            break;
        case GAMEPLAY: 
            DrawGame(&player, &enemy_list, &projectile_list, myfont, power_up_list, &score);
            break;
        case HISTORY:
            DrawHistory(background_history, myfont);
            break;
        case PAUSE:
            DrawPause();
            break;
        case GAME_OVER:
            DrawGameOver();
            break;        
        case SETTINGS: 
            DrawSettings(); 
            break;
        case CREDITS: 
            DrawCredits(); 
            break;
        case QUIT: 
            break;
    }
    
    EndDrawing();
}