// Zachary Colby
// Student ID: 002440344
// Chapman email: zcolby@chapman.edu
// Course number and section: CPSC 350, Section 01
// Assignment or exercise number: PA5

#ifndef RUNSCAREGAME_H
#define RUNSCAREGAME_H

#include "TournamentTree.h"
// #include <iostream>
// #include <fstream>

// Define member variables
class RunScareGame {
    public:
        void runTournament(const std::string& inputFile, const std::string& outputFile, const std::string& tournamentType);
    private:
        string line;
        std::vector<Monster> allMonsters;
};

// Define the class that runs a tournament
void RunScareGame::runTournament(const std::string& inputFile, const std::string& outputFile, const std::string& tournamentType) {
    // Help from Microsoft Copilot here - Asked about reading lines, then reading in each line
    // First, define values to help with iterating the file lines
    std::ifstream file(inputFile);
    std::string line;
    // Now define the delimiter to separate the Monster names from the power levels
    string delimiter = ", ";

    // Now iterate through the file lines
    while (std::getline(file, line)) {
        // BEGIN CODE FROM OUTSIDE SOURCE: Microsoft Copilot - I asked how to separate values from a line for multiple lines
        size_t pos = line.find(delimiter);
        if (pos != std::string::npos) {
            std::string name = line.substr(0, pos);
            int powerLevel = std::stoi(line.substr(pos + delimiter.length()));
            // END CODE FROM OUTSIDE SOURCE: Microsoft Copilot

            // Create an instance of a monster using the values
            Monster monst = Monster(name, powerLevel);
            // Add the monster to the vector
            allMonsters.push_back(monst);
        }
    }
    // With a vector of all monsters, I can use it to call TournamentTree and make the tournament!

    // Create an instance of TournamentTree
    TournamentTree<Monster> scareGame;

    // Depending on command line argument depends on the type, so see if it is single or double
    if (tournamentType == "single") {
        // Run a single elimination tournament
        scareGame.runSingleElimination(allMonsters, outputFile);

        // Delete the tree afterwards!
        scareGame.~TournamentTree();

    } else if (tournamentType == "double") {
        // Run a double elimination tournament!
        scareGame.runDoubleElimination(allMonsters, outputFile);

        // Delete the tree afterwards!
        scareGame.~TournamentTree();

    } else {
        cout << "Please enter 'single' or 'double'" << endl;
    }

}

#endif