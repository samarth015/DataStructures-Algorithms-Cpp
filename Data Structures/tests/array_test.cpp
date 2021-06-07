#include "randint.cpp"
#include "../array.cpp"
#include <iostream>
#include <algorithm>

using namespace std;

int main(){

	samarth::array<int,7> sv {5,3,2,6,7,4,1} ;
	for( auto n : sv ) cout << n << " " ;

	cout << "\n\nmax : " << *std::max_element( sv.begin() ,sv.end() ) << endl;
	cout << "min : " << *std::min_element( sv.begin() ,sv.end() ) << endl;

	std::sort( sv.begin() , sv.end() );

	cout << "\nSorted : \n";
	for( auto a : sv ) cout << a << " " ;
	cout << endl;
}
