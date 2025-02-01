// Zachary Colby
// Student ID: 002440344
// Chapman email: zcolby@chapman.edu
// Course number and section: CPSC 350, Section 01
// Assignment or exercise number: PA5

// This class was created in class!! So technically not my own code, but still what I wrote down

#ifndef TREENODE_H
#define TREENODE_H

#include <string>
#include <cstdlib>
using namespace std;

template <typename T>
class TreeNode{
    public:
        TreeNode(T data);
        virtual ~TreeNode();
        T getData();

// Gives direct access to these member variables, instead of making them public (or as using accessors or mutators)
// And template works with S, S or T is just a parameter, is changeable
template <typename S>
friend class BST;
        T m_data;
        TreeNode<T>* m_left;
        TreeNode<T>* m_right; 
};

template <typename T>
TreeNode<T>::TreeNode(T data){
    m_data = data;
    m_left = NULL;
    m_right = NULL;
}

template <typename T>
TreeNode<T>::~TreeNode(){
    if(m_left != NULL){
        delete m_left;
    }
    if(m_right != NULL){
        delete m_right;
    }
}

template <typename T>
T TreeNode<T>::getData(){
    return m_data;
}

#endif