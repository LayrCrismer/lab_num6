//
// Created by fedot on 21.11.2025.
//
#include <iostream>
#include <iomanip>
#include "heads.h"
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

void draw_board(const int board[SIZE][SIZE]) { //отрисовка игрового поля
    for (int i = 0; i < SIZE; i++) {
        cout<<"|";
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                cout<<setw(4)<<" "; //пустая ячейка - пробел
            }
            else {
                cout<<setw(4)<<board[i][j];
            }
            cout<<"|"; //разделители
        }
        cout<<endl;
    }
}
