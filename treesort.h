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

namespace //Attempt to restrict use of these functions to just this file
{

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

	template<typename dataType>
	static std::shared_ptr<Treenode<dataType>> retrieve(dataType item, std::shared_ptr<Treenode<dataType>> & node)
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

	template<typename dataType>
	void insert(dataType item, std::shared_ptr<Treenode<dataType>> & node)
	{
		if (!node)
		{
			node = std::make_shared<Treenode<dataType>>(item, nullptr, nullptr);
			return;
		}

		auto parent = retrieve(item, node);
		if (parent)
		{
			if (!parent->_left && (item < parent->_data))
			{
				parent->_left = std::make_shared<Treenode<dataType>>(item, nullptr, nullptr);
			}
			else if (!parent->_right && !(item < parent->_data))
			{
				parent->_right = std::make_shared<Treenode<dataType>>(item, nullptr, nullptr);
			}
		}
	}

	template<typename dataType>
	void remove(std::shared_ptr<Treenode<dataType>> & node)
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

		remove(node);
	}
}

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
