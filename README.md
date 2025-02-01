# PA5 - Scare_Games

Course: CPSC 350 - Data Structures and Algorithms

Sources: 

    -  Dr. Stevens, for DOT file generation
    -  For understanding overloaded comparison operators: https://en.cppreference.com/w/cpp/language/operator_comparison
    -  For a couple instances, mentioned specifically inside the code when: Microsoft Copilot and ChatGPT
    -  For extra help with debugging: Microsoft Copilot and ChatGPT

Class Overview

 - TreeNode.h
   
       - Header implementation file for the usage of TreeNodes in binary trees

 - Monster.h
   
       - Header file that defines the Monster class
       - Utilizes inheritance of TreeNode.h
       - Defines comparison operators for the class

 - TournamentNode.h
   
       - Header file that defines the TournamentNode class
       - Utilizes inheritance of Monster.h
       - Defines nodes for usage in TournamentTree.h

 - TournamentTree.h
   
       - Header file that defines the TournamentTree class
       - Utilizes inheritance of TournamentNode.h to create a full binary tree for the tournament
       - Includes code for both single and double elimination tournaments
       - Uses recursion to prevent redundant code within the double elimination
       - Allows for the tournament to be exported as a DOT file

 - RunScareGame.h
   
       - Header file that defines the RunScareGame class
       - Utilizes the inheritance of TournamentTree.h to run a complete tournament
       - Holds the primary function of the program; only need to create an instance and call it

 - main.cpp
   
       - .cpp file that inherits each of the header files
       - Creates an instance of the RunScareGame class to use its methods
       - Takes command-line arguments to run the program
       - Includes error handling in case of incompatible command-line arguments
