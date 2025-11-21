//
// Created by fedot on 21.11.2025.
//
#include <iostream>
#include <iomanip>
#include "head.h"
using namespace std;

void board_generation(int board[SIZE][SIZE]) { //генерация игрового поля, где каждая клетка - упорядоченное число от 1 до SIZE*SIZE-1
    int count = 1;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = count++;
        }
    }
    board[SIZE-1][SIZE-1] = 0; //правый нижний угол - пустой
}
