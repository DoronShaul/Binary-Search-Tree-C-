#include <iostream>
#include "Tree.hpp"
using namespace ariel;

//this method is a constructor.
Tree::Tree()
{
    treeRoot = NULL;
    treeSize = 0;
}

//this method is a distructor.
Tree::~Tree()
{
    deleteTree(treeRoot);
}

//this method recursively deletes all the leaves of the tree.
void Tree::deleteTree(Node *leaf)
{
    if (leaf != NULL)
    {
        deleteTree(leaf->left);
        deleteTree(leaf->right);
        delete leaf;
    }
}

//returns the size of the tree.
int Tree::size()
{
    return treeSize;
}

//returns the left leaf of a given key.
int Tree::left(int key)
{
    Node *temp = treeRoot;
    while (temp != NULL)
    {
        if (key < temp->value)     //goes left.
        {
            temp = temp->left;
        }
        else if (key > temp->value)   //goes right.
        {
            temp = temp->right;
        }
        else    //key equals to temp's value.
        {
            if (temp->left != NULL) //if temp has a left child.
            {
                return temp->left->value;
            }
            else //there is no left child for this key.
            {
                throw std::invalid_argument("there is no left leaf to this node.");
            }
        }
    } 
    // key wasn't found in the tree.
    throw std::invalid_argument("the node doesn't exist");
}


//returns the left leaf of a given key.
int Tree::right(int key)
{
    Node *temp = treeRoot;
    while (temp != NULL)
    {
        if (key < temp->value)   //goes left.
        {
            temp = temp->left;
        }
        else if (key > temp->value)    //goes right.
        {
            temp = temp->right;
        }
        else     //key equals to temp's value.
        {
            if (temp->right != NULL)   //if temp has a right child.
            {
                return temp->right->value;
            }
            else    //there is no right child for this key.
            {
                throw std::invalid_argument("there is no right leaf to this node.");
            }
        }
    }
    // key wasn't found in the tree.
    throw std::invalid_argument("the node doesn't exist");
}

//inserts a new node to the tree, only if the value of the node is not in the tree already.
void Tree::insert(int key)
{
    //if the tree is empty, adds the value as the root.
    if (treeRoot == NULL)
    {
        treeRoot = new Node;
        treeRoot->value = key;
        treeRoot->left = NULL;
        treeRoot->right = NULL;
        treeRoot->parent = NULL;
        treeSize++;
    }
    else //tree isn't empty
    {
        Node *temp = treeRoot;
        Node *prev = temp->parent;
        while (temp != NULL)
        {
            if (key < temp->value) 
            {
                if (temp->left == NULL) /* if 'temp' has no left child , creates a new node with the value of
                                          'key' to be it's left child */
                {
                    temp->left = new Node;
                    prev = temp;
                    temp = temp->left;
                    temp->value = key;
                    temp->left = NULL;
                    temp->right = NULL;
                    temp->parent = prev;
                    treeSize++;
                    break;
                }
                else //has a left child, goes left.
                {
                    prev = temp;
                    temp = temp->left;
                }
            }
            else if (key > temp->value) 
            {
                if (temp->right == NULL) /* if 'temp' has no right child , creates a new node with the value of
                                          'key' to be it's right child */
                {
                    temp->right = new Node;
                    prev = temp;
                    temp = temp->right;
                    temp->value = key;
                    temp->left = NULL;
                    temp->right = NULL;
                    temp->parent = prev;
                    treeSize++;
                    break;
                }
                else  //has a right child, goes right.
                {
                    prev = temp;
                    temp = temp->right;
                }
            }
            else //key already exists.
            {
                throw std::invalid_argument("the given number is already exists");
            }
        }
    }
}

//return true if the key node exists in the tree ,false otherwise.
bool Tree::contains(int key)
{
    if (treeRoot == NULL) //tree is empty
    {
        return false;
    }
    Node *temp = treeRoot;
    while (temp != NULL)
    {
        if (key < temp->value) //goes left.
        {
            temp = temp->left;
        }

        else if (key > temp->value) //goes right.
        {
            temp = temp->right;
        }
        else //found the key.
        {
            return true;
        }
    }
    //key isn't in the tree.
    return false;
}

//returns the root's value of the tree.
int Tree ::root()
{
    if (treeRoot != NULL) //tree isn't empty
    {
        return treeRoot->value;
    }
    else //tree is empty
    {
        throw std::invalid_argument("there is no root");
    }
}

//returns the parent of 'key', if he is in the tree.
int Tree::parent(int key)
{
    if (treeRoot->value == key) //'key' is the root ,hence it has no parent.
    {
        throw std::invalid_argument("the node of this key is the root");
    }
    Node *temp = treeRoot;
    while (temp != NULL)
    {
        if (key < temp->value) //goes left.
        {
            temp = temp->left;
        }

        else if (key > temp->value) //goes right.
        {
            temp = temp->right;
        }
        else // key=temp->value
        {
            if (temp->parent != NULL) //in case it isn't the root.
            {
                return temp->parent->value;
            }
        }
    }
    //'key' wasn't found in the tree.
    throw std::invalid_argument("node with this key doesn't exist");
}

//prints the tree in Inorder, calls the recursive function-'printInorder'.
void Tree::print()
{
    printInorder(treeRoot);
}

//recursively prints the tree in Inorder
void Tree::printInorder(Node *leaf)
{
    if (leaf != NULL)
    {
        printInorder(leaf->left);
        std::cout << leaf->value << ", ";
        printInorder(leaf->right);
    }
}

//this method disconnects a node from the tree.
void disconnectNode(Node *leaf)
{
    leaf->parent->right = leaf->left; 
    if (leaf->left != NULL)
    {
        leaf->left->parent = leaf->parent;
    }
    leaf->parent = NULL;
    leaf->left = NULL;
}

//this method removes a node from the tree if it exists.
void Tree::remove(int key)
{
    //if the tree is empty
    if (treeRoot == NULL)
    {
        throw std::invalid_argument("the tree is empty.");
    }
    /* the key is root */
    else if (treeRoot->value == key)
    {
        //if the root has left leaves.
        if (treeRoot->left != NULL)
        {
            Node *biggest = searchBiggestNode(treeRoot->left); //searches for the greatest value in it's left sub-tree.
            swapValue(biggest, treeRoot); 
            disconnectNode(biggest); 
            delete biggest;
            treeSize--;
        }
        //if the root has only right leaves.
        else if (treeRoot->right != NULL)
        {
            Node *temp = treeRoot;
            treeRoot->right->parent = NULL; //disconnects the right child from the root
            treeRoot = temp->right; //the right child is the new root
            temp->right = NULL; //disconnects the root from the right child.
            delete temp;
            treeSize--;
        }
        else //the root is the only node in the tree.
        {
            treeRoot->value = NULL;
            treeSize--;
        }
    }

    /*'key' is not the root */
    else
    {
        Node *temp = searchNode(key, treeRoot); //finds the node that matches the key.
        if (temp == NULL) //the key doesn't exist.
        {
            throw std::invalid_argument("node doesn't exist.");
        }
        else
        {
            if (temp->left != NULL) //has left leaves.
            {
                Node *maxLeft = searchBiggestNode(temp->left); //searches for the greatest value in it's left sub-tree.
                swapValue(maxLeft, temp);
                disconnectNode(maxLeft);
                delete maxLeft;
                treeSize--;
            }

            else if (temp->right != NULL) //has only right leaves.
            {
                temp->right->parent = temp->parent;
                if (temp->parent->right == temp) //if 'temp' is a right leaf.
                {
                    temp->parent->right = temp->right;
                }
                else // if 'temp' is a left leaf.
                {
                    temp->parent->left = temp->right;
                }
                temp->right = NULL;
                temp->parent = NULL;
                delete temp;
                treeSize--;
            }
            else  //'temp' is a leaf.
            {
                //if 'temp' is a right leaf.
                if (temp->parent->right == temp)
                {
                    temp->parent->right = NULL;
                }
                else //if 'temp' is a left leaf.
                {
                    temp->parent->left = NULL;
                }
                temp->parent = NULL;
                delete temp;
                treeSize--;
            }
        }
    }
}

//this methods swaps only the values of two given nodes.
void Tree::swapValue(Node *a, Node *b)
{
    int temp = a->value;
    a->value = b->value;
    b->value = temp;
}

//this method returns the node that it's value matches 'key' from a given leaf.
Node *Tree::searchNode(int key, Node *leaf)
{

    if (leaf == NULL)
    {
        return NULL;
    }
    Node *temp = leaf;
    while (temp != NULL)
    {
        if (key < temp->value) //goes left.
        {
            temp = temp->left;
        }
        else if (key > temp->value) //goes right.
        {
            temp = temp->right;
        }
        else //found the node.
        {
            return temp;
        }
    }
    //'key' doesn't exist in the tree.
    return NULL;
}

//from a given node, this method returns the greatest value of all leaves in it's sub-tree.
Node *Tree::searchBiggestNode(Node *leaf)
{

    Node *max = leaf;
    Node *temp = leaf->right;
    while (temp != NULL)  //while temp has right leaves.
    {
        max = temp;
        temp = temp->right;
    }
    return max;
}
