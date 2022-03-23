#include <iostream>
#include <iomanip>
#include <conio.h>
#include <ctime>
#include <windows.h>
#define Width 5
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
struct NODE{
    char key;
    int row, col;
    NODE* p_next;
    NODE* p_prev;
};

struct List{
    NODE* p_head;
    NODE* p_tail;
    Pair firstCorner, secondCorner;
};

//1. Initialize a NODE from a given integer
NODE* createNode(char key, int row, int col){
    NODE *node = new NODE;
    node->key = key;
    node->row = row;
    node->col = col;
    node->p_next = nullptr;
    node->p_prev = nullptr;
    return node; 
}
//Create Queue
void createQueue(List *Queue, Pair *p){
    Queue->p_head = createNode('#', p[0].row, p[0].col);
    Queue->p_tail = createNode('#', p[1].row, p[1].col);
    Queue->p_head->p_next = Queue->p_tail;
    Queue->p_tail->p_prev = Queue->p_head;
}
//Insert before tail
void insertBeforeTail(NODE* &pTail, char key, int row, int col){
    NODE *new_node = createNode(key, row, col);
    NODE *temp = pTail->p_prev;
    temp->p_next = new_node;
    new_node->p_prev = temp;
    new_node->p_next = pTail;
    pTail->p_prev = new_node;
}
//Remove node ater head
void removeNode(NODE * &Node){
    NODE *temp = Node->p_prev;
    temp->p_next = Node->p_next;
    Node->p_next->p_prev = temp;  
    delete Node;
}
//Remove NODE between 2 Start and End
void removeAll(List *Queue){
    NODE * cursor = Queue->p_head->p_next, *temp;
    while(cursor != Queue->p_tail){
        temp = cursor;
        cursor = cursor->p_next;
        removeNode(temp);
    }
}  
//-----------------------------------------------------------------
Vector calVec(Pair start, Pair end)
{
    Vector vec;
    vec.c = end.col - start.col;
    vec.r = end.row - start.row;
    
    vec.c = (vec.c > 0) - (vec.c < 0);
    vec.r = (vec.r > 0) - (vec.r < 0);

    return vec;
}

bool CheckQueue(List* Queue){
    for(NODE* cursor = Queue->p_head->p_next; cursor != Queue->p_tail; cursor = cursor->p_next){
        if(cursor->key != ' ')
            return false;
    }
    return true;
}
void SetQueue(char **board, Pair *p, List *Queue){
    Vector v1, v2, v3;
    //find Vector;
    v1 = calVec(p[0], Queue->firstCorner);
    v2 = calVec(Queue->firstCorner, Queue->secondCorner);
    v3 = calVec(Queue->secondCorner, p[1]);
    //Set Queue
    for(int i = p[0].row + v1.r, j = p[0].col + v1.c; i != Queue->firstCorner.row || j != Queue->firstCorner.col; i += v1.r, j += v1.c){
        insertBeforeTail(Queue->p_tail, board[i][j], i, j);
    }
    for(int i = Queue->firstCorner.row, j = Queue->firstCorner.col; i != Queue->secondCorner.row || j != Queue->secondCorner.col; i += v2.r, j += v2.c){
        insertBeforeTail(Queue->p_tail, board[i][j], i, j);
    }
    for(int i = Queue->secondCorner.row, j = Queue->secondCorner.col; i != p[1].row || j != p[1].col; i += v3.r, j += v3.c){
        insertBeforeTail(Queue->p_tail, board[i][j], i, j);
    }
}
bool CheckConect(char **board, Board b, Pair *p, List *Queue){
    createQueue(Queue, p);
    
    //----------------------------------------------
    for(int r = p[0].row; r >= 0; r--){
        //Set 2 conner
        Queue->firstCorner = {r, p[0].col};
        Queue->secondCorner = {r, p[1].col};
        SetQueue(board, p, Queue);
        if(CheckQueue(Queue))
        {
            return true;
        }
        removeAll(Queue);
    }
    //------------------------------------------------
    //----------------------------------------------
    for(int r = p[0].row; r < b.rows; r++){
        //Set 2 conner
        Queue->firstCorner = {r, p[0].col};
        Queue->secondCorner = {r, p[1].col};
        SetQueue(board, p, Queue);
        if(CheckQueue(Queue))
        {
            return true;
        }
        removeAll(Queue);
    }
    //------------------------------------------------
    //----------------------------------------------
    for(int c = p[0].col; c >= 0; c--){
        //Set 2 conner
        Queue->firstCorner = {p[0].row, c};
        Queue->secondCorner = {p[1].row, c};
        SetQueue(board, p, Queue);
        if(CheckQueue(Queue))
        {
            return true;
        }
        removeAll(Queue);
    }
    //------------------------------------------------
    //----------------------------------------------
    for(int c = p[0].col; c < b.columns; c++){
        //Set 2 conner
        Queue->firstCorner = {p[0].row, c};
        Queue->secondCorner = {p[1].row, c};
        SetQueue(board, p, Queue);
        if(CheckQueue(Queue))
        {
            return true;
        }
        removeAll(Queue);
    }
    //------------------------------------------------
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

void drawH(int columns, int row, char **board, int direct, Board b){
    char chr;
    cout << setw(Width/2) << setfill(' ') << left << " ";
    for(int i = 0; i < columns; i++){
        
        if(board[row][i] == ' ')
        {   
            if(row+direct >=0 && row+direct < b.rows){
                if(board[row+direct][i] == ' '){
                    chr = ' ';
                }else chr = '-';
            }
            else chr = ' ';
        }
        else chr = '-';
        cout << " " << setw(Width+2) << setfill(chr) << " ";
    }
    cout << endl;
}

void drawV(int columns, int row, char **board, Board b){
    char chr = '|';
    cout << setw(Width/2) << setfill(' ') << left << " ";
    for(int j = 0; j < columns; j++){
        if(board[row][j] == ' ')
        {
            if(j > 0 ){
                if(board[row][j-1] == ' '){
                    chr = ' ';
                }else chr = '|';
            }else chr = ' ';
        }
        else chr = '|';
        cout << chr << setw(Width+2) << setfill(' ') << " ";
    }
    
    if(board[row][b.columns-1] == ' ')
    {
        chr = ' ';
    }
    else chr = '|';
    cout << chr << endl;
}

void drawBoard(char **board, Board b, int row, int col){
    system("cls");
    char chr;
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    for(int i = 0; i < b.rows; i++){
        drawH(b.columns, i, board, -1, b);
        drawV(b.columns, i, board, b);
        cout << setw(Width/2) << setfill(' ') << left << " ";
        for(int j = 0; j < b.columns; j++){
            if(board[i][j] == ' ')
            {
                if(j > 0 ){
                    if(board[i][j-1] == ' '){
                        chr = ' ';
                    }else chr = '|';
                }else chr = ' ';
            }
            else chr = '|';
            cout << chr << " ";
            if(i == row && j == col){
                SetConsoleTextAttribute(hStdout, 240);
            }
            cout << setw(Width) << right << board[i][j] <<" ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        }
        if(board[i][b.columns-1] == ' ')
        {
            chr = ' ';
        }
        else chr = '|';
        cout << chr <<endl;
        drawV(b.columns, i, board, b);
    }
    drawH(b.columns,b.rows-1, board, 1, b);
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

    //----------------------
    bool exist = false;
    int key_event;
    int col = 0,row = 0;
    Pair p[2];
    int count = 0;

    while(exist == false){ 
        exist = check(board, b);
        drawBoard(board, b, row, col);
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
                List Queue;
                //Update movement
                p[count].row = row;
                p[count].col = col;
                count++; 
                cout << (char)7;
                //Marking 
                //Setcolor(table[row][col], "\e[45m");
                
                //Control flow
                if(count == 2){
                    if((p[0].row == p[1].row) && (p[0].col == p[1].col)){
                        count = 0;
                        continue;
                    }
                    //drawBoard(table, b, col, row);
                    //system("sleep");
                    if((board[p[0].row][p[0].col] == board[p[1].row][p[1].col]) && (board[p[0].row][p[0].col] != ' ')){
                        if(CheckConect(board, b, p, &Queue)){
                            board[p[0].row][p[0].col] = board[p[1].row][p[1].col] =  ' ';    
                            removeAll(&Queue);
                        }
                        delete Queue.p_head;
                        delete Queue.p_tail;
                    }
                    count = 0;
                }
    
                break;
            }
            
            default: continue;
        }
        
        //--------
    }
        
    

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
