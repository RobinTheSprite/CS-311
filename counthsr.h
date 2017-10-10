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

int countHSR(int,int,
			    int,int,
			    int,int,
			    int,int);

class Board
{
public:
	Board::Board(int x, int y, int finishx, int finishy);
	int & operator()(int x, int y);
	size_t width() const;
	size_t height() const;
	int finishx() const;
	int finishy() const;
	Board & operator=(const Board & lhs) = default;
private:
	vector<vector<int>> _board;
	size_t _width;
	size_t _height;
	int _finishx;
	int _finishy;
	int _squaresLeft;
};

#endif // !FILE_SPIDERRUNS_H_INCLUDED