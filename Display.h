#include <iostream>
#include <windows.h>
#include <string>
#include "Structure.h"
#define Width 8
#define CURSOR_COLOR 176
#define SCREEN_COLOR 5
using namespace std;
//DRAW ########################################################################################################################---
//iprint board
void drawBoard(string ****table, Board b, int col, int row){
    system("cls");
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    
    //Draw first row 
    string output;
    for(int r = 0; r < b.rows; r++){
        for(int i = 0; i < 5; i++){
            for(int c = 0; c < b.columns; c++){
                for(int j = 0; j < Width; j++){
                    if(r == row && c == col){
                        if(i == 2 && j == Width/2)
                        SetConsoleTextAttribute(hStdout, CURSOR_COLOR);
                    }
                    cout << table[r][c][i][j];
                    SetConsoleTextAttribute(hStdout, SCREEN_COLOR);
                }
            }
            cout << endl;
        }
    }
    
}
//Erase grid
void erase(string** grid){
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < Width; j++){
            grid[i][j] = " ";
        }
    }
}
//Set color
void Setcolor(string** grid, string color){
    for(int r = 1; r < 5-1; r++){
        for(int c = 1; c < Width-1; c++){
            grid[r][c].insert(0,color);
        }
    }
}
//Reset color
void Recolor(string** grid, string color){
    for(int r = 1; r < 5-1; r++){
        for(int c = 1; c < Width-1; c++){
            if(grid[r][c].size() >= color.size())
                grid[r][c].erase(0,color.size());
        }
    }
}
//Draw Path 
void DrawPath(string ****table, List *Queue){
    for(NODE* cursor = Queue->p_head; cursor != Queue->p_tail; cursor = cursor->p_next){
        Setcolor(table[cursor->row][cursor->col], "\e[44m");
    }
}

void DeletePath(string ****table, List *Queue){
    for(NODE* cursor = Queue->p_head; cursor != Queue->p_tail; cursor = cursor->p_next){
        Recolor(table[cursor->row][cursor->col], "\e[44m");
    }
}