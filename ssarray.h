/*
ssarray.h
Mark Underwood
10.19.17
Contains declarations for SSArray class
*/

#ifndef FILE_SSARRAY_H_INCLUDED
#define FILE_SSARRAY_H_INCLUDED

template <typename dataType>
class SSArray
{
public:
	using size_type = size_t; //Type of every object's _size member variable.
	using value_type = dataType;
	using iterator = value_type *;
	using const_iterator = const value_type *;
public:

	/**********Constructors***********/

	//Default Ctor
	//Pre: None
	//Post: A SSArray object is created with an array of size ten, of a type specified by the client.
	SSArray()
		: _data(new value_type[10]),
		_size(10)
	{}

	//One-Param Ctor
	//Pre: None
	//Post: A SSArray object is created with a size and type specified by the client.
	explicit SSArray(size_type size)
		: _data(new value_type[size]),
		_size(size)
	{}

	//Dtor
	//Pre: None
	//Post: The array of *this SSArray is deallocated, and the object is destructed. 
	//		The _data pointer is set to null. 
	~SSArray()
	{
		delete[] _data;
		_data = nullptr;
	}

	//Copy Constructor
	//Pre: None
	//Post: A new SSArray is constructed that is identical to the one passed as an argument.
	SSArray(const SSArray & toBeCopied)
		: _data(new value_type[toBeCopied.size()]),
		_size(toBeCopied.size())
	{
		for (size_type i = 0; i < toBeCopied.size(); ++i)
		{
			_data[i] = toBeCopied[i];
		}
	}

	//Move Constructor
	//Pre: toBeCopied is an rvalue
	//Post: A new SSArray is constructed that is identical to the one passed as an argument. 
	//      The _data pointer of toBeCopied is set to null.
	SSArray(SSArray && toBeCopied) noexcept
		: _size(toBeCopied.size())
	{
		value_type * tempPtr = toBeCopied._data;
		toBeCopied._data = nullptr;
		_data = tempPtr;
	}

	/**********Misc. "Get" Functions***********/

	//size
	//Pre: None
	//Post: Returns the size of *this SSArray.
	size_type size() const
	{
		return _size;
	}

	//begin (non-const)
	//Pre: None
	//Post: Returns a pointer to the first element in *this SSArray.
	value_type * begin()
	{
		return _data;
	}

	//begin (const)
	//Pre: None
	//Post: Returns a pointer to the first element in *this SSArray. 
	//      Is not allowed to modify the SSArray.
	const value_type * begin() const
	{
		return _data;
	}

	//end (non-const)
	//Pre: None
	//Post: Returns a pointer to one past the end of *this's array.
	value_type * end()
	{
		return (begin() + size());
	}

	//end (const)
	//Pre: None
	//Post: Returns a pointer to the first element in *this SSArray.
	//      Does not modify the KSArray.
	const value_type * end() const
	{
		return (begin() + size());
	}

	//swap
	//Pre: None
	//Post: The arrays and sizes of *this and the other SSArray are swapped.
	void swap(SSArray & other) noexcept
	{
		std::swap(_data, other._data);
		std::swap(_size, other._size);
	}

	bool empty() const
	{
		return this->size() == 0;
	}

	void resize(size_type)
	{

	}

	iterator insert(iterator, value_type)
	{
		return this->begin(); //DUMMY
	}

	iterator erase(iterator)
	{
		return this->begin(); //DUMMY
	}

	void push_back(value_type)
	{}

	void pop_back()
	{}

	/**********Member Operators***********/

	//op= (Copy)
	//Pre: None
	//Post: *this SSArray is identical to the SSArray on the right side of the = sign.
	SSArray & operator=(const SSArray & lhs)
	{
		SSArray tempLhs(lhs);
		swap(tempLhs);
		return *this;
	}

	//op= (Move)
	//Pre: rValueTrash must be an rvalue.
	//Post: *this SSArray is identical to the SSArray on the right side of the = sign.
	SSArray & operator=(SSArray && rValueTrash) noexcept
	{
		swap(rValueTrash);
		return *this;
	}

	//op[] (non-const)
	//Pre: index >= 0
	//Post: Returns the item stored at the index passed by the client.
	value_type & operator[](size_type index)
	{
		return _data[index];
	}

	//op[] (const)
	//Pre: index >= 0
	//Post: Returns the item stored at the index passed by the client.
	//      Does not modify *this's array.
	const value_type & operator[](size_type index) const
	{
		return _data[index];
	}

private:

	value_type * _data;
	size_type _size;

}; //End class SSarray


   /***********Global Comparison Operators***********/

   //op==
   //Requirements On Types: value_type is the type of the items in a SSArray array. 
   //Pre: None
   //Post: Returns true if the two SSArrays have the same items in their arrays and the same size, otherwise returns false.
template <typename value_type>
bool operator==(const SSArray<value_type> & lhs, const SSArray<value_type> & rhs)
{
	return (lhs.size() == rhs.size()) && std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

//op!=
//Requirements On Types: value_type is the type of the items in a SSArray array. 
//Pre: None
//Post: Returns true if anything about the two SSArrays are different, otherwise returns false.
template <typename value_type>
bool operator!=(const SSArray<value_type> & lhs, const SSArray<value_type> & rhs)
{
	return !(lhs == rhs);
}

//op<
//Requirements On Types: value_type is the type of the items in a SSArray array. 
//Pre: None
//Post: Compares the SSArrays in lexicographic order:
//      -If lhs[0] < rhs[0], returns true.
//		-If not, compare lhs[1] to rhs[1].
//		-If the end of the array is reached, compare to see if the size of lhs < size of rhs.
template <typename value_type>
bool operator<(const SSArray<value_type> & lhs, const SSArray<value_type> & rhs)
{
	return (lhs != rhs) && !(lhs > rhs);
}

//op>
//Requirements On Types: value_type is the type of the items in a SSArray array. 
//Pre: None
//Post: Compares the SSArrays in lexicographic order:
//      -If lhs[0] > rhs[0], returns true.
//		-If not, compare lhs[1] to rhs[1].
//		-If the end of the array is reached, compare to see if the size of lhs > size of rhs.
template <typename value_type>
bool operator>(const SSArray<value_type> & lhs, const SSArray<value_type> & rhs)
{
	auto elementsNotTheSame = std::mismatch(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());

	bool didNotReachEnd = elementsNotTheSame.first != lhs.end() && elementsNotTheSame.second != rhs.end();

	if (didNotReachEnd)
	{
		return (*elementsNotTheSame.first > *elementsNotTheSame.second);
	}
	return (lhs.size() > rhs.size());
}

//op<=
//Requirements On Types: value_type is the type of the items in a SSArray array. 
//Pre: None
//Post: Returns true if operator== or operator< returns true. See their documentation for details.
template <typename value_type>
bool operator<=(const SSArray<value_type> & lhs, const SSArray<value_type> & rhs)
{

	return (lhs == rhs) || (lhs < rhs);
}

//op>=
//Requirements On Types: value_type is the type of the items in a SSArray array. 
//Pre: None
//Post: Returns true if operator== or operator> returns true. See their documentation for details.
template <typename value_type>
bool operator>=(const SSArray<value_type> & lhs, const SSArray<value_type> & rhs)
{
	return (lhs == rhs) || (lhs > rhs);
}

#endif // !FILE_SSARRAY_H_INCLUDED
