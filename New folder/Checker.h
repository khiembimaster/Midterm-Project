
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
            return true;

        removeAll(Queue);
    }
    //------------------------------------------------
    return false;
}