#pragma once
#include <iostream>
#include "Node.h"
template <typename T>
class Node;
/** Binary sorted tree class
/* Not balanced
/* *root - pointer for root of the tree
/* size - current amount of Nodes in tree*/
template <typename T>
class Tree
{
public:
    /*Basic ctor*/
    Tree();

    /*Returns amount of elements in tree*/
    int GetSize() { return this->size; }

    /*Prints all elements from minimal to maximal*/
    void Print();

    /*Method for insertion new elements*/
    void insert(T data);

    /* Method for deletion members
    /* Takes value as parameter, searches for element, having this value and deletes it/ Method saves tree structure*/
    void del(T data);

    /*Returns value (data) in contained in root Node*/
    T GetRootVal() { return this->root->data; }

    /*Returns minimum value in Tree*/
    T Minimum();

     /*Returns maximum value in Tree*/
    T Maximum();

    /*method finds the Node with the smallest key greater than the key of the input node (successor)
    /* input Node key - is the parameter of method.*/
    T SuccessorVal(T data);

    /* perform left turn around root node*/
    void LeftRootTurn ();

    /* perform right turn around root node*/
    void RightRootTurn ();
private:
    Node<T>* root;      // ROOT-node pointer
    int size;           // Amount of elements in Tree

    /* Service-method:
    /* Returns pointer for brunch in tree, where we can insert value,
    /* Arguments: T data - value to insert,
    /*            Node<T> * node - pointer for Node, from which we starting to search place for insertion*/
    Node<T>* FindWhereToInsert(T data, Node<T>* node);

    /* Service-method for printing values from min to max. Used in Print method
    /* Argument is a pointer on Node from which to start recursive bypath through tree (bypass usually starts from root)*/
    void PrintFrom(Node<T>* node);

    /* Service-method for finding pointer to Node with minimal value
    /* Argument is a pointer on Node from which to start recursive bypath through tree (bypass usually starts from root)*/
    Node<T>* FindMinNode(Node<T>* node);

    /* Service-method for finding pointer to Node with maximum value
    /* Argument is a pointer on Node from which to start recursive bypath through tree (bypass usually starts from root)*/
    Node<T>* FindMaxNode(Node<T>* node);

    /* Service-method for finding pointer to Node with maximum value
    /* Arguments: T data - searching value
    /*            Node<T>* node - is a pointer on Node from which to start recursive bypath through tree (bypass usually starts from root)*/
    Node<T>* FindNodeByValue(T data, Node<T>* node);

    /* Service-method for finding pointer to Node with maximum value
    /* Arguments: T data - value of the Node for which we are searching successor */
    Node<T>* FindSuccessor(T data);
};

template <typename T>
Tree<T>::Tree() : root(nullptr), size(0)
{
}

template<typename T>
void Tree<T>::Print()
{
    if (root == nullptr)
    {
        std::cout << "Tree is empty\n";
        return;
    }
    PrintFrom(root);
}

template<typename T>
Node<T>* Tree<T>::FindWhereToInsert(T data,  Node<T>* node)
{
    if (data < node->data)
    {
        if (node->left == nullptr) return node;
        FindWhereToInsert(data, node->left);
    }
    else
    {
        if (node->right == nullptr) return node;
        FindWhereToInsert(data, node->right);
    }
}

template<typename T>
void Tree<T>::PrintFrom(Node<T>* node)
{
    if (node->left) PrintFrom(node->left);
    std::cout << node->data << ' ';
    if (node->right) PrintFrom(node->right);
}

template<typename T>
Node<T>* Tree<T>::FindMinNode(Node<T>* node)
{
    if (!node->left) return node;
    FindMinNode(node->left);
}

template<typename T>
Node<T>* Tree<T>::FindMaxNode(Node<T>* node)
{
    if (!node->right) return node;
    FindMaxNode(node->right);
}

template<typename T>
Node<T>* Tree<T>::FindNodeByValue(T data, Node<T>* node)
{
    if (data == node->data) return node;
    else if (data < node->data)
    {
        if (!node->left) return nullptr;
        FindNodeByValue(data, node->left);
    }
    else
    {
        if (!node->right)return nullptr;
        FindNodeByValue(data, node->right);
    }
}

template<typename T>
Node<T>* Tree<T>::FindSuccessor(T data)
{
    Node<T>* current = FindNodeByValue(data, root);
    if (current->right) return FindMinNode(current->right);
    else
    {
        while (true)
        {
            if (current->parent->left == current) return current->parent;
            else current = current->parent;
        }
    }
}

template<typename T>
void Tree<T>::insert(T data)
{
    if (!root) root = new Node<T>(data);
    else
    {
        Node<T>* current = FindWhereToInsert(data, root);
        if (data < current->data) current->left = new Node<T>(data, current);
        else current->right = new Node<T>(data, current);
    }
    ++size;
}

template<typename T>
void Tree<T>::del(T data)
{
    Node<T>* current = FindNodeByValue(data, root);
    if (current == root)
    {
        if (current->right && current->left)
        {
            Node<T>* temp = FindMinNode(current->right);
            current->left->parent = temp;
            temp->left = current->left;
            root = current->right;

        }
        else if (current->right)
        {
            current->right->parent = nullptr;
            root = current->right;
        }
        else if (current->left)
        {
            current->left->parent = nullptr;
            root = current->left;
        }
        else
        {
            current->data = 0;
        }
        delete current;
        --size;
        return;
    }
    if (!current) return;
    if (!current->left && !current->right)      //если лист
    {
        if (current->data < current->parent->data) current->parent->left = nullptr;
        else current->parent->right = nullptr;
        delete current;
    }
    else if (!current->left)                    //если нет левого поддерева
    {
        if (current->data < current->parent->data)
        {
            current->parent->left = current->right;
            current->right->parent = current->parent;
        }
        else
        {
            current->parent->right = current->right;
            current->right->parent = current->parent;
        }
        delete current;
    }
    else if (!current->right)                   //если нет правого поддерева
    {
        if (current->data < current->parent->data)
        {
            current->parent->left = current->left;
            current->left->parent = current->parent;
        }
        else
        {
            current->parent->right = current->left;
            current->right->parent = current->parent;
        }
        delete current;
    }
    else                //если есть оба поддерева
    {
        Node<T>* successor = FindMinNode(current->right);
        if (current->data < current->parent->data) current->parent->left = successor;
        else current->parent->right = successor;
        successor->parent = current->parent;
        successor->left = current->left;
        if (current->right != successor) successor->parent->left = nullptr;
        delete current;
    }
    --size;
}

template<typename T>
T Tree<T>::Minimum()
{
    return FindMinNode(root)->data;
}

template<typename T>
T Tree<T>::Maximum()
{
    return FindMaxNode(root)->data;
}

template<typename T>
T Tree<T>::SuccessorVal(T data)
{
    return FindSuccessor(data)->data;
}

template<typename T>
void Tree<T>::LeftRootTurn ()
{
    if (root->right)
    {
        Node<T> * NewRoot = root->right;
        root->right = NewRoot->left;
        NewRoot->left = root;
        root = NewRoot;
    }
}

template<typename T>
void Tree<T>::RightRootTurn ()
{
    if (root->left)
    {
        Node<T> * NewRoot = root->left;
        root->left = NewRoot->right;
        NewRoot->right = root;
        root = NewRoot;
    }
}
