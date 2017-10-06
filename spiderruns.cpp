/*
spiderruns.cpp
Mark Underwood
10.4.17
Contains definitions of functions for Holey Spider Runs problem.
*/

#include "spiderruns.h"
#include <iostream>
#include <vector>
using std::vector;

using boardType = vector<vector<bool>>;

Board::Board(int x, int y)
{
	_width = x;
	_height = y;
	boardType board((y + 2), vector<bool>(x + 2));
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
	return _board[x + 1][y + 1];
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

size_t countHSR_recurse(Board board, int finishx, int finishy, std::pair<int, int> spider)
{
	//Setup
	static size_t squaresLeft = (board.width() * board.height()) - 2;
	static size_t numOfSolutions = 0;
	//Base Case
	if (squaresLeft == 0 && spider.first == finishx && spider.second == finishy)
	{
		return numOfSolutions;
	}

	//Recursive case(s)
	if (0)
	{

	}
}

size_t countHSR(int sizex, int sizey, int holex, int holey, int startx, int starty, int finishx, int finishy)
{
	Board board(sizex, sizey);

	board(holex + 1,holey + 1) = 1;
	//board[startx + 1][holey + 1] = 1;

	std::pair<int, int> spider{startx, starty};
	return countHSR_recurse(board, finishx, finishy, spider);
}

int main()
{

	Board board(4, 4);
	board.print();
	board(3, 2) = 1;
	std::cout << std::endl;
	board.print();

	while (std::cin.get() != '\n')

	return 0;
}