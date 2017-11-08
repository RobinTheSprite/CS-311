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
	LLMap() = default;

	~LLMap() = default;

	bool empty() const
	{
		return isEmpty(_head);
	}

	size_t size() const
	{
		//Code copied from Glenn Chappell's da6.h

		auto p = _head;  // Iterates through list
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
		auto foundKey = findNode(key);
		secondType * foundItem = nullptr;
		if (foundKey != nullptr)
		{
			foundItem = &foundKey->_data.second;
			return foundItem;
		}
		return nullptr;
	}

	const secondType * find(firstType key) const
	{
		auto foundKey = findNode(key);

		return &foundKey->_data.second;
	}

	void insert(firstType key, secondType val)
	{
		auto foundKey = findNode(key);
		if (foundKey == nullptr)
		{
			push_front(_head, std::make_pair(key, val));
		}
		else
		{
			foundKey->_data = std::make_pair(key, val);
		}
	}

	void erase(firstType key)
	{
		auto foundKey = findNode(key);
		if (foundKey != nullptr)
		{
			auto p = _head;
			shared_ptr<LLNode2<std::pair<firstType, secondType>>> oneBack = nullptr;
			while (p)
			{
				if (p->_data.first == key)
				{
					break;
				}
				oneBack = p;
				p = p->_next;
			}

			if (oneBack != nullptr)
			{
				oneBack->_next = p->_next;
			}
			else
			{
				pop_front(_head);
			}
			
			foundKey->_next = nullptr;
		}
	}

	void traverse(std::function<void(firstType,secondType)> lambda)
	{
		auto p = _head;
		while (p)
		{
			lambda(p->_data.first, p->_data.second);
			p = p->_next;
		}
	}

private:
	shared_ptr<LLNode2<std::pair<firstType, secondType>>> findNode(firstType key) const
	{
		auto p = _head;
		while (p)
		{
			if (p->_data.first == key)
			{
				break;
			}
			p = p->_next;
		}

		return p;
	}

	shared_ptr<LLNode2<std::pair<firstType, secondType>>> _head;
};

#endif // !FILE_DA6_H_INCLUDED
