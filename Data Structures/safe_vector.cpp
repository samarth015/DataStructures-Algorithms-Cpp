// A vector implementation that provides stringent iterator checking.
// It checks the validity of a iterator before insertions, deletions and 
// dereferencing.
// It also checks the range validity when accessing the objects of vector
// through [] operator.

#ifndef SAMARTH_SAFE_VECTOR
#define SAMARTH_SAFE_VECTOR 

#include<utility>
#include <iterator>
#include <exception>

namespace samarth {

	template<typename Object>
		class safe_vector {
			public: 

				class iterator
				{
					private:
						Object* ptr;
						safe_vector *container_ptr;

					public:
						void assert_itr_within_valid_halfopen_range(){
							if(ptr == nullptr)
								throw std::runtime_error { "Iterator is uninitialized. Cannot dereference nullptr." };
							if( !(container_ptr->begin() <= *this and  *this <= container_ptr->end()) )
								throw std::runtime_error { "Range mismatch .The iterator is invalidated." };
						}

						void assert_iterator_is_not_end(){
							if( *this == container_ptr->end() ) 
								throw std::runtime_error {"Dereferencing end() not allowed"};
						}

						using iterator_category = std::random_access_iterator_tag;
						using value_type        = Object;
						using difference_type   = std::ptrdiff_t;
						using pointer           = value_type*;
						using reference         = value_type&;

						iterator(): ptr{nullptr}, container_ptr{nullptr} {}
						iterator(pointer ptr, safe_vector* cont): ptr{ptr}, container_ptr{cont} {}
						iterator(const iterator &other): ptr{other.ptr}, container_ptr {other.container_ptr} {}
						iterator & operator = (const iterator &other){
							if(this == &other) return *this;
							ptr = other.ptr;
							container_ptr = other.container_ptr;
							return *this;
						}
						iterator(iterator &&other) noexcept: ptr{other.ptr}, container_ptr{other.container_ptr} {
							other.ptr = nullptr;
							other.container_ptr = nullptr;
						}
						iterator & operator = (iterator &&other) noexcept {
							if(this == &other) return *this;
							ptr = other.ptr;
							container_ptr = other.container_ptr;
							other.ptr = nullptr;
							other.container_ptr = nullptr;
							return *this;
						}
						~ iterator() = default;

						reference operator* () {
							assert_itr_within_valid_halfopen_range();
							assert_iterator_is_not_end();
							return *ptr ;
						}

						pointer operator->() {
							assert_itr_within_valid_halfopen_range();
							assert_iterator_is_not_end();
							return ptr;
						}

						reference operator[]( size_t ind ) {
							assert_itr_within_valid_halfopen_range();
							if( !(container_ptr->begin() <= ptr+ind and ptr+ind < container_ptr->end()) )
								throw std::out_of_range {"Out of bounds. Object being tried to access must be within the half-open range of container"};
							return ptr[ind];
						}

						iterator operator+ ( long long offset ) {
							return iterator{ ptr + offset, container_ptr } ;
						}

						difference_type operator- ( const iterator &oth ) {
							return this->ptr - oth.ptr ;
						}

						iterator operator- ( long long offset ) {
							return iterator{ ptr - offset, container_ptr } ;
						}

						bool operator== ( const iterator& oth ) {
							return oth.ptr == this->ptr ;
						}

						bool operator!= ( const iterator& oth ) {
							return oth.ptr != this->ptr ;
						}

						iterator& operator++ ( ) {
							ptr++;
							return *this;
						}

						iterator operator++ (int) {
							iterator tmp { ptr, container_ptr };
							ptr++ ;
							return tmp;
						}

						iterator& operator-- ( ) {
							ptr--;
							return *this;
						}

						iterator operator-- (int) {
							pointer tmp = ptr ;
							ptr-- ;
							return tmp;
						}

						bool operator< ( const iterator& oth ) {
							return this->ptr <  oth.ptr ;
						}
						bool operator> ( const iterator& oth ) {
							return this->ptr >  oth.ptr ;
						}
						bool operator<= ( const iterator& oth ) {
							return this->ptr <=  oth.ptr ;
						}
						bool operator>= ( const iterator& oth ) {
							return this->ptr >=  oth.ptr ;
						}
				};

				class const_iterator{
					private:
						iterator itr;

					public:

						using const_iterator_category = std::random_access_iterator_tag;
						using value_type        = Object;
						using difference_type   = std::ptrdiff_t;
						using pointer           = value_type*;
						using reference         = value_type&;

					const_iterator(): itr{} {}
					const_iterator(pointer ptr, safe_vector* cont): itr{ptr, cont} {}
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

					const Object& operator[]( long long ind ) const {
						return itr[ind];
					}

					bool operator==(const const_iterator &oth){
						return itr == oth.itr;
					}

					bool operator!=(const const_iterator &oth){
						return itr != oth.itr;
					}

					const_iterator operator+ ( long long offset ) {
						const_iterator temp {*this};
						temp.itr = temp.itr + offset;
						return temp;
					}

					difference_type operator- ( const const_iterator &oth ) {
						return itr - oth.itr;
					}

					const_iterator operator- ( long long offset ) {
						const_iterator temp {*this};
						temp.itr = temp.itr - offset;
						return temp;
					}

					const_iterator& operator++ ( ) {
						++itr;
						return *this;
					}

					const_iterator operator++ (int) {
						const_iterator tmp {*this};
						++(*this);
						return tmp;
					}

					const_iterator& operator-- ( ) {
						--itr;
						return *this;
					}

					const_iterator operator-- (int) {
						const_iterator tmp {*this};
						--(*this);
						return tmp;
					}

					bool operator< ( const const_iterator& oth ) {
						return itr < oth.itr;
					}
					bool operator> ( const const_iterator& oth ) {
						return itr > oth.itr;
					}
					bool operator<= ( const const_iterator& oth ) {
						return itr <= oth.itr;
					}
					bool operator>= ( const const_iterator& oth ) {
						return itr >= oth.itr;					}
				};


				safe_vector( std::initializer_list<Object> init_list ) : safe_vector( init_list.size() ){
					std::size_t i {} ;
					for( auto& object : init_list ) objects[i++] = object ;
				}

				safe_vector( std::size_t len ) :
					length{ len } ,
					capacity{ ( length < 32 ) ? 64 : length * 2 } ,
					objects{ new Object[capacity] } 
				{}

				safe_vector(): safe_vector(0) {}

				safe_vector( std::size_t len , const Object& obj ): safe_vector(len) {			
					for( std::size_t i {} ; i < length ; i++ ) objects[i] = obj ;
				}

				safe_vector( const safe_vector &oth ): 
					length{ oth.length } ,
					capacity{ oth.capacity } ,
					objects{ new Object[ capacity ] } {
						for( std::size_t i {} ; i < length ; i++ ) this->objects[i] = oth.objects[i] ;
					}

				safe_vector( safe_vector&& oth ) noexcept : 
					length{ oth.length } ,
					capacity{ oth.capacity } ,
					objects{ oth.objects } {
						oth.objects = nullptr ;
						oth.length = 0 ;
						oth.capacity = 0 ;
					}

				~safe_vector() {
					if( objects ) delete[] objects ;
				}

				safe_vector& operator= ( const safe_vector &oth ) {
					if(this == &oth) return *this;
					safe_vector temp { oth } ;
					*this = std::move( temp ) ;
					return *this ;
				}

				safe_vector& operator= ( safe_vector&& oth ) noexcept {
					if(this == &oth) return *this;
					if( objects ) delete[] this->objects ;
					this->length = oth.length ;
					this->capacity = oth.capacity ;
					this->objects = oth.objects ;
					oth.length = 0 ;
					oth.capacity = 0 ;
					oth.objects = nullptr ;
					return *this ;
				}

				Object& operator[]( std::size_t index ) {
					if( index >= length ) throw std::out_of_range {"Out of bounds. Index supplied must be >=0 and < length"};
					return objects[index];
				}

				const Object & operator[]( std::size_t index ) const {
					return objects[index] ;
				}

				void resize( std::size_t n , Object val = Object{} ) {
					if( n > capacity ) reserve( n * 2 ) ;
					if( n > length ) for( ; length < n ; length++ ) objects[length] = val ;
					else length = n ;
				}

				void reserve( std::size_t n ) {
					if( n >= length && capacity != n ) {
						Object* new_block = new Object[n] ;
						for( std::size_t i = 0 ; i < length ; i++ ) new_block[i] = std::move(objects[i]) ;
						delete[] objects ;	
						objects = new_block ;
					}
				}

				iterator insert(iterator it, const Object &val){
					it.assert_itr_within_valid_halfopen_range();

					std::size_t index_to_insert_at { it - objects };

					add_space_if_required();

					for(std::size_t i{length-1}; index_to_insert_at <= i; i++ )
						objects[i+1] = std::move(objects[i]);

					objects[index_to_insert_at] = val; 
					length++;
				}

				iterator insert(iterator it, Object &&val){
					it.assert_itr_within_valid_halfopen_range();

					std::size_t index_to_insert_at { static_cast<std::size_t>(it - objects) };

					add_space_if_required();

					for(std::size_t i{length-1}; index_to_insert_at <= i; i-- )
						objects[i+1] = std::move(objects[i]);

					objects[index_to_insert_at] = std::move(val); 
					length++;
					return iterator{ objects + index_to_insert_at };
				}

				void push_back( const Object &val ) {
					add_space_if_required();
					objects[length++] = val ;
				}

				void push_back( Object &&val ) {
					add_space_if_required();
					objects[length++] = std::move(val) ;
				}

				iterator erase(iterator it){
					it.assert_itr_within_valid_halfopen_range();
					if( it == end() ) throw std::logic_error{ "Iterator supplied to erase cannot be end()" };

					iterator next{it}, ret_it{it};
					next++;

					while(next!=end()){
						*it = std::move(*next);
						it++;
						next++;
					}
					length--;
					return ret_it;

				}

				iterator erase( iterator from, iterator to ){

					from.assert_itr_within_valid_halfopen_range();
					to.assert_itr_within_valid_halfopen_range();
					if( to > from ) throw std::logic_error{"Half open range supplied to erase is not valid."};

					if( to == from ) return iterator{from};

					while(to != end()){
						*from = std::move(*to);
						to++;
						from++;
					}
					length = from - begin();
					return iterator{from};
				}

				void pop_back( ) {
					length-- ;
				}

				bool empty( ) const {
					return length == 0 ;
				}

				void clear() {
					length = 0;
				}

				std::size_t size() const {
					return length ;
				}

				std::size_t cap() const {
					return capacity ;
				}

				Object& front() {
					return *objects;
				}

				Object& back() {
					return objects[length - 1];
				}

				iterator begin() {
					return iterator{objects, this};
				}
				const_iterator begin() const {
					return objects;
				}
				iterator end() {
					return iterator{objects + length, this };
				}
				const_iterator end() const {
					return objects + length;
				}

			private:
				void add_space_if_required(){
					if( length == capacity ) 
						reserve( capacity * 2 + 1 ) ;
				}
				std::size_t length;
				std::size_t capacity ;
				Object *objects;

		};
}

#endif
