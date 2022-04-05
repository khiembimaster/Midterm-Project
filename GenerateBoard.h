#include <ctime>
#include <iostream>
#include "Structure.h"

//CREATE BOARD ###################################################################################################################
void swap(char & a, char & b){
    char temp = a;
    a = b;
    b = temp;
}
char** createBoard(Board b){
    char pokemon;
    int x1, x2, y1, y2;
    char **board = new char*[b.rows];
// create board
    srand(time(NULL));
    for(int i = 0; i < b.rows; i++){
        board[i] = new char[b.columns];
        for(int j = 0; j < b.columns; j+=2)
            board[i][j] = board[i][j+1] = rand()% 26 + 65;
    } 
// shuffle :v
    srand(time(NULL));
    for(int i = 0; i < rand()% (b.columns*b.columns)+20; i++){
        
        x1 = rand()%b.columns + 0;
        y1 = rand()%b.rows + 0;

        x2 = rand()%b.columns + 0;
        y2 = rand()%b.rows + 0;

        swap(board[y1][x1], board[y2][x2]);
        swap(board[y1][x2], board[y2][x1]);
    }
    

    return board; 
}