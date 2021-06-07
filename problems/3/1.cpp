/* 

   You are given a list, L , and another list, P , containing integers sorted in ascending
   order. The operation printLots(L,P) will print the elements in L that are in positions
   speciﬁed by P . For instance, if P = 1, 3, 4, 6, the elements in positions 1, 3, 4, and 6
   in L are printed. Write the procedure printLots(L,P) . You may use only the public
   STL container operations. What is the running time of your procedure?

*/

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

// Let length of L be l and P be p.
//Complexity is O( l * log( p ) ) if Blist uses random access iterators. It is O( l * p ) otherwise. 

template<typename AList, typename BList>
void printLots(AList L, BList P){

	auto it { L.begin() };
	std::size_t i {1};
	while(i <= L.size()) {
		auto [ start, end ] = std::equal_range(P.begin(), P.end(), i );
		if( start != end ) std::cout << *it << std::endl;
		i++;
		it++;
	}
}

int main(){
	std::list<int> L { 69, 100, 23, 45, 23, 56, 78, 56 };
	std::vector<int> P {1, 3, 4, 6};
	printLots(L, P);
}
