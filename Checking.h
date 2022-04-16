#include "LinkedList.h"
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
            return false;// Invalid move
    } 
    return true;// Valid move
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
    createQueue(Queue, p); // create Base Queue
    //----------------------------------------------
    for(int r = p[0].row - 1; r >= 0; r--){
        //Set 2 conner
        Queue->firstCorner = {r, p[0].col};
        Queue->secondCorner = {r, p[1].col};
        SetQueue(board, p, Queue);
        if(CheckQueue(Queue)) return true; //There are legal move
        removeAll(Queue);
    }
    //------------------------------------------------
    //----------------------------------------------
    for(int r = p[0].row + 1; r < b.rows; r++){
        //Set 2 conner
        Queue->firstCorner = {r, p[0].col};
        Queue->secondCorner = {r, p[1].col};
        SetQueue(board, p, Queue);
        if(CheckQueue(Queue)) return true; //There are legal move
        removeAll(Queue);
    }
    //----------------------------------------------
    //----------------------------------------------
    for(int c = p[0].col - 1; c >= 0; c--){
        //Set 2 conner
        Queue->firstCorner = {p[0].row, c};
        Queue->secondCorner = {p[1].row, c};
        SetQueue(board, p, Queue);
        if(CheckQueue(Queue)) return true; //There are legal move
        removeAll(Queue);
    }
    //----------------------------------------------
    //----------------------------------------------
    for(int c = p[0].col + 1; c < b.columns; c++){
        //Set 2 conner
        Queue->firstCorner = {p[0].row, c};
        Queue->secondCorner = {p[1].row, c};
        SetQueue(board, p, Queue);
        if(CheckQueue(Queue)) return true; //There are legal move
        removeAll(Queue);
    }
    //------------------------------------------------
    return false; //There is no more legal move
}

//Check if the game got stuck
int check(char **board, Board b, Pair *helper){
    int checker = 1; //Set if there is no more legal move first.
    int count = 0; //Help count the number of existing pokemon 
    for(int i = 0; i < b.rows*b.columns; i++){    
        if(board[i / (b.columns)][i % (b.columns)] == ' ') {
            count++;
            continue; // Skip the below step if this grid is empty
        }
        for(int j = i + 1; j < b.rows*b.columns; j++){
            if(board[i / (b.columns)][i % b.columns] != board[j / b.columns][j % (b.columns)]) continue;
            List Queue;
            Pair p[2] = {{i / (b.columns), i % (b.columns)},{j / (b.columns), j % (b.columns)}};
            if(CheckConect(board, b, p, &Queue)){
                //To help player find legal move
                helper[0] = p[0];
                helper[1] = p[1];
                removeAll(&Queue);
                checker = 0;// there is legal move
            }
            delete Queue.p_head;
            delete Queue.p_tail;
        }
    }
    if(count == b.rows*b.columns)
        checker = 2;// Board cleaned
    return checker;
}
