
#include "randint.cpp"
#include "../queue_linked_list.cpp"
#include <iostream>

using namespace std;

int main(){

	samarth::queuell<int> qu;

	cout << "After enqueueing 10 random integers : " ;
	for(std::size_t i{};i<10;i++){
		int ran { randint() };
		qu.enqueue( ran );
		cout << ran << " " ;
	}
	cout << endl;

	cout << "size : " << qu.size() << endl;
	cout << "front : " << qu.front() << endl;
	cout << "back : " << qu.back() << endl;

	qu.dequeue();
	qu.dequeue();

	cout << "After dequeueing twice " << endl;
	cout << "size : " << qu.size() << endl;
	cout << "front : " << qu.front() << endl;
	cout << "back : " << qu.back() << endl;

	qu.enqueue(1);
	qu.enqueue(2);
	qu.enqueue(3);

	cout << "After enqueueing 1,2,3 " << endl;
	cout << "size : " << qu.size() << endl;
	cout << "front : " << qu.front() << endl;
	cout << "back : " << qu.back() << endl;


	for(std::size_t i{};i<7;i++) qu.dequeue();
	cout << "After dequeueing 7 times " << endl;
	cout << "size : " << qu.size() << endl;
	cout << "front : " << qu.front() << endl;
	cout << "back : " << qu.back() << endl;



	cout << "After enqueueing 5 random ints  : ";
	for(std::size_t i{};i<5;i++){
		int ran { randint() };
		qu.enqueue( ran );
		cout << ran << " " ;
	}
	cout << endl;

	cout << "After dequeueing 7 times " << endl;
	cout << "size : " << qu.size() << endl;
	cout << "front : " << qu.front() << endl;
	cout << "back : " << qu.back() << endl;

	qu.clear();
	cout << "Calling clear" << endl;
	cout << "size : " << qu.size() << endl;

}

