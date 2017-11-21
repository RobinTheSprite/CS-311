/*
treesort.h
Mark Underwood
11.15.17
Contains definitions for treesort algorithm
*/

#ifndef FILE_TREESORT_H_INCLUDED
#define FILE_TREESORT_H_INCLUDED

#include <memory>
#include <algorithm>
#include <iterator>
#include <exception>
#include <iostream>

namespace //Attempt to restrict use of these functions to just this file
{
	//Treenode
	//Requirements on Types
	//	-dataType dctor must not throw
	//Invariants
	//	-_left points either to the next left node on a binary search tree or nullptr
	//	-_right points either to the next right node on a binary search tree or nullptr
	//	-_data holds an item of type dataType
	template<typename dataType>
	struct Treenode
	{
		Treenode() = default;
		Treenode(dataType data, std::shared_ptr<Treenode<dataType>> left, std::shared_ptr<Treenode<dataType>> right)
			: _data(data), _left(left), _right(right) {}

		~Treenode() = default;
		Treenode(const Treenode &) = delete;
		Treenode(const Treenode &&) = delete;
		Treenode & operator=(const Treenode &) = delete;
		Treenode & operator=(const Treenode &&) = delete;

		std::shared_ptr<Treenode<dataType>> _left;
		std::shared_ptr<Treenode<dataType>> _right;
		dataType _data;
	};

	//retrieve
	//Requirements on Types
	//	-dataType dctor must not throw
	//Exception Neutral
	template<typename dataType>
	std::shared_ptr<Treenode<dataType>> retrieve(dataType item, std::shared_ptr<Treenode<dataType>> & node)
	{
		if (!node->_left && !node->_right)
		{
			return node;
		}

		if (item < node->_data)
		{
			if (!node->_left)
			{
				return node;
			}
			return retrieve(item, node->_left);
		}
		else if (!(item < node->_data))
		{
			if (!node->_right)
			{
				return node;
			}
			return retrieve(item, node->_right);
		}
	}

	//insert
	//Requrirements on Types
	//	-dataType must have a copy ctor
	//	-dataType dctor must not throw
	//Exception Neutral
	//std::make_shared may throw std::bad_alloc
	template<typename dataType>
	void insert(dataType item, std::shared_ptr<Treenode<dataType>> & node)
	{
		if (!node)
		{
			try
			{
				node = std::make_shared<Treenode<dataType>>(item, nullptr, nullptr);
			}
			catch (std::bad_alloc & e)
			{
				node = nullptr;
				std::cout << e.what() << std::endl;
			}
			
			return;
		}

		auto parent = retrieve(item, node);
		if (parent)
		{
			if (!parent->_left && (item < parent->_data))
			{
				try
				{
					parent->_left = std::make_shared<Treenode<dataType>>(item, nullptr, nullptr);
				}
				catch (std::bad_alloc & e)
				{
					parent = nullptr;
					std::cout << e.what() << std::endl;
				}
				
			}
			else if (!parent->_right && !(item < parent->_data))
			{
				try
				{
					parent->_right = std::make_shared<Treenode<dataType>>(item, nullptr, nullptr);
				}
				catch (std::bad_alloc & e)
				{
					parent = nullptr;
					std::cout << e.what() << std::endl;
				}
				
			}
		}
	}

	//remove 
	//Requirements on Types
	//	-dataType dctor must not throw
	template<typename dataType>
	void removeNode(std::shared_ptr<Treenode<dataType>> & node)
	{
		if (!node->_left && !node->_right)
		{
			node = nullptr;
		}
		else if (!node->_left && node->_right)
		{
			node = node->_right;
		}
	}

	//fromTree
	//Requirements on Types
	//	-iter must be a pointer or an iterator to a valid location in memory
	//	-dataType dctor must not throw
	template<typename dataType, typename iter>
	void fromTree(iter & writeLocation, std::shared_ptr<Treenode<dataType>> & node)
	{
		if (!node)
		{
			return;
		}

		fromTree(writeLocation, node->_left);
		*writeLocation++ = node->_data;
		fromTree(writeLocation, node->_right);

		removeNode(node);
	}
}

//treesort
//Requirements on Types
//	-iter must be a pointer or an iterator to a valid location in memory
template<typename iter>
void treesort(iter first, iter last)
{
	using dataType = typename std::iterator_traits<iter>::value_type;

	if (std::distance(first, last) == 0 || std::distance(first, last) == 1) //If the range is zero or one item long,
	{																		//it is sorted already. Don't even bother.
		return;
	}

	std::shared_ptr<Treenode<dataType>> root;

	for (iter it = first; it != last; ++it)
	{
		insert(*it, root);
	}

	fromTree(first, root);
}

#endif
