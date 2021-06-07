/*
	 
	An alternative to the deletion strategy we have given is to use lazy deletion. To
	delete an element, we merely mark it deleted (using an extra bit ﬁeld). The number
	of deleted and nondeleted elements in the list is kept as part of the data structure. If
	there are as many deleted elements as nondeleted elements, we traverse the entire
	list, performing the standard deletion algorithm on all marked nodes.
		a. List the advantages and disadvantages of lazy deletion.
		b. Write routines to implement the standard linked list operations using lazy
		deletion.
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
					bool is_deleted;

					node() = delete;
					node(const Object &data, node* next, node* prev): 
						data{data}, 
						next{next},
						prev{prev}, 
						is_deleted{false}
					{}
					node(Object &&data, node* next, node* prev) noexcept: 
						data{ std::move(data) }, 
						next{next},
						prev{prev},
						is_deleted{false}
					{}
					node(node& oth) = delete ;
					node( node&& oth) noexcept = delete ;
					~node() = default;
				};

				void mark_node_as_deleted(node* ptr){
					ptr->is_deleted = true;
					deleted_size++;
					if( deleted_size >= non_deleted_size ) lazy_deletion();
				}

				void lazy_deletion(){
					node *curr{head.next}, *prev{&head};
					while(curr != &tail){
						curr = curr->next;
						if(prev->next->is_deleted){
							delete prev->next;
							prev->next = curr;
							curr->prev = prev;
						}
						else {
							prev = prev->next;
						}
					}
					deleted_size = 0;
				}

			public:
				struct iterator 
				{
					private:
					node* nodeptr;
					
					public:
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
						do{
							nodeptr = nodeptr->next;
						} while( nodeptr->is_deleted == true);

						return *this;
					}

					iterator operator++(int){
						iterator tmp {nodeptr};
						++(*this);
						return tmp;
					}

					iterator& operator--(){
						do{
							nodeptr = nodeptr->prev;
						} while( nodeptr->is_deleted == true);

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
					const_iterator(node* nodeptr): it{nodeptr} {}
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
					non_deleted_size{},
					deleted_size{},
					head{ Object{}, &tail, nullptr},
					tail{ Object{}, nullptr, &head} 
				{}

				list(std::initializer_list<Object> init_list): list() {
					for( auto &object : init_list ) push_back( object );
				}

				list(const list &other) :list() {
					for(const Object &object : other) push_back( object );
				}

				list(list &&oth):
					non_deleted_size{oth.non_deleted_size},
					deleted_size{oth.deleted_size},
					head{ Object{}, oth.head.next, nullptr },
					tail{ Object{}, nullptr, oth.tail.prev } 
				{
					oth.non_deleted_size = 0;
					oth.deleted_size = 0;
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

					non_deleted_size = oth.non_deleted_size;
					deleted_size = oth.deleted_size;
					this->head.next = oth.head.next ;
					this->tail.prev = oth.tail.prev ;

					oth.non_deleted_size = 0;
					oth.deleted_size = 0;
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
					non_deleted_size++;
					return ptr->prev;
				}

				iterator insert( Object &&object, iterator it) {
					node* ptr { it.nodeptr };
					ptr->prev = ptr->prev->next = new node{ std::move(object), ptr, ptr->prev};
					non_deleted_size++;
					return ptr->prev;
				}

				iterator erase(iterator it){

					node *ptr { it.nodeptr };
					node *ret_val {ptr->next};

					non_deleted_size--;
					mark_node_as_deleted(ptr);

					return ret_val;
				}

				iterator erase(iterator from, iterator to){
					iterator it {from};
					while( it != to ){
						it = erase(it);
					}
					return to;
				}

				std::size_t size() const {
					return non_deleted_size;
				}

				bool empty() const {
					return non_deleted_size == 0;
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
						
					return ++iterator{ &head } ;
				}
				const_iterator begin() const {
					return const_iterator{ head.next };
				}

				iterator end() {
					return iterator{ &tail } ;
				}
				const_iterator end() const {
					return const_iterator{ const_cast<node*>(&tail) }; // A call to end() is made when the list object is const.
				}		  								// So tail is also const. A const node* cannot be assigned to node* type.

			private:
				std::size_t non_deleted_size, deleted_size;
				node head, tail;
		};
}


int main(){
	samarth::list<int> li {1,2,3,4,5};
	auto it = ++li.begin();	
	li.erase(it);
	for(auto a : li) std::cout << a << " ";
	std::cout << std::endl;
	li.erase(li.begin());
	for(auto a : li) std::cout << a << " ";
	std::cout << std::endl;
	li.erase(--li.end());
	for(auto a : li) std::cout << a << " ";
	std::cout << std::endl;
	li.push_back(10);
	li.push_back(20);
	for(auto a : li) std::cout << a << " ";
	std::cout << std::endl;
	li.pop_front();
	li.pop_back();
	for(auto a : li) std::cout << a << " ";
	std::cout << std::endl;
}
