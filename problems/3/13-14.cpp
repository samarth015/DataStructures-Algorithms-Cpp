/* 
  Q13
  Add support for operator- to the List iterator classes.

  Q14
	  Looking ahead in an STL iterator requires an application of operator++ , which in
	turn advances the iterator. In some cases looking at the next item in the list, without
	advancing to it, may be preferable. Write the member function with the declaration:

		const_iterator operator+( int k ) const;

	to facilitate this in a general case. The binary operator+ returns an iterator that
	corresponds to k positions ahead of current

*/

// Go to lines 117-154 or 226-263 to see the overload.

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
						return nodeptr->data; }

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

					iterator operator + (long long i) const {
						iterator result_it { *this };
						while(i > 0){
							++result_it;
							i--;
						}
						while(i < 0){
							--result_it;
							i++;
						}
						return result_it;
					}

					friend iterator operator + (long long i, iterator it){
						return it + i;
					}

					iterator operator - (long long i){
						return *this + (-i);
					}

					long long operator - ( iterator other ){
						long long i{};
						iterator curr { *this };
						while( curr.nodeptr != nullptr and curr != other ) {
							curr++; i++;
						}
						if(curr == other) return i;

						curr = *this; 
						i = 0;
						while( curr.nodeptr != nullptr and curr != other ){
							curr--; i--;
						}
						if(curr == other) return i;

						throw std::runtime_error {"One or both iterators used in operator- is/are invalid."};
					}

					template<typename> friend class list;

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
					oth.head.next = nullptr;
					oth.tail.next = nullptr;
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
					this->head->next = oth.head->next ;
					oth.head->next = &oth.tail;
					this->tail->prev = oth.tail->prev ;
					oth.tail->prev = &oth.head;
					oth.length = 0;
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

				iterator end() {
					return iterator{ &tail } ;
				}

			private:
				std::size_t length;
				node head, tail;
		};
}

#include <iostream>

int main(){

	samarth::list<int> li {1,2,3,4,5,6,7};

	//Testing -
	auto it { li.end() - 2 };
	std::cout << *it << std::endl;
	it = it - 3;
	std::cout << *it << std::endl;

	std::cout << li.begin() - it << std::endl;

	//Testing +

	it = li.begin() + 6;
	std::cout << *it << std::endl;

}
