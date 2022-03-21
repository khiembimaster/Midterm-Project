#include <iostream>
#include <iomanip>
#include <conio.h>
#include <ctime>
#define Width 8
using namespace std;

struct Board{
    int rows;
    int columns;
};
struct Vector{
    int r,c;
};
struct Pair{
    int row,col;
};

Vector calVec(Pair start, Pair end)
{
    Vector vec;
    vec.c = end.col - start.col;
    vec.r = end.row - start.row;
    
    vec.c = (vec.c > 0) - (vec.c < 0);
    vec.r = (vec.r > 0) - (vec.r < 0);

    return vec;
}

bool CheckI(char **board, Board b, Pair start, Pair end, char chr){
    Vector vec = calVec(start, end);
    // if(board[start.row][start.col] != ' '){
    //     start.col += vec.c;
    //     start.row += vec.r;
    // }

    for(int c = start.col, r = start.row; c != end.col || r != end.row; c += vec.c, r += vec.r){
        if(board[r][c] != ' ' && board[r][c] != chr)
            return false;
    }
    return true;
}

bool CheckConect(char **board, Board b, Pair *p){
    Pair start, end;
    for(int r = 0; r < b.rows; r++){
        //Set 2 conner
        start.col = p[0].col;
        start.row = r;

        end.col = p[1].col;
        end.row = r;
        //CheckI 3 line 
        if(CheckI(board, b, start, end, board[p[0].row][p[0].col]) 
            && CheckI(board, b, start, p[0],board[p[0].row][p[0].col]) 
            && CheckI(board, b, end, p[1],board[p[0].row][p[0].col]))
            return true;
    }

    for(int c = 0; c < b.columns; c++){
        //Set 2 conner
        start.col = c;
        start.row = p[0].row;

        end.col = c;
        end.row = p[1].row;
        //CheckI 3 line 
        if(CheckI(board, b, start, end,board[p[0].row][p[0].col])
            && CheckI(board, b, start, p[0],board[p[0].row][p[0].col]) 
            && CheckI(board, b, end, p[1],board[p[0].row][p[0].col]))
            return true;
    }
    
    return false;
}

//Check if there are any square left
bool check(char **board, Board b){

    
    for(int i = 0; i < b.rows; i++){
        for(int j = 0; j < b.columns; j++){
            if(board[i][j] != ' ')
                return false;
        }
    }
    return true;
}


//DRAW ########################################################################################################################---
//iprint board
void drawBoard(string ****table, Board b, int col, int row){
    system("cls");
    //Draw first row 
    string output;
    for(int j = 0; j < b.columns; j++){
        for(int c = 0; c < Width; c++){
            if(table[0][j][0][c].empty())
                output = ' ';
            else output = table[0][j][0][c];
            cout << output << "\e[0m";
        }
    }
    cout << endl;
    //Draw the rest
    for(int i = 0; i < b.rows; i++){
        for(int r = 1; r < 5; r++){
            for(int j = 0; j < b.columns; j++){
                for(int c = 0; c < Width; c++){
                    output.erase();
                    if(c == Width/2 && r == 5/2){
                        if(row == i && col == j)
                            cout << "\e[4;32m" ;
                    }
                    output = table[i][j][r][c];
                    if((r == 4)  &&  (i+1 != b.rows)){
                        output = table[i][j][4][c] + table[i+1][j][0][c];
                        if(output == "--") output = "-";
                    }
                    if(c == Width-1 && (j+1 != b.columns)){
                        output = table[i][j][r][Width-1] + table[i][j+1][r][0];
                        if(output == "||") output = "|";
                    }
                    if(j > 0 && c == 0){
                        output = " ";
                    }
                    if(output.empty() || output == "\e[45m")
                        output += ' ';

                    cout << output << "\e[0m";
                }     
            }
            cout << endl;
        }
    }
    //system("pause");
}
//Erase grid
void erase(string** grid){
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < Width; j++){
            grid[i][j] = "";
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


//CREATE BOARD ###################################################################################################################
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
    for(int i = 0; i < rand()% (b.columns*b.columns)+100; i++){
        
        x1 = rand()%b.columns + 0;
        y1 = rand()%b.rows + 0;

        x2 = rand()%b.columns + 0;
        y2 = rand()%b.rows + 0;

        swap(board[y1][x1], board[y2][x2]);
        swap(board[y1][x2], board[y2][x1]);
    }


    return board; 
}

//IN GAME  ########################################################################################################################-
void Client(char **board, Board b){
    system("cls");

    
    //Drawable 2d array
        //create a screen
    string ****table = new string***[b.rows];
    for(int i = 0; i < b.rows; i++){
        table[i] = new string**[b.columns];
        for(int j = 0; j < b.columns; j++){
            table[i][j] = new string*[5];
            for(int r = 0; r < 5; r++){
                table[i][j][r] = new string[Width];
            }
            //draw Hline
            for(int c = 1; c < Width-1; c++){
                table[i][j][0][c] = table[i][j][4][c] = '-';
            }
            //draw Vline
            for(int r = 1; r < 5-1; r++){
                table[i][j][r][0] = table[i][j][r][Width-1] = "|";
            }
            //Set value
            table[i][j][5/2][Width/2] = board[i][j];
        }
    }

    //Pair *tracker = new Pair [b.rows*b.columns+1];


    //----------------------
    bool exist = false;
    int key_event;
    int col = 0,row = 0;
    Pair p[2];
    int count = 0;

    while(exist == false){ 
        exist = check(board, b);
        drawBoard(table, b, col, row);
        cout << count;
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
                        if(CheckConect(board, b, p)){
                            board[p[0].row][p[0].col] = board[p[1].row][p[1].col] =  ' ';    
                            //earse grid
                            erase(table[p[0].row][p[0].col]);
                            erase(table[p[1].row][p[1].col]);
                        }
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

    //delete[] tracker;
        
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
    
    Board b= {6,10};
    
    char ** board = createBoard(b);

    Client(board,b);



// delete board
    for(int i = 0; i < b.rows; i++){
        delete[] board[i];
    }
    delete[] board;
}
