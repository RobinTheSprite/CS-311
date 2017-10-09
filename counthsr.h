/*
counthsr.h
Mark Underwood
10.4.17
Contains declarations of functions for the Holey Spider Runs problem.
*/

#ifndef FILE_SPIDERRUNS_H_INCLUDED
#define FILE_SPIDERRUNS_H_INCLUDED

#include <deque>
using std::deque;

size_t countHSR(int,int,
			    int,int,
			    int,int,
			    int,int);

class Board
{
public:
	Board(int x, int y);
	bool & operator()(int x, int y);
	size_t width() const;
	size_t height() const;
	int finishx() const;
	int finishy() const;
	size_t & numOfSolutions();
	bool allOnes();
	void print();
	Board & operator=(const Board & lhs) = default;
private:
	deque<deque<bool>> _board;
	size_t _width;
	size_t _height;
	size_t _numOfSolutions;
};

#endif // !FILE_SPIDERRUNS_H_INCLUDED