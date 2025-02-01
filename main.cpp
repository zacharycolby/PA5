// Zachary Colby
// Student ID: 002440344
// Chapman email: zcolby@chapman.edu
// Course number and section: CPSC 350, Section 01
// Assignment or exercise number: PA5

// Include all the header files
#include "RunScareGame.h"

// Run the main method using command line arguments
int main(int argc, char* argv[]) {
    // Error handling for incorrect command line arguments sent in!
    if (argc != 4) {
        std::cout << "Usage: " << argv[0] << " <input_file> <output_file> <single|double>" << std::endl;
        return 1;
    }

    
    // Set the command line arguments' values to std::strings
    std::string inputFile = argv[1];
    std::string outputFile = argv[2];
    std::string format = argv[3];

    // Create an instance of RunScareGame!
    RunScareGame game;

    // Now run a tournament using the command line arguments!!
    game.runTournament(inputFile, outputFile, format);

    return 0;
}