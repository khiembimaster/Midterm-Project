#ifndef STRUCT
#define STRUCT

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

#endif // STRUCT