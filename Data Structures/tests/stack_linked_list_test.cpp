#include "randint.cpp"
#include "../stack_linked_list.cpp"
#include <iostream>

using namespace std;

int main(){
	samarth::stackll<int> st;

	cout << "After pushing 10 random integers : " ;
	for(std::size_t i{};i<10;i++){
		int ran { randint() };
		st.push( ran );
		cout << ran << " " ;
	}
	cout << endl;

	cout << "size : " << st.size() << endl;
	cout << "top : " << st.top() << endl;

	st.pop();
	st.pop();

	cout << "After popping twice " << endl;
	cout << "size : " << st.size() << endl;
	cout << "top : " << st.top() << endl;

	st.push(1);
	st.push(2);
	st.push(3);

	cout << "After pushing 1,2,3 " << endl;
	cout << "size : " << st.size() << endl;
	cout << "top : " << st.top() << endl;

	st.clear();

	cout << "Calling clear" << endl;
	cout << "size : " << st.size() << endl;
}
