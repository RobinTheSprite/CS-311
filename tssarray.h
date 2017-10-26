/*
tssarray.h
Mark Underwood
10.19.17
Contains declarations and definitions for TSSArray class
*/

#ifndef FILE_TSSARRAY_H_INCLUDED
#define FILE_TSSARRAY_H_INCLUDED

template <typename dataType>
class TSSArray
{
public:
	using size_type = size_t; 
	using value_type = dataType;
	using iterator = value_type *;
	using const_iterator = const value_type *;

	const static size_type minimumCapacity = 16;
public:

	/**********Constructors***********/

	//Default Ctor and One-Param Ctor
	//Strong Guarantee
	explicit TSSArray(size_type size = 0)
		: _capacity(std::max((size * 2), minimumCapacity)),
		_size(size),
		_data(new value_type[_capacity])
	{}

	//Dtor
	//No-Throw
	~TSSArray()
	{
		delete [] _data;
	}

	//Copy Constructor
	//Strong Guarantee
	TSSArray(const TSSArray & toBeCopied)
		: _capacity(toBeCopied._capacity),
		  _size(toBeCopied._size),
		  _data(new value_type [_capacity])
	{
		#pragma warning(disable: 4996)
		std::copy(toBeCopied.begin(), toBeCopied.end(), begin());
	}

	//Move Constructor
	//No-Throw
	TSSArray(TSSArray && toBeCopied) noexcept
	{
		swap(toBeCopied);
		toBeCopied._data = nullptr;
		toBeCopied._size = 0;
	}

	/**********Misc. "Get" Functions***********/

	//size
	//No-Throw
	size_type size() const noexcept
	{
		return _size;
	}

	//begin (non-const)
	//No-Throw 
	value_type * begin() noexcept
	{
		return _data;
	}

	//begin (const)
	//No-Throw 
	const value_type * begin() const noexcept
	{
		return _data;
	}

	//end (non-const)
	//No-Throw
	value_type * end() noexcept
	{
		return (begin() + _size);
	}

	//end (const)
	//No-Throw
	const value_type * end() const noexcept
	{
		return (begin() + _size);
	}

	//empty
	//No-Throw
	bool empty() const noexcept
	{
		return _size == size_type(0);
	}

	/**********Modifying Functions***********/

	//swap
	//No-Throw
	void swap(TSSArray & other) noexcept
	{
		std::swap(_data, other._data);
		std::swap(_size, other._size);
		std::swap(_capacity, other._capacity);
	}

	//resize

	void resize(size_type newsize)
	{
		if (newsize > _capacity)
		{
			TSSArray newarr(newsize);
			std::copy(begin(), end(), newarr.begin());
			*this = newarr;
		}
		else
		{
			_size = newsize;
		}
	}

	//insert

	iterator insert(iterator it, value_type item)
	{
		resize(_size + 1);
		for (iterator i = end(); i > it; --i)
		{
			*i = *(i - 1);
		}
		*it = item;
		return it;
	}

	//erase

	iterator erase(iterator it)
	{
		for (iterator i = it; i < end(); ++i)
		{
			*i = *(i + 1);
		}
		resize(_size - 1);
		return it;
	}

	//push_back

	void push_back(value_type item)
	{
		insert(end(), item);
	}

	//pop_back

	void pop_back()
	{
		erase(end() - 1);
	}

	/**********Member Operators***********/

	//op= (Copy)
	//Pre: None
	TSSArray & operator=(const TSSArray & lhs)
	{
		TSSArray tempLhs(lhs);
		swap(tempLhs);
		return *this;
	}

	//op= (Move)
	//Pre: rValueTrash must be an rvalue.
	TSSArray & operator=(TSSArray && rValueTrash) noexcept
	{
		swap(rValueTrash);
		return *this;
	}

	//op[] (non-const)
	//Pre: index >= 0
	value_type & operator[](size_type index)
	{
		return _data[index];
	}

	//op[] (const)
	//Pre: index >= 0
	const value_type & operator[](size_type index) const
	{
		return _data[index];
	}

private:
	
	size_type _capacity;
	size_type _size;
	value_type * _data;
	

}; //End class TSSarray

#endif // !FILE_TSSARRAY_H_INCLUDED
