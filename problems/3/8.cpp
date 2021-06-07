/* 
  Add insert and erase to the Vector class.
  */

// Implementation of a Vector class with insert and erase provided in Data Structures and Algorithms directory
// relative path -->   ../../Data Structures/vector.cpp


#include "../../Data Structures/vector.cpp"
#include <iostream>
#include <algorithm>

int main() {
	samarth::vector<int> v {};
	for( std::size_t i{}; i < 10; i++) v.push_back(i);

	std::cout << "length : " << v.size() << std::endl;
	for(auto ele : v ) std::cout << ele << ' ';
	std::cout << std::endl;

	auto it { std::find( v.begin(), v.end(), 5 ) };

	v.insert(it, 100);

	std::cout << "length : " << v.size() << std::endl;
	for(auto ele : v ) std::cout << ele << ' ';
	std::cout << std::endl;

	auto it1 { std::find( v.begin(), v.end(), 2 ) };
	auto it2 { std::find( v.begin(), v.end(), 8 ) };
	v.erase( it1, it2 );

	std::cout << "length : " << v.size() << std::endl;
	for(auto ele : v ) std::cout << ele << ' ';
	std::cout << std::endl;
}
