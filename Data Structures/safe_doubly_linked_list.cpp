// Stringent iterator checking. 
// It checks the validity of a iterator before insertions, deletions,
// dereferencing and any other operation that requires valid iterators.

// If iterator is invalid throws std::runtime_error

#ifndef SAMARTH_SAFE_LIST
#define SAMARTH_SAFE_LIST 

#include <vector>
#include <stdexcept>
#include <utility>
#include <iterator>

namespace samarth {

	template<typename Object>
		class safe_list 
		{
			public: struct iterator;
			private:
				struct node
				{			
					Object data;
					node* next;
					node* prev;
					std::vector<iterator*> itr_record;

					node() = delete;
					node(const Object &data, node* next, node* prev): 
						data{data}, 
						next{next},
						prev{prev},
						itr_record{}
					{}
					node(Object &&data, node* next, node* prev) noexcept: 
						data{ std::move(data) }, 
						next{next},
						prev{prev},
						itr_record{}
					{}
					node(node& oth) = delete ;
					node( node&& oth) noexcept = delete ;

					~node(){
						for(auto ptr: itr_record) ptr->nodeptr = nullptr;
					}
				};

				std::size_t length;
				node head, tail;


			public:
				struct iterator 
				{
					private:
					node* nodeptr;
					safe_list* listptr;

					std::vector<iterator*> & get_itr_record(){
						return nodeptr->itr_record;
					}

					void assert_validity() const {
						if(listptr == nullptr or nodeptr == nullptr or nodeptr == &listptr->head)
							throw std::runtime_error {"Invalid iterator."};
					}

					void assert_validity(safe_list* calling_container) const {
						assert_validity();
						if(calling_container != listptr) 
							throw std::runtime_error {"Invalid iterator. Iterator belongs to a different list"};
					}

					void remove_from_iterator_record(){
						 auto &itr_record { get_itr_record() };
						 auto it_vec { itr_record.end() };
						 
						 do{
							 it_vec--;
							 if(*it_vec == this){
								 itr_record.erase(it_vec);
								 return;
							 }
						 } while( it_vec != itr_record.begin() );

						 throw std::runtime_error {"Iterator not found to remove in remove_from_iterator_record() call"};
					}
					
					void add_to_iterator_record() {
						assert_validity();
						get_itr_record().push_back(this);
					}

					public:
					using iterator_category = std::bidirectional_iterator_tag;
					using value_type        = Object;
					using difference_type   = std::ptrdiff_t;
					using pointer           = value_type*;
					using reference         = value_type&;

					iterator(): nodeptr{nullptr}, listptr{nullptr} {}
					iterator(node* nodeptr, safe_list* listptr): nodeptr{nodeptr}, listptr{listptr} {
						add_to_iterator_record();
					}
					iterator(const iterator& oth): nodeptr{oth.nodeptr}, listptr{oth.listptr} {
						add_to_iterator_record();
					}
					iterator(iterator&& oth):nodeptr{oth.nodeptr}, listptr{oth.listptr} {
						this->add_to_iterator_record();
						oth.remove_from_iterator_record();
						oth.nodeptr = nullptr;
						oth.listptr = nullptr;
					}
					~iterator() {
						if(nodeptr) this->remove_from_iterator_record();
					}

					iterator& operator=( const iterator &oth ){
						if(this == &oth) return *this;

						if(nodeptr) this->remove_from_iterator_record();
						nodeptr = oth.nodeptr;
						listptr = oth.listptr;
						this->add_to_iterator_record();

						return *this;
					}
					iterator& operator=( iterator&& oth) {
						if(this == &oth) return *this;

						if(nodeptr) this->remove_from_iterator_record();
						nodeptr = oth.nodeptr;
						listptr = oth.listptr;
						add_to_iterator_record();

						oth.remove_from_iterator_record();
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
						assert_validity();
						this->remove_from_iterator_record();
						nodeptr = nodeptr->next;
						this->add_to_iterator_record();
						return *this;
					}

					iterator operator++(int){
						iterator tmp {nodeptr};
						++(*this);
						return tmp;
					}

					iterator& operator--(){
						assert_validity();
						this->remove_from_iterator_record();
						nodeptr = nodeptr->prev;
						this->add_to_iterator_record();
						return *this;
					}

					iterator operator--(int){
						iterator tmp {nodeptr};
						--(*this);
						return tmp;
					}

					template<typename>
						friend class safe_list;
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
					const_iterator(node* nodeptr, safe_list* listptr): it{nodeptr, listptr} {}
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

			public:
				safe_list(): 
					length{},
					head{ Object{}, &tail, nullptr},
					tail{ Object{}, nullptr, &head}
				{}

				safe_list(std::initializer_list<Object> initr_record): safe_list() {
					for( const Object &object : initr_record ) push_back( object );
				}

				safe_list(const safe_list &other) :safe_list() {
					for(const Object &object : other) push_back( object );
				}

				safe_list(safe_list &&oth):
					length{oth.length},
					head{ Object{}, oth.head.next, nullptr },
					tail{ Object{}, nullptr, oth.tail.prev }
				{
					oth.length = 0;
					oth.head.next = &oth.tail;
					oth.tail.prev = &oth.head;
				}

				~safe_list() {
					clear();
				}

				safe_list& operator= (const safe_list& oth) {
					if(this == &oth) return *this;

					clear();
					for(const Object &object : oth) push_back( object );

					return *this;
				}

				safe_list& operator= (safe_list&& oth) {

					if(this == &oth) return *this;
					clear();

					length = oth.length;
					this->head.next = oth.head.next ;
					this->tail.prev = oth.tail.prev ;
					this->

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

				iterator erase(iterator it){
					it.assert_validity(this);

					node* ptr { it.nodeptr };
					iterator ret_val {ptr->next, this};

					ptr->prev->next = ptr->next;
					ptr->next->prev = ptr->prev;

					length--;
					delete ptr;

					return ret_val;
				}

				iterator erase(iterator from, iterator to){
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
					auto non_const_this { const_cast<safe_list*>(this) };
					return const_iterator{ head.next, non_const_this };
				}

				iterator end() {
					return iterator{ &tail, this } ;
				}
				const_iterator end() const {
					auto non_const_tail { const_cast<node*>(&tail) };
					auto non_const_this { const_cast<safe_list*>(this) };
					return const_iterator{ non_const_tail , non_const_this }; 
				}		  								
		};
}

#endif
