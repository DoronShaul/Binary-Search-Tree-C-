#include <iostream>

#pragma once
namespace ariel
{
struct Node
{
    int value;
    Node *parent;
    Node *left;
    Node *right;
};

class Tree
{
  public:
    Tree();
    ~Tree();
    
    void insert(int key);
    void remove(int key);
    int size();
    bool contains(int key);
    int root();
    int parent(int key);
    int left(int key);
    int right(int key);
    void print();
    void printInorder(Node *leaf);
    void swapValue (Node *a,Node *b);
    Node* searchNode(int key, Node *leaf);
    Node* searchBiggestNode(Node *leaf);
  
   

  private:
    void deleteTree(Node *leaf);

    int treeSize;
    Node *treeRoot;
};
} // end namespace ariel
