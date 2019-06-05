// ChessPlayers.cpp
// A .cpp file that contains the types of players in the game (human or computer)
// Elliot Goodwin
// 10/05/2019

// Includes and headers
#include <vector>
#include "ChessPlayers.h"

// Group code in namespace "Chess"
namespace Chess {

	// Default constructor
	Player::Player() {};

	// Parameterised constructor
	Player::Player(std::string c) {

		//std::cout << "Constructing " << c << " team." << std::endl;

		int num_pieces = 16;
		colour = c;
		player_pieces = new Piece*[num_pieces];

		for (int i = 0; i <= 8; i++) { player_pieces[i] = new Pawn(); }
		player_pieces[8] = new Castle();
		player_pieces[9] = new Knight();
		player_pieces[10] = new Bishop();
		player_pieces[11] = new Queen();
		player_pieces[12] = new King();
		player_pieces[13] = new Bishop();
		player_pieces[14] = new Knight();
		player_pieces[15] = new Castle();
	};

	// Player copy constructor
	Player::Player(Player &p)
	{
		//std::cout << "Calling player copy constructor." << std::endl;
		// initialise a new player
		colour = p.colour;
		player_pieces = 0;
		type = 'P';
		for (int i = 0; i < 16; i++) {
			player_pieces = p.player_pieces;
		}
	}
	// Player move constructor
	Player::Player(Player &&p)
	{
		//std::cout << "Calling player move constructor." << std::endl;
		colour = p.colour;
		player_pieces = p.player_pieces;
		type = p.type;
		p.colour = "null_string";
		p.player_pieces = nullptr;
		p.type = '0';
	}
	// Player copy assignment operator
	Player &Player::operator=(Player &p)
	{
		//std::cout << "Calling player copy assignment operator." << std::endl;
		if (&p == this) { return *this; }

		// Delete this object's members
		//player_pieces = nullptr; player_pieces = 0; colour = "null_string";
		// Copy other object's members
		player_pieces = p.player_pieces;
		colour = p.colour;
		type = p.type;

		return *this;
	}
	// Player move assignment operator
	Player &Player::operator=(Player &&p)
	{
		//std::cout << "Calling player move assignment operator." << std::endl;
		// swap contents of one player with another
		std::swap(colour, p.colour);
		std::swap(player_pieces, p.player_pieces);
		std::swap(type, p.type);
		return *this;
	}

	// Destructor 
	Player::~Player()
	{
		//std::cout << "Destroying " << colour << " team." << std::endl;
		colour = "null_string";
		player_pieces = nullptr;
		type = '0';
	};

	// Show player info (when printing board)
	void Player::Show()
	{
		if (colour == "white" || colour == "White") { std::cout << "W"; }
		else if (colour == "black" || colour == "Black") { std::cout << "B"; }
		else { std::cout << "Unknown player." << std::endl; exit(1); }
	}

	// Access functions
	Piece &Player::getPlayerPiece(int p) { return *player_pieces[p]; }
	std::string &Player::getPlayerColour() { return colour; };
	char &Player::getPlayerType() { return type; };

	// Vector containing all played moves
	std::vector<std::string> Player::getPlayedMoves() { return played_moves; }
	void Player::addPlayedMove(std::string player_move) { played_moves.push_back(player_move); }

	// Vector containing all available moves
	std::vector<std::string> Player::getAvailableMoves() { return available_moves; }
	void Player::addAvailableMove(std::string player_move) { available_moves.push_back(player_move); }



	// Over-rides for human and computer classes
	Human::Human() : Player() { type = 'H'; };
	Human::Human(std::string c) : Player(c) { type = 'H'; };
	Human::~Human() {};

	void Human::Show() { Player::Show(); };
	Piece & Human::getPlayerPiece(int p) { return Player::getPlayerPiece(p); };
	char &Human::getPlayerType() { return type; }


	Computer::Computer() : Player() { type = 'C'; };
	Computer::Computer(std::string c) : Player(c) { type = 'C'; };
	Computer::~Computer() {};

	void Computer::Show() { Player::Show(); };
	Piece &Computer::getPlayerPiece(int p) { return Player::getPlayerPiece(p); };
	char &Computer::getPlayerType() { return type; }
};

