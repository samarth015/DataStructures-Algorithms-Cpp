/*

	Modify the Vector class to provide stringent iterator checking by making itera-
	tors class types rather than pointer variables. The hardest part is dealing with stale
	iterators, as described in Exercise 3.9.

*/


// The implementation of such a vector class is provided in the Data Structures directory as safe_vector.
// relative path -->    ../../Data Structures/safe_vector.cpp


#include <iostream>
#include "../../Data Structures/safe_vector.cpp"

int main(){
	samarth::safe_vector<int> sv { 1,2,3,4,5,6,7,8,8,9,10};

	for(auto a : sv) std::cout << a << " ";
	std::cout << std::endl;

	samarth::safe_vector<int>::iterator empty_it{nullptr,nullptr} ;
	//std::cout << *empty_it << std::endl;       //Will not dereference uninitialized iterator

	auto it{sv.begin()};

	for(std::size_t i{}; i < 100; i++){
		sv.push_back(0);
	}

	//std::cout << *it;    //After a 100 pushes iterator is invalidated.

	//sv.erase(it);       //Methods will also not work with invalidated iterators.
}

//More tests for this vector at -->      ../../Data Structures/tests/safe_vector.cpp
