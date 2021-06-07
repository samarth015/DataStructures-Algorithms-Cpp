	/*
	 
	 Add reverse iterators to the STL List class implementation. Deﬁne reverse_iterator
	and const_reverse_iterator . Add the methods rbegin and rend to return appro-
	priate reverse iterators representing the position prior to the endmarker and the
	position that is the header node. Reverse iterators internally reverse the meaning of
	the ++ and -- operators. You should be able to print a list L in reverse by using the
	code

	List<Object>::reverse_iterator itr = L.rbegin( );
	while( itr != L.rend( ) )
		cout << *itr++ << endl;

 */



// The implementation of List along with its reverse iterators is provided at
// ../../Data Structures/doubly_linked_list.cpp

#include "../../Data Structures/doubly_linked_list.cpp"
#include <iostream>


int main(){
	samarth::list<int> li {1,2,3,4,5,6};

	samarth::list<int>::reverse_iterator rit { li.rbegin() };
	while( rit != li.rend()){
			std::cout << *rit++ << std::endl;
		}
}
