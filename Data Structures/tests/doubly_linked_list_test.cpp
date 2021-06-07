#include "randint.cpp"
#include "../doubly_linked_list.cpp"
#include "../doubly_linked_list.cpp"
#include <iostream>
#include <algorithm>

using namespace std;

int main(){

	samarth::list<int> li; 

	cout << "\nPushing 1, 2, 3, 4 at back\n" ;
	li.push_back(1);
	li.push_back(2);
	li.push_back(3);
	li.push_back(4);

	cout << "len : " << li.size() << endl;
	for(auto& n : li) cout << n << " ";
	cout << endl;

	cout << "\nPushing 70, 520 at front\n" ;
	li.push_front(70);
	li.push_front(520);

	cout << "len : " << li.size() << endl;
	for(auto& n : li) cout << n << " ";
	cout << endl;

	auto it { std::find( li.begin() , li.end() , 1)};
	li.insert( 100, it );
	it = std::find( li.begin() , li.end() , 4);
	li.insert( 7, it);

	li.erase( std::find( li.begin() , li.end() , 70) ); 

	cout << "\nAfter insert and erase call : \n" ;
	cout << "len : " << li.size() << endl;
	for(auto& n : li) cout << n << " " ;
	cout << endl;


	auto minmax {  std::minmax_element( li.begin(),li.end() )  };
	cout << "min : " << *minmax.first <<endl;
	cout << "max : " << *minmax.second <<endl;

	cout << "\nRange erase : " << endl;
	
	auto from = std::find( li.begin() , li.end() , 100) ; 
	auto to = std::find( li.begin() , li.end() , 7) ; 
	li.erase( from, to);

	for(auto& n : li) cout << n << " " ;
	cout << "len : " << li.size() << endl;
	cout<<endl;

	cout << "calling clear : " << endl;
	li.clear();
	for(auto& n : li) cout << n << " " ;
	cout << "len : " << li.size() << endl;
	cout<<endl;


	samarth::list<int> lites {1,20,3,40,5,60,7,8};        //testing reverse iterators

	auto ittes = lites.rbegin();
	while( ittes != lites.rend() ){
		std::cout << *ittes << std::endl;
		ittes++;
	}

	

}

