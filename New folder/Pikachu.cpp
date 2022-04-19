#include<iostream>
#include"Node.h"
#include"Display.h"
#include"Board.h"
using namespace std;



//
//IN GAME  ########################################################################################################################-
void Client(Board &board, bool isDifficult){
    system("cls");
    
    Node* cursor = board.p_head;
    Node* first;
    Node* second;
    first = second = nullptr;
    //----------------------
    bool exist = false;
    int key_event;
    int col = 0,row = 0;
    int count = 0;
    //-------
    int timer = 0;
    time_t curent, past;
    curent = time(NULL);
    
    board.SetTable();
    while(exist == false){
        past = curent;
        curent = time(NULL);
        timer += curent - past;
        int col = getPos(board.rows[cursor->row].p_head, cursor);
        board.DrawBoard(col, cursor->row, timer);
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
            if(cursor->right != nullptr) cursor = cursor->right;
                break;
            }
            //Move left
            case 'A':
            case 75:
            case 'a':{
                if(cursor->left != nullptr) cursor = cursor->left;
                break;
            }
            //Move Up
            case 'W':
            case 72:
            case 'w':{
                if(cursor->row == 0) break;
                cursor = getNode(board.rows[cursor->row-1].p_head, col);
                break;
            }
            //Move down
            case 'S':
            case 80:
            case 's':{
                if(cursor->row+1 == board.height) break;
                cursor = getNode(board.rows[cursor->row+1].p_head, col);
                break;
            }
            //Confirm - Space
            case 32:{  
                if(first == nullptr){
                    first = cursor;
                    Setcolor(board.table[first->row][col], "\e[45m");
                    break;
                }
                else second = cursor;

                if(first != second){
                    if(first->key == second->key){
                        if(isDifficult){
                            int row = cursor->row;
                            board.rows[first->row].deleteNode(first);
                            board.rows[second->row].deleteNode(second);
                            cursor = getNode(board.rows[row].p_head, col);
                        }
                        else first->key = second->key = ' ';
                    }
                }
                board.SetTable();
                first = second = nullptr;
            }break;
        }
        //--------
    }
}


int main(){
    Board board(10,6);
    srand(time(NULL));
    board.createDoublyLinkedlist(nullptr, board.p_head, 0);
    board.Shuffle();

    board.createBoard();
    Client(board, true);

    board.deleteBoard();
}