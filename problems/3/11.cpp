/*
	  Assume that a singly linked list is implemented with a header node, but no tail
	node, and that it maintains only a pointer to the header node. Write a class that
	includes methods to
	a. return the size of the linked list
	b. print the linked list
	c. test if a value x is contained in the linked list
	d. add a value x if it is not already contained in the linked list
	e. remove a value x if it is contained in the linked list
*/

#include <stdexcept>
#include <iostream>

template<typename T>
class singly_linked_list
{
	private:
		struct node
		{
				T data;
				node* next;
				node(): data{}, next{nullptr} {}
				node(const T& data): data{data}, next{nullptr}{}
		};

		node* head;

	public:
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

	private:
		//Finds the node preceding the node containing x. Returns Last node if x not found present.
		node* find_preceding_node(const T& x) const {
			node* curr{head->next}, *prev{head};
			while(curr and curr->data != x){
				prev = curr;
				curr = curr->next;
			}
			return prev;
		}

	public:
		bool is_contained(const T& x) const {
			node* no { find_preceding_node(x)->next };
			return no != nullptr;
		}

		void add_if_not_present(const T& x){
			node* no { find_preceding_node(x) };
			if(no->next==nullptr)
				no->next = new node{x};
		}

		void remove_if_present(const T& x){
			node* no { find_preceding_node(x) };
			if(no->next!=nullptr){
				node* temp { no->next };
				no->next = no->next->next;
				delete temp;
			}
		}
};

int main(){

	singly_linked_list<int> sll{};
	for(int i{};i<10;i++){
		sll.push_back(i);
	}

	sll.print();

	std::cout <<"size : " << sll.size() << std::endl;

	std::cout << "Testing for 14 : " << sll.is_contained(14) << std::endl;
	std::cout << "Testing for 7 : " << sll.is_contained(7) << std::endl;

	sll.add_if_not_present(9);
	sll.add_if_not_present(20);
	sll.print();

	sll.remove_if_present(111);
	sll.remove_if_present(3);

	sll.print();
}
