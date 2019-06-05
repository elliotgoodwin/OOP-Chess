// ChessEngine.cpp
// A .cpp file containing the game engine for object-oriented chess
// Elliot Goodwin
// 10/05/2019

// C++ STL includes
#include <iostream>  // std::cin, std::cout
#include <string>    // std::to_string
#include <sstream>   // std::stringstream
#include <vector>    // std::vector
#include <algorithm> // std::sort
#include <ctime>     // seed random number generator

// Headers for a game of chess
#include "ChessEngine.h"

// Group code in namespace "Chess"
namespace Chess {

	// Function to print elements of a vector of strings using lambdas
	void printVector(std::vector<std::string> myVector){

		// Example of printing vector using iterators; this function was updated to use an example of an advanced C++ feature (lambdas)
		//if (!myVector.empty()) {
		//	for (std::vector<std::string>::iterator it = myVector.begin(); it != myVector.end(); it++) {
		//		std::cout << *it << std::setw(10);
		//	}
		//}

		// Print vector elements using lambdas
		std::for_each(myVector.begin(), myVector.end(), [](std::string entry) {
			std::cout << entry << std::setw(10);
		} );
		std::cout << std::endl;
	}

	// Conversions between integer and character coordinates
	// Take A --> 1 etc for [A, H]
	int coord2number(char a)
	{
		if (a == 'A' || a == 'a') { return 1; }
		else if (a == 'B' || a == 'b') { return 2; }
		else if (a == 'C' || a == 'c') { return 3; }
		else if (a == 'D' || a == 'd') { return 4; }
		else if (a == 'E' || a == 'e') { return 5; }
		else if (a == 'F' || a == 'f') { return 6; }
		else if (a == 'G' || a == 'g') { return 7; }
		else if (a == 'H' || a == 'h') { return 8; }
		else { return 10; }
	}
	// Take 1 --> A etc for [1, 8]
	char number2coord(int a)
	{
		if (a == 1) { return 'A'; }
		else if (a == 2) { return 'B'; }
		else if (a == 3) { return 'C'; }
		else if (a == 4) { return 'D'; }
		else if (a == 5) { return 'E'; }
		else if (a == 6) { return 'F'; }
		else if (a == 7) { return 'G'; }
		else if (a == 8) { return 'H'; }
		else { return 'X'; }
	}

	// Checks that a character corresponds to a piece key
	bool isPiece(char a)
	{
		if (a == 'P' || a == 'p' || a == 'B' || a == 'b' || a == 'C' || a == 'c' || a == 'N' || a == 'n' || a == 'K' || a == 'k' || a == 'Q' || a == 'q')
		{
			return true;
		}
		else { return false; }
	}

	// Parses move info (piece, coords, capture) and appends to a vector
	// This hasn't been used in the program (instead I did this explictly in every bool function below)
	// I understand that the method implemented in the program is less efficient than using getMoveInfo
	std::vector<std::string> getMoveInfo(std::string player_move)
	{
		std::vector <std::string> moveVector;
		char a, b;
		std::string piece, capture, x_1, y_1, x_2, y_2;
		std::istringstream ss;
		ss.str(player_move);

		// get length of stringstream contents
		ss.seekg(0, ss.end);
		int length = int(ss.tellg());
		ss.seekg(0, ss.beg);

		if (length == 5) {
			ss >> piece >> std::ws >> a >> std::ws >> y_1 >> std::ws >> b >> std::ws >> y_2 >> std::ws;
			x_1 = std::to_string(coord2number(a));
			x_1 = std::to_string(coord2number(b));
			moveVector.push_back(piece);
			moveVector.push_back(x_1);
			moveVector.push_back(y_1);
			moveVector.push_back(x_2);
			moveVector.push_back(y_2);
		}
		else if (length == 6) {
			ss >> piece >> std::ws >> a >> std::ws >> y_1 >> std::ws >> capture >> std::ws >> b >> std::ws >> y_2 >> std::ws;
			x_1 = std::to_string(coord2number(a));
			x_1 = std::to_string(coord2number(b));
			moveVector.push_back(piece);
			moveVector.push_back(x_1);
			moveVector.push_back(y_1);
			moveVector.push_back(capture);
			moveVector.push_back(x_2);
			moveVector.push_back(y_2);
		}

		return moveVector;
	}

	// Parses string stream to check that user has valid input format
	bool validInput(std::string player_move)
	{
		char piece, x_1, x_2, capture;
		int y_1, y_2, board_size{ 8 };
		std::istringstream ss;
		ss.str(player_move);

		// get length of stringstream contents
		ss.seekg(0, ss.end);
		int length = int(ss.tellg());
		ss.seekg(0, ss.beg);

		if (length == 5) {
			if (ss >> piece >> std::ws >> x_1 >> std::ws >> y_1 >> std::ws >> x_2 >> std::ws >> y_2 >> std::ws) {
				if (isPiece(piece)) {
					if (coord2number(x_1) <= board_size && coord2number(x_2) <= board_size && y_1 <= board_size && y_2 <= board_size) {
						return true;
					}
					else { std::cout << "Error, coordinate not on board." << std::endl; }
				}
				else { std::cout << "Error, invalid chess piece." << std::endl; }
			}
		}

		else if (length == 6) {
			if (ss >> piece >> std::ws >> x_1 >> std::ws >> y_1 >> std::ws >> capture >> std::ws >> x_2 >> std::ws >> y_2 >> std::ws) {
				if (isPiece(piece)) {
					if (coord2number(x_1) <= board_size && coord2number(x_2) <= board_size && y_1 <= board_size && y_2 <= board_size) {
						if (capture == 'x' || capture == 'X') {
							return true;
						}
						else { std::cout << "Error, use x to indicate capture." << std::endl; }
					}
					else { std::cout << "Error, coordinate not on board." << std::endl; }
				}
				else { std::cout << "Error, invalid chess piece." << std::endl; }
			}
			else { std::cout << "Error, invalid input format." << std::endl; }
		}

		return false;
	}

	// Returns true if the move is allowed by the rules of chess
	bool validMove(std::string player_move, Player &player, Board &board)
	{
		// Extract information about the move from string "player_move"
		char piece, a, b, capture;
		int y_1, y_2, board_size{ 8 };
		std::istringstream ss;
		ss.str(player_move);

		ss.seekg(0, ss.end);
		int length = int(ss.tellg());
		ss.seekg(0, ss.beg);

		if (length == 5) {
			ss >> piece >> std::ws >> a >> std::ws >> y_1 >> std::ws >> b >> std::ws >> y_2 >> std::ws;
		}
		else if (length == 6) {
			ss >> piece >> std::ws >> a >> std::ws >> y_1 >> std::ws >> capture >> std::ws >> b >> std::ws >> y_2 >> std::ws;
		}

		int x_1 = coord2number(a);
		int x_2 = coord2number(b);

		// Cycle through types of piece 
		for (int i = 7; i <= 12; i++) {
			// and match to user input
			if (piece == player.getPlayerPiece(i).getKey()){
				// if move is allowed for given piece
				if (player.getPlayerPiece(i).allowedMove(&board, &player, x_1, y_1, x_2, y_2)) {
					// return true
					return true;
				}
			}
		}

		// otherwise, return false
		return false;
	}

	// Returns true if the destination square is occupied 
	bool isOccupied(std::string player_move, Board &board)
	{
		// Extract information about the move from string "player_move"
		int move_length = 5;
		int capture_length = 6;
		char piece, a, b, capture;
		int y_1, y_2, board_size{ 8 };
		std::istringstream ss;
		ss.str(player_move);

		ss.seekg(0, ss.end);
		int length = int(ss.tellg());
		ss.seekg(0, ss.beg);

		if (length == move_length) {
			ss >> piece >> std::ws >> a >> std::ws >> y_1 >> std::ws >> b >> std::ws >> y_2 >> std::ws;

		}
		else if (length == capture_length) {
			ss >> piece >> std::ws >> a >> std::ws >> y_1 >> std::ws >> capture >> std::ws >> b >> std::ws >> y_2 >> std::ws;
		}

		int x_1 = coord2number(a);
		int x_2 = coord2number(b);

		if (board.getPiece(x_2, y_2) != '0'){ return true; }  // Recall '0' was the key for a null piece def. line 22 in ChessPiece.h
		else { return false; }
	}
    // Overload: input explicit co-ordinates 
	bool isOccupied(int x_1, int y_1, int x_2, int y_2, Board &board)
	{
		std::istringstream ss;
		ss >> x_1 >> std::ws >> y_1 >> std::ws >> x_2 >> std::ws >> y_2 >> std::ws;

		if (board.getPiece(x_2, y_2) != '0'){ return true; }  // Recall '0' was the key for a null piece def. line 22 in ChessPiece.h
		else { return false; }
	}

	// Checks that the route to a destination squaure is accessible to the piece
	bool inbetweenisOccupied(std::string player_move, Board &board)
	{
		// Extract information about the move from string "player_move"
		int move_length = 5;
		int capture_length = 6;
		char piece, a, b, capture;
		int y_1, y_2, board_size{ 8 };
		std::istringstream ss;
		ss.str(player_move);

		ss.seekg(0, ss.end);
		int length = int(ss.tellg());
		ss.seekg(0, ss.beg);

		if (length == move_length) {
			ss >> piece >> std::ws >> a >> std::ws >> y_1 >> std::ws >> b >> std::ws >> y_2 >> std::ws;
		}
		else if (length == capture_length) {
			ss >> piece >> std::ws >> a >> std::ws >> y_1 >> std::ws >> capture >> std::ws >> b >> std::ws >> y_2 >> std::ws;
		}

		int x_1 = coord2number(a);
		int x_2 = coord2number(b);

		// Iterate through each square on the route to destination
		if (board.isVertical(x_1, y_1, x_2, y_2)) {
			int dy = y_2 - y_1;
			if (std::abs(dy) > 1) {
				for (int i = 1; i < std::abs(dy); i++) {
					if (dy > 0) {
						if (isOccupied(x_1, y_1, x_2, y_1 + i, board)) { return true; }
					}
					if (dy < 0) {
						if (isOccupied(x_1, y_1, x_2, y_1 - i, board)) { return true; }
					}
				}
			}
		}
		if (board.isHorizontal(x_1, y_1, x_2, y_2)) {
			int dx = x_2 - x_1;
			if (std::abs(dx) > 1) {
				for (int i = 1; i < std::abs(dx); i++) {
					if (dx > 0) {
						if (isOccupied(x_1, y_1, x_1 + i, y_2, board)) { return true; }
					}
					if (dx < 0) {
						if (isOccupied(x_1, y_1, x_1 - i, y_2, board)) { return true; }
					}
				}
			}
		}
		if (board.isDiagonal(x_1, y_1, x_2, y_2)) {
			int dx = x_2 - x_1;
			int dy = y_2 - y_1;

			if (std::abs(dx) > 1) {
				for (int i = 1; i < std::abs(dx); i++) {
					if (dx > 0 && dy > 0) {
						if (isOccupied(x_1, y_1, x_1 + i, y_1 + i, board)) { return true; }
					}
					else if (dx > 0 && dy < 0) {
						if (isOccupied(x_1, y_1, x_1 + i, y_1 - i, board)) { return true; }
					}
					else if (dx < 0 && dy > 0) {
						if (isOccupied(x_1, y_1, x_1 - i, y_1 + i, board)) { return true; }
					}
					else if (dx < 0 && dy < 0) {
						if (isOccupied(x_1, y_1, x_1 - i, y_1 - i, board)) { return true; }
					}
				}
			}
		}
		else if (board.isLshaped(x_1, y_1, x_2, y_2)) { return false; }

		return false;
	}

	// Returns true if player has indicatd a capture
	bool isCapture(std::string player_move)
	{
		int capture_length = 6;
		std::istringstream ss;
		ss.str(player_move);

		ss.seekg(0, ss.end);
		int length = int(ss.tellg());
		ss.seekg(0, ss.beg);

		if (length == capture_length) { return true; }
		else { return false; }
	}

	// Returns true if the square player is moving from is occupied by their own piece (i.e move allowed)
	bool from_ownPiece(std::string player_move, Board &board, Player &player)
	{
		// Extract information about the move from string "player_move"
		int move_length = 5;
		int capture_length = 6;
		char piece, a, b, capture;
		int y_1, y_2, board_size{ 8 };
		std::istringstream ss;
		ss.str(player_move);

		ss.seekg(0, ss.end);
		int length = int(ss.tellg());
		ss.seekg(0, ss.beg);

		if (length == move_length) {
			ss >> piece >> std::ws >> a >> std::ws >> y_1 >> std::ws >> b >> std::ws >> y_2 >> std::ws;
		}
		else if (length == capture_length) {
			ss >> piece >> std::ws >> a >> std::ws >> y_1 >> std::ws >> capture >> std::ws >> b >> std::ws >> y_2 >> std::ws;
		}

		int x_1 = coord2number(a);
		int x_2 = coord2number(b);

		// Match square colours
		if (player.getPlayerColour() == board.getColour(x_1, y_1)){ return true; }
		else { return false; }
	}

	// Returns true if the square player is moving to is occupied by their own piece (i.e move not allowed)
	bool to_ownPiece(std::string player_move, Board &board, Player &player)
	{
		// Extract information about the move from string "player_move"
		int move_length = 5;
		int capture_length = 6;
		char piece, a, b, capture;
		int y_1, y_2, board_size{ 8 };
		std::istringstream ss;
		ss.str(player_move);

		ss.seekg(0, ss.end);
		int length = int(ss.tellg());
		ss.seekg(0, ss.beg);

		if (length == move_length) {
			ss >> piece >> std::ws >> a >> std::ws >> y_1 >> std::ws >> b >> std::ws >> y_2 >> std::ws;
		}
		else if (length == capture_length) {
			ss >> piece >> std::ws >> a >> std::ws >> y_1 >> std::ws >> capture >> std::ws >> b >> std::ws >> y_2 >> std::ws;
		}

		int x_1 = coord2number(a);
		int x_2 = coord2number(b);


		if (from_ownPiece(player_move, board, player)) {
			// If colour of square 1 -> square 2 match; return true
			if (board.getColour(x_1, y_1) == board.getColour(x_2, y_2)) { return true; }
			// If not; return false
			else if (board.getColour(x_1, y_1) != board.getColour(x_2, y_2)) { return false; }
			// Graceful exit
			else { std::cout << "Something went wrong." << std::endl; exit(1); }
		}
		else { return false; }
	}

	// Ask player to input a move
	std::string askMove()
	{
		// Ask user to input a move
		std::cout << "Input move or press 'h' for help: ";
		std::string move;
		std::cin >> move;
		// Convert to upper, hasn't worked
		std::string output;
		char c;
		for (int i = 0; i < int(move.length()); i++) {
			c = move[i];
			output += toupper(c);
		}
		return output;
	}

	// Executes a move on the board using move semantics; return new board
	Board makeMove(std::string player_move, Board &board, Player *player)
	{
		// Extract information from string "player_move"
		int move_length = 5;
		int capture_length = 6;
		char piece, a, b, capture;
		int x_1, x_2, y_1, y_2, board_size{ 8 };
		std::istringstream ss;
		ss.str(player_move);

		ss.seekg(0, ss.end);
		int length = int(ss.tellg());
		ss.seekg(0, ss.beg);

		if (length == move_length) {
			ss >> piece >> std::ws >> a >> std::ws >> y_1 >> std::ws >> b >> std::ws >> y_2 >> std::ws;

			x_1 = coord2number(a);
			x_2 = coord2number(b);
		}

		else if (length == capture_length) {
			ss >> piece >> std::ws >> a >> std::ws >> y_1 >> std::ws >> capture >> std::ws >> b >> std::ws >> y_2 >> std::ws;

			x_1 = coord2number(a);
			x_2 = coord2number(b);

			// Execute move
			if (board.getColour(x_2, y_2) == "white" || board.getColour(x_2, y_2) == "White") {

				if (board.getPiece(x_2, y_2) == 'P') { board.decrementWP(); }
				else if (board.getPiece(x_2, y_2) == 'C') { board.decrementWC(); }
				else if (board.getPiece(x_2, y_2) == 'N') { board.decrementWN(); }
				else if (board.getPiece(x_2, y_2) == 'B') { board.decrementWB(); }
				else if (board.getPiece(x_2, y_2) == 'Q') { board.decrementWQ(); }
				else if (board.getPiece(x_2, y_2) == 'K') { board.decrementWK(); }
				else { std::cout << "Something went wrong." << std::endl; exit(1); }

		    }

			// If capturing, decrement piece counter and set square to NullPiece
			else if (board.getColour(x_2, y_2) == "black" || board.getColour(x_2, y_2) == "Black") {

				if (board.getPiece(x_2, y_2) == 'P') { board.decrementBP(); }
				else if (board.getPiece(x_2, y_2) == 'C') { board.decrementBC(); }
				else if (board.getPiece(x_2, y_2) == 'N') { board.decrementBN(); }
				else if (board.getPiece(x_2, y_2) == 'B') { board.decrementBB(); }
				else if (board.getPiece(x_2, y_2) == 'Q') { board.decrementBQ(); }
				else if (board.getPiece(x_2, y_2) == 'K') { board.decrementBK(); }
				else { std::cout << "Something went wrong." << std::endl; exit(1); }

			}
			else { std::cout << "Something went wrong." << std::endl; exit(1); }

			// Remove captured piece from board
			board.setNullPiece(x_2, y_2);
		}

		// Execute move
		board.MovePiece(x_1, y_1, x_2, y_2);
		player->addPlayedMove(player_move);

		return board;
	}

	// Fills vector with all moves available from one board square
	std::vector<std::string> get_squareAvailableMoves(Board &board, Player *player, int m, int n)
	{
		// Initialise variables
		int x_1{ m }, y_1{ n }, boardSize{ 8 };
		char piece = board.getPiece(x_1, y_1);
		std::vector<std::string> squareMoves;
		std::string theMove = "";
		std::istringstream ss;

		// Iterate through all boardsquares (exclude initial square)
		for (int x_2 = 1; x_2 <= boardSize; x_2++) {
			// Clear the string containing the move in each iteration
			theMove = "";
			for (int y_2 = 1; y_2 <= boardSize; y_2++) {
				theMove = "";
				if (x_2 == x_1 && y_2 == y_1) {}
				else {
					// Construct the move
					theMove += piece;
					theMove += number2coord(x_1);
					theMove += std::to_string(y_1);
					theMove += number2coord(x_2);
					theMove += std::to_string(y_2);

					// Check for unoccupied squares that piece can move to
					if (from_ownPiece(theMove, board, *player)) {
						if (validMove(theMove, *player, board)) {
							if (!inbetweenisOccupied(theMove, board)) {
								// If move available
								if (!isOccupied(theMove, board)) {
									squareMoves.push_back(theMove);
								}
								// Indicate that a capture is possible
								else if (isOccupied(theMove, board) && !to_ownPiece(theMove, board, *player)) {
									//Erase the last two coordinates
									theMove.erase(theMove.end()-2 , theMove.end());

									// Add an x to distinguish capture (and the last two coordinates back)
									theMove += "x";
									theMove += number2coord(x_2);
									theMove += std::to_string(y_2);

									squareMoves.push_back(theMove);
									theMove = "";
								}
							}
						}
					}
				}
			}
		}

		return squareMoves;
	}

	// Fills vector with all moves available to a player
	std::vector<std::string> get_allAvailableMoves(Board &board, Player *player)
	{
		int boardSize{ 8 };
		std::vector<std::string> tempVector, moveVector;
		
		// Iterate through all board squares
		for (int i = 1; i <= boardSize; i++) {
			for (int j = 1; j <= boardSize; j++) {
				// Fill a vector with moves available to each square
				tempVector = get_squareAvailableMoves(board, player, i, j);
				if (!tempVector.empty()) {
					for (std::vector<std::string>::iterator it = tempVector.begin(); it != tempVector.end(); it++) {
						moveVector.push_back(*it);
					}
				}
			}
		}

		return moveVector;
	}

	// Define a template so that a function-type can be used as an input parameter in sort functions below
	template<typename Func>
	// Will return a vector with all moves that match func criteria
	std::vector<std::string> findMatchingMoves(Board &board, Player *player, Func func)
	{
		std::vector<std::string> results;
		std::vector<std::string> moveVector = get_allAvailableMoves(board, player);
		for (auto it = moveVector.begin(), end = moveVector.end(); it != end; ++it) {
			// call the function passed into findMatchingMoves and see if it matches
			if (func(*it)) { results.push_back(*it); }
		}
		return results;
	}

	// An example of sorting player moves using templates and lambdas
	// Search engine to find moves
	std::vector<std::string> findMove(Board &board, Player *player)
	{
		// Prompt user to search for a move
		std::string input;
		std::cout << std::endl << "Enter a piece key or board coordinate to find a move." << std::endl;
		std::cin >> input;

		// Convert to capitals using toupper
		std::string search_criteria;
		char c;
		for (int i = 0; i < int(input.length()); i++) {
			c = input[i];
			search_criteria += toupper(c);
		}

		// Use lambdas to return available moves containing their query term
		return findMatchingMoves(board, player, [&](const std::string& text) {
			return text.find(search_criteria) != std::string::npos; }
		);
	}

	// Shows the help interface to the player
	void helpPlayer(Board &board, Player *player)
	{
		// Initialise variables
		std::istringstream ss;
		std::string user_input;
		int help_option{ 0 };
		bool re_prompt{ true };

		std::cout << std::endl << "You have asked for help." << std::endl << std::endl;
		std::cout << "Press" << std::endl;
		std::cout << "  [1] - See all available moves" << std::endl;
		std::cout << "  [2] - Search for moves for a type of piece or board square" << std::endl;

		getline(std::cin, user_input);
		ss.str(user_input);

		// Pass in the user help option; re-prompt if input isn't 1 or 2.
		ss >> help_option;
		if (help_option != 1 || help_option != 2) {

			do {

				ss.clear();
				getline(std::cin, user_input);
				ss.str(user_input);
				ss >> help_option;

				if (help_option == 1 || help_option == 2) { re_prompt = false; }
				else { std::cout << std::endl << "Please try again." << std::endl; }

			} while (re_prompt);

		}

		// if 1
		if (help_option == 1) {
			// Print all available moves to console
			std::vector<std::string> moveVector = get_allAvailableMoves(board, player);
			std::cout << std::endl; printVector(moveVector); std::cout << std::endl;
		}
		// if 2
		else if (help_option == 2) {
			// Give user access to move search engine
			std::vector<std::string> moveVector = findMove(board, player);
			std::cout << std::endl; printVector(moveVector); std::cout << std::endl;
		}
		// Graceful exit
		else { std::cout << "Something went wrong." << std::endl; exit(1); }
	}

	// Try to execute move (returns true if move is possible)
	bool tryMove(std::string player_move, Board &board, Player *player)
	{
		// if player hasn't indicated a capture
		if (!isCapture(player_move)) {
			if (validInput(player_move)) {
				if (from_ownPiece(player_move, board, *player)) {
					if (validMove(player_move, *player, board)) {
						if (!isOccupied(player_move, board)) {
							if (!inbetweenisOccupied(player_move, board)) {
								// move allowed; return true
								return true;
							}
							else { std::cout << "Pieces in the way!" << std::endl; return false; }
						}
						else { std::cout << "Square is already occupied!" << std::endl; return false; }
					}
					else { std::cout << "Move not allowed." << std::endl; return false; }
				}
				else { std::cout << "Cannot move other player's piece!" << std::endl; return false; }
			}
			else { std::cout << "Invalid input format." << std::endl; return false; }
		}

		// if player has indicated a capture
		else if (isCapture(player_move)) {
			if (validInput(player_move)) {
				if (from_ownPiece(player_move, board, *player)) {
					if (validMove(player_move, *player, board)) {
						if (isOccupied(player_move, board)) {
							if (!to_ownPiece(player_move, board, *player)) {
								if (!inbetweenisOccupied(player_move, board)) {
									// move allowed; return true
									return true;
								}
								else { std::cout << "Pieces in the way!" << std::endl; }
							}
						}
						else { std::cout << "Cannot capture this square!" << std::endl; return false; }
					}
					else { std::cout << "Move not allowed." << std::endl; return false; }
				}
				else { std::cout << "Cannot move other player's piece!" << std::endl; return false; }
			}
			else { std::cout << "Invalid input format." << std::endl; return false; }
		}

		else { std::cout << "Something went wrong." << std::endl; exit(1); }
		return false;
	}

	// Plays one round of chess (each player moves)
	Board playRound(Board &board, Player *player)
	{
		// initialise round variables
		std::string player_move;
		bool quit_flag = false;

		// If human player
		if (player->getPlayerType() == 'H') {
			do {

				// ask for player input
				player_move = askMove();

				// quit if user selects to quit
				if (player_move == "Q" || player_move == "q") {
					quit_flag = true;
					std::cout << std::endl << std::endl << std::setw(35) << "You chose to quit." << std::endl << std::endl;
					exit(1);
				}

				// show help screen if user requests help
				else if (player_move == "Help" || player_move == "help" || player_move == "H" || player_move == "h") {
					helpPlayer(board, player);
				}

				// else, make the move
				else {
					// if the move can be executed without throwing an error
					if (tryMove(player_move, board, player)) {
						// clear console screen
						system("cls");
						// make the move and return the new board
						return makeMove(player_move, board, player);
					}
				}

			} while (!quit_flag);
		}

		// If computer player
		else if (player->getPlayerType() == 'C') {

			// Fill vector with all available moves
			std::vector<std::string> moveVector = get_allAvailableMoves(board, player);
			// Pick a random vector element
			int p = rand() % moveVector.size();
			std::string computer_move = moveVector[p];
			// clear console screen
			system("cls");
			// make the move and return the new board
			return makeMove(computer_move, board, player);
		}

		// return board if user opts to quit
		return board;
	}

	// Initialise default board (p1 = white human, p2 = black computer)
	Board initialiseDefaultBoard()
	{
		Board b("");
		return b;
	}

	// Set up chess board with user input
	Board initialiseCustomBoard()
	{

		char type1, type2, colour1, colour2;
		bool bad_input;
		std::string s;
		std::istringstream ss;

		// Construct player 1
		do {

			// Prompt user for input
			std::cout << std::endl;
			std::cout << "Enter Player 1 type:" << std::endl;
			std::cout << "   [H]uman" << std::endl;
			std::cout << "   [C]omputer" << std::endl;
			 
			// Clear string and ss in every loop
			s = "";
			ss.clear();
			// Get user input
			getline(std::cin, s);
			ss.str(s);

			// Error handling
			if (ss >> type1) {
				ss >> type1;
				bad_input = false;
				if (type1 != 'H' && type1 != 'h' && type1 != 'C' && type1 != 'c') {
					bad_input = true;
				}
			}
			else { bad_input = true; }

		} while (bad_input);

		do {

			// Prompt user for input
			std::cout << "Enter Player 1 colour:" << std::endl;
			std::cout << "   [W]hite" << std::endl;
			std::cout << "   [B]lack" << std::endl;

			// Clear string and ss in every loop
			s = "";
			ss.clear();
			// Get user input
			getline(std::cin, s);
			ss.str(s);

			// Error handling
			if (ss >> colour1) {
				ss >> colour1;
				bad_input = false;
				if (colour1 != 'W' && colour1 != 'w' && colour1 != 'B' && colour1 != 'b') {
					bad_input = true;
				}
			}
			else { bad_input = true; }

		} while (bad_input);

		Player *p1;
		if (type1 == 'H' || type1 == 'h') {
			if (colour1 == 'W' || colour1 == 'w') { p1 = new Human("White"); }
			else if (colour1 == 'B' || colour1 == 'b') { p1 = new Human("Black"); }
			else { std::cout << "Something went wrong." << std::endl; exit(1); }
		}
		else if (type1 == 'C' || type1 == 'c') {
			if (colour1 == 'W' || colour1 == 'w') { p1 = new Computer("White"); }
			else if (colour1 == 'B' || colour1 == 'b') { p1 = new Computer("Black"); }
			else { std::cout << "Something went wrong." << std::endl; exit(1); }
		}
		else { std::cout << "Something went wrong." << std::endl; exit(1); }


		// Construct player 2
		do {

			// Prompt user for input
			std::cout << std::endl;
			std::cout << "Enter Player 2 type:" << std::endl;
			std::cout << "   [H]uman" << std::endl;
			std::cout << "   [C]omputer" << std::endl;

			// Clear string and ss in every loop
			s = "";
			ss.clear();
			// Get user input
			getline(std::cin, s);
			ss.str(s);

			// Error handling
			if (ss >> type2) {
				ss >> type2;
				bad_input = false;
				if (type2 != 'H' && type2 != 'h' && type2 != 'C' && type2 != 'c') {
					bad_input = true;
				}
			}
			else { bad_input = true; }

		} while (bad_input);

		if (colour1 == 'W' || colour1 =='w') { colour2 = 'B'; }
		else if (colour1 == 'B' || colour1 == 'b') { colour2 = 'W'; }
		else { std::cout << "Something went wrong." << std::endl; exit(1); }

		Player *p2;
		if (type2 == 'H' || type2 == 'h') {
			if (colour2 == 'W' || colour2 == 'w') { p2 = new Human("White"); }
			else if (colour2 == 'B' || colour2 == 'b') { p2 = new Human("Black"); }
			else { std::cout << "Something went wrong." << std::endl; exit(1); }
		}
		else if (type2 == 'C' || type2 == 'c') {
			if (colour2 == 'W' || colour2 == 'w') { p2 = new Computer("White"); }
			else if (colour2 == 'B' || colour2 == 'b') { p2 = new Computer("Black"); }
			else { std::cout << "Something went wrong." << std::endl; exit(1); }
		}
		else { std::cout << "Something went wrong." << std::endl; exit(1); }
		std::cout << p2->getPlayerType() << p2->getPlayerColour();

		Board b(p1, p2);
		return b;
	}

	// Prompts the user to set up the game
	Board setupBoard() {

		std::string s;
		std::istringstream ss;
		int choice;
		bool bad_input;

		do {

			// Prompt user for input
			std::cout << std::endl;
			std::cout << "Choose your game mode:" << std::endl;
			std::cout << "   [1]  -  Default game" << std::endl;
			std::cout << "   [2]  -  Custom game" << std::endl;

			// Clear string and ss in every loop
			s = ""; ss.clear();
			// Get user input
			getline(std::cin, s);
			ss.str(s);

			// Error handling
			if (ss >> choice) {
				ss >> choice;
				bad_input = false;
				if (choice != 1 && choice != 2) {
					bad_input = true;
				}
			}
			else { bad_input = true; }

		} while (bad_input);

		if (choice == 1) { return initialiseDefaultBoard(); }
		else if (choice == 2) { return initialiseCustomBoard(); }
		else { std::cout << "Something went wrong." << std::endl; exit(1); }
	}

	// Show intro interface
	void showIntro()
	{
		// Initialise variables
		std::istringstream ss;
		std::string user_input;
		int option{ 0 };
		bool re_prompt{ true };
		bool ready{ true };

		do {
			std::cout << std::endl << "Would you like to see the intructions?" << std::endl << std::endl;
			std::cout << "Press" << std::endl;
			std::cout << "  [1] - See instructions" << std::endl;
			std::cout << "  [2] - Continue to game" << std::endl;

			getline(std::cin, user_input);
			ss.str(user_input);
			ss >> option;

			// Pass in the user option; re-prompt if input isn't 1 or 2.
			// Show intro screen if input = '1'
			if (option == 1) {
				do {
					std::cout << std::endl << std::endl;
					std::cout << "Piece key:" << std::endl;
					std::cout << "    P - Pawn" << std::endl;
					std::cout << "    C - Castle" << std::endl;
					std::cout << "    N - Knight" << std::endl;
					std::cout << "    B - Bishop" << std::endl;
					std::cout << "    Q - Queen" << std::endl;
					std::cout << "    K - King" << std::endl;

					std::cout << std::endl << std::endl;
					std::cout << "Board coordinates:" << std::endl;
					std::cout << "    Letter coordinates - [A, H]" << std::endl;
					std::cout << "    Number coordinates - [1, 8]" << std::endl;

					std::cout << std::endl << std::endl;
					std::cout << "Capture" << std::endl;
					std::cout << "    Indicate capture with an 'x'" << std::endl;

					std::cout << std::endl << std::endl;
					std::cout << "Move input" << std::endl;
					std::cout << "Enter moves in the following formats (ommiting -):" << std::endl;
					std::cout << "    (Piece key)-(letter)-(number)-(letter)-(number)" << std::endl;
					std::cout << "    (Piece key)-(letter)-(number)-(capture)-(letter)-(number)" << std::endl;

					do {

						std::cout << std::endl << std::endl;
						std::cout << "Are you ready to play chess?" << std::endl;
						std::cout << "    [1] - Yes" << std::endl;
						std::cout << "    [2] - No" << std::endl;

						ss.clear();
						getline(std::cin, user_input);
						ss.str(user_input);
						ss >> option;

						if (option == 1) { ready = true; }
						else if (option == 2) { exit(1); }

					} while (!ready);
				} while (!ready);
			}

			// Break from funtion if user inputs '2'
			else if (option == 2) { return; }

			else if (option != 1 || option != 2) {

				do {

					ss.clear();
					getline(std::cin, user_input);
					ss.str(user_input);
					ss >> option;

					if (option == 1 || option == 2) { re_prompt = false; }
					else { std::cout << std::endl << "Please try again." << std::endl; }

				} while (re_prompt);
			}
		} while (!ready);
	}

	// Game recap
	void gameRecap(Player *p1, Player *p2) {

		// Initialise variables
		std::istringstream ss;
		std::string user_input;
		int option{ 0 };
		bool re_prompt{ true };

		std::cout << std::endl << "Would you like to see a game recap?" << std::endl << std::endl;
		std::cout << "Press" << std::endl;
		std::cout << "  [1] - See game recap" << std::endl;
		std::cout << "  [2] - Exit" << std::endl;

		getline(std::cin, user_input);
		ss.str(user_input);
		ss >> option;

		// Pass in the user option; re-prompt if input isn't 1 or 2.
		// Show intro screen if input = '1'
		if (option == 1) {
			std::cout << std::endl << std::endl;

			std::cout << "Player 1 moves:" << std::endl;
			printVector(p1->getPlayedMoves());
			std::cout << std::endl << std::endl;

			std::cout << "Player 2 moves:" << std::endl;
			printVector(p2->getPlayedMoves());
			return;
		}

		// Break from funtion if user inputs '2'
		else if (option == 2) { return; }

		// re-prompt for user input if not '1' or '2'
		else if (option != 1 || option != 2) {
			do {
				ss.clear();
				getline(std::cin, user_input);
				ss.str(user_input);
				ss >> option;

				if (option == 1 || option == 2) { re_prompt = false; }
				else { std::cout << std::endl << "Please try again." << std::endl; }

			} while (re_prompt);
		}

	}

	// Plays a game of chess
	void playGame()
	{

		// Seed random number generator (for computer moves)
		srand(int(time(nullptr)));

		std::cout << "**********************************************************" << std::endl;
		std::cout << "******************* Welcome to chess *********************" << std::endl;
		std::cout << "**********************************************************" << std::endl;
		std::cout << std::endl << std::endl << std::endl;

		// initialise game variables 
		int number_of_turns{ 0 };
		bool game_in_progress = true;
		bool winner_white = false;
		bool winner_black = false;

		// Show intro interface
		showIntro();

		// Set up board
		Board b(setupBoard());

		// Clear console screen
		system("cls");
		// And print board
		std::cout << b << std::endl << std::endl << std::endl;

		// Game-play 
		do {
			// cycle through player turns (player 1 moves if number_of_turns is odd)
			if (! (number_of_turns % 2)) {
				std::cout << "Player1" << std::endl;
				// Play the round
				b = playRound(b, &b.getPlayer1());
				// And increment the counter
				number_of_turns++;
				std::cout << "Round " << (number_of_turns+1)/2 << std::endl;
			}
			else {
				std::cout << "Player2" << std::endl;
				b = playRound(b, &b.getPlayer2());
				number_of_turns++;
				std::cout << "Round " << number_of_turns/2 << std::endl;
			}
			
		    std::cout << std::endl << b << std::endl << std::endl << std::endl;

			// Check if game has been won
			if (b.get_numberWK() == 0) { winner_black = true; }
			else if (b.get_numberBK() == 0) { winner_white = true; }

		    if (number_of_turns >= 100 || winner_black || winner_white) { game_in_progress = false; }

			// Prompt player to continue after computer move
			if (!(number_of_turns % 2)) {
				if (b.getPlayer1().getPlayerType() == 'C') { system("pause"); }
			}
			else {
				if (b.getPlayer2().getPlayerType() == 'C') { system("pause"); }
			}

		} while (game_in_progress);


		// Print out game conclusion
		if (winner_white) { std::cout << std::setw(35) << "White team wins!" << std::endl; }
		else if (winner_black) { std::cout << std::setw(35) << "Black team wins!" << std::endl; }
		else { std::cout << std::setw(35) << "No winnders this time!" << std::endl; }

		gameRecap(&b.getPlayer1(), &b.getPlayer2());

		std::cout << std::endl << std::endl << std::endl;
		std::cout << "**********************************************************" << std::endl;
		std::cout << "************** Thank you for playing chess ***************" << std::endl;
		std::cout << "**********************************************************" << std::endl;
		std::cout << std::endl << std::endl << std::endl;

	}

}
