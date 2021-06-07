/*
	 
	Add the splice operation to the List class. The method declaration
	void splice( iterator position, List<T> & lst );
	removes all the items from lst , placing them prior to position in List *this. lst
	and *this must be different lists. Your routine must run in constant time.

 */

#include <utility>
#include <iterator>
#include <iostream>

namespace samarth {

	template<typename Object>
		class list 
		{
			private:
				struct node
				{			
					Object data;
					node* next;
					node* prev;

					node() = delete;
					node(const Object &data, node* next, node* prev): 
						data{data}, 
						next{next},
						prev{prev} 
					{}
					node(Object &&data, node* next, node* prev) noexcept: 
						data{ std::move(data) }, 
						next{next},
						prev{prev} 
					{}
					node(node& oth) = delete ;
					node( node&& oth) noexcept = delete ;
					~node() = default;
				};

				public:

				struct iterator 
				{
					using iterator_category = std::bidirectional_iterator_tag;
					using value_type        = Object;
					using difference_type   = std::ptrdiff_t;
					using pointer           = value_type*;
					using reference         = value_type&;

					iterator(): nodeptr{nullptr} {}
					iterator(node* nodeptr): nodeptr{nodeptr} {}
					iterator(const iterator& oth): nodeptr{oth.nodeptr} {}
					iterator(iterator&& oth):nodeptr{oth.nodeptr} {
						oth.nodeptr = nullptr;
					}
					~iterator() = default;

					iterator& operator=( const iterator &oth ){
						if(this == &oth) return *this;
						nodeptr = oth.nodeptr;
						return *this;
					}
					iterator& operator=( iterator&& oth) {
						nodeptr = oth.nodeptr;
						oth.nodeptr = nullptr;
						return *this;
					}

					Object& operator*() {
						return nodeptr->data;
					}

					Object* operator->() {
						return nodeptr;
					}

					bool operator==(const iterator &oth){
						return oth.nodeptr == this->nodeptr;
					}

					bool operator!=(const iterator &oth){
						return oth.nodeptr != this->nodeptr;
					}

					iterator& operator++(){
						nodeptr = nodeptr->next;
						return *this;
					}

					iterator operator++(int){
						iterator tmp {nodeptr};
						++(*this);
						return tmp;
					}

					iterator& operator--(){
						nodeptr = nodeptr->prev;
						return *this;
					}

					iterator operator--(int){
						iterator tmp {nodeptr};
						--(*this);
						return tmp;
					}

					template<typename>
						friend class list;

					private:
					node* nodeptr;
				};

				list(): 
					length{},
					head{ Object{}, &tail, nullptr},
					tail{ Object{}, nullptr, &head} 
				{}

				list(std::initializer_list<Object> init_list): list() {
					for( auto &object : init_list ) push_back( object );
				}

				list(const list &other) :list() {
					for( auto &object : other ) push_back( object );
				}

				list(list &&oth):
					length{oth.length},
					head{ Object{}, oth.head.next, nullptr },
					tail{ Object{}, nullptr, oth.tail.prev } 
				{
					oth.length = 0;
					oth.head.next = &oth.tail;
					oth.tail.prev = &oth.head;
				}

				~list() {
					clear();
				}

				list& operator= (const list& oth) {
					if(this == &oth) return *this;
					list tmp {oth};
					std::swap(*this, tmp);
					return *this;
				}

				list& operator= (list&& oth) {
					if(this == &oth) return *this;
					clear();

					length = oth.length;
					this->head.next = oth.head.next ;
					this->tail.prev = oth.tail.prev ;

					oth.length = 0;
					oth.head.next = &oth.tail;
					oth.tail.prev = &oth.head;

					return *this;
				}

				void push_back(const Object& object){
					insert( object, end() );
				}
				void push_back(Object&& object){
					insert( std::move(object), end() );
				}

				void push_front(const Object& object){
					insert( object, begin() );
				}
				void push_front(Object&& object){
					insert( std::move(object), begin() );
				}

				void pop_back() {
					erase( --end() );
				}

				void pop_front() {
					erase( begin() ) ;
				}

				iterator insert(const Object &object, iterator it) {
					node* ptr { it.nodeptr };
					ptr->prev = ptr->prev->next = new node{ object, ptr, ptr->prev};
					length++;
					return ptr->prev;
				}

				iterator insert( Object &&object, iterator it) {
					node* ptr { it.nodeptr };
					ptr->prev = ptr->prev->next = new node{ std::move(object), ptr, ptr->prev};
					length++;
					return ptr->prev;
				}

				iterator erase(iterator it){

					node* ptr { it.nodeptr };
					node* ret_val {ptr->next};
					ptr->prev->next = ptr->next;
					ptr->next->prev = ptr->prev;

					length--;
					delete ptr;

					return ret_val;
				}

				iterator erase(iterator from, iterator to){
					iterator it {from};
					while( it != to ){
						it = erase(it);
					}
					return to;
				}

				void splice(iterator position, list& lst){

					if(lst.empty()) return;

					node *pos_ptr{position.nodeptr},
					     *preceding_pos_ptr{ position.nodeptr->prev },
						 *first_node_lst{ lst.head.next },
						 *last_node_lst{ lst.tail.prev };

					first_node_lst->prev = preceding_pos_ptr;
					preceding_pos_ptr->next = first_node_lst;
					last_node_lst->next = pos_ptr;
					pos_ptr->prev = last_node_lst;

					lst.length = 0;
					lst.head.next = &lst.tail;
					lst.tail.prev = &lst.head;
				}

				std::size_t size() const {
					return length;
				}

				bool empty() const {
					return length == 0;
				}

				void clear() {
					erase( begin(), end() );
				}

				Object& front() {
					return head.next->data;
				}

				Object& back() {
					return tail.prev->data;
				}

				iterator begin() {
					return iterator{ head.next } ;
				}

				iterator end() {
					return iterator{ &tail } ;
				}

				private:
				std::size_t length;
				node head, tail;
		};
}

int main(){

	samarth::list<int> li1{ 1,2,3,4,5,6,7,8};
	samarth::list<int> li2{ 10,20,30,40,50,60,70,80};

	li1.splice( ++li1.begin(), li2 );

	for(auto a : li1) std::cout << a << std::endl;

}
