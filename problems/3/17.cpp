/*

	Modify the List class to provide stringent iterator checking by using the ideas
	suggested at the end of Section 3.5.

*/

#include <iostream>
#include <vector>
#include <stdexcept>

#include <utility>
#include <iterator>

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
					private:
					node* nodeptr;
					list* listptr;

					void assert_validity() const {
						if(listptr == nullptr or nodeptr == nullptr or nodeptr == &listptr->head)
							throw std::runtime_error {"Invalid iterator."};
					}

					void assert_validity(list* calling_container) const {
						assert_validity();
						if(calling_container != listptr) 
							throw std::runtime_error {"Invalid iterator. Iterator belongs to a different list"};
					}

					public:
					using iterator_category = std::bidirectional_iterator_tag;
					using value_type        = Object;
					using difference_type   = std::ptrdiff_t;
					using pointer           = value_type*;
					using reference         = value_type&;

					iterator(): nodeptr{nullptr}, listptr{nullptr} {}
					iterator(node* nodeptr, list* listptr): nodeptr{nodeptr}, listptr{listptr} {}
					iterator(const iterator& oth): nodeptr{oth.nodeptr}, listptr{oth.listptr} {}
					iterator(iterator&& oth):nodeptr{oth.nodeptr}, listptr{oth.listptr} {
						oth.nodeptr = nullptr;
						oth.listptr = nullptr;
					}
					~iterator() = default;

					iterator& operator=( const iterator &oth ){
						if(this == &oth) return *this;
						nodeptr = oth.nodeptr;
						listptr = oth.listptr;
						return *this;
					}
					iterator& operator=( iterator&& oth) {
						nodeptr = oth.nodeptr;
						listptr = oth.listptr;
						oth.nodeptr = nullptr;
						oth.listptr = nullptr;
						return *this;
					}

					Object& operator*() {
						assert_validity();
						return nodeptr->data;
					}

					Object* operator->() {
						assert_validity();
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
				};

				struct const_iterator {
					private:
					iterator it;

					public:
					using iterator_category = typename iterator::iterator_category; 
					using value_type        = typename iterator::value_type; 
					using difference_type   = typename iterator::difference_type;
					using pointer           = typename iterator::pointer;
					using reference         = typename iterator::reference;

					const_iterator(): it{} {}
					const_iterator(node* nodeptr, list* listptr): it{nodeptr, listptr} {}
					const_iterator(const const_iterator &other): it{other.it} {}
					const_iterator & operator = (const const_iterator &other){
						it = other.it;
						return *this;
					}
					const_iterator(const_iterator &&other) noexcept: it{std::move(other.it)} {}
					const_iterator & operator = (const_iterator &&other) noexcept {
						it = std::move(other.it);
						return *this;
					}
					~ const_iterator() = default;

					const Object& operator*() {
						return *it;
					}

					const Object* operator->() {
						return it.operator->();
					}

					bool operator==(const const_iterator &oth){
						return it == oth.it;
					}

					bool operator!=(const const_iterator &oth){
						return it != oth.it;
					}

					const_iterator& operator++(){
						++it;
						return *this;
					}

					const_iterator operator++(int){
						const_iterator tmp {*this};
						++it;
						return tmp;
					}

					const_iterator& operator--(){
						--it;
						return *this;
					}

					const_iterator operator--(int){
						const_iterator tmp {*this};
						--it;
						return tmp;
					}
				};

				list(): 
					length{},
					head{ Object{}, &tail, nullptr},
					tail{ Object{}, nullptr, &head} 
				{}

				list(std::initializer_list<Object> init_list): list() {
					for( const Object &object : init_list ) push_back( object );
				}

				list(const list &other) :list() {
					for(const Object &object : other) push_back( object );
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
					it.assert_validity(this);

					node* ptr { it.nodeptr };
					ptr->prev = ptr->prev->next = new node{ object, ptr, ptr->prev};
					length++;

					return {ptr->prev, this};
				}

				iterator insert( Object &&object, iterator it) {
					it.assert_validity(this);

					node* ptr { it.nodeptr };
					ptr->prev = ptr->prev->next = new node{ std::move(object), ptr, ptr->prev};
					length++;

					return {ptr->prev, this};
				}

				iterator erase(iterator& it){
					it.assert_validity(this);

					node* ptr { it.nodeptr };
					node* ret_val {ptr->next};
					ptr->prev->next = ptr->next;
					ptr->next->prev = ptr->prev;

					length--;
					delete ptr;
					it.nodeptr = nullptr;     //Sets iterator to null so it cannot be reused.

					return {ret_val, this};
				}

				iterator erase(iterator& from, iterator& to){
					to.assert_validity(this);

					iterator it {from};
					while( it != to ){
						it = erase(it);
					}
					return to;
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
					return iterator{ head.next, this } ;
				}
				const_iterator begin() const {
					auto non_const_this { const_cast<list*>(this) };
					return const_iterator{ head.next, non_const_this };
				}

				iterator end() {
					return iterator{ &tail, this } ;
				}
				const_iterator end() const {
					auto non_const_tail { const_cast<node*>(&tail) };
					auto non_const_this { const_cast<list*>(this) };
					return const_iterator{ non_const_tail , non_const_this }; 
				}		  								

			private:
				std::size_t length;
				node head, tail;
		};
}

//Commented code uses invalid iterators and will not work.

int main() {

	samarth::list<int> li {1,2,3,4,5,6,7};
	
	samarth::list<int>::iterator it1 {};
	//std::cout << *it1 << std::endl;          //Uninitialized iterator will not dereference

	auto it2 { --li.begin() };            

	//std::cout << *it2 << std::endl;        // Iterator cannot point at head (before begin()) 

	auto it3 { ++li.end() };

	//std::cout << *it3 << std::endl;        // Iterator cannot point past the tail.  (after end())

	auto li2 = li;

	//li.insert( 10 , li2.begin());            // list mismatch.
}
