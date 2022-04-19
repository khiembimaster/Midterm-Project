#ifndef DISPLAY
#define DISPLAY
#include <iostream>
#include <windows.h>
#include <string>
#include "Board.h"
#include "Node.h"
#define Width 8
#define CURSOR_COLOR 251
#define SCREEN_COLOR 11
using namespace std;

//DRAW ########################################################################################################################---
//iprint board
void Board::DrawBoard( int col, int row, int timer){
    system("cls");
    //-----------------------------------------------------
    int hour = timer/3600;
    timer %= 3600;
    int minute = timer/60;
    int second = timer%60;
    cout << hour << "h " << minute << "m " << second << "s " << endl ;

    //-----------------------------------------------------
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    
    //Draw first row 
    string output;
    for(int r = 0; r < height; r++){
        for(int i = 0; i < 5; i++){
            for(int c = 0; c < width; c++){
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
void Board::SetTable(){
for(int r = 0; r < height; r++){
        table[r] = new string**[width];
        int c = 0;
        for(Node* cursor = rows[r].p_head; cursor != nullptr; cursor = cursor->right, c++){
            table[r][c] = new string*[5];
            for(int i = 0; i < 5; i++){
                table[r][c][i] = new string[Width];
            }
            //draw Hline
            char chr = '-';
            if(cursor->key == ' ')
                chr = ' ';
                
            for(int j = 1; j < Width-1; j++){
                table[r][c][0][j] = table[r][c][4][j] = chr;
            }
            //draw row 1-3
            chr = '|';
            if(cursor->key == ' ')
                chr = ' ';
                
            for(int i = 1; i < 5-1; i++){
                table[r][c][i][0] = table[r][c][i][Width-1] = chr;
                for(int j = 1; j < Width-1; j++){
                    table[r][c][i][j] = ' ';
                }
            }
            //Set corner
            table[r][c][0][0] = table[r][c][0][Width-1] = table[r][c][4][0] = table[r][c][4][Width-1] = ' ';
            //Set value
            table[r][c][5/2][Width/2] = cursor->key;

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

// //Draw Path 
// void DrawPath(string ****table, List *Queue){
//     for(NODE* cursor = Queue->p_head; cursor != Queue->p_tail; cursor = cursor->p_next){
//         Setcolor(table[cursor->row][cursor->col], "\e[44m");
//     }
// }

// void DeletePath(string ****table, List *Queue){
//     for(NODE* cursor = Queue->p_head; cursor != Queue->p_tail; cursor = cursor->p_next){
//         Recolor(table[cursor->row][cursor->col], "\e[44m");
//     }
// }


#endif