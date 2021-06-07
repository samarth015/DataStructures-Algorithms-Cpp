#ifndef SAMARTH_LIST
#define SAMARTH_LIST

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

				struct reverse_iterator
				{
					private:
						iterator it;

					public:
						using iterator_category = typename iterator::iterator_category; 
						using value_type        = typename iterator::value_type; 
						using difference_type   = typename iterator::difference_type;
						using pointer           = typename iterator::pointer;
						using reference         = typename iterator::reference;

						reverse_iterator(): it{} {}
						reverse_iterator(node* nodeptr): it{nodeptr} {}
						reverse_iterator(const reverse_iterator &other): it{other.it} {}
						reverse_iterator & operator = (const reverse_iterator &other){
							it = other.it;
							return *this;
						}
						reverse_iterator(reverse_iterator &&other) noexcept: it{std::move(other.it)} {}
						reverse_iterator & operator = (reverse_iterator &&other) noexcept {
							it = std::move(other.it);
							return *this;
						}
						~ reverse_iterator() = default;

						Object& operator*() {
							return *it;
						}

						Object* operator->() {
							return it.operator->();
						}

						bool operator==(const reverse_iterator &oth){
							return it == oth.it;
						}

						bool operator!=(const reverse_iterator &oth){
							return it != oth.it;
						}

						reverse_iterator& operator++(){
							--it;
							return *this;
						}

						reverse_iterator operator++(int){
							reverse_iterator tmp {*this};
							--it;
							return tmp;
						}

						reverse_iterator& operator--(){
							++it;
							return *this;
						}

						reverse_iterator operator--(int){
							reverse_iterator tmp {*this};
							++it;
							return tmp;
						}
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

				struct const_reverse_iterator {
					private:
						iterator it;

					public:
						using iterator_category = typename iterator::iterator_category; 
						using value_type        = typename iterator::value_type; 
						using difference_type   = typename iterator::difference_type;
						using pointer           = typename iterator::pointer;
						using reference         = typename iterator::reference;

						const_reverse_iterator(): it{} {}
						const_reverse_iterator(node* nodeptr): it{nodeptr} {}
						const_reverse_iterator(const const_reverse_iterator &other): it{other.it} {}
						const_reverse_iterator & operator = (const const_reverse_iterator &other){
							it = other.it;
							return *this;
						}
						const_reverse_iterator(const_reverse_iterator &&other) noexcept: it{std::move(other.it)} {}
						const_reverse_iterator & operator = (const_reverse_iterator &&other) noexcept {
							it = std::move(other.it);
							return *this;
						}
						~ const_reverse_iterator() = default;

						const Object& operator*() {
							return *it;
						}

						const Object* operator->() {
							return it.operator->();
						}

						bool operator==(const const_reverse_iterator &oth){
							return it == oth.it;
						}

						bool operator!=(const const_reverse_iterator &oth){
							return it != oth.it;
						}

						const_reverse_iterator& operator++(){
							--it;
							return *this;
						}

						const_reverse_iterator operator++(int){
							const_reverse_iterator tmp {*this};
							--it;
							return tmp;
						}

						const_reverse_iterator& operator--(){
							++it;
							return *this;
						}

						const_reverse_iterator operator--(int){
							const_reverse_iterator tmp {*this};
							++it;
							return tmp;
						}
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
				const_iterator begin() const {
					return const_iterator{ head.next };
				}

				iterator end() {
					return iterator{ &tail } ;
				}
				const_iterator end() const {
					return const_iterator{ const_cast<node*>(&tail) }; // A call to end() is made when the list object is const.
				}		  								// So tail is also const. A const node* cannot be assigned to node* type.

				reverse_iterator rbegin() {
					return reverse_iterator{ tail.prev };
				}
				const_reverse_iterator rbegin() const {
					return const_reverse_iterator{ tail.prev };
				}

				reverse_iterator rend(){
					return reverse_iterator{ const_cast<node*>(&head) };
				}
				const_reverse_iterator rend() const {
					return const_reverse_iterator {&head};
				}

			private:
				std::size_t length;
				node head, tail;
		};
}

#endif
