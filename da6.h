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
#include "llnode2.h"

//***TODO: Check what can throw in everything

//reverseList
//Requirements on Types
// -TODO
//No Throw Guarantee
//Exception Neutral
template <typename dataType>
void reverseList(std::shared_ptr<LLNode2<dataType>> & head) noexcept
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

//LLMap
//Invariants
// -TODO
//Requirements on Types
// -TODO
template <typename firstType, typename secondType>
class LLMap
{
public:
	//Deflault Functions
	LLMap() = default;
	~LLMap() = default;

	//Deleted Functions
	LLMap(const LLMap &) = delete;
	LLMap(const LLMap &&) = delete;
	LLMap & operator=(const LLMap &) = delete;
	LLMap & operator=(const LLMap &&) = delete;

	/*==============================================*/
	/*             Misc. Member Functions			*/
	/*==============================================*/

	//empty
	//No Throw Guarantee
	//Exception Neutral
	bool empty() const
	{
		return isEmpty(_head);
	}

	//size
	//No Throw Guarantee
	//Exception Neutral
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

	//find (non-const)
	//Strong Guarantee
	//Exception Neutral
	secondType * find(firstType key)
	{
		auto foundKey = findNode(key);
		if (foundKey != nullptr)
		{
			return &foundKey->_data.second;
		}
		return nullptr;
	}

	//find (const)
	//Strong Guarantee
	//Exception Neutral
	const secondType * find(firstType key) const
	{
		auto foundKey = findNode(key);
		if (foundKey != nullptr)
		{
			return &foundKey->_data.second;
		}
		return nullptr;
	}

	//insert
	//Strong Guarantee
	//Exception Neutral
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

	//erase
	//Strong Guarantee
	//Exception Neutral
	void erase(firstType key)
	{
		auto foundKey = findNode(key);
		if (foundKey != nullptr)
		{
			auto p = _head;
			ptrType oneBack = nullptr;
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

	//traverse
	//Strong Guarantee
	//Exception Neutral
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
	//Useful shorthand for any pointer to the LLMap
	using ptrType = shared_ptr<LLNode2<std::pair<firstType, secondType>>>;

	//findNode
	//Strong Guarantee
	//Exception Neutral
	ptrType findNode(firstType key) const
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

	ptrType _head;
};

#endif // !FILE_DA6_H_INCLUDED
