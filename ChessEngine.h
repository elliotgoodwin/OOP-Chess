// ChessEngine.h
// A header file containing the game engine for object-oriented chess
// Elliot Goodwin - 9621958
// 10/05/2019


#ifndef ChessEngine_h
#define ChessEngine_h

// C++ STL includes
#include <vector>
// Headers for game of chess
#include "ChessPieces.h"
#include "ChessBoard.h"

namespace Chess {

	// Function to print elements of a vector of strings using lambdas
	void printVector(std::vector<std::string> myVector);

	// Conversions between integer and character coordinates
	// Take A --> 1 etc for [A, H]
	int coord2number(char a);
	// Take 1 --> A etc for [1, 8]
	char number2coord(int a);

	// Checks that a character corresponds to a piece key
	bool isPiece(char a);

	// Parses move info (piece, coords, capture) and appends to a vector
	// This hasn't been used in the program (instead I did this explictly in every bool function below)
	// I understand that the method implemented in the program is less computationally efficient than using a method such as that in getMoveInfo
	std::vector<std::string> getMoveInfo(std::string player_move);

	// Parses string stream to check that user has valid input format
	bool validInput(std::string player_move);

	// Returns true if the move is allowed by the rules of chess
	bool validMove(std::string player_move, Player &player, Board &board);

	// Returns true if the destination square is occupied 
	bool isOccupied(std::string player_move, Board &board);
	// Overload: input explicit co-ordinates 
	bool isOccupied(int x_1, int y_1, int x_2, int y_2, Board &board);

	// Checks that the route to a destination squaure is accessible to the piece
	bool inbetweenisOccupied(std::string player_move, Board &board);

	// Returns true if player has indicatd a capture
	bool isCapture(std::string player_move);

	// Returns true if the square player is moving from is occupied by their own piece (i.e move allowed)
	bool from_ownPiece(std::string player_move, Board &board, Player &player);

	// Returns true if the square player is moving to is occupied by their own piece (i.e move not allowed)
	bool to_ownPiece(std::string player_move, Board &board, Player &player);

	// Ask player to input a move
	std::string askMove();

	// Executes a move on the board using move semantics; return new board
	Board makeMove(std::string player_move, Board &board, Player *player);

	// Fills vector with all moves available from one board square
	std::vector<std::string> get_squareAvailableMoves(Board &board, Player *player, int m, int n);

	// Fills vector with all moves available to a player
	std::vector<std::string> get_allAvailableMoves(Board &board, Player *player);

	// Define a template so that a function can be used as an input parameter to sort functions below
	template<typename Func>
	// Will return a vector with all moves that match func criteria
	std::vector<std::string> findMatchingMoves(Board &board, Player *player, Func func);

	// An example of sorting player moves using templates and lambdas
	// Search engine to find moves
	std::vector<std::string> findMove(Board &board, Player *player);

	// Shows the help interface to the player
	void helpPlayer(Board &board, Player *player);

	// Try to execute move (returns true if move is possible)
	bool tryMove(std::string player_move, Board &board, Player *player);

	// Plays one round of chess (each player moves)
	Board playRound(Board &board, Player *player);

	// Initialise default board (p1 = white human, p2 = black computer)
	Board initialiseDefaultBoard();

	// Set up chess board with user input
	Board initialiseCustomBoard();

	// Prompts the user to set up the game
	Board setupBoard();

	// Plays a game of chess
	void playGame();



}
#endif
