#pragma once
#include <stdint.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

struct Node{
    Node(){}
    int32_t number;
    int32_t price;
    int32_t amount;
    Node *rlink;
    Node *llink;
    Node *parent;
};

class tree{
public:
    Node** infix()                 //create array
    {
        Node **array = new Node*[size_];
        infix(array, root);
        return array;
    }
    Node** levelorder();
    void create(int32_t number,int32_t price,int32_t amount);
    void show();                   //create and show
    Node* search(int32_t number);
    Node* insucc(Node *current);
    void remove(Node *current);
    Node *pricesearch();
    size_t size(){return size_;}
private:    
    Node ** infix(Node **arr,Node *ptr);
    Node *root = nullptr;
    size_t size_ = 0;
};
