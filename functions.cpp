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

void mixTiles(int board[SIZE][SIZE]) { //перемешивание плиток для начала игры
    int flat[SIZE * SIZE];
    int k = 0;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            flat[k++] = board[i][j];
        }
    }
    //алгоритм для случайного перемешивания
    for (int i = SIZE * SIZE - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        swapSlots(flat[i], flat[j]);
    }

    k = 0;
    for (int i = 0; i < SIZE; ++i) { //обратно в двумерный массив
        for (int j = 0; j < SIZE; ++j) {
            board[i][j] = flat[k++];
        }
    }
}

bool isComplete(const int board[SIZE][SIZE]) { //проверка завершения игры, расположены ли все плитки в правильном порядке
    int count = 1;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i==SIZE-1 && j==SIZE-1) {
                return board[i][j]==0; //последняя ячейка должна быть пустой
            }
            if (board[i][j] != count++) {
                return false; //найдена неверно расположенная плитка
            }
        }
    }
    return true; //все плитки успешно попали на свои места
}

int getInversions(const int board[SIZE][SIZE]) { //подсчет количества инверсий в расстановке, т.е подсчёт пар плиток, где большая цифра предшествует меньшей
    int flat[SIZE * SIZE];//двумерный массив в одномерный
    int k = 0;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            flat[k++] = board[i][j];
        }
    }

    int inversions = 0;
    for (int i = 0; i < SIZE * SIZE - 1; ++i) { //подсчёт инверсий без пустой ячейки
        for (int j = i + 1; j < SIZE * SIZE; ++j) {
            if (flat[i] != 0 && flat[j] != 0 && flat[i] > flat[j]) {
                inversions++;
            }
        }
    }
    return inversions;
}

bool mayCompleted(const int board[SIZE][SIZE]) { //проверка возможности решения головоломки из текущего состояния
    //использует математическое условие разрешимости "пятнашек" (нашёл в инете)
    int inversions = getInversions(board);
    int empty_row, empty_col;
    find_emptyslot(board, empty_row, empty_col);
    //вычисление строки пустой ячейки снизу от 1 до SIZE
    int emptyrow_bottom = SIZE - empty_row;

    if (SIZE % 2 != 0) {
        return inversions %2 == 0;
    }
    else {
        if (emptyrow_bottom % 2 != 0) {//для нечетного размера четное количество инверсий
            return inversions %2 ==0;
        }
        else { //для четного размера зависит от строки пустой ячейки и четности инверсий
            return inversions %2 != 0;
        }
    }
}