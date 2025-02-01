// Zachary Colby
// Student ID: 002440344
// Chapman email: zcolby@chapman.edu
// Course number and section: CPSC 350, Section 01
// Assignment or exercise number: PA5

#ifndef MONSTER_H
#define MONSTER_H

#include "TreeNode.h"
#include <sstream>
#include <ostream>
#include <iostream>

// Declare member variables
class Monster {
    public:
        Monster();
        Monster(string name, int power);
        ~Monster();
        bool operator<(const Monster& other) const;
        bool operator>(const Monster& other) const;
        void printValues();
        string getName() const;
        int getLevel() const;
    private:
        std::string monsterName;
        int powerLevel;
};

// Define Default Constructor
// Purely for standard, not utilized in code
Monster::Monster() {
    monsterName = "basicBob";
    powerLevel = 50;
}

// Define Constructor
Monster::Monster(std::string name, int power) {
    monsterName = name;
    powerLevel = power;
}

// Include Destructor as well
Monster::~Monster() {
}

// Define Comparison Operators

// Operator if first monster is less than:
bool Monster::operator<(const Monster& other) const {
    return powerLevel < other.powerLevel;
}

// Operator for opposite, first is greater than
bool Monster::operator>(const Monster& other) const {
    return powerLevel > other.powerLevel;
}

// Define method for printing Monster values as seen in input
void Monster::printValues() {
    cout << monsterName << ", " << powerLevel << endl;
}

// Define method for accessing monster names
string Monster::getName() const {
    return monsterName;
}

// Define method for accessing monster power levels
int Monster::getLevel() const {
    return powerLevel;
}

#endif