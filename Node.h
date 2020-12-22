#pragma once
#include "Tree.h"

template <typename T>
class Tree;

/** Node class, each example contains:
/* T data - some value to contain
/* *parent - pointer to parent Node
/* *left - pointer to left brunch Node (value in left Node is smaller than one, contained in current Node)
/* *right - pointer to right  brunch Node (value in left Node is bigger or equal than one, contained in current Node)*/

template <typename T>
class Node
{
public:
    friend Tree<T>;
    Node(T data, Node<T>* parent = nullptr, Node<T>* left = nullptr, Node<T>* right = nullptr);
private:
    T data;
    Node<T>* parent;
    Node<T>* right;
    Node<T>* left;
};

template <typename T>
Node<T>::Node(T data, Node<T>* parent, Node<T>* left , Node<T>* right) : data(data), parent(parent), left(left), right(right)
{
}
