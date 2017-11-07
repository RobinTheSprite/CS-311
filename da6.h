/*
da6.h
Mark Underwood
11.6.17
Contains implementations for assn. 6 exercises
*/

#ifndef FILE_DA6_H_INCLUDED
#define FILE_DA6_H_INCLUDED

#include <memory>
#include <functional>
#include <iostream>
#include "llnode2.h"

template <typename dataType>
void reverseList(std::shared_ptr<LLNode2<dataType>> & head)
{
	std::shared_ptr<LLNode2<dataType>> backwardsHead;
	while (head)
	{
		auto savedNext = head->_next;
		head->_next = backwardsHead;
		backwardsHead = head;
		head = savedNext;
	}
	head = backwardsHead;
}

template <typename firstType, typename secondType>
class LLMap
{
public:

	bool empty() const
	{
		return isEmpty(_data);
	}

	int size() const
	{
		//Code copied from Glenn Chappell's da6.h

		auto p = _data;  // Iterates through list
		size_t n = 0;   // Number of nodes so far
		while (p)
		{
			p = p->_next;
			++n;
		}
		return n;
	}

	secondType * find(firstType key)
	{
		return nullptr;
	}

	const secondType * find(firstType key) const
	{
		return nullptr;
	}

	void insert(firstType, secondType)
	{

	}

	void erase(firstType)
	{

	}

	void traverse(std::function<void(firstType,secondType)> lambda)
	{

	}

private:
	shared_ptr<LLNode2<std::pair<firstType, secondType>>> _data;
};

#endif // !FILE_DA6_H_INCLUDED
