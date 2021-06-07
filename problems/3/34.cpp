
/*
 
	A linked list contains a cycle if, starting from some node p, following a sufﬁcient
	number of next links brings us back to node p. p does not have to be the ﬁrst node
	in the list. Assume that you are given a linked list that contains N nodes; however,
	the value of N is unknown.

	a. Design an O(N) algorithm to determine if the list contains a cycle. You may use
	O(N) extra space.

	 b. Repeat part (a), but use only O(1) extra space. (Hint: Use two iterators that are
	initially at the start of the list but advance at different speeds.)written if the routine is a constant member function?
 
*/

#include <iostream>
#include <vector>

//Special singly linked list that can be turned into a circular list, as its head ptr is public,
//implemented solely for the puspose of testing the algorithm.
template<typename T>
class singly_linked_list{
	public:
		struct node
		{
			T data;
			node* next;
			node(const T& data): data{data}, next{nullptr}{}
		};

		node *first; 
		node *last;        
		
		singly_linked_list(): first{nullptr}, last{nullptr} {};

		~singly_linked_list(){
			while(first != last){
				node *temp{first};
				first = first->next;
				delete temp; 
			}
			delete last;
		}

		void push_back(const T& data){
			node* new_node = new node{data};
			if(first == nullptr) first = last = new_node;
			else last = last->next = new_node;
		}

		void print() const {
			node* curr {first};
			std::cout << "List : ";
			while(curr!=last){
				std::cout << curr->data << ", " ;
				curr = curr->next;
			}
			std::cout << last->data << std::endl;
		}
};


template<typename T>
bool is_circular_linked_list_linear_space_complexity(const singly_linked_list<T>& li ){
	using node = typename singly_linked_list<T>::node;
	std::vector<node*> record {};

	node *curr = li.first->next;
	while( curr != nullptr ){
		for(auto p : record) if(curr == p) return true;
		record.push_back(curr);
		curr = curr->next;
	}
	return false;
}

template<typename T>
bool is_circular_linked_list_constant_space_complexity(const singly_linked_list<T>& li ){
	using node = typename singly_linked_list<T>::node;
	node* start_node = li.first;

	if(start_node == nullptr) return false;

	node *slow, *fast;
	slow = start_node;
	fast = start_node->next;

	while(slow and fast and fast->next){
		slow = slow->next;
		fast = fast->next->next;
		if(fast == slow) return true;
	}

	return false;
}

int main(){
	singly_linked_list<int> li;
	for(int i {};i < 10;i++) li.push_back(i);

	li.print();

	std::cout << is_circular_linked_list_constant_space_complexity(li) << std::endl;
	std::cout << is_circular_linked_list_linear_space_complexity(li) << std::endl;

	li.last->next = li.first->next->next->next;   //making it circular

	std::cout << is_circular_linked_list_linear_space_complexity(li) << std::endl;
	std::cout << is_circular_linked_list_constant_space_complexity(li) << std::endl;
}
