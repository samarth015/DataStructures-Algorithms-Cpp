/*
 
   Write an algorithm for printing a singly linked list in reverse, using only constant
	extra space. This instruction implies that you cannot use recursion but you may
	assume that your algorithm is a list member function. Can such an algorithm be
	written if the routine is a constant member function?
 
*/

// No such a routiene cannot be written if it is const as this routiene requires the modification
// of links between the different nodes.


#include <iostream>

template<typename T>
class singly_linked_list{
	private:
		struct node
		{
				T data;
				node* next;
				node(): data{}, next{nullptr} {}
				node(const T& data): data{data}, next{nullptr}{}
		};

		node *head;

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

		void reverse_list(){

			if(head->next == nullptr) return;

			node *prev{nullptr}, *curr{head->next}, *next{head->next->next};

			while(next){
				curr->next = prev;
				prev = curr;
				curr = next;
				next = next->next;
			}

			curr->next = prev;
			head->next = curr;
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
	li.reverse_list();
	li.print();
	li.reverse_list();
	li.print();
}



