#include <ctime>
#include <iostream>
#include "Structure.h"

//CREATE BOARD ###################################################################################################################
void swap(char & a, char & b){
    char temp = a;
    a = b;
    b = temp;
}

void shuffle(char **&board, Board b){
    srand(time(NULL));
    int x1, x2, y1, y2;
    for(int i = 0; i < rand()% (b.columns*b.columns)+10; i++){
        do{
            x1 = rand()%(b.columns-1) + 1;
            y1 = rand()%(b.rows-1) + 1;
            x2 = rand()%(b.columns-1) + 1;
            y2 = rand()%(b.rows-1) + 1;
        }while(board[y1][x1] == ' ' || board[y2][x2] == ' ' || board[y1][x2] == ' ' || board[y2][x1] == ' ');

        swap(board[y1][x1], board[y2][x2]);
        swap(board[y1][x2], board[y2][x1]);
    }
}

char** createBoard(Board &b){
    char pokemon;
    b.rows += 2;
    b.columns += 2;
    char **board = new char*[b.rows];
// create board
    srand(time(NULL));
    for(int i = 0; i < b.rows; i++){
        board[i] = new char[b.columns];
        board[i][0] = board[i][b.columns-1] = ' ';
         
        for(int j = 1; j < b.columns-2; j+=2){
            if(i == 0 || i == b.rows - 1)
                pokemon = ' ';
            else pokemon = rand()% 26 + 65;

            board[i][j] = board[i][j+1] = pokemon;
        }
    } 
// shuffle :v
    shuffle(board, b);

    return board; 
}