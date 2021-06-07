/*
 
	 Suppose we have a pointer to a node in a singly linked list that is guaranteed not
	to be the last node in the list. We do not have pointers to any other nodes (except
	by following links). Describe an O(1) algorithm that logically removes the value
	stored in such a node from the linked list, maintaining the integrity of the linked
	list. (Hint: Involve the next node.)

*/

// ALGORITHM
// 1 - Copy the next node's value into current node. (Effectively overwriting the value to remove)
// 2 - Save a ptr to the next node to a temp ptr.
// 3 - Set the current node's next ptr to the next node's next node ptr.
// 4 - Now delete/free node being pointed to by temp ptr. ()

//NOTE Step 2 and 4 are not required if your language has automatic garbage collection.


//Algorithm implemented at line 61.

#include <iostream>

template<typename T>
class singly_linked_list{
	public:
		struct node
		{
				T data;
				node* next;
				node(): data{}, next{nullptr} {}
				node(const T& data): data{data}, next{nullptr}{}
		};

		node *head;

		singly_linked_list(): head{ new node{} } {};

		~singly_linked_list(){
			node* temp;
			while(head){
				temp = head;
				head = head->next;
				delete temp;
			}
		}

		void push_back(const T& data){
			node* curr{ head };
			while(curr->next) curr = curr->next;
			curr->next = new node{data};
		}

		node* get_nth_node_ptr(std::size_t n) const {
			node* nth_node {head};
			for( std::size_t i{}; i < n; i++)
				nth_node = nth_node->next;
			return nth_node;
		}

		void remove_node(node* p){
			p->data = std::move(p->next->data);
			node* temp { p->next };
			p->next = p->next->next;
			delete temp;
		}

		void print() const {
			node* curr{head->next};
			std::cout << "List : " ;
			while(curr){
				std::cout << curr->data << ", ";
				curr = curr->next;
			}
			std::cout << std::endl;
		}
};

int main(){
	singly_linked_list<int> li {};
	for(int i{1}; i <= 10; i++) li.push_back(i);
	li.print();
	auto ptr5th { li.get_nth_node_ptr(5) };
	auto ptr2nd { li.get_nth_node_ptr(2) };

	li.remove_node( ptr5th );
	li.print();
	li.remove_node( ptr2nd );
	li.print();
}

