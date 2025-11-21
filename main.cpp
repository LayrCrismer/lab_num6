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


    draw_board(board);
}