/*

Implement the STL find routine that returns the iterator containing the ﬁrst occur-
rence of x in the range that begins at start and extends up to but not including end .
If x is not found, end is returned. This is a nonclass (global function) with signature
template <typename Iterator, typename Object>
iterator find( Iterator start, Iterator end, const Object & x );

   */

#include <iostream>
#include "vector"

template<typename ForwardIterator, typename Object>
ForwardIterator find(ForwardIterator begin, ForwardIterator end, const Object &x ){

	for( auto curr_it {begin}; curr_it != end; curr_it++)
		if( *curr_it == x ) return curr_it;
	
	return end;
}


int main(){

	std::vector<int> v { 5, 3, 100, 67, 78 };

	if( find( v.begin(), v.end(), 67) != v.end() ) std::cout << "67 found" << std::endl;
	else std::cout <<  "not found" << std::endl;

}
