#include <iostream>
#include <conio.h>
#include <windows.h>
// My header file
#include "Checking.h"
#include "Display.h"
#include "GenerateBoard.h"
//--------------------
using namespace std;

void Difficulty(char **board, Board b, Pair* p, Pair* helper){
    int count = 3;
    for(int i = 0; i < 2; i++){
        if(board[p[i].row][p[i].col] != ' ')
            p[i].col--; 
        for(int j = p[i].col ; j < b.columns-1; j++){
            board[p[i].row][j] = board[p[i].row][j+1];
        }
        board[p[i].row][b.columns-1] = ' ';    
    }

}

void MoveH(char**board, Board b, int &row, int &col, int dr){
    //move
    int wide = 0;
    while(0 < row - wide || row + wide < b.rows-1){
        int step = dr;
        while(0 < col+step && col+step < b.columns-1){
            if(0 < row - wide){
                if(board[row - wide][col + step] != ' ') 
                {   
                    row -= wide;
                    col += step;
                    return;
                }
            }
            if(row + wide < b.rows-1){
                if(board[row + wide][col + step] != ' ') 
                {   
                    row += wide;
                    col += step;
                    return;
                }
            }
            step += dr;
        }
        wide++;
    }
}

void MoveV(char**board, Board b, int &row, int &col, int dr){
    //move
    int wide = 0;
    while(0 < col - wide || col + wide < b.columns-1){
        int step = dr;
        while(0 < row+step && row+step < b.rows-1){
            if(0 < col - wide){
                if(board[row + step][col - wide] != ' ') 
                {   
                    col -= wide;
                    row += step;
                    return;
                }
            }
            if(col + wide < b.columns-1){
                if(board[row + step][col + wide] != ' ') 
                {   
                    col += wide;
                    row += step;
                    return;
                }
            }
            step += dr;
        }
        wide++;
    }
}

//IN GAME  ########################################################################################################################-
void Client(char **board, Board b, bool difficult, Pair *helper, int &timer){
    system("cls");
    timer = 0;
    string* background = new string[b.rows*5*2];
    string bg_name = "BGs\\BG.txt";
    srand(time(NULL));
    char chr = '0' + rand()%3;
    bg_name.insert(bg_name.begin()+6, chr);
    createBackGround(background, b, bg_name);
    
    //Drawable 2d array
        //create a screen
    string ****table = new string***[b.rows];
    SetTable(table, board, b);

    //Pair *tracker = new Pair [b.rows*b.columns+1];


    //----------------------
    bool exist = false;
    int key_event;
    int col = 1,row = 1;
    Pair p[2];
    int count = 0;
    //-------
    time_t curent, past;
    curent = time(NULL);

    while(exist == false){

        //time
        past = curent;
        curent = time(NULL);
        timer += curent - past;

        drawBoard(table, b, col, row, timer, background);


        //move-----
        key_event = getch();
        switch(key_event){
            //13 Enter
            case 13:{
                Setcolor(table[helper[0].row][helper[0].col], "\e[45m");
                Setcolor(table[helper[1].row][helper[1].col], "\e[45m");
                drawBoard(table, b, col, row, timer, background);
                system("pause");
                Recolor(table[helper[0].row][helper[0].col], "\e[45m");
                Recolor(table[helper[1].row][helper[1].col], "\e[45m");
            }break;
            //27 for escape ESC
            case 27:{
                exist = true;
                break; 
            }
            //Move right
            case 'D':
            case 77:
            case 'd':{
                MoveH(board, b, row, col, 1);
                break;
            }
            //Move left
            case 'A':
            case 75:
            case 'a':{
                MoveH(board, b, row, col, -1);
                break;
            }
            //Move Up
            case 'W':
            case 72:
            case 'w':{
                MoveV(board, b, row, col, -1); 
                break;
            }
            //Move down
            case 'S':
            case 80:
            case 's':{
                MoveV(board, b, row, col, 1); 
                break;    
            }
            //Confirm - Space
            case 32:{  
                //Update movement
                p[count].row = row;
                p[count].col = col;
                count++; 
                //Sound
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
                    drawBoard(table, b, col, row, timer, background);
                    system("sleep");
                    if((board[p[0].row][p[0].col] == board[p[1].row][p[1].col]) && (board[p[0].row][p[0].col] != ' ')){
                        List Queue;
                        if(CheckConect(board, b, p, &Queue)){
                            DrawPath(table, &Queue);
                            drawBoard(table, b, col, row, timer, background);
                            DeletePath(table, &Queue);
                            board[p[0].row][p[0].col] = board[p[1].row][p[1].col] = ' ';
                            
                            if(difficult)
                                Difficulty(board, b, p, helper);
                            
                            //reset Table

                            removeAll(&Queue);
                            exist = check(board, b, helper);
                        }
                        delete Queue.p_head;
                        delete Queue.p_tail;
                    }
                    //Reset table
                    while(check(board, b, helper) == 1){
                        shuffle(board, b);
                    }
                    SetTable(table, board, b);
                    count = 0;
                }
                break;
            }
            
            default: continue;
        }
        
        //--------
    }
    delete[] background;
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

void Game(){
    Board b;
    char ** board;
    int timer;
    //Helper
    Pair helper[2] = {-1,-1};
    bool isDiff;

    //-----------------------
    bool exist = false;
    char choice;

    while(true){
        system("cls");
        cout 
        << "1. Normal(6x12)" << endl
        << "2. Difficult(6x12) " << endl
        << "3. Custom " << endl
        << "4. Back to main" << endl
        << "5. Continue" << endl;

        choice = getch();
        cout << (char)7;
        switch (choice)
        {
        case '1':{
            b.rows = 2;
            b.columns = 4;
            isDiff = false;
        }break;
        case '2':{
            b.rows = 2;
            b.columns = 4;
            isDiff = true;
        }break;
        case '3':{
            cout << "Enter BOARD size (Height / Width): " ;
            cin >> b.rows >> b.columns;
            cout << "Enter 0 to of Difficult mode: ";
            cin >> isDiff;
        }break;
        case '4':{
            exist = true;
        }break;
        case '5':{
            break;
        }break;
        
        default:
            continue;
        }
        if(b.rows >= 8)
            exist = true;
        if(exist)
            break;
        do{
            board = createBoard(b);
            if (check(board, b, helper))
            {
                for(int i = 0; i < b.rows; i++){
                    delete[] board[i];
                }
                delete[] board;
            }
            break;
        }while(true);
        Client(board,b, isDiff, helper, timer);
        
        // delete board
        for(int i = 0; i < b.rows; i++){
            delete[] board[i];
        }
        delete[] board;
    }
    

}

int main(){
    ::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
    Game();

}
