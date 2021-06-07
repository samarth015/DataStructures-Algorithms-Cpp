/*
   
	  Suppose that a singly linked list is implemented with both a header and a tail node.
	  Describe constant-time algorithms to

		a. insert item x before position p (given by an iterator)
		b. remove the item stored at position p (given by an iterator)

*/


//Algorithm A
 		// Let the node that the given iterator points to be curr_node

// 1. Create a new node using the value to insert and make its next point at the next of curr_node.
// 2. Make curr_node's next point at the new node.
// 3. Swap the values of the curr node and the new node.


//Algorithm B
 		// Let the node that the given iterator points to be curr_node

// 1. Copy the contents of curr_node's next node to curr_node. (Overwrite curr_node's data)
// 2. Make curr_node's next point at the next of curr_node's next.
// 3. Delete curr_node's next node.


// std::forward_list has been used for implementation of the algorithm which is a singly linked list.

#include <forward_list>
#include <algorithm>
#include <iostream>

template<typename T>
using list_iter = typename std::forward_list<T>::iterator ;

template<typename T>
void insert_before(const T& val, list_iter<T> it, std::forward_list<T> & li){
	li.insert_after(it, val);  // 1 and 2
	auto curr {it};
	auto next {++it};
	std::swap(*curr, *next);    // 3
}

template<typename T>
void remove_at(list_iter<T> it, std::forward_list<T> &li){
	auto curr {it};
	auto next {++it};
	*curr = std::move(*next);    //1
	li.erase_after(curr);        // 2 and 3
}

int main(){
	std::forward_list<int> li {1,2,3,4,5,6,7};
	auto it1 {std::find(li.begin(), li.end(), 5)};
	auto it2 {std::find(li.begin(), li.end(), 3)};
	insert_before( 99, it1, li );
	remove_at( it2, li);

	for(auto n : li) std::cout << n << " ";
	std::cout << std::endl;

}
