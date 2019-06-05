// ChessSquare.cpp
// A .cpp file that contains the chess square class
// Elliot Goodwin - 9621958
// 10/05/2019

// Chess includes
#include "ChessSquare.h"

// Group code in namespace "Chess"
namespace Chess {

	// BoardSquare
	BoardSquare::BoardSquare() { square_piece = new NullPiece(); }
	BoardSquare::BoardSquare(Piece &p){ square_piece = &p; }
	BoardSquare::BoardSquare(Piece &p, std::string c){ square_piece = &p; colour = c; }

	// Copy constructor
	BoardSquare::BoardSquare(BoardSquare &sq)
	{
		std::cout << "Calling BoardSquare copy constructor." << std::endl;
		square_piece = 0; colour = "null_string";

		square_piece = sq.square_piece;
		colour = sq.colour;
	}

	// Move constructor
	BoardSquare::BoardSquare(BoardSquare &&sq)
	{
		std::cout << "Calling BoardSquare move constructor." << std::endl;
		square_piece = sq.square_piece; square_piece = nullptr;
		colour = sq.colour;             colour = "null_string";
	}

	// Copy assignment operator
	BoardSquare &BoardSquare::operator=(BoardSquare &sq)
	{
		std::cout << "Calling BoardSquare copy assignment operator." << std::endl;

		if (&sq == this) { return *this; }

		square_piece = nullptr; colour = "null_string";

		square_piece = sq.square_piece;

		return *this;
	}

	// Move assignment operator
	BoardSquare &BoardSquare::operator=(BoardSquare &&sq)
	{
		std::cout << "Calling BoardSquare move assignment operator." << std::endl;
		// swap contents of one board with another
		std::swap(colour, sq.colour);
		std::swap(square_piece, sq.square_piece);

		return *this;
	}

	// Destructor
	BoardSquare::~BoardSquare()
	{
		std::cout << "Destroying BoardSquare." << std::endl;
		square_piece = nullptr;
		colour = "null_string";
	};

	// Access functions
	Piece &BoardSquare::getSquarePiece() { return *square_piece; }
	std::string &BoardSquare::getSquareColour() { return colour; }

	// Show contents of board square
	void BoardSquare::Show() {
		if (colour == "white" || colour == "White") {
			std::cout << "W";
		}
		if (colour == "black" || colour == "Black") {
			std::cout << "B";
		}
		square_piece->Show();
	}

}

