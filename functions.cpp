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

void find_emptyslot(const int board[SIZE][SIZE], int& empty_row, int& empty_col) { //поиск позиции пустой ячейки (обозначена нулем)
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                empty_row = i;
                empty_col = j;
                return; //выход при первой найденой пустой ячейке
            }
        }
    }
}

void swapSlots(int& a, int& b) { //вспомоготальеная перемещения плиток  - обмен значений двух переменных
    int temp = a;
    a=b;
    b=temp;
}

bool moveTile(int board[SIZE][SIZE],char move) { //перемещение плитки относительно пустой ячейки
    int e_UD, e_RL; //координаты пустой ячейки UD - Up/Down, RL - Right/Left
    find_emptyslot(board, e_UD, e_RL);

    int t_UD = e_UD; //координаты ячейки для перемещения
    int t_RL = e_RL;

    //определение координат ячейки которую нужно переместить
    switch (move) {
        case 'w':
            t_UD = e_UD+1;
            break;
        case 's':
            t_UD = e_UD-1;
            break;
        case 'a':
            t_RL = e_RL+1;
            break;
        case 'd':
            t_RL = e_RL-1;
            break;

    }
    //проверка правильности хода
    if (t_UD >= 0 && t_UD < SIZE && t_RL >= 0 && t_RL < SIZE) {
        swapSlots(board[e_UD][e_RL], board[t_UD][t_RL]); //обмен пустой и целевой ячейки
        return true;//успех
    }
    return false;//недопустимый ход
}