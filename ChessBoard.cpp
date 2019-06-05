// ChessBoard.cpp
// A .cpp file that contains the chess board
// Elliot Goodwin
// 10/05/2019

// C++ STL includes
#include <iostream>
#include <iomanip>
#include <sstream>
// Chess header files
#include "ChessPlayers.h"
#include "ChessPieces.h"
#include "ChessSquare.h"
#include "ChessBoard.h"

namespace Chess {

	// Default constructor
	Board::Board()  // Default constructor
	{
		//std::cout << "Board constructor called." << std::endl;
		const int N = 8; // Set board dimension

		// Initialise character board coordinates
		coords = new char[N];
		coords[0] = 'A'; coords[1] = 'B'; coords[2] = 'C'; coords[3] = 'D';
		coords[4] = 'E'; coords[5] = 'F'; coords[6] = 'G'; coords[7] = 'H';

		// Initialise array of BoardSquares
		rows = N; columns = N;
		square_array = new BoardSquare*[rows*columns];

		// Set players
		std::string colour1 = "white";
		player1 = new Human(colour1);
		std::string colour2 = "black";
		player2 = new Human(colour2);

		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				square_array[index(i, j)] = new BoardSquare();
			}
		}
	}

	// Parameterised constructor
	Board::Board(std::string s)
	{
		//std::cout << "Board constructor called." << std::endl;

		// Set board dimension
		const int N = 8;

		// Initialise letter coordinates
		coords = new char[N];
		coords[0] = 'A'; coords[1] = 'B'; coords[2] = 'C'; coords[3] = 'D';
		coords[4] = 'E'; coords[5] = 'F'; coords[6] = 'G'; coords[7] = 'H';

		// Initialise array of BoardSquares
		rows = N; columns = N;
		square_array = new BoardSquare*[rows*columns];

		// Set player1
		std::string colour1 = "white";
		player1 = new Human(colour1);

		// Set up pawns
		for (int i = 1; i <= N; i++) {
			square_array[index(i, 7)] = new BoardSquare(player1->getPlayerPiece(i - 1), player1->getPlayerColour());
			number_WP++;
		}

		// Set bottom row
		square_array[index(1, 8)] = new BoardSquare(player1->getPlayerPiece(8), player1->getPlayerColour());
		number_WC++;
		square_array[index(2, 8)] = new BoardSquare(player1->getPlayerPiece(9), player1->getPlayerColour());
		number_WN++;
		square_array[index(3, 8)] = new BoardSquare(player1->getPlayerPiece(10), player1->getPlayerColour());
		number_WB++;
		square_array[index(4, 8)] = new BoardSquare(player1->getPlayerPiece(11), player1->getPlayerColour());
		number_WQ++;
		square_array[index(5, 8)] = new BoardSquare(player1->getPlayerPiece(12), player1->getPlayerColour());
		number_WK++;
		square_array[index(6, 8)] = new BoardSquare(player1->getPlayerPiece(13), player1->getPlayerColour());
		number_WB++;
		square_array[index(7, 8)] = new BoardSquare(player1->getPlayerPiece(14), player1->getPlayerColour());
		number_WN++;
		square_array[index(8, 8)] = new BoardSquare(player1->getPlayerPiece(15), player1->getPlayerColour());
		number_WC++;

		// Set empty rows
		for (int i = 1; i <= N; i++) {
			for (int j = 2; j <= N - 2; j++) {
				square_array[index(i, j)] = new BoardSquare();
				number_NP++;
			}
		}

		// Set player2
		std::string colour2 = "black";
		player2 = new Computer(colour2);

		// Set up pawns
		for (int i = 1; i <= N; i++) {
			square_array[index(i, 2)] = new BoardSquare(player2->getPlayerPiece(i - 1), player2->getPlayerColour());
			number_BP++;
		}

		// Set top row
		square_array[index(1, 1)] = new BoardSquare(player2->getPlayerPiece(8), player2->getPlayerColour());
		number_BC++;
		square_array[index(2, 1)] = new BoardSquare(player2->getPlayerPiece(9), player2->getPlayerColour());
		number_BN++;
		square_array[index(3, 1)] = new BoardSquare(player2->getPlayerPiece(10), player2->getPlayerColour());
		number_BB++;
		square_array[index(4, 1)] = new BoardSquare(player2->getPlayerPiece(11), player2->getPlayerColour());
		number_BQ++;
		square_array[index(5, 1)] = new BoardSquare(player2->getPlayerPiece(12), player2->getPlayerColour());
		number_BK++;
		square_array[index(6, 1)] = new BoardSquare(player2->getPlayerPiece(13), player2->getPlayerColour());
		number_BB++;
		square_array[index(7, 1)] = new BoardSquare(player2->getPlayerPiece(14), player2->getPlayerColour());
		number_BN++;
		square_array[index(8, 1)] = new BoardSquare(player2->getPlayerPiece(15), player2->getPlayerColour());
		number_BC++;

	}

	// Parameterised constructor
	Board::Board(Player *p1, Player *p2)
	{
		//std::cout << "Board constructor called." << std::endl;

		// Set board dimension
		const int N = 8;

		// Initialise letter coordinates
		coords = new char[N];
		coords[0] = 'A'; coords[1] = 'B'; coords[2] = 'C'; coords[3] = 'D';
		coords[4] = 'E'; coords[5] = 'F'; coords[6] = 'G'; coords[7] = 'H';

		// Initialise array of BoardSquares
		rows = N; columns = N;
		square_array = new BoardSquare*[rows*columns];

		// Initialise players
		player1 = p1;
		player2 = p2;

		// Set empty rows
		for (int i = 1; i <= N; i++) {
			for (int j = 2; j <= N - 2; j++) {
				square_array[index(i, j)] = new BoardSquare();
				number_NP++;
			}
		}

		// Set up player 1
		if (player1->getPlayerColour() == "white" || player1->getPlayerColour() == "White") {
			// Set up pawns
			for (int i = 1; i <= N; i++) {
				square_array[index(i, 7)] = new BoardSquare(player1->getPlayerPiece(i - 1), player1->getPlayerColour());
				number_WP++;
			}

			// Set bottom row
			square_array[index(1, 8)] = new BoardSquare(player1->getPlayerPiece(8), player1->getPlayerColour());
			number_WC++;
			square_array[index(2, 8)] = new BoardSquare(player1->getPlayerPiece(9), player1->getPlayerColour());
			number_WN++;
			square_array[index(3, 8)] = new BoardSquare(player1->getPlayerPiece(10), player1->getPlayerColour());
			number_WB++;
			square_array[index(4, 8)] = new BoardSquare(player1->getPlayerPiece(11), player1->getPlayerColour());
			number_WQ++;
			square_array[index(5, 8)] = new BoardSquare(player1->getPlayerPiece(12), player1->getPlayerColour());
			number_WK++;
			square_array[index(6, 8)] = new BoardSquare(player1->getPlayerPiece(13), player1->getPlayerColour());
			number_WB++;
			square_array[index(7, 8)] = new BoardSquare(player1->getPlayerPiece(14), player1->getPlayerColour());
			number_WN++;
			square_array[index(8, 8)] = new BoardSquare(player1->getPlayerPiece(15), player1->getPlayerColour());
			number_WC++;
		}
		else if (player1->getPlayerColour() == "black" || player1->getPlayerColour() == "Black") {
			// Set up pawns
			for (int i = 1; i <= N; i++) {
				square_array[index(i, 7)] = new BoardSquare(player1->getPlayerPiece(i - 1), player1->getPlayerColour());
				number_BP++;
			}

			// Set bottom row
			square_array[index(1, 8)] = new BoardSquare(player1->getPlayerPiece(8), player1->getPlayerColour());
			number_BC++;
			square_array[index(2, 8)] = new BoardSquare(player1->getPlayerPiece(9), player1->getPlayerColour());
			number_BN++;
			square_array[index(3, 8)] = new BoardSquare(player1->getPlayerPiece(10), player1->getPlayerColour());
			number_BB++;
			square_array[index(4, 8)] = new BoardSquare(player1->getPlayerPiece(11), player1->getPlayerColour());
			number_BQ++;
			square_array[index(5, 8)] = new BoardSquare(player1->getPlayerPiece(12), player1->getPlayerColour());
			number_BK++;
			square_array[index(6, 8)] = new BoardSquare(player1->getPlayerPiece(13), player1->getPlayerColour());
			number_BB++;
			square_array[index(7, 8)] = new BoardSquare(player1->getPlayerPiece(14), player1->getPlayerColour());
			number_BN++;
			square_array[index(8, 8)] = new BoardSquare(player1->getPlayerPiece(15), player1->getPlayerColour());
			number_BC++;
		}
		else { std::cout << "Something went wrong." << std::endl; exit(1); }
		
		// Set up player2
		if (player2->getPlayerColour() == "black" || player2->getPlayerColour() == "Black") {
			// Set up pawns
			for (int i = 1; i <= N; i++) {
				square_array[index(i, 2)] = new BoardSquare(player2->getPlayerPiece(i - 1), player2->getPlayerColour());
				number_BP++;
			}

			// Set top row
			square_array[index(1, 1)] = new BoardSquare(player2->getPlayerPiece(8), player2->getPlayerColour());
			number_BC++;
			square_array[index(2, 1)] = new BoardSquare(player2->getPlayerPiece(9), player2->getPlayerColour());
			number_BN++;
			square_array[index(3, 1)] = new BoardSquare(player2->getPlayerPiece(10), player2->getPlayerColour());
			number_BB++;
			square_array[index(4, 1)] = new BoardSquare(player2->getPlayerPiece(11), player2->getPlayerColour());
			number_BQ++;
			square_array[index(5, 1)] = new BoardSquare(player2->getPlayerPiece(12), player2->getPlayerColour());
			number_BK++;
			square_array[index(6, 1)] = new BoardSquare(player2->getPlayerPiece(13), player2->getPlayerColour());
			number_BB++;
			square_array[index(7, 1)] = new BoardSquare(player2->getPlayerPiece(14), player2->getPlayerColour());
			number_BN++;
			square_array[index(8, 1)] = new BoardSquare(player2->getPlayerPiece(15), player2->getPlayerColour());
			number_BC++;
		}
		else if (player2->getPlayerColour() == "white" || player2->getPlayerColour() == "White") {
			// Set up pawns
			for (int i = 1; i <= N; i++) {
				square_array[index(i, 2)] = new BoardSquare(player2->getPlayerPiece(i - 1), player2->getPlayerColour());
				number_BP++;
			}

			// Set top row
			square_array[index(1, 1)] = new BoardSquare(player2->getPlayerPiece(8), player2->getPlayerColour());
			number_WC++;
			square_array[index(2, 1)] = new BoardSquare(player2->getPlayerPiece(9), player2->getPlayerColour());
			number_WN++;
			square_array[index(3, 1)] = new BoardSquare(player2->getPlayerPiece(10), player2->getPlayerColour());
			number_WB++;
			square_array[index(4, 1)] = new BoardSquare(player2->getPlayerPiece(11), player2->getPlayerColour());
			number_WQ++;
			square_array[index(5, 1)] = new BoardSquare(player2->getPlayerPiece(12), player2->getPlayerColour());
			number_WK++;
			square_array[index(6, 1)] = new BoardSquare(player2->getPlayerPiece(13), player2->getPlayerColour());
			number_WB++;
			square_array[index(7, 1)] = new BoardSquare(player2->getPlayerPiece(14), player2->getPlayerColour());
			number_WN++;
			square_array[index(8, 1)] = new BoardSquare(player2->getPlayerPiece(15), player2->getPlayerColour());
			number_WC++;
		}
		else { std::cout << "Something went wrong." << std::endl; exit(1); }

	}

	// Board copy constructor
	Board::Board(Board &b)
	{
		//std::cout << "Calling Board copy constructor." << std::endl;
		square_array = 0; rows = columns = 0; player1 = player2 = 0; coords = 0;

		// Copy board members
		rows = b.rows; columns = b.columns; coords = b.coords;
		player1 = b.player1; player2 = b.player2;
		number_NP = b.number_NP;
		number_WP = b.number_WP;  number_WK = b.number_WK;
		number_WC = b.number_WC;  number_WN = b.number_WN;
		number_WB = b.number_WB;  number_WQ = b.number_WQ;
		
		number_BP = b.number_BP;  number_BC = b.number_BC;
		number_BN = b.number_BN;  number_BB = b.number_BB; 
		number_BQ = b.number_BQ;  number_BK = b.number_BK;

		if (rows > 0 && columns > 0) {
			square_array = new BoardSquare*[rows*columns];

			// Copy values into new Board
			for (int i = 1; i <= rows; i++) {
				for (int j = 1; j <= columns; j++){
					square_array[index(i, j)] = b.square_array[index(i, j)];
				}
			}
		}
		else { std::cout << "Error. Cannot copy board with no size." << std::endl; exit(1); }
	}

	// Board move constructor
	Board::Board(Board &&b)
	{
		//std::cout << "Calling Board move constructor." << std::endl;
		rows = b.rows;
		columns = b.columns;
		square_array = b.square_array;
		player1 = b.player1;
		player2 = b.player2;
		number_NP = b.number_NP;
		number_WP = b.number_WP;  number_WK = b.number_WK;
		number_WC = b.number_WC;  number_WN = b.number_WN;
		number_WB = b.number_WB;  number_WQ = b.number_WQ;

		number_BP = b.number_BP;  number_BC = b.number_BC;
		number_BN = b.number_BN;  number_BB = b.number_BB;
		number_BQ = b.number_BQ;  number_BK = b.number_BK;

		b.player1 = nullptr; b.player2 = nullptr;
		b.rows = 0; b.columns = 0;
		b.square_array = nullptr;
	}

	// Board copy assignment operator
	Board &Board::operator=(Board &b)
	{
		//std::cout << "Calling Board assignment operator." << std::endl;
		if (&b == this) { return *this; }

		// Initialise this objects members
		square_array = nullptr; square_array = 0; rows = columns = 0; coords = 0;
		number_NP = 0;
		number_WP = 0;  number_WK = 0;
		number_WC = 0;  number_WN = 0;
		number_WB = 0;  number_WQ = 0;

		number_BP = 0;  number_BC = 0;
		number_BN = 0;  number_BB = 0;
		number_BQ = 0;  number_BK = 0;

		// Copy across other objects members
		rows = b.rows; columns = b.columns;
		number_NP = b.number_NP;
		number_WP = b.number_WP;  number_WK = b.number_WK;
		number_WC = b.number_WC;  number_WN = b.number_WN;
		number_WB = b.number_WB;  number_WQ = b.number_WQ;

		number_BP = b.number_BP;  number_BC = b.number_BC;
		number_BN = b.number_BN;  number_BB = b.number_BB;
		number_BQ = b.number_BQ;  number_BK = b.number_BK;

		if (rows > 0 && columns > 0) {
			square_array = new BoardSquare*[rows*columns];
			for (int i = 1; i <= b.rows; i++) {
				for (int j = 1; j <= b.columns; j++){
					square_array[index(i, j)] = b.square_array[index(i, j)];
				}
			}
		}

		// return this object
		return *this;
	}

	// Board move assignment operator
	Board &Board::operator=(Board &&b)
	{
		//std::cout << "Calling Board move assignment operator." << std::endl;

		// swap contents of one board with another
		std::swap(rows, b.rows);
		std::swap(columns, b.columns);
		std::swap(square_array, b.square_array);
		std::swap(player1, b.player1);
		std::swap(player2, b.player2);

		std::swap(number_NP, b.number_NP);
		std::swap(number_WP, b.number_WP);
		std::swap(number_WC, b.number_WC);
		std::swap(number_WN, b.number_WN);
		std::swap(number_WB, b.number_WB);
		std::swap(number_WQ, b.number_WQ);
		std::swap(number_WK, b.number_WK);

		std::swap(number_BP, b.number_BP);
		std::swap(number_BC, b.number_BC);
		std::swap(number_BN, b.number_BN);
		std::swap(number_BB, b.number_BB);
		std::swap(number_BQ, b.number_BQ);
		std::swap(number_BK, b.number_BK);

		return *this;
	}

	// Board destructor
	Board::~Board() {

		// Delete this objects members
		square_array = nullptr; square_array = 0; rows = columns = 0;

		number_NP = 0;
		number_WP = 0;  number_WK = 0;
		number_WC = 0;  number_WN = 0;
		number_WB = 0;  number_WQ = 0;

		number_BP = 0;  number_BC = 0;
		number_BN = 0;  number_BB = 0;
		number_BQ = 0;  number_BK = 0;

		player1 = nullptr; player2 = nullptr;
		//std::cout << "Board destructor called." << std::endl;
	};

	// Access functions

	// Bools that use dx, dy to categorise spatial directions on the board
	// dx, dy are difference in x and y coordinates, respectively
	bool Board::isDiagonal(int i, int j, int m, int n)
	{
		int dx = std::abs(m - i);
		int dy = std::abs(n - j);

		if (dx == dy) { return true; }
		else { return false; }
	}
	bool Board::isVertical(int i, int j, int m, int n)
	{
		int dx = m - i;
		if (dx == 0) { return true; }
		else { return false; }
	}
	bool Board::isForward(int i, int j, int m, int n)
	{
		int dx = m - i;
		int dy = n - j;
		if (dx == 0 && dy < 0) { return true; }
		else { return false; }
	}
	bool Board::isBackward(int i, int j, int m, int n)
	{
		int dx = m - i;
		int dy = n - j;
		if (dx == 0 && dy > 0) { return true; }
		else { return false; }
	}
	bool Board::isHorizontal(int i, int j, int m, int n)
	{
		int dy = n - j;
		if (dy == 0) { return true; }
		else { return false; }
	}
	bool Board::isLshaped(int i, int j, int m, int n)
	{
		int dx = m - i;
		int dy = n - j;

		if ((dx == 1 || dx == -1) && (dy == 2 || dy == -2)) { return true; }
		else if ((dx == 2 || dx == -2) && (dy == 1 || dy == -1)) { return true; }
		else { return false; }
	}
	bool Board::is1square(int i, int j, int m, int n)
	{
		int dx = m - i;
		int dy = n - j;

		if (((dx == 1 || dx == -1) && dy == 0) || ((dy == 1 || dy == -1) && dx == 0)) { return true; }
		else { return false; }
	}
	bool Board::is2square(int i, int j, int m, int n)
	{
		int dx = m - i;
		int dy = n - j;

		if ((dx == 2 || dx == -2 || dy == 2 || dy == -2)) { return true; }
		else { return false; }
	}

	// Get index of a BoardSquare e.g (E, 4) in square_array
	int Board::index(char a, int n) const {
		for (int m = 1; m <= columns; m++) {
			if (a == coords[m - 1]) {
				if (m > 0 && m <= columns && n > 0 && n <= rows) {
					return (n - 1)*rows + (m - 1);
				}
			}
		}
		// Error message if index out of range
		std::cout << "Error: square is not on chess board!" << std::endl; exit(1);
	}

	// overloaded index function for use with two integer inputs
	int Board::index(int m, int n) const {
		if (m > 0 && m <= columns && n > 0 && n <= rows) {
			return (n - 1)*rows + (m - 1);
		}
		else { std::cout << "Error: square is not on chess board!" << std::endl; exit(1); }
	}

	// Get player1
	Player &Board::getPlayer1() { return *player1; }

	// Get player2
	Player &Board::getPlayer2() { return *player2; }

	// Get piece occupying square (m, n)
	char &Board::getPiece(int m, int n)
	{
		Piece &piece = square_array[index(m, n)]->getSquarePiece();
		char key = piece.getKey();
		return key;
	}

	// Get colour of piece occupying square (m, n)
	std::string &Board::getColour(int m, int n) { return square_array[index(m, n)]->getSquareColour(); }

	// Set piece occupying square (m, n)
	void Board::setNullPiece(int m, int n)
	{
		square_array[index(m, n)] = nullptr;
		square_array[index(m, n)] = new BoardSquare();
	}

	// MovePiece on Board
	void Board::MovePiece(int i, int j, int m, int n)
	{
		std::cout << "Moving: " << coords[i - 1] << j << " " << coords[m - 1] << n << std::endl;
		std::swap(square_array[index(i, j)], square_array[index(m, n)]);
	}
	// Overload to take Board coordinate input
	void Board::MovePiece(char a, int j, char b, int n)
	{
		for (int i = 1; i <= columns; i++) {
			for (int m = 1; m <= columns; m++)
				if (a == coords[i - 1]) {
					if (b == coords[m - 1]) {
						std::cout << "Moving: " << coords[i - 1] << j << " " << coords[m - 1] << n << std::endl;
						std::swap(square_array[index(i, j)], square_array[index(m, n)]);
					}
				}
		}
	}

	// Decrement the number of specified pieces on the board
	void Board::decrementWP() { number_WP--; }
	void Board::decrementWC() { number_WC--; }
	void Board::decrementWN() { number_WN--; }
	void Board::decrementWB() { number_WB--; }
	void Board::decrementWQ() { number_WQ--; }
	void Board::decrementWK() { number_WK--; }

	void Board::decrementBP() { number_BP--; }
	void Board::decrementBC() { number_BC--; }
	void Board::decrementBN() { number_BN--; }
	void Board::decrementBB() { number_BB--; }
	void Board::decrementBQ() { number_BQ--; }
	void Board::decrementBK() { number_BK--; }

	//
	int &Board::get_numberWK() { return number_WK; }
	int &Board::get_numberBK() { return number_BK; }

	// Over-ride << operator to use with Board class
	std::ostream & operator<< (std::ostream &os, const Board &b)
	{
		// Print top coordinates
		for (int j = 1; j <= b.columns; j++){
			if (j == 1) {
				os << std::setw(6) << b.coords[j - 1] << "  ";
			}
			else { os << std::setw(5) << b.coords[j - 1] << "  "; }
		}
		os << std::endl;

		// Print board with left coordinates
		for (int i = 1; i <= b.rows; i++) {
			for (int j = 1; j <= b.columns; j++){
				if (j == 1) {
					os << "  ------";
				}
				else { os << " ------"; }
			}
			os << std::endl;
			for (int j = 1; j <= b.columns; j++){
				os << " |" << std::setw(7);
				if (j == b.columns) {
					os << " |" << std::endl;
				}
			}
			os << i;
			for (int j = 1; j <= b.columns; j++){
				os << "|  "; b.square_array[b.index(j, i)]->Show(); os << "  ";
				if (j == b.columns) {
					os << "|" << std::endl;
				}
			}
			for (int j = 1; j <= b.columns; j++){
				os << " |" << std::setw(7);
				if (j == b.columns) {
					os << " |" << std::endl;
				}
			}
		}

		os << " ";
		for (int j = 1; j <= b.columns; j++){
			os << " ------";
		}

		return os;
	}

}
