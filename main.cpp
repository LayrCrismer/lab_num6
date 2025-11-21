//
// Created by fedot on 21.11.2025.
//
#include <iostream>
#include "heads.h"
#include "functions.cpp"
using namespace std;

void board_generation(int board[SIZE][SIZE]);
void draw_board(const int board[SIZE][SIZE]);
void find_emptyslot(const int board[SIZE][SIZE],int& empty_row, int& empty_col);
void swapSlots(int& a, int& b);
bool moveTile(int board[SIZE][SIZE], char move);
void mixTiles(int board[SIZE][SIZE]);


int main() {
    int board[SIZE][SIZE];


    srand(time(NULL));
    do {
        board_generation(board);
        mixTiles(board);
    } while (!mayCompleted(board));

    char move;

    while (!isComplete(board)) {
        draw_board(board);

        cout<<"Введите ход: "<<endl;
        cin>>move;

        if (move=='q') {
            cout<<"Выход из игры."<<endl;
            return 0;
        }

        if (!moveTile(board, move)) {
            cerr<<"Недопустимый ход! Попробуйте снова."<<endl;
        }
    }

    draw_board(board);
    cout<<"Вы успешно решили головоломку!";

    return 0;
}