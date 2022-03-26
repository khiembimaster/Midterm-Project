#include <iostream>
#include <conio.h>
// My header file
#include "Checking.h"
#include "Display.h"
#include "GenerateBoard.h"
//--------------------
using namespace std;



//IN GAME  ########################################################################################################################-
void Client(char **board, Board b){
    system("cls");

    
    //Drawable 2d array
        //create a screen
    string ****table = new string***[b.rows];
    for(int r = 0; r < b.rows; r++){
        table[r] = new string**[b.columns];
        for(int c = 0; c < b.columns; c++){
            table[r][c] = new string*[5];
            for(int i = 0; i < 5; i++){
                table[r][c][i] = new string[Width];
            }
            //draw Hline
            for(int j = 1; j < Width-1; j++){
                table[r][c][0][j] = table[r][c][4][j] = '-';
            }
            //draw row 1-3
            for(int i = 1; i < 5-1; i++){
                table[r][c][i][0] = table[r][c][i][Width-1] = "|";
                for(int j = 1; j < Width-1; j++){
                    table[r][c][i][j] = ' ';
                }
            }
            //Set corner
            table[r][c][0][0] = table[r][c][0][Width-1] = table[r][c][4][0] = table[r][c][4][Width-1] = ' ';
            //Set value
            table[r][c][5/2][Width/2] = board[r][c];

        }
    }

    //Pair *tracker = new Pair [b.rows*b.columns+1];
    

    //----------------------
    bool exist = false;
    int key_event;
    int col = 0,row = 0;
    Pair p[2];
    int count = 0;
    //-------
    int counter = 0;
    time_t curent, past;
    curent = time(NULL);

    while(exist == false){ 
        past = curent;
        curent = time(NULL);
        counter += curent - past;

        drawBoard(table, b, col, row);
        cout << counter << endl;

        //move-----
        key_event = getch();
        switch(key_event){
            //27 for escape ESC
            case 27:{
                exist = true;
                break; 
            }
            //Move right
            case 'D':
            case 77:
            case 'd':{
                if(col < b.columns - 1) col++;
                break;
            }
            //Move left
            case 'A':
            case 75:
            case 'a':{
                if(col > 0) col--;
                break;
            }
            //Move Up
            case 'W':
            case 72:
            case 'w':{
                if(row > 0) row--;
                break;
            }
            //Move down
            case 'S':
            case 80:
            case 's':{
                if(row < b.rows - 1) row++;
                break;
            }
            //Confirm - Space
            case 32:{  
                //Update movement
                p[count].row = row;
                p[count].col = col;
                count++; 
                cout << (char)7;
                //Marking 
                Setcolor(table[row][col], "\e[45m");
                
                
                //Control flow
                if(count == 2){
                    if((p[0].row == p[1].row) && (p[0].col == p[1].col)){
                        Recolor(table[p[0].row][p[0].col], "\e[45m");
                        Recolor(table[p[1].row][p[1].col], "\e[45m");
                        count = 0;
                        continue;
                    }
                    //Upadate Screen
                    drawBoard(table, b, col, row);
                    system("sleep");
                    if((board[p[0].row][p[0].col] == board[p[1].row][p[1].col]) && (board[p[0].row][p[0].col] != ' ')){
                        List Queue;
                        if(CheckConect(board, b, p, &Queue)){
                            DrawPath(table, &Queue);
                            drawBoard(table, b, col, row);
                            system("pause");
                            DeletePath(table, &Queue);
                            board[p[0].row][p[0].col] = board[p[1].row][p[1].col] =  ' ';    
                            //earse grid
                            erase(table[p[0].row][p[0].col]);
                            erase(table[p[1].row][p[1].col]);
                            removeAll(&Queue);

                            exist = check(board, b);
                        }
                        delete Queue.p_head;
                        delete Queue.p_tail;
                    }
                    //Reset
                    Recolor(table[p[0].row][p[0].col], "\e[45m");
                    Recolor(table[p[1].row][p[1].col], "\e[45m");
                    count = 0;
                }
                break;
            }
            
            default: continue;
        }
        
        //--------
    }

        
    for(int i = 0; i < b.rows; i++){
        for(int j = 0; j < b.columns; j++){
            for(int r = 0; r < 5; r++){
                delete[] table[i][j][r];
            }
            delete[] table[i][j];
        }
        delete[] table[i];
    }
    delete[] table;

    
    

}


int main(){
    
    Board b= {6,8};
    char ** board;

    do{
        board = createBoard(b);
        if (check(board, b))
        {
            for(int i = 0; i < b.rows; i++){
                delete[] board[i];
            }
            delete[] board;
        }
        break;
    }while(true);

    Client(board,b);



// delete board
    for(int i = 0; i < b.rows; i++){
        delete[] board[i];
    }
    delete[] board;
}
