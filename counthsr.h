/*
counthsr.h
Mark Underwood
10.4.17
Contains declarations of functions for the Holey Spider Runs problem.
*/

#ifndef FILE_SPIDERRUNS_H_INCLUDED
#define FILE_SPIDERRUNS_H_INCLUDED

#include <vector>
using std::vector;
#include <cstring>
using std::size_t;

//countHSR
//counts the number of different routes a "spider" can make on a game 
//	board with a start and finish position, without visiting the same
//	square twice or falling in the "hole," which is also in place on the board.
//Pre: All arguments must be >= 0.
int countHSR(int,int,
			 int,int,
			 int,int,
			 int,int);

//Board
//Stores the state of a particular board for the countHSR function.
//Invariants:
//	-A vector of vectors of ints representing the board must have a size greater than zero.
//	-Private member variables representing the board's width and height must be > 0 and be two less than the 
//	 corresponding sizes of _board.
//	-Private member variables representing the finish position of the spider from the countHSR function
//	 must be one greater than those passed to countHSR.
//  -_squaresLeft >= 0.
class Board
{
public:

	//Board (four-param constructor)
	//Create a game board of a given size, with a given finish position marked.
	//Pre: All parameters must be > 0. The finish position must be within the bounds of the board.
	//Does not throw
	Board::Board(int x, int y, int finishx, int finishy);

	//op()
	//Return the state of a specific space on the board.
	//Pre: Arguments must be within the bounds of _board.
	//Could throw an access violation if preconditions are not obeyed.
	int & operator()(int x, int y);

	//op=
	//Sets one board equal to another.
	//Does not throw.
	Board & operator=(const Board & lhs) = default;

	//width
	//Gets the width of the board.
	//Does not throw.
	size_t width() const;

	//height
	//Gets the height of the board.
	//Does not throw.
	size_t height() const;

	//finishx
	//Gets the x position of the finish space on the board.
	//Does not throw.
	int finishx() const;

	//finishy
	//Gets the y position of the finish space on the board.
	//Does not throw.
	int finishy() const;

private:
	vector<vector<int>> _board;
	size_t _width;
	size_t _height;
	int _finishx;
	int _finishy;
	int _squaresLeft;
};

#endif // !FILE_SPIDERRUNS_H_INCLUDED