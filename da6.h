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

template <typename dataType>
void reverseList(std::shared_ptr<dataType>);

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
		return size();
	}

	secondType * find(firstType key)
	{
		return nullptr;
	}

	secondType * find(firstType key) const
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
