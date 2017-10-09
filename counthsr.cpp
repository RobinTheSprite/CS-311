/*
counthsr.cpp
Mark Underwood
10.4.17
Contains definitions of functions for Holey Spider Runs problem.
*/

#include "counthsr.h"
#include <iostream>
using std::cout;
using std::endl;
#include <algorithm>
#include <deque>
using std::deque;
#include <unordered_map>

using boardType = deque<deque<bool>>;

Board::Board(int x, int y)
{
	_width = x;
	_height = y;
	_numOfSolutions = 0;
	boardType board((x + 2), deque<bool>(y + 2));
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
	return _board[x][y];
}

size_t Board::width() const
{
	return _width;
}

size_t Board::height() const
{
	return _height;
}

size_t & Board::numOfSolutions()
{
	return _numOfSolutions;
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

bool Board::allOnes()
{
	size_t rowsFullOfOnes = 0;
	for (auto row : _board)
	{
		if (std::find(row.begin(), row.end(), 0) == row.end())
		{
			++rowsFullOfOnes;
		}
	}
	return rowsFullOfOnes == _board.size();
}

void pickADirection(Board & board, std::pair<int, int> spider)
{
	std::deque<std::pair<int, int>> allPossibleDirections =
	{	std::make_pair(spider.first, spider.second + 1),
		std::make_pair(spider.first, spider.second - 1),

		std::make_pair(spider.first + 1, spider.second),
		std::make_pair(spider.first - 1, spider.second),

		std::make_pair(spider.first + 1, spider.second + 1),
		std::make_pair(spider.first - 1, spider.second - 1),

		std::make_pair(spider.first - 1, spider.second + 1),
		std::make_pair(spider.first + 1, spider.second - 1) };

	//if (board(spider.first, spider.second + 1) == 0)
	//{ }
	//
	//if (board(spider.first, spider.second - 1) == 0)
	//{ }
	//
	//if (board(spider.first + 1, spider.second) == 0)
	//{ }
	//
	//if (board(spider.first - 1, spider.second) == 0)
	//{ }
	//
	//if (board(spider.first + 1, spider.second + 1) == 0)
	//{ }
	//
	//if (board(spider.first - 1, spider.second - 1) == 0)
	//{ }
	//
	//if (board(spider.first - 1, spider.second + 1) == 0)
	//{ }
	//
	//if (board(spider.first + 1, spider.second - 1) == 0)
	//{ }
}



size_t countHSR_recurse(Board & board, 
						const int & finishx, const int & finishy, 
						std::pair<int, int> & spider)
{
	board.print();
	cout << endl;

	//Base Case
	if ((spider.first == finishx) && (spider.second == finishy) && board.allOnes())
	{
		return 1;
	} //Recursive Cases

	std::deque<std::pair<int, int>> allPossibleDirections =
	{ std::make_pair(spider.first, spider.second + 1),
		std::make_pair(spider.first, spider.second - 1),

		std::make_pair(spider.first + 1, spider.second),
		std::make_pair(spider.first - 1, spider.second),

		std::make_pair(spider.first + 1, spider.second + 1),
		std::make_pair(spider.first - 1, spider.second - 1),

		std::make_pair(spider.first - 1, spider.second + 1),
		std::make_pair(spider.first + 1, spider.second - 1) };

	int numOfSols = 0;
	//std::pair<int, int> savedSpiderLoc = spider;

	for (auto pair : allPossibleDirections)
	{
		if (board(pair.first, pair.second) == 0)
		{
			std::pair<int, int> savedSpiderLoc = spider;
			spider = pair;
			board(spider.first, spider.second) = 1;
			numOfSols += countHSR_recurse(board, finishx, finishy, spider);
			board(spider.first, spider.second) = 0;
			spider = savedSpiderLoc;
		}
	}

	return numOfSols;
}

size_t countHSR(int sizex, int sizey, 
				int holex, int holey, 
				int startx, int starty, 
				int finishx, int finishy)
				
{	
	static int count = 0;
	Board board(sizex, sizey);
	++finishx;
	++finishy;
	++holex;
	++holey;
	++startx;
	++starty;
	board(holex,holey) = 1;
	
	std::pair<int, int> spider{startx, starty};
	board(spider.first, spider.second) = 1;
	cout << "New one " << ++count << endl;
	cout << endl;

	return countHSR_recurse(board, finishx, finishy, spider);
}








//int main()
//{
//
//	Board board(1,3);
//	board.print();
//	std::cout << std::endl;
//	board.print();
//	std::cout << std::endl;
//
//	while(std::cin.get() != '\n')
//
//	return 0;
//}

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


//if (board(spider.first, spider.second + 1) == 0
//	|| board(spider.first, spider.second - 1) == 0
//	|| board(spider.first + 1, spider.second) == 0
//	|| board(spider.first - 1, spider.second) == 0
//	|| board(spider.first + 1, spider.second + 1) == 0
//	|| board(spider.first - 1, spider.second - 1) == 0
//	|| board(spider.first - 1, spider.second + 1) == 0
//	|| board(spider.first + 1, spider.second - 1) == 0)
//{
//	numOfSolutions += countHSR_recurse(board, finishx, finishy, spider = { spider.first + 1, spider.second + 1 });
//}

//size_t countHSR_recurse(Board & board,
//	int finishx, int finishy,
//	std::pair<int, int> spider,
//	size_t squaresLeft)
//{
//	if (0)//board.width() == 8 && board.height() == 2 && finishx == 6 && finishy == 1)
//	{
//		board.print();
//		cout << endl;
//	}
//	//Base Case
//	if ((spider.first == finishx) && (spider.second == finishy) && board.allOnes())
//	{
//		return 1;
//	} //Recursive Cases
//
//	int numOfSols = 0;
//	std::pair<int, int> savedSpiderLoc = spider;
//
//	if (board(spider.first, spider.second + 1) == 0)
//	{
//		spider = { spider.first, spider.second + 1 };
//		board(spider.first, spider.second) = 1;
//		numOfSols += countHSR_recurse(board, finishx, finishy, spider, squaresLeft);
//		board(spider.first, spider.second) = 0;
//		spider = savedSpiderLoc;
//	}
//
//	if (board(spider.first, spider.second - 1) == 0)
//	{
//		spider = { spider.first, spider.second - 1 };
//		board(spider.first, spider.second) = 1;
//		numOfSols += countHSR_recurse(board, finishx, finishy, spider, squaresLeft);
//		board(spider.first, spider.second) = 0;
//		spider = savedSpiderLoc;
//	}
//
//	if (board(spider.first + 1, spider.second) == 0)
//	{
//		spider = { spider.first + 1, spider.second };
//		numOfSols += countHSR_recurse(board, finishx, finishy, spider, squaresLeft);
//		//board(spider.first, spider.second) = 0;
//		spider = savedSpiderLoc;
//	}
//
//	if (board(spider.first - 1, spider.second) == 0)
//	{
//		spider = { spider.first - 1, spider.second };
//		numOfSols += countHSR_recurse(board, finishx, finishy, spider, squaresLeft);
//		//board(spider.first, spider.second) = 0;
//		spider = savedSpiderLoc;
//	}
//
//	if (board(spider.first + 1, spider.second + 1) == 0)
//	{
//		spider = { spider.first + 1, spider.second + 1 };
//		numOfSols += countHSR_recurse(board, finishx, finishy, spider, squaresLeft);
//		board(spider.first, spider.second) = 0;
//		spider = savedSpiderLoc;
//	}
//
//	if (board(spider.first - 1, spider.second - 1) == 0)
//	{
//		spider = { spider.first - 1, spider.second - 1 };
//		numOfSols += countHSR_recurse(board, finishx, finishy, spider, squaresLeft);
//		board(spider.first, spider.second) = 0;
//		spider = savedSpiderLoc;
//	}
//
//	if (board(spider.first - 1, spider.second + 1) == 0)
//	{
//		spider = { spider.first - 1, spider.second + 1 };
//		numOfSols += countHSR_recurse(board, finishx, finishy, spider, squaresLeft);
//		board(spider.first, spider.second) = 0;
//		spider = savedSpiderLoc;
//	}
//
//	if (board(spider.first + 1, spider.second - 1) == 0)
//	{
//		spider = { spider.first + 1, spider.second - 1 };
//		numOfSols += countHSR_recurse(board, finishx, finishy, spider, squaresLeft);
//		board(spider.first, spider.second) = 0;
//		spider = savedSpiderLoc;
//	}
//
//	//board(spider.first, spider.second) = 0;
//	//spider = savedSpiderLoc;
//
//	return numOfSols;
//}



