#include "Structure.h"
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