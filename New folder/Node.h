#ifndef NODE
#define NODE

struct Node{
    char key;
    int row;
    Node *left =  nullptr;
    Node *right =  nullptr;
};  

Node*createNode(char key){
    Node *node = new Node;
    node->key = key;
    return node;
}
int getPos(Node* pHead, Node* cur){
    if(pHead == cur) return 0;
    return 1 + getPos(pHead->right, cur);
}
Node *getNode(Node* pHead, int pos){
    if(pHead == nullptr) return pHead;
    if(pos == 0) return pHead;
    return getNode(pHead->right, pos-1);
}

#endif // NODE