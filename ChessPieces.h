// Pieces.h
// A header file that contains an abstract base class for a generic chess piece, and derived classes for each chess piece
// Elliot Goodwin
// 10/05/2019

// C++ STL includes
#include <iostream>
// Headers for a game of chess
#include "ChessBoard.h"
#include "ChessPlayers.h"

#ifndef Pieces_h
#define Pieces_h

// Group code in namespace "Chess"
namespace Chess {

	// Forward declarations of Board and Player classes (for use with allowedMove) 
	class Board;
	class Player;

	// Abstract base class for pieces
	class Piece {
	public:
		virtual ~Piece() {};

		// Virtual functions to show the piece identifier
		virtual void Show() = 0;
		// Get the piece identifier
		virtual char getKey() = 0;
		// Get allowed moves for each piece
		virtual bool allowedMove(Board *board, Player *player, int x_1, int y_1, int x_2, int y_2) = 0;
	};

	// NullPiece 
	class NullPiece : public Piece {
	private:
		char key = '0';

	public:
		// Constructors
		NullPiece();
		NullPiece(NullPiece &p);
		NullPiece(NullPiece &&p);
		NullPiece &operator=(NullPiece &p);
		NullPiece &operator=(NullPiece &&p);

		// Destructor
		~NullPiece();

		// Virtual function overrides
		void Show();
		char getKey();
		bool allowedMove(Board *board, Player *player, int x_1, int y_1, int x_2, int y_2);
	};

	// All other Pieces are defined analogously
	class Pawn : public Piece {
	private:
		char key = 'P';

	public:
		Pawn();
		Pawn(Pawn &p);
		Pawn(Pawn &&p);
		Pawn &operator=(Pawn &p);
		Pawn &operator=(Pawn &&p);
		
		~Pawn();

		void Show();
		char getKey();
		bool allowedMove(Board *board, Player *player, int x_1, int y_1, int x_2, int y_2);
	};

	class Castle : public Piece {
	private:
		char key = 'C';

	public:
		Castle();
		Castle(Castle &p);
		Castle(Castle &&p);
		Castle &operator=(Castle &p);
		Castle &operator=(Castle &&p);

		~Castle();

		void Show();
		char getKey();
		bool allowedMove(Board *board, Player *player, int x_1, int y_1, int x_2, int y_2);
	};

	class Bishop : public Piece {
	private:
		char key = 'B';

	public:
		Bishop();
		Bishop(Bishop &p);
		Bishop(Bishop &&p);
		Bishop &operator=(Bishop &p);
		Bishop &operator=(Bishop &&p);

		~Bishop();

		void Show();
		char getKey();
		bool allowedMove(Board *board, Player *player, int x_1, int y_1, int x_2, int y_2);
	};

	class Knight : public Piece {
	private:
		char key = 'N';

	public:
		Knight();
		Knight(Knight &p);
		Knight(Knight &&p);
		Knight &operator=(Knight &p);
		Knight &operator=(Knight &&p);

		~Knight();

		void Show();
		char getKey();
		bool allowedMove(Board *board, Player *player, int x_1, int y_1, int x_2, int y_2);
	};

	class Queen : public Piece {
	private:
		char key = 'Q';

	public:
		Queen();
		Queen(Queen &p);
		Queen(Queen &&p);
		Queen &operator=(Queen &p);
		Queen &operator=(Queen &&p);

		~Queen();

		void Show();
		char getKey();
		bool allowedMove(Board *board, Player *player, int x_1, int y_1, int x_2, int y_2);
	};

	class King : public Piece {
	private:
		char key = 'K';

	public:
		King();
		King(King &p);
		King(King &&p);
		King &operator=(King &p);
		King &operator=(King &&p);

		~King();

		void Show();
		char getKey();
		bool allowedMove(Board *board, Player *player, int x_1, int y_1, int x_2, int y_2);
	};

}

#endif
