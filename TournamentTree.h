// Zachary Colby
// Student ID: 002440344
// Chapman email: zcolby@chapman.edu
// Course number and section: CPSC 350, Section 01
// Assignment or exercise number: PA5

#ifndef TOURNAMENTTREE_H
#define TOURNAMENTTREE_H

#include "TournamentNode.h"
#include <iostream>
#include <fstream>
// For searching and removing from a vector
#include <algorithm>


// Define member variables and methods
template <typename T>
class TournamentTree {
    public:
        TournamentTree();
        ~TournamentTree();
        TournamentNode<T>* root;

        void runSingleElimination(std::vector<T>& monsterList, const std::string& filename);
        void runDoubleElimination(std::vector<T>& monsterList, const std::string& filename);
        // This is defined in a different class, keep here for reference
        void saveTreeAsDot(const std::string& filename, TournamentNode<T>* rootNode) const;
        void saveTreeAsDotHelper(TournamentNode<T>* node, std::ofstream& file, int& nodeID) const ;
        //void createNodes();
        void createNodes(std::vector<TournamentNode<T>*>& roundNodes);
        void deleteTree(TournamentNode<T>* node);
};

// Define Constructor
template <typename T>
TournamentTree<T>::TournamentTree() {
    root = nullptr;
}

// Define Destructor
template <typename T>
TournamentTree<T>::~TournamentTree() {
    deleteTree(root);
}

// This class is for single elimation tournament logic, which will be used in double elimination
template <typename T>
void TournamentTree<T>::runSingleElimination(std::vector<T>& monsterList, const std::string& filename) {
    // Given a vector of Monsters, create a vector of tournament nodes to make a tree
    // Also given a file to use for outputting the DOT file!

    // Error handling in case the vector is empty
    if (monsterList.empty()) {
        return;
    }

    // Create a vector to store TournamentNodes
    std::vector<TournamentNode<T>*> startingNodes;
    // Iterate through the Monster vector to create the initial nodes
    for (int i = 0; i < monsterList.size(); ++i) {
        TournamentNode<T>* round1 = new TournamentNode<T>(&monsterList[i]);
        startingNodes.push_back(round1);
        //cout << monsterList[i].getName() << endl;
    }

    // Now that the first nodes are created, create the rest of the tree using the createNodes method
    createNodes(startingNodes);

    // Now output the completed tournament as a DOT file using the given method!
    saveTreeAsDot(filename, root);

}

// This class is for double eliminations
template <typename T>
void TournamentTree<T>::runDoubleElimination(std::vector<T>& monsterList, const std::string& filename) {
    // Logic is similar to single elimination, however it runs two tournaments
    // So it utilizes runSingleElimination for the loser's bracket

    // First, run a single elimination tournament. Because some things change, I only use it for the second
    //      

    // Error handling in case the vector is empty
    if (monsterList.empty()) {
        return;
    }

    // Create a vector to store TournamentNodes
    std::vector<TournamentNode<T>*> startingNodes;
    // Iterate through the Monster vector to create the initial nodes
    for (int i = 0; i < monsterList.size(); ++i) {
        TournamentNode<T>* round1 = new TournamentNode<T>(&monsterList[i]);
        startingNodes.push_back(round1);
    }

    // Now that the first nodes are created, create the rest of the tree using the createNodes method
    createNodes(startingNodes);

    // Preserve the root and the tree of the original bracket for later use
    TournamentNode<T>* winnerTree = root;

    // Copy the vector from input into a new vector so we can remove the winner
    std::vector<T> loserList;

    // Now REMOVE THAT SUCKER
    for (const auto& monster : monsterList) { // Use the correct type for the loop variable
        if (monster.getName() != winnerTree->winner->getName()) { // Compare the correct member
            loserList.push_back(monster); // Push back the correct type
        }
    }

    // Now, run the losers' tournament
    runSingleElimination(loserList, filename);

    // Preserve the loser tree and root
    TournamentNode<T>* loserTree = root;

    // NOW THEY FIGHT
    TournamentNode<T>* absoluteWinner = new TournamentNode<T>((winnerTree->winner < loserTree->winner) ? winnerTree->winner : loserTree->winner);

    // Assign the competing trees to left and right children
    absoluteWinner->left = winnerTree;
    absoluteWinner->right = loserTree;

    // Save the created tree as a DOT file!
    saveTreeAsDot(filename, absoluteWinner);

}

// Function to save the tree as a DOT file, as given in assignment specs
template <typename T>
void TournamentTree<T>::saveTreeAsDot(const std::string& filename, TournamentNode<T>* rootNode) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for DOT output: " << filename << "\n";
        return;
    }

    file << "digraph TournamentTree {\n";
    int nodeID = 0;
    saveTreeAsDotHelper(rootNode, file, nodeID);
    file << "}\n";
    file.close();
}

// Recursive helper function for DOT file generation, also given in assignment specs
template <typename T>
void TournamentTree<T>::saveTreeAsDotHelper(TournamentNode<T>* node, std::ofstream& file, int& nodeID) const {
    if (node == NULL) return;

    int currentID = nodeID++;
    file << "    node" << currentID << " [label=\"" << node->winner->getName()
         << " (Power: " << node->winner->getLevel() << ")\"];\n";

    if (node->left) {
        int leftID = nodeID;
        saveTreeAsDotHelper(node->left, file, nodeID);
        file << "    node" << currentID << " -> node" << leftID << ";\n";
    }

    if (node->right) {
        int rightID = nodeID;
        saveTreeAsDotHelper(node->right, file, nodeID);
        file << "    node" << currentID << " -> node" << rightID << ";\n";
    }
};

// This class creates the nodes of the tree for the tournament using recursion
template <typename T>
void TournamentTree<T>::createNodes(std::vector<TournamentNode<T>*>& roundNodes) {
    // Create a vector that will be written over for each recursive case
    std::vector<TournamentNode<T>*> nodeHolder;

    // Loop through the vector of tournament nodes, adding the winners of each match to make a tree!
    for (size_t i = 0; i < roundNodes.size(); i+=2) {

        // Make sure there an even amount of competitors
        // This if statement will only run if there is an odd amount, and will correct it
        if (roundNodes.size() % 2 != 0) {
            TournamentNode<T>* monsterBy = roundNodes.back();
            roundNodes.pop_back(); // Remove the promoted node from the current round
            nodeHolder.push_back(monsterBy);
        }
        // Compare i and i+1, and find the winner

        // Help here from Microsoft Copilot with simplifying my code of if statement for setting the winner
        T* roundWinner = (roundNodes[i]->winner < roundNodes[i + 1]->winner) ? roundNodes[i]->winner : roundNodes[i+1]->winner;
        // End help
            
        // Create a node for the winner, then attach the competitors as its left and right children
        TournamentNode<T>* match = new TournamentNode<T>(roundWinner);
        match->left = roundNodes[i];
        match->right = roundNodes[i + 1];
        // Add it to the vector to recursively use the method again!
        nodeHolder.push_back(match);
        
    }

    // Handling if there is only one node left, the winner of the tournament
    if (nodeHolder.size() == 1) {
        root = nodeHolder.front();
    } else {
        // Otherwise, use recursion to go to the next round
        createNodes(nodeHolder);
    }

}

// This class recursively goes through and deletes the entire tree
// Help from ChatGPT in understanding logic of removing a tree without skipping nodes
template <typename T>
void TournamentTree<T>::deleteTree(TournamentNode<T>* node) {
    // Error handling if a node is null
    if (node == nullptr) {
        return;
    }
    // Recursion to delete both children (and further) of the tree
    deleteTree(node->left);
    deleteTree(node->right);
    // Once the children are deleted, then the node can be too!
    delete node;
}

#endif