#include "raylib.h"
#include "game.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Power_up_time(EnemyList* enemyList, double time_pass, float normal_speed, int* freeze){ // função para executar o power up "timer" ele congela o tempo
    float amount_time = 3.0; // tempo de congelamento (4 segundos)

    if ( (GetTime() - time_pass) >= amount_time){ // o tempo de congelamento acabou
        *freeze = 0;
    }

    if(*freeze == 0){
        for (int i = 0; i < enemyList->qty_enemies; i++){
            enemyList->enemies[i].speed = normal_speed; // faz com que os inimigos voltem a velocidade normal antes de aceleração
        }
    }

    else { // o tempo de congelamento aida não acabou
        for (int i = 0; i < enemyList->qty_enemies; i++){ // percorre todos os enimigos e zera a velocidade deles
            enemyList->enemies[i].speed = 0;
        }
    }

}

void Power_up_delet(EnemyList* enemyList, int number_enemies, Score* score){ // mata uma quantidade de inimigos

    for (int i = 0; i < number_enemies; i++){
        if (enemyList->qty_enemies > 0) RemoveEnemy(enemyList, 0, score);  
    }

}

void Inicializar_power_up_list(Power_up_list* lista){
    int max = 3;
    lista->max_power_up = max;
    lista->number_power_ups = 0;
    for (int i = 0; i < max; i++){
        lista->power_up[i].type = 0;
        lista->power_up[i].rec.x = 0;
        lista->power_up[i].rec.y = 0;
        lista->power_up[i].rec.width = 0;
        lista->power_up[i].rec.height = 0;
    }
}

void Adicionar_power_up(int type, Power_up_list* power_up_list){
    int adicionar = 0;

    if (power_up_list->number_power_ups < power_up_list->max_power_up){ // se ainda tiver espaço para adicionar
        adicionar = 1;
        power_up_list->number_power_ups++;
        Power_up power_up; // define a altura, largura e tipo do power up que vai ser adicionado a lista de power_ups
        power_up.rec.height = 40;
        power_up.rec.width = 40;
        power_up.rec.x = 30;
        power_up.rec.y = 650; // testar pra ver onde vai ficar
        power_up.type = type;

        int indice = power_up_list->max_power_up - power_up_list->number_power_ups; // indice onde vai ser colocado o power up
        power_up_list->power_up[indice] = power_up;
        
    }

    if (adicionar){
        for (int i = 0; i < power_up_list->max_power_up; i++){ // move a posição de todos os power ups na barra
            if (power_up_list->power_up[i].type != 0){
                power_up_list->power_up[i].rec.x += 42;
            }
        }
    }
}

void print_power_up_bar(Power_up_list power_up_list){
    for (int i = 0; i < power_up_list.max_power_up; i++){

        if (power_up_list.power_up[i].type == 1){ // desenha o power up de congelamento
            DrawRectangleRec(power_up_list.power_up[i].rec, BLUE);
        }
        else if (power_up_list.power_up[i].type == 2){ // desenha o power up de explode os inimigos
            DrawRectangleRec(power_up_list.power_up[i].rec, YELLOW);
        }

    }
}

void activate_power_up(Power_up_list* power_up_list, EnemyList* enemyList, double *time_pass, int* freeze, Score* score){
    if (IsKeyPressed(KEY_ENTER)) {
        Power_up power_up;
        if(power_up_list->number_power_ups >0){
            power_up_list->number_power_ups--;
            for (int i = 0; i < power_up_list->max_power_up; i++){
                if (power_up_list->power_up[i].type != 0){
                    power_up.type = power_up_list->power_up[i].type;
                    power_up_list->power_up[i].rec.height = 0;
                    power_up_list->power_up[i].rec.width = 0;
                    power_up_list->power_up[i].type = 0;
                    break;
                }
            }

            if (power_up.type == 1){
                *freeze = 1; // ativa o congelamento
                *time_pass = GetTime();
            }

            else if (power_up.type == 2){
                Power_up_delet(enemyList, 3, score);
            }

            for (int i = 0; i < power_up_list->max_power_up; i++){ // move a posição de todos os power ups na barra
                if (power_up_list->power_up[i].type != 0){
                    power_up_list->power_up[i].rec.x -= 42;
                }
            }
        }
    }
}


