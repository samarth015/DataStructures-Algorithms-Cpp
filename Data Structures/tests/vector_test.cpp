#include "randint.cpp"
#include "../vector.cpp"
#include <iostream>
#include <algorithm>

using namespace std;

int main(){

	samarth::vector<int> sv {} ;
	for( std::size_t i {} ; i < 20 ; i++ ) {
		sv.push_back( randint() ) ;
	}
	for( auto n : sv ) cout << n << " " ;

	cout << "\n\nmax : " << *std::max_element( sv.begin() ,sv.end() ) << endl;
	cout << "min : " << *std::min_element( sv.begin() ,sv.end() ) << endl;

	std::sort( sv.begin() , sv.end() );

	cout << "\nSorted : \n";
	for( auto a : sv ) cout << a << " " ;
	cout << endl;
}
