/*
   Repeat Exercise 3.11, maintaining the singly linked list in sorted order.
*/

#include <stdexcept>
#include <iostream>
#include <random>

template<typename T>
class singly_linked_list_sorted
{
	private:
		struct node
		{
				T data;
				node* next;
				node(): data{}, next{nullptr} {}
				node(const T& data): data{data}, next{nullptr}{}
				node(const T& data, node* next): data{data}, next{next}{}
		};

		node* head;

		// Returns the node containing the largest value smaller than x.
		node* find_node_smaller_than(const T& x) const {
			node* curr{head->next}, *prev{head};
			while(curr and curr->data < x){
				prev = curr;
				curr = curr->next;
			}
			return prev;
		}

	public:
		singly_linked_list_sorted(): head{ new node{} } {};

		~singly_linked_list_sorted(){
			node* temp;
			while(head){
				temp = head;
				head = head->next;
				delete temp;
			}
		}

		void add(const T& data){
			node* no {find_node_smaller_than(data)};
			if(no->next == nullptr) no->next = new node{data};
			else no->next = new node{data, no->next};
		}

		void pop_back(){
			if(head->next == nullptr) throw std::runtime_error {"List is empty. Nothing to pop."};

			node* curr{head->next}, *prev{head};
			while(curr->next){
				prev = curr;
				curr = curr->next;
			}
			prev->next = nullptr;
			delete curr;
		}

		std::size_t size() const{
			node* curr{head->next};
			std::size_t length{0};
			while(curr){
				length++;
				curr = curr->next;
			}
			return length;
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

		bool is_contained(const T& x) const {
			node* no { find_node_smaller_than(x)->next };
			return no->data == x ;
		}

		void add_if_not_present(const T& x){
			node* no { find_node_smaller_than(x) };
			if(no->next == nullptr or no->next->data != x)
				no->next = new node{x,no->next};
		}

		void remove_if_present(const T& x){
			node* no { find_node_smaller_than(x) };
			if(no->next != nullptr and no->next->data == x){
				node* temp { no->next };
				no->next = no->next->next;
				delete temp;
			}
		}
};

int main(){

	std::mt19937 ran {0};

	singly_linked_list_sorted<int> sll{};
	for(int i{};i<10;i++){
		sll.add(ran()%100);
	}

	sll.print();

	std::cout <<"size : " << sll.size() << std::endl;

	std::cout << "Testing for 14 : " << sll.is_contained(14) << std::endl;
	std::cout << "Testing for 60 : " << sll.is_contained(60) << std::endl;

	sll.add_if_not_present(39);
	sll.add_if_not_present(40);
	sll.print();

	sll.remove_if_present(111);
	sll.remove_if_present(83);

	sll.print();
}
