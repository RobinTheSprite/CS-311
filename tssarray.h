/*
tssarray.h
Mark Underwood
10.19.17
Contains declarations and definitions for TSSArray class
*/
#ifndef FILE_TSSARRAY_H_INCLUDED
#define FILE_TSSARRAY_H_INCLUDED
#include <algorithm>

//TSSArray
//"Smart array" class that knows its size and can have elements added or removed.
//Requirements on Types:
//	-All elements in the array are of type dataType.
//Class Invariants:
//	-The class object owns a pointer of type dataType*, which points to a dynamically allocated array of type dataType.
//	-The size of the array is recorded in a size_type variable _size.
//	-The capacity of the array is >= 16 and is recorded in a size_type variable _capacity.
//	-Any object declared as "const TSSArray" is not modified in any way.
template <typename dataType>
class TSSArray
{
public:	//Member Types and Constants
	using size_type = size_t; 
	using value_type = dataType;
	using iterator = value_type *;
	using const_iterator = const value_type *;

	const static size_type minimumCapacity = 16;
public:

	/**********Constructors***********/

	//Default Ctor and One-Param Ctor
	//Strong Guarantee
	//Exception-neutral
	explicit TSSArray(size_type size = 0)
		: _capacity(std::max((size * 2), minimumCapacity)),
		_size(size),
		_data(new value_type[_capacity])
	{}

	//Dtor
	//No-Throw Guarantee
	//Exception-neutral
	~TSSArray()
	{
		delete [] _data;
	}

	//Copy Constructor
	//Strong Guarantee
	//Exception-neutral
	TSSArray(const TSSArray & toBeCopied)
		: _capacity(toBeCopied._capacity),
		  _size(toBeCopied._size),
		  _data(new value_type [_capacity])
	{
		try
		{
			std::copy(toBeCopied.begin(), toBeCopied.end(), begin());
		}
		catch (...)
		{
			delete[] _data;
			throw;
		}
	}

	//Move Constructor
	//No-Throw Guarantee
	//Exception-neutral
	TSSArray(TSSArray && toBeCopied) noexcept
	{
		swap(toBeCopied);
		toBeCopied._data = nullptr;
		toBeCopied._size = 0;
		toBeCopied._capacity = 0;
	}

	/**********Misc. "Get" Functions***********/

	//size
	//No-Throw Guarantee
	//Exception-neutral
	size_type size() const noexcept
	{
		return _size;
	}

	//begin (non-const)
	//No-Throw Guarantee
	//Exception-neutral
	value_type * begin() noexcept
	{
		return _data;
	}

	//begin (const)
	//No-Throw Guarantee
	//Exception-neutral
	const value_type * begin() const noexcept
	{
		return _data;
	}

	//end (non-const)
	//No-Throw Guarantee
	//Exception-neutral
	value_type * end() noexcept
	{
		return (begin() + _size);
	}

	//end (const)
	//No-Throw Guarantee
	//Exception-neutral
	const value_type * end() const noexcept
	{
		return (begin() + _size);
	}

	//empty
	//No-Throw Guarantee
	//Exception-neutral
	bool empty() const noexcept
	{
		return _size == 0;
	}

	/**********Modifying Functions***********/

	//swap
	//No-Throw Guarantee
	//Exception-neutral
	void swap(TSSArray & other) noexcept
	{
		std::swap(_data, other._data);
		std::swap(_size, other._size);
		std::swap(_capacity, other._capacity);
	}

	//resize
	//Strong Guarantee
	//Exception-neutral
	void resize(size_type newsize)
	{
		if (newsize > _capacity)
		{
			TSSArray newArray(newsize);
			try
			{
				std::copy(begin(), end(), newArray.begin());
			}
			catch (...)
			{
				throw;
			}

			*this = newArray;
		}
		else
		{
			_size = newsize;
		}
	}

	//insert
	//Pre: insertLoc >= begin() and <= end()
	//Strong Guarantee
	//Exception-neutral
	iterator insert(iterator insertLoc, value_type item)
	{
		size_type distance = end() - insertLoc;
		resize(_size + 1);
		insertLoc = end() - distance - 1; 

		for (iterator i = (end()-1); i > insertLoc; --i)
		{
			*i = *(i - 1);
		}
		*insertLoc = item;

		return insertLoc;
	}

	//erase
	//Pre: eraseLoc >= begin() and < end()
	//Strong Guarantee
	//Exception-neutral
	iterator erase(iterator eraseLoc)
	{
		for (iterator i = eraseLoc; i < end(); ++i)
		{
			*i = *(i + 1);
		}
		resize(_size - 1);
		return eraseLoc;
	}

	//push_back
	//Strong Guarantee
	//Exception-neutral
	void push_back(value_type item)
	{
		insert(end(), item);
	}

	//pop_back
	//Strong Guarantee
	//Exception-neutral
	void pop_back()
	{
		erase(end() - 1);
	}

	/**********Member Operators***********/

	//op= (Copy)
	//Strong Guarantee
	//Exception-neutral
	TSSArray & operator=(const TSSArray & lhs)
	{
		TSSArray tempLhs(lhs);
		swap(tempLhs);
		return *this;
	}

	//op= (Move)
	//Pre: rValueTrash must be an rvalue.
	//No-Throw Guarantee
	//Exception-neutral
	TSSArray & operator=(TSSArray && rValueTrash) noexcept
	{
		swap(rValueTrash);
		return *this;
	}

	//op[] (non-const)
	//Pre: index >= 0 and < size
	//No-Throw Guarantee
	//Exception-neutral
	value_type & operator[](size_type index) noexcept
	{
		return _data[index];
	}

	//op[] (const)
	//Pre: index >= 0 and < size
	//No-Throw Guarantee
	//Exception-neutral
	const value_type & operator[](size_type index) const noexcept
	{
		return _data[index];
	}

private:
	
	size_type _capacity;
	size_type _size;
	value_type * _data;
	

}; //End class TSSarray

#endif // !FILE_TSSARRAY_H_INCLUDED
