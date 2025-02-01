// Zachary Colby
// Student ID: 002440344
// Chapman email: zcolby@chapman.edu
// Course number and section: CPSC 350, Section 01
// Assignment or exercise number: PA5

#ifndef TOURNAMENTNODE_H
#define TOURNAMENTNODE_H

#include "Monster.h"
#include <vector>
#include <string>

// Declare member variables!
template <typename T>
class TournamentNode {
    public:
        T* winner;
        TournamentNode* left;
        TournamentNode* right;
        TournamentNode(T* w);
};

// Define Constructor
template <typename T>
TournamentNode<T>::TournamentNode(T* w) {
    winner = w;
    left = nullptr;
    right = nullptr;

}

#endif