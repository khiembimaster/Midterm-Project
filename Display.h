#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "Structure.h"
#define Width 10
#define SCREEN_COLOR 9
using namespace std;

void createBackGround(string *&background, Board b, string b_name){
    ifstream fs(b_name);
    int i = 0;
    while(i < b.rows*5){
        if(fs)
            getline(fs, background[i]);
        background[i].resize(b.columns*Width, ' ');
        i++;
    }
    fs.close();
}

//DRAW ########################################################################################################################---
//iprint board

void drawBoard(string ****table, Board b, int col, int row, int timer, string *background){
    string output;

    system("cls");
    //-----------------------------------------------------
    int hour = timer/3600;
    timer %= 3600;
    int minute = timer/60;
    int second = timer%60;
    cout << hour << "h " << minute << "m " << second << "s " << endl ;

    //-----------------------------------------------------
    //Draw first row 
    for(int r = 0; r < b.rows; r++){
        for(int i = 0; i < 5; i++){
            for(int c = 0; c < b.columns; c++){
                for(int j = 0; j < Width; j++){
                    if(r == row && c == col){
                        if(i == 2 && j == Width/2)
                            output.append("\e[47m");
                    }
                    if(table[r][c][i][j] == " " ){
                        output.append("\e[1;36m");
                        output+=(background[(r*5 + i)][c*Width+j]);
                        output.append("\e[0m");
                    }else {
                        output.append("\e[1;94m");
                        output.append(table[r][c][i][j]);
                        output.append("\e[0m");
                    }
                }
            }
            output.append("\n");
        }
    }
    cout << output;
}
//Erase grid
void SetTable(string**** table, char**board,  Board b){
for(int r = 0; r < b.rows; r++){
        table[r] = new string**[b.columns];
        for(int c = 0; c < b.columns; c++){
            table[r][c] = new string*[5];
            for(int i = 0; i < 5; i++){
                table[r][c][i] = new string[Width];
            }
            //draw Hline
            char chr = '-';
            if(board[r][c] == ' ')
                chr = ' ';
                
            for(int j = 1; j < Width-1; j++){
                table[r][c][0][j] = table[r][c][4][j] = chr;
            }
            //draw row 1-3
            chr = '|';
            if(board[r][c] == ' ')
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
            table[r][c][5/2][Width/2] = board[r][c];
            if(board[r][c] != ' ')table[r][c][5/2][Width/2].insert(0,"\e[4;31m");
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
                grid[r][c].erase(grid[r][c].find(color),color.size());
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