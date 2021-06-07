#include <iostream>
#include <algorithm>
/*

   Swap two adjacent elements by adjusting only the links (and not the data) using
   a. singly linked lists
   b. doubly linked lists

*/

// NOTE : Answer at bottom.

//Implementation of singly list. 
template<typename Object>
class singly_list
{
	private:
		struct node
		{
			Object data;
			node *next;

			node(const Object &data, node* next):
				data{data},
				next{next}
			{}
			node(Object &&data, node* next):
				data{std::move(data)},
				next{next}
			{}

			node() = delete;
			node(const node &other) = delete;
			node & operator = (const node &other) = delete;
			node(node &&other) noexcept = delete;
			node & operator = (node &&other) noexcept = delete;
			~ node() = default;

		};

		struct iterator
		{
			node *currptr, *prevptr; 

			using iterator_category = std::forward_iterator_tag;
			using value_type        = Object;
			using difference_type   = std::ptrdiff_t;
			using pointer           = value_type*;
			using reference         = value_type&;

			iterator(): currptr{}, prevptr{} {}
			iterator(node* currptr, node* prevptr): currptr{currptr}, prevptr{prevptr} {}
			iterator(const iterator &other): currptr{other.currptr}, prevptr{other.prevptr} {}

			iterator & operator = (const iterator &other){
				if(this == &other) return *this;
				currptr = other.currptr;
				prevptr = other.prevptr;
				return *this;
			}

			iterator(iterator &&other) noexcept: currptr{other.currptr}, prevptr(other.prevptr) {
				other.currptr = nullptr;
				other.prevptr = nullptr;
			}

			iterator & operator = (iterator &&other) noexcept {
				if(this == &other) return *this;
				currptr = other.currptr;
				prevptr = other.prevptr;
				other.currptr = nullptr;
				other.prevptr = nullptr;
				return *this;
			}

			~ iterator() = default;

			Object& operator*() {
				return currptr->data;
			}

			Object* operator->() {
				return currptr;
			}

			bool operator==(const iterator &oth){
				return oth.currptr == this->currptr ;
			}

			bool operator!=(const iterator &oth){
				return !(*this == oth);
			}

			iterator& operator++(){
				prevptr = currptr;
				currptr = currptr->next;
				return *this;
			}

			iterator operator++(int){
				iterator tmp {currptr};
				++(*this);
				return tmp;
			}
		};

		struct const_iterator{
			node *currptr, *prevptr; 

			using const_iterator_category = std::forward_iterator_tag;
			using value_type        = Object;
			using difference_type   = std::ptrdiff_t;
			using pointer           = value_type*;
			using reference         = value_type&;

			const_iterator(): currptr{}, prevptr{} {}
			const_iterator(node* currptr, node* prevptr): currptr{currptr}, prevptr{prevptr} {}
			const_iterator(const const_iterator &other): currptr{other.currptr}, prevptr{other.prevptr} {}

			const_iterator & operator = (const const_iterator &other){
				if(this == &other) return *this;
				currptr = other.currptr;
				prevptr = other.prevptr;
				return *this;
			}

			const_iterator(const_iterator &&other) noexcept: currptr{other.currptr}, prevptr(other.prevptr) {
				other.currptr = nullptr;
				other.prevptr = nullptr;
			}

			const_iterator & operator = (const_iterator &&other) noexcept {
				if(this == &other) return *this;
				currptr = other.currptr;
				prevptr = other.prevptr;
				other.currptr = nullptr;
				other.prevptr = nullptr;
				return *this;
			}

			~ const_iterator() = default;

			const Object& operator*() const {
				return currptr->data;
			}

			const Object* operator->() const {
				return currptr;
			}

			bool operator==(const const_iterator &oth){
				return oth.currptr == this->currptr ;
			}

			bool operator!=(const const_iterator &oth){
				return !(*this == oth);
			}

			const_iterator& operator++(){
				prevptr = currptr;
				currptr = currptr->next;
				return *this;
			}

			const_iterator operator++(int){
				const_iterator tmp {currptr};
				++(*this);
				return tmp;
			}
		};

		node *head, *tail, *second_last;
		std::size_t length;

	public:
		singly_list():
			head{nullptr},
			tail{nullptr},
			second_last{nullptr},
			length{}
		{
			tail = new node { Object{}, nullptr };
			second_last = head = new node { Object{}, tail };
		}

		singly_list(std::initializer_list<Object> init_list): singly_list() {
			for(auto & object : init_list)
				push_back(object);
		}

		singly_list(const singly_list &other): singly_list() {
			for(auto & object : other) 
				push_back(object);
		}

		singly_list & operator = (const singly_list &other){
			if(this == &other) return *this;

			singly_list temp {other};
			std::swap(*this,temp);

			return *this;
		}

		singly_list(singly_list &&other) noexcept: 
			head{other.head},
			tail{other.tail},
			second_last{other.second_last},
			length{other.length}
		{
			other.head = nullptr;
			other.tail = nullptr;
			other.second_last = nullptr;
			other.length = 0;
		}

		singly_list & operator = (singly_list &&other) noexcept {
			if(this == &other) return *this;
			clear();

			head = other.head;
			tail = other.tail;
			second_last = other.second_last;
			length = other.length;

			other.head = nullptr;
			other.tail = nullptr;
			other.second_last = nullptr;
			other.length = 0;

			return *this;
		}

		~ singly_list() {
			erase( begin(), end());
			if(head) delete head;
			if(tail) delete tail;	
		}

		void clear(){
			erase( begin(), end());
			length = 0;
		}

		bool empty() const {
			return length == 0;
		}

		std::size_t size() const {
			return length;
		}

		iterator insert(iterator it, const Object &val){
			auto new_node_ptr = it.prevptr->next = new node{val, it.currptr};
			if( it.currptr == tail ) second_last = new_node_ptr;
			length++;
			return iterator{ new_node_ptr, it.prevptr };
		}

		iterator insert(iterator it, Object &&val){
			auto new_node_ptr = it.prevptr->next = new node{std::move(val), it.currptr};
			if( it.currptr == tail ) second_last = new_node_ptr;
			length++;
			return iterator{ new_node_ptr, it.prevptr };
		}

		Object& front(){
			return head->next->data;
		}
		const Object& front() const {
			return head->next->data;
		}
		Object& back(){
			return second_last->data;
		}
		const Object& back() const {
			return second_last->data;
		}

		iterator erase( iterator it ){
			auto tempit = it.prevptr->next = it.currptr->next;
			if( it.currptr == second_last )
				second_last = it.prevptr;
			delete it.currptr;
			length--;
			return iterator{ tempit, it.prevptr };
		}

		iterator erase(iterator from, iterator to){
			iterator it {from};
			while( it != to ){
				it = erase(it);
			}
			return to;
		}

		iterator begin(){
			return iterator{ head->next, head };
		}
		const_iterator begin() const {
			return const_iterator{ head->next, head} ;
		}
		iterator end(){
			return iterator{ tail, second_last };
		}
		const_iterator end() const {
			return const_iterator{ tail, second_last };
		}

		void push_back(const Object &val){
			insert(end(), val);
		}
		void push_back(Object &&val){
			insert(end(), std::move(val));
		}
		void push_front(const Object &val){
			insert(begin(), val);
		}
		void push_front(Object &&val){
			insert(begin(), std::move(val));
		}

		void pop_back(){
			iterator it { begin() };
			while( it.currptr != second_last ) it++;
			it.prevptr->next = second_last->next;
			delete second_last;
			length--;
			second_last = it.prevptr;
		}

		void pop_front(){
			erase(begin());
		}


		void swap_adjacent( iterator it );
};


//Implementation of doubly linked list.
template<typename Object>
class doubly_list 
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

			node* nodeptr;
		};

		struct const_iterator {
			using iterator_category = std::bidirectional_iterator_tag;
			using value_type        = Object;
			using difference_type   = std::ptrdiff_t;
			using pointer           = value_type*;
			using reference         = value_type&;

			const_iterator(): nodeptr{nullptr} {}
			const_iterator(node* nodeptr): nodeptr{nodeptr} {}
			const_iterator(const const_iterator& oth): nodeptr{oth.nodeptr} {}
			const_iterator(const_iterator&& oth):nodeptr{oth.nodeptr} {
				oth.nodeptr = nullptr;
			}
			~const_iterator() = default;

			const_iterator& operator=( const const_iterator &oth ){
				nodeptr = oth.nodeptr;
				return *this;
			}
			const_iterator& operator=( const_iterator&& oth) {
				nodeptr = oth.nodeptr;
				oth.nodeptr = nullptr;
				return *this;
			}

			const Object& operator*() {
				return nodeptr->data;
			}

			const Object* operator->() {
				return nodeptr;
			}

			bool operator==(const const_iterator &oth){
				return oth.nodeptr == this->nodeptr;
			}

			bool operator!=(const const_iterator &oth){
				return oth.nodeptr != this->nodeptr;
			}

			const_iterator& operator++(){
				nodeptr = nodeptr->next;
				return *this;
			}

			const_iterator operator++(int){
				const_iterator tmp {nodeptr};
				++(*this);
				return tmp;
			}

			const_iterator& operator--(){
				nodeptr = nodeptr->prev;
				return *this;
			}

			const_iterator operator--(int){
				const_iterator tmp {nodeptr};
				--(*this);
				return tmp;
			}

			node* nodeptr;
		};

	public:

		doubly_list(): 
			length{},
			head{ Object{}, &tail, nullptr},
			tail{ Object{}, nullptr, &head} 
		{}

		doubly_list(std::initializer_list<Object> init_doubly_list): doubly_list() {
			for( auto &object : init_doubly_list ) push_back( object );
		}

		doubly_list(const doubly_list &other) :doubly_list() {
			for( auto &object : other ) push_back( object );
		}

		doubly_list(doubly_list &&oth):
			length{oth.length},
			head{ Object{}, oth.head.next, nullptr },
			tail{ Object{}, nullptr, oth.tail.prev } 
		{
			oth.length = 0;
			oth.head.next = nullptr;
			oth.tail.next = nullptr;
		}

		~doubly_list() {
			clear();
		}

		doubly_list& operator= (const doubly_list& oth) {
			doubly_list tmp {oth};
			std::swap(*this, tmp);
			return *this;
		}

		doubly_list& operator= (doubly_list&& oth) {
			clear();
			this->head->next = oth.head->next ;
			oth.head->next = &oth.tail;
			this->tail->prev = oth.tail->prev ;
			oth.tail->prev = &oth.head;
			oth.length = 0;
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
			return const_iterator{ &tail } ;
		}

		void swap_adjacent(iterator it);    

	private:
		std::size_t length;
		node head, tail;
};

// Methods to swaps adjacent elements. Take an iterator and swaps it with the element to its right.

template<typename Object>
void doubly_list<Object>::swap_adjacent (doubly_list<Object>::iterator it) {

	if( it == end() or it == --end() ) throw std::out_of_range {"Iterator argument cannot be equal to end() or the one before end()"};

	auto left{it.nodeptr}, right{(++it).nodeptr};

	right->prev = left->prev;
	left->prev = left->prev->next = right;
	left->next = right->next;
	right->next = right->next->prev = left;
}

template<typename Object>
void singly_list<Object>::swap_adjacent (singly_list<Object>::iterator it) {

	if( it == end() or it.currptr == second_last) throw std::out_of_range {"Iterator argument cannot be equal to end() or the one before end()"};

	it.prevptr->next = it.currptr->next;
	it.currptr->next = it.currptr->next->next;
	it.prevptr->next->next = it.currptr;
}

int main(){

	doubly_list<int> li1 { 1, 2, 3, 4, 5, 6, 7, 8, 9};
	singly_list<int> li2 { 1, 2, 3, 4, 5, 6, 7, 8, 9};

	std::cout << "Doubly Test" << std::endl;
	li1.swap_adjacent(li1.begin());
	auto it = std::find(li1.begin(), li1.end(), 5);
	li1.swap_adjacent(it);
	for(auto ele : li1) std::cout << ele << " ";
	std::cout << std::endl;

	auto it2 { li1.end() };
	do{
		--it2;
		std::cout << *it2 << " " ;
	}while(it2!=li1.begin());
	std::cout <<  std::endl;

	std::cout << "Singly Test" << std::endl;
	li2.swap_adjacent(li2.begin());
	auto it3 = std::find(li2.begin(), li2.end(), 5);
	li2.swap_adjacent(it3);
	for(auto ele : li2) std::cout << ele << " ";
	std::cout << std::endl;
}
