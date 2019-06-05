// ChessPieces.cpp
// A .cpp file that contains the derived classes for each chess piece
// Elliot Goodwin
// 10/05/2019

// Chess includes
#include "ChessPieces.h"

// Group code in namespace "Chess"
namespace Chess {

	// Define the constructors, destructors and access functions for each piece
	NullPiece::NullPiece() : Piece() {};
	NullPiece::~NullPiece() {};
	void NullPiece::Show() { std::cout << "  "; }
	bool NullPiece::allowedMove(Board *board, Player *player, int x_1, int y_1, int x_2, int y_2) { return true; }
	char NullPiece::getKey() { return key; }

	Pawn::Pawn() : Piece() {};
	Pawn::~Pawn() {};
	void Pawn::Show() { std::cout << "P"; }
	bool Pawn::allowedMove(Board *board, Player *player, int x_1, int y_1, int x_2, int y_2)
	{
		// Player1 pawns move forward on board
		if (board->getPlayer1().getPlayerColour() == player->getPlayerColour()) {
			if (board->isForward(x_1, y_1, x_2, y_2) && board->is1square(x_1, y_1, x_2, y_2)) { return true; }
			else { return false; }
		}
		// Player2 pawns move backward on board
		else if (board->getPlayer2().getPlayerColour() == player->getPlayerColour()) {
			if (board->isBackward(x_1, y_1, x_2, y_2) && board->is1square(x_1, y_1, x_2, y_2)) { return true; }
			else { return false; }
		}
		else { std::cout << "Something went wrong." << std::endl; exit(1); }
	}
	char Pawn::getKey() { return key; }

	Castle::Castle() : Piece() {};
	Castle::~Castle() {};
	void Castle::Show() { std::cout << "C"; }
	bool Castle::allowedMove(Board *board, Player *player, int x_1, int y_1, int x_2, int y_2)
	{
		if (board->isHorizontal(x_1, y_1, x_2, y_2) || board->isVertical(x_1, y_1, x_2, y_2)) { return true; }
		return false;
	}
	char Castle::getKey() { return key; }

	Bishop::Bishop() : Piece() {};
	Bishop::~Bishop() {};
	void Bishop::Show() { std::cout << "B"; }
	bool Bishop::allowedMove(Board *board, Player *player, int x_1, int y_1, int x_2, int y_2)
	{
		if (board->isDiagonal(x_1, y_1, x_2, y_2)) { return true; }
		return false;
	}
	char Bishop::getKey() { return key; }

	Knight::Knight() : Piece() {};
	Knight::~Knight() {};
	void Knight::Show() { std::cout << "N"; }
	bool Knight::allowedMove(Board *board, Player *player, int x_1, int y_1, int x_2, int y_2)
	{
		if (board->isLshaped(x_1, y_1, x_2, y_2)) { return true; }
		return false;
	}
	char Knight::getKey() { return key; }

	Queen::Queen() : Piece() {};
	Queen::~Queen() {};
	void Queen::Show() { std::cout << "Q"; }
	bool Queen::allowedMove(Board *board, Player *player, int x_1, int y_1, int x_2, int y_2)
	{
		if (board->isHorizontal(x_1, y_1, x_2, y_2) || board->isVertical(x_1, y_1, x_2, y_2) || board->isDiagonal(x_1, y_1, x_2, y_2)) { return true; }
		return false;
	}
	char Queen::getKey() { return key; }

	King::King() : Piece() {};
	King::~King() {};
	void King::Show() { std::cout << "K"; }
	bool King::allowedMove(Board *board, Player *player, int x_1, int y_1, int x_2, int y_2)
	{
		if (board->is1square(x_1, y_1, x_2, y_2)) { return true; }
		return false;
	}
	char King::getKey() { return key; }
}

