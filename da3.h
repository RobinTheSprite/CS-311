// da3.h  INCOMPLETE
// Glenn G. Chappell
// 24 Sep 2017
//
// For CS 311 Fall 2017
// Header for Assignment 3 Functions

#ifndef FILE_DA3_H_INCLUDED
#define FILE_DA3_H_INCLUDED

#include <cstddef>
using std::size_t;
#include <functional>
using std::function;
#include <vector>
using std::vector;
#include <algorithm>
#include <iterator>
#include <stdexcept>

// **************************************************************** // *
// Begin DO-NOT-CHANGE section                                      // *
// Do not alter the lines below                                     // *
// **************************************************************** // *
                                                                    // *
                                                                    // *
// struct LLNode                                                    // *
// Linked List node, with client-specified value type               // *
// Intended Invariants (breakable, as data members are public):     // *
//     Either _next is nullptr, or _next points to an LLNode,       // *
//      allocated with new, owned by *this.                         // *
// Requirements on Types:                                           // *
//     ValueType must have a copy ctor and a dctor.                 // *
template <typename ValueType>                                       // *
struct LLNode {                                                     // *
    ValueType _data;  // Data for this node                         // *
    LLNode *  _next;   // Ptr to next node, or nullptr if none      // *
                                                                    // *
    // The following simplify creation & destruction                // *
                                                                    // *
    // 1- & 2-param ctor                                            // *
    // Pre:                                                         // *
    //     theNext, if passed, is either nullptr, or else it        // *
    //      points to an LLNode, allocated with new, with           // *
    //      ownership transferred to *this.                         // *
    // Post:                                                        // *
    //     _data == data.                                           // *
    //     If _next passed, then _next == next. Otherwise, _next    // *
    //      is nullptr.                                             // *
    explicit LLNode(const ValueType & data,                         // *
                    LLNode * next = nullptr)                        // *
        :_data(data),                                               // *
         _next(next)                                                // *
    {}                                                              // *
                                                                    // *
    // dctor                                                        // *
    // Pre: None.                                                   // *
    // Post: None. (_next delete'd)                                 // *
    ~LLNode()                                                       // *
    { delete _next; }                                               // *
};  // End struct LLNode                                            // *
                                                                    // *
                                                                    // *
// **************************************************************** // *
// End DO-NOT-CHANGE section                                        // *
// Do not alter the lines above                                     // *
// **************************************************************** // *

//lookUp (by Mark Underwood)
//Requirements on Types: None
//Exceptions: May throw out_of_range
//Pre: head must point to either nullptr or a new LLNode object.
//Post: Returns the data from the node that is a distance of [index] nodes from head. 
template <typename ValueType>
ValueType lookUp(const LLNode<ValueType> * head,
                 size_t index)
{
	//Is the list empty?
	if (head == nullptr)
	{
		throw out_of_range("Index out of range");
	}

	for (size_t i = 0; i < index; ++i)
	{
		//Is this the last node in the list?
		if (head->_next != nullptr)
		{
			head = head->_next;
		}
		else if (i != index) //If this is the last node in the list, are we trying to seek past it?
		{
			throw out_of_range("Index out of range");
		}
	}

	return head->_data;
}

//callBetween (by Mark Underwood)
//Exceptions: May throw any exception that the functions passed as arguments can throw.
//Pre: Any functions passed as start, middle, or finish must not return anything.
//Post: Functions start, middle, and finish are all called in precisely that order.
// Implementation in source file
void callBetween(const function<void()> & start,
                 const function<void()> & middle,
                 const function<void()> & finish);

//uniqueCount (by Mark Underwood)
//Requirements on Types:
//	-Value type of RAIter must have operators <, ==, and =.
//	-Value type of RAIter must be default and copy constructable.
//Exceptions: Does not throw
//Pre: first < last.
//Post: Returns number of unique elements in a given range.
template <typename RAIter>
size_t uniqueCount(RAIter first,
                   RAIter last)
{
	std::sort(first, last); //Get range ready for binary search

	vector<typename std::iterator_traits<RAIter>::value_type> foundElements;
	size_t uniqueFound = 0;

	//Go through every element in the range
	while (first < last)
	{
		//Have we found this number before?
		if (!std::binary_search(foundElements.begin(), foundElements.end(), *first))
		{
			//If not, add it to the list
			foundElements.push_back(*first); 
			++uniqueFound;
		}

		first++;
	}

    return uniqueFound;  
}

//gcd (by Mark Underwood)
//Exceptions: Does not throw
//Pre: a and b must be positive.
//Post: Returns the greatest number that can evenly divide both a and b.
// Implementation in source file
int gcd(int a,
        int b);


#endif  //#ifndef FILE_DA3_H_INCLUDED

