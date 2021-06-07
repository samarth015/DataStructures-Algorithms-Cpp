
/* 

   G  Given two sorted lists, L1 and L2 , write a procedure to compute L1 U L2 using only
   the basic list operations. 

*/

// The L1 U L2 set can be represented as a std::vector.

#include <iostream>
#include <vector>
#include <list>

template<typename AList, typename BList>
auto find_union(const AList& L1, const BList& L2){

	using A_value_type = typename AList::value_type;
	using B_value_type = typename BList::value_type;
	constexpr bool type_is_same { std::is_same< A_value_type , B_value_type >::value };
	static_assert( type_is_same, "The contained type of the two lists must be the same");

	using value_type = typename AList::value_type;

	std::vector< value_type > result {};

	auto itL1 { L1.begin() };
	auto itL2 { L2.begin() };

	while( itL1 != L1.end() and itL2 != L2.end() ){
		if( *itL1 == *itL2 ){
			value_type common_val { *itL1 };
			result.push_back( common_val );
			while( itL1 != L1.end() and *itL1 == common_val ) itL1++;
			while( itL2 != L2.end() and *itL2 == common_val ) itL2++;
		}
		else if( *itL1 < *itL2 ) {
			value_type uncommon_smaller_value { *itL1 };
			result.push_back(uncommon_smaller_value);
			while( itL1 != L1.end() and *itL1 == uncommon_smaller_value ) itL1++;
		}
		else {
			value_type uncommon_smaller_value { *itL2 };
			result.push_back(uncommon_smaller_value);
			while( itL2 != L2.end() and *itL2 == uncommon_smaller_value ) itL2++;
		}
	}

	while(itL1 != L1.end()){ 
		result.push_back( *itL1 );
		itL1++;
	}
	while(itL2 != L2.end()){
		result.push_back( *itL2 );
		itL2++;
	}

	return result;
}

int main() {

	std::vector<int> L1 {1,1,2,3,4,10,15,17,20,20,20,60};
	std::list<int> L2 {2,4,7,11,15,16,17,18,18,18,18,20,50};

	std::vector<int> inc { find_union(L1,L2)};

	for( auto ele : inc ) std::cout << ele << std::endl;
}
