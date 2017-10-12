/*
counthsr.cpp
Mark Underwood
10.4.17
Contains definitions of functions for Holey Spider Runs problem,
as well as definitions for Board class.
*/

#include "counthsr.h"
#include <algorithm>
#include <vector>
using std::vector;
#include <cstring>
using std::size_t;

using boardType = vector<vector<int>>;

//Board (4-param constructor)
//Docs in counthsr.h
Board::Board(int x, int y, int finishx, int finishy)
{
	_width = x;
	_height = y;
	_finishx = finishx;
	_finishy = finishy;
	boardType board((y + 2), vector<int>(x + 2));
	for (size_t col = 0; col < board.size(); ++col)
	{
		for (size_t row = 0; row < board[col].size(); ++row)
		{
			if (col == 0 || col == (board.size() - 1))
			{
				board[col][row] = 1;
			}
			else
			{
				board[col][0] = 1;
				board[col][board[col].size() - 1] = 1;
			}
		}
	}
	_board = board;
}

//op()
//Docs in counthsr.h
int & Board::operator()(int x, int y)
{
	return _board[y][x];
}

//width
//Docs in counthsr.h
size_t Board::width() const
{
	return _width;
}

//height
//Docs in counthsr.h
size_t Board::height() const
{
	return _height;
}

//finishx
//Docs in counthsr.h
int Board::finishx() const
{
	return _finishx;
}

//finishy
//Docs in counthsr.h
int Board::finishy() const
{
	return _finishy;
}

//countHSR_recurse
//Finds how many "Holey Spider Runs" can be made with a given board.
//Pre: Spider is within the bounds of the board.
int countHSR_recurse(Board & board,  
					std::pair<int, int> & spider,
					int & squaresLeft)
{
	//Base Case
	if ((spider.first == board.finishx()) && (spider.second == board.finishy()) && squaresLeft == 0)
	{
		return 1;
	} 
	
	//Recursive Case

	//Define all the possible directions that spider could go from any given square.
	std::vector<std::pair<int, int>> allPossibleDirections =
	{	std::make_pair(spider.first, spider.second + 1),
		std::make_pair(spider.first, spider.second - 1),

		std::make_pair(spider.first + 1, spider.second),
		std::make_pair(spider.first - 1, spider.second),

		std::make_pair(spider.first + 1, spider.second + 1),
		std::make_pair(spider.first - 1, spider.second - 1),

		std::make_pair(spider.first - 1, spider.second + 1),
		std::make_pair(spider.first + 1, spider.second - 1) };

	int numOfSols = 0;

	for (auto currentPair : allPossibleDirections)
	{
		//Can the spider move to the current position on the board?
		if (board(currentPair.first, currentPair.second) == 0)
		{
			//Save the previous location of the spider, move it, and decrement the number of squares left.
			auto savedSpiderLoc = spider;
			spider = currentPair;
			board(spider.first, spider.second) = 1;
			--squaresLeft;
				
			numOfSols += countHSR_recurse(board, spider, squaresLeft); //Recurse!
			
			//Undo the changes made before the recursive call.
			++squaresLeft;
			board(spider.first, spider.second) = 0;
			spider = savedSpiderLoc;
		}
	}

	return numOfSols;
}

//countHSR
//Docs in counthsr.h
int countHSR(int sizex, int sizey, 
			 int holex, int holey, 
			 int startx, int starty, 
			 int finishx, int finishy)			
{	
	//Switch all values to 1-based coordinates.
	++finishx;
	++finishy;
	++holex;
	++holey;
	++startx;
	++starty;

	Board board(sizex, sizey, finishx, finishy);

	board(holex,holey) = 1;
	std::pair<int, int> spider{startx, starty};
	board(spider.first, spider.second) = 1;
	int squaresLeft = (board.width() * board.height()) - 2;

	return countHSR_recurse(board, spider, squaresLeft);
}


