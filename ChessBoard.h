// ChessBoard.h
// A header file that contains the chess board class
// Elliot Goodwin
// 10/05/2019


#ifndef ChessBoard_h
#define ChessBoard_h

// C++ STL includes
#include <iostream>
#include <iomanip>
#include <vector>
// Custom headers for a game of OO chess
#include "ChessPlayers.h"
#include "ChessPieces.h"
#include "ChessSquare.h"


// Group code in namespace "Chess"
namespace Chess {

	// Define the board class
	class Board
	{
		// Decalre friend functions 
		friend std::ostream & operator<<(std::ostream &os, const Board &b);

	// Private members
	private:
		BoardSquare **square_array; // Array of pointers to board squares 
		char *coords;               // Array of letter coordinates 
		int rows, columns;          // Number of rows and columns (in practise the same, but make code more readable)
		Player *player1, *player2;  // Pointers to player base class
		// Number of pieces on the board
		int number_NP;
		int number_WP, number_WC, number_WN, number_WB, number_WQ, number_WK;
		int number_BP, number_BC, number_BN, number_BB, number_BQ, number_BK;

	// Public members
	public:
		Board();                       // Default constructor
		Board(std::string s);          // Parameterised constructors
		Board::Board(Player *p1, Player *p2);  
		Board(Board&);                 // Copy constructor
		Board(Board&&);                // Move constructor
		Board& operator= (Board&);     // Copy Assignment operator
		Board& operator= (Board&&);    // Move Assignment operator
		~Board();                      // Destructor

		// Access functions

		// Bools that use dx, dy to categorise spatial directions on the board
		bool isDiagonal(int i, int j, int m, int n);
		bool isVertical(int i, int j, int m, int n);
		bool isForward(int i, int j, int m, int n);
		bool isBackward(int i, int j, int m, int n);
		bool isHorizontal(int i, int j, int m, int n);
		bool isLshaped(int i, int j, int m, int n);
		bool is1square(int i, int j, int m, int n);
		bool is2square(int i, int j, int m, int n);

		// Get index of a coordinate e.g (E, 4) in piece_array
		int index(char a, int n) const;
		// Overloaded index function for use with two integer inputs
		int index(int m, int n) const;

		// Gets a string that identifies a player on the board
		Player &getPlayer1();
		Player &getPlayer2();

		// Returnsthe size of the board
		int &getBoardSize() { return rows; }
		
		// Gets the type of piece on a square
		char &getPiece(int m, int n);
		// Get the colour of the team occupying a square
		std::string &getColour(int m, int n);
		// Set null piece at square (m, n)
		void setNullPiece(int m, int n);
		// Move a piece on board
		void MovePiece(int i, int j, int m, int n);
		// Overloaded to accept coordinate input e.g (E, 4)
		void MovePiece(char a, int m, char b, int n);

		// Piece decrementers
		void decrementWP();
		void decrementWC();
		void decrementWN();
		void decrementWB();
		void decrementWQ();
		void decrementWK();

		void decrementBP();
		void decrementBC();
		void decrementBN();
		void decrementBB();
		void decrementBQ();
		void decrementBK();

		// Acces to number of kings on board
		int &get_numberWK();
		int &get_numberBK();

	};
}
#endif
