#ifndef SAMARTH_FORWARD_LIST
#define SAMARTH_FORWARD_LIST

#include<utility>
#include<stdexcept>
#include<iterator>

namespace samarth {

	template<typename Object>
		class forward_list
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
					private:
					node *currptr, *prevptr; 

					public:
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

					template<typename> friend class forward_list;
				};

				struct const_iterator{
					private:
						iterator itr;

					public:
					using const_iterator_category = typename iterator::iterator_category;
					using value_type        	  = typename iterator::value_type;
					using difference_type   	  = typename iterator::difference_type;
					using pointer           	  = typename iterator::pointer;
					using reference         	  = typename iterator::reference;

					const_iterator(): itr{} {}
					const_iterator(node* currptr, node* prevptr): itr{currptr, prevptr} {}
					const_iterator(const const_iterator &other): itr{other.itr} {}

					const_iterator & operator = (const const_iterator &other){
						if(this == &other) return *this;
						itr = other.itr;
						return *this;
					}

					const_iterator(const_iterator &&other) noexcept: itr{std::move(other.itr)} {}

					const_iterator & operator = (const_iterator &&other) noexcept {
						if(this == &other) return *this;
						itr = std::move(other.itr);
						return *this;
					}

					~ const_iterator() = default;

					const Object& operator*() const {
						return *itr;
					}

					const Object* operator->() const {
						return itr.operator->();
					}

					bool operator==(const const_iterator &oth){
						return itr == oth.itr;
					}

					bool operator!=(const const_iterator &oth){
						return itr != oth.itr;
					}

					const_iterator& operator++(){
						++itr;
						return *this;
					}

					const_iterator operator++(int){
						const_iterator tmp {*this};
						++(*this);
						return tmp;
					}
				};

				node *head, *tail, *second_last;
				std::size_t length;

			public:
				forward_list():
					head{nullptr},
					tail{nullptr},
					second_last{nullptr},
					length{}
				{
					tail = new node { Object{}, nullptr };
					second_last = head = new node { Object{}, tail };
				}

				forward_list(std::initializer_list<Object> init_list): forward_list() {
					for(auto & object : init_list)
						push_back(object);
				}

				forward_list(const forward_list &other): forward_list() {
					for(auto & object : other) 
						push_back(object);
				}

				forward_list & operator = (const forward_list &other){
					if(this == &other) return *this;

					forward_list temp {other};
					std::swap(*this,temp);

					return *this;
				}

				forward_list(forward_list &&other) noexcept: 
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

				forward_list & operator = (forward_list &&other) noexcept {
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

				~ forward_list() {
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
		};
}

#endif
