#ifndef BOARD
#define BOARD

#include <ctime>
#include <conio.h>
#include <iostream>
#include"Node.h"
#define Width 8
#define CURSOR_COLOR 251
#define SCREEN_COLOR 11
using namespace std;

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

struct List{
    void deleteNode(Node* cur){
        Node* temp = createNode(' ');
        temp->right = nullptr;
        temp->left = p_tail;
        temp->row = p_tail->row;
        p_tail->right = temp;
        p_tail = temp;
        
        if(cur == p_head){
            cur = cur->right;
            delete p_head;
            p_head = cur;
            return;
        }
        
        Node*left = cur->left;
        Node*right = cur->right; 
        left->right = right;
        right->left = left;
        delete cur;
    }
    Node*p_head;
    Node*p_tail;
};

struct Board{
    Board(int width, int height): width{width}, height{height}{
        rows = new List[height];
    }
    void createDoublyLinkedlist(Node *prev, Node *&cur, int index){
        if(index == width*height){
            p_tail = prev;
            return;
        } 
        char key = rand()% 26 + 65;
        cur = createNode(key);
        cur->left = prev;
        Node* temp = cur->right = createNode(key);
        temp->left = cur;
        cur->row = index/width;
        temp->row = (index+1)/width;
        createDoublyLinkedlist(temp, temp->right, index+2);
    }   

    void Shuffle(){
        srand(time(NULL));
        for(int i = 0; i < (width*height); i++){
            int a = rand()% (width*height);
            int b = rand()% (width*height);
            Node*a_ptr = getNode(p_head, a);
            Node*b_ptr = getNode(p_head, b); 
            char temp = a_ptr->key;
            a_ptr->key = b_ptr->key;
            b_ptr->key = temp; 
        }
    }

    void createBoard(){
        Node* cursor = p_head;
        for(int i = 0; i < height; i++){
            rows[i].p_head = getNode(cursor, 0);
            rows[i].p_tail = getNode(cursor, width-1);
            cursor = rows[i].p_tail->right;
        }
        for(int i = 0; i < height; i++){
            rows[i].p_head->left = nullptr;
            rows[i].p_tail->right = nullptr;
        }
    }

    void deleteBoard(){
        for(int i = 0; i < height; i++){
            for(Node* cursor = rows[i].p_head; cursor != nullptr; ){
                Node* temp = cursor->right;
                delete cursor;
                cursor = temp;
            }
        }
        delete[] rows;
    } 

    void DrawBoard(int col, int row, int timer);
    void SetTable();    

    bool CheckQueue();

    void SetQueue(Pair *p);

    bool CheckConect(int col1, int col2, int row1, int row2);

    string****table;
    List *rows;
    List Queue;
    Node *p_head;
    Node *p_tail;
    int width, height;
};

#endif