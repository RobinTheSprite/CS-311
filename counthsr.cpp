/*
counthsr.cpp
Mark Underwood
10.4.17
Contains definitions of functions for Holey Spider Runs problem.
*/

#include "counthsr.h"
#include <iostream>
#include <deque>
using std::deque;

using boardType = deque<deque<bool>>;

Board::Board(int x, int y)
{
	_width = x;
	_height = y;
	boardType board((y + 2), deque<bool>(x + 2));
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

bool & Board::operator()(int x, int y)
{
	return _board[y][x];
}

size_t Board::width() const
{
	return _width;
}

size_t Board::height() const
{
	return _height;
}

void Board::print()
{
	for (auto col : _board)
	{
		for (bool row : col)
		{
			std::cout << row;
		}
		std::cout << std::endl;
	}
}

size_t countHSR_recurse(Board & board, int finishx, int finishy, std::pair<int, int> spider)
{
	//Setup
	size_t squaresLeft = (board.width() * board.height()) - 2;
	
	//Base Case
	if (squaresLeft == 0 && spider.first == finishx && spider.second == finishy)
	{
		return 1;
	}

	size_t numOfSolutions = 0;
	--squaresLeft;
	//Recursive case(s)
	if (board(spider.first, spider.second + 1) == 0)
	{
		board(spider.first, spider.second + 1) = 1;
		++spider.second;
	}
	else if (board(spider.first, spider.second - 1) == 0)
	{
		board(spider.first, spider.second - 1) = 1;
		--spider.second;
	}
	else if (board(spider.first + 1, spider.second) == 0)
	{
		board(spider.first + 1, spider.second) = 1;
		++spider.first;
	}
	else if (board(spider.first - 1, spider.second) == 0)
	{
		board(spider.first - 1, spider.second) = 1;
		--spider.first;
	}
	else if (board(spider.first + 1, spider.second + 1) == 0)
	{
		board(spider.first + 1, spider.second + 1) = 1;
		++spider.first;
		++spider.second;
	}
	else if (board(spider.first - 1, spider.second - 1) == 0)
	{
		board(spider.first - 1, spider.second - 1) = 1;
		--spider.first;
		--spider.second;
	}
	else if (board(spider.first - 1, spider.second + 1) == 0)
	{
		board(spider.first - 1, spider.second + 1) = 1;
		--spider.first;
		++spider.second;
	}
	else if (board(spider.first + 1, spider.second - 1) == 0)
	{
		board(spider.first + 1, spider.second - 1) = 1;
		++spider.first;
		--spider.second;
	}
	else
	{
		++squaresLeft;
		return 0;
	}
	numOfSolutions += countHSR_recurse(board, finishx, finishy, spider);
	return numOfSolutions;
}

size_t countHSR(int sizex, int sizey, 
				int holex, int holey, 
				int startx, int starty, 
				int finishx, int finishy)
				
{				
	Board board(sizex, sizey);

	board(holex,holey) = 1;
	
	std::pair<int, int> spider{startx, starty};
	return countHSR_recurse(board, finishx, finishy, spider);
}

int main()
{

	while (std::cin.get() != '\n')

	return 0;
}


//size_t countHSR_recurse(Board & board, int finishx, int finishy, std::pair<int, int> spider)
//{
//	//Setup
//	size_t squaresLeft = (board.width() * board.height()) - 2;
//
//	//Base Case
//	if (squaresLeft == 0 && spider.first == finishx && spider.second == finishy)
//	{
//		return 1;
//	}
//
//	size_t numOfSolutions = 0;
//	--squaresLeft;
//	//Recursive case(s)
//	if (board(spider.first, spider.second + 1) == 0)
//	{
//		board(spider.first, spider.second + 1) = 1;
//		++spider.second;
//	}
//	else if (board(spider.first, spider.second - 1) == 0)
//	{
//		board(spider.first, spider.second - 1) = 1;
//		--spider.second;
//	}
//	else if (board(spider.first + 1, spider.second) == 0)
//	{
//		board(spider.first + 1, spider.second) = 1;
//		++spider.first;
//	}
//	else if (board(spider.first - 1, spider.second) == 0)
//	{
//		board(spider.first - 1, spider.second) = 1;
//		--spider.first;
//	}
//	else if (board(spider.first + 1, spider.second + 1) == 0)
//	{
//		board(spider.first + 1, spider.second + 1) = 1;
//		++spider.first;
//		++spider.second;
//	}
//	else if (board(spider.first - 1, spider.second - 1) == 0)
//	{
//		board(spider.first - 1, spider.second - 1) = 1;
//		--spider.first;
//		--spider.second;
//	}
//	else if (board(spider.first - 1, spider.second + 1) == 0)
//	{
//		board(spider.first - 1, spider.second + 1) = 1;
//		--spider.first;
//		++spider.second;
//	}
//	else if (board(spider.first + 1, spider.second - 1) == 0)
//	{
//		board(spider.first + 1, spider.second - 1) = 1;
//		++spider.first;
//		--spider.second;
//	}
//	else
//	{
//		++squaresLeft;
//		return 0;
//	}
//	numOfSolutions += countHSR_recurse(board, finishx, finishy, spider);
//	return numOfSolutions;
//}