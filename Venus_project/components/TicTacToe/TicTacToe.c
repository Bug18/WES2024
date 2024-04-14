#include <stdio.h>
#include <stdbool.h>
#include "TicTacToe.h"


char game[9];
volatile player onmove;

void startGame(char start) {
    //isprazni matricu igre
    for (int i = 0; i < 9; i++) {
        game[i]= '\0';
    }

    if (start == 'x') {
        onmove = DEVICE;
    }else {
        onmove = SERVER;
    }
}

bool gameWon(void) {
    if (game[0] == game[1] && game[0] == game[2] && game[0] != '\0') {
        return true;
    }else if (game[3] == game[4] && game[3] == game[5] && game[3] != '\0') {
        return true;
    }else if (game[6] == game[7] && game[6] == game[8] && game[6] != '\0') {
        return true;
    }else if (game[3] == game[0] && game[3] == game[6] && game[3] != '\0') {
        return true;
    }else if (game[1] == game[4] && game[1] == game[7] && game[1] != '\0') {
        return true;
    }else if (game[2] == game[5] && game[2] == game[8] && game[2] != '\0') {
        return true;
    }else if (game[0] == game[4] && game[0] == game[8] && game[0] != '\0') {
        return true;
    }else if (game[2] == game[4] && game[2] == game[6] && game[2] != '\0') {
        return true;
    }
    return false;
}

bool gameEnded() {
    bool end = true;
    for(int i = 0; i < 9; i ++) {
        if (game[i] == '\0') {
            end = false;
            break;
        }
    }
    return end;
}

game_status makeMove(char letter, int position) {
    if (game[position] == '\0') {
        game[position] = letter;
    }else {
        printf("Invalid move");
        return INVALID_MOVE;
    }

    if (gameWon()) {
        return GAME_WON;
    }else if (gameEnded()){
        return GAME_ENDED;
    }else {
        if (onmove == DEVICE) onmove = SERVER;
        else onmove = DEVICE;
        return GAME_ONGOING;
    }
}

player getCurrentPlayer() {
    return onmove;
}

char *get_game_array(void) {
    return game;
}
