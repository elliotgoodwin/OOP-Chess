// ChessSquare.h
// A header file that contains the chess square class
// Elliot Goodwin
// 10/05/2019

// Chess includes
#include "ChessPieces.h"

#ifndef ChessSquare_h
#define ChessSquare_h

// Group code in namespace "Chess"
namespace Chess {

	// Define BoardSquae class
	class BoardSquare
	{
	// private members
	private:
		Piece *square_piece;  // Pointer to piece occupying square
		std::string colour;   // Strig identifying colour of piece occupying square

	public:
		// Default constructor
		BoardSquare();
		// Parameterised constructors
		BoardSquare(Piece &p);
		BoardSquare(Piece &p, std::string c);

		// Move and copy constructors and assignment operators
		BoardSquare(BoardSquare&);
		BoardSquare(BoardSquare&&);
		BoardSquare& operator=(BoardSquare&);
		BoardSquare& operator=(BoardSquare&&);

		// Destructor
		~BoardSquare();

		// Access functions
		Piece &getSquarePiece();        // Get the piece occupying square
		std::string &getSquareColour(); // Get the colour of the piece occupying square
		void Show();                    // Show the contents of square (to print to board)
	};

}


#endif /* ChessBoardSquare_h */
