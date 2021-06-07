/*
	 
	 Rewrite the List class without using header and tail nodes and describe the
	differences between the class and the class provided in Section 3.5.

*/


/*
 
 
   The original version was much better as it eliminated a lot of cases which need to be considered
   when not using sentinal nodes( head and tail ). Specially in the methods insert and erase both of 
   which have to treat 4 possible cases seperately.

  When list is empty the new version uses points at nullptr while older version pointed at tail node.
  So --end() is an invalid operation for this implementation.

  No major difference in iterator design.

*/

#include <iostream>
#include <utility>
#include <iterator>
#include <algorithm>

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
					length{},
					head{nullptr},
					tail{nullptr} 
				{}

				list(std::initializer_list<Object> init_list): list() {
					for( const Object &object : init_list ) push_back( object );
				}

				list(const list &other) :list() {
					for(const Object &object : other) push_back( object );
				}

				list(list &&oth):
					length{oth.length},
					head{oth.head},
					tail{oth.tail} 
				{
					oth.length = 0;
					oth.head = nullptr;
					oth.tail = nullptr;
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
					head = oth.head;
					tail = oth.tail;

					oth.length = 0;
					oth.head = nullptr;
					oth.tail = nullptr;

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
					erase( iterator{tail} );
				}

				void pop_front() {
					erase( begin() ) ;
				}

				iterator insert(const Object &object, iterator it) {
					node* ret_val;
					if(empty()){
						ret_val = head = tail = new node{object, nullptr, nullptr };
					}
					else if(it == begin()){
						ret_val = new node {object, head, nullptr};
						head->prev = ret_val;
						head = ret_val;
					}
					else if(it == end()){
						ret_val = new node {object, nullptr, tail};
						tail->next = ret_val;
						tail = ret_val;
					}
					else {
						node* ptr { it.nodeptr };
						ptr->prev = ptr->prev->next = new node{ object, ptr, ptr->prev};
					}

					length++;
					return ret_val;
				}

				iterator insert(Object &&object, iterator it) {
					node* ret_val;
					if(empty()){
						ret_val = head = tail = new node{object, nullptr, nullptr };
					}
					else if(it == begin()){
						ret_val = new node {std::move(object), head, nullptr};
						head->prev = ret_val;
						head = ret_val;
					}
					else if(it == end()){
						ret_val = new node {std::move(object), nullptr, tail};
						tail->next = ret_val;
						tail = ret_val;
					}
					else {
						node* ptr { it.nodeptr };
						ptr->prev = ptr->prev->next = new node{ std::move(object), ptr, ptr->prev};
					}

					length++;
					return ret_val;
				}

				iterator erase(iterator it){

					node *ret_val, *ptr_to_del;

					if(length == 1){
						ptr_to_del = head;
						ret_val = head = tail = nullptr;
					}
					else if(it == iterator{tail}){
						ptr_to_del = tail;
						tail = tail->prev;
						ret_val = nullptr;
					}
					else if(it == begin()){
						ptr_to_del = head;
						ret_val = head = head->next;
					}
					else {
						node* ptr { it.nodeptr };
						ptr->prev->next = ptr->next;
						ptr->next->prev = ptr->prev;

						ret_val = ptr->next;
						ptr_to_del = ptr;
					}
					length--;
					delete ptr_to_del;

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
					return head->data;
				}

				Object& back() {
					return tail->data;
				}

				iterator begin() {
					return iterator{ head } ;
				}
				const_iterator begin() const {
					return const_iterator{ head };
				}

				iterator end() {
					return iterator{ nullptr } ;
				}
				const_iterator end() const {
					return const_iterator{ nullptr }; 
				}		  								

			private:
				std::size_t length;
				node* head, *tail;
		};
}

using namespace std;

int main(){

	samarth::list<int> li; 

	cout << "\nPushing 1, 2, 3, 4 at back\n" ;
	li.push_back(1);
	li.push_back(2);
	li.push_back(3);
	li.push_back(4);

	cout << "len : " << li.size() << endl;
	for(auto& n : li) cout << n << " ";
	cout << endl;

	cout << "\nPushing 70, 520 at front\n" ;
	li.push_front(70);
	li.push_front(520);

	cout << "len : " << li.size() << endl;
	for(auto& n : li) cout << n << " ";
	cout << endl;

	auto it { std::find( li.begin() , li.end() , 1)};
	li.insert( 100, it );
	it = std::find( li.begin() , li.end() , 4);
	li.insert( 7, it);

	li.erase( std::find( li.begin() , li.end() , 70) ); 

	cout << "\nAfter insert and erase call : \n" ;
	cout << "len : " << li.size() << endl;
	for(auto& n : li) cout << n << " " ;
	cout << endl;


	auto minmax {  std::minmax_element( li.begin(),li.end() )  };
	cout << "min : " << *minmax.first <<endl;
	cout << "max : " << *minmax.second <<endl;

	cout << "\nRange erase : " << endl;
	
	auto from = std::find( li.begin() , li.end() , 100) ; 
	auto to = std::find( li.begin() , li.end() , 7) ; 
	li.erase( from, to);

	for(auto& n : li) cout << n << " " ;
	cout << "len : " << li.size() << endl;
	cout<<endl;

	cout << "calling clear : " << endl;
	li.clear();
	for(auto& n : li) cout << n << " " ;
	cout << "len : " << li.size() << endl;
	cout<<endl;
}
