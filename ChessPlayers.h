// ChessPlayers.h
// A header file that contains the types of players in the game (human or computer)
// Elliot Goodwin - 9621958
// 10/05/2019

// C++ STL includes
#include <vector>

#ifndef ChessPlayers_h
#define ChessPlayers_h

// Chess includes
#include "ChessPieces.h"

// Group code in namespace "Chess"
namespace Chess {

	// Define player class
	class Player {
	// Protected members (accessible to derived classes)
	protected:
		Piece **player_pieces;  // Array of pointers to piece base class
		std::string colour;     // Team colour
		char type;              // Character identifying human or computer player
		std::vector<std::string> played_moves;    // Vector containing all played moves
		std::vector<std::string> available_moves; // Vector containing all available moves

	// Public members
	public:
		Player();                 // Default constructor
		Player(std::string c);    // Parameterised constructor (takes tema colour as string input "white" or "black")

		// Move and copy constructors and assignment operators
		Player(Player&);
		Player(Player&&);
		Player& operator= (Player&);
		Player& operator= (Player&&);
		 
		virtual ~Player();             // Virtual destructor

		// Virtual access functions
		virtual void Show(); // Show player information (for printing with board) 
		virtual Piece &getPlayerPiece(int p);   // Get element p of player piece array
		virtual std::string &getPlayerColour(); // Get string identidying team colour
		virtual char &getPlayerType();          // Get character identifying type of player 'H'uman or 'C'omputer

		// Vector containing all played moves
		virtual std::vector<std::string> getPlayedMoves();
		virtual void addPlayedMove(std::string player_move);

		// Vector containing all available moves
		virtual std::vector<std::string> getAvailableMoves();
		virtual void addAvailableMove(std::string player_move);

	};

	// Derived human class
	class Human : public Player {
	private:
		char type = 'H';

	public:
		Human();
		Human(std::string c);
		~Human();

		// Over-ride virtual functions
		void Show();
		Piece &getPlayerPiece(int p);
		char &getPlayerType();
	};

	// Derived computer class
	class Computer : public Player {
	public:
		Computer();
		Computer(std::string c);
		~Computer();

		// Over-ride virtual functions
		void Show();
		Piece &getPlayerPiece(int p);
		char &getPlayerType();
	};
}
#endif


