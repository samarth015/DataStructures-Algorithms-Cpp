/*

	Modify the Vector class to add bounds checks for indexing. 

*/


// Go to line 79 to see bounds checking.

#include <utility>
#include <stdexcept>
#include <iostream>

namespace samarth {

	template<typename Object>
		class vector {
			public: 
				using iterator = Object*; 
				using const_iterator = const Object *;

				vector( std::initializer_list<Object> init_list ) : vector( init_list.size() ){
						std::size_t i {} ;
						for( auto& object : init_list ) objects[i++] = object ;
					}

				vector( std::size_t len ) :
					length{ len } ,
					capacity{ ( length < 32 ) ? 64 : length * 2 } ,
					objects{ new Object[capacity] } 
				{}

				vector(): vector(0) {}

				vector( std::size_t len , const Object& obj ): vector(len) {			
						for( std::size_t i {} ; i < length ; i++ ) objects[i] = obj ;
					}

				vector( const vector &oth ): 
					length{ oth.length } ,
					capacity{ oth.capacity } ,
					objects{ new Object[ capacity ] } {
						for( std::size_t i {} ; i < length ; i++ ) this->objects[i] = oth.objects[i] ;
					}

				vector( vector&& oth ) noexcept : 
					length{ oth.length } ,
					capacity{ oth.capacity } ,
					objects{ oth.objects } {
						oth.objects = nullptr ;
						oth.length = 0 ;
						oth.capacity = 0 ;
					}

				~vector() {
					if( objects ) delete[] objects ;
				}

				vector& operator= ( const vector &oth ) {
					if(this == &oth) return *this;
					vector temp { oth } ;
					*this = std::move( temp ) ;
					return *this ;
				}

				vector& operator= ( vector&& oth ) noexcept {
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
					if( index >= length)
						throw std::out_of_range { "Index supplied is invalid. Index must be >=0 and <length" };

					return objects[index] ;
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

				void push_back( const Object &val ) {
					if( length == capacity ) {
						reserve( capacity * 2 + 1 ) ;
					}
					objects[length++] = val ;
				}

				void push_back( Object &&val ) {
					if( length == capacity ) {
						resize( capacity * 2 + 1 ) ;
					}
					objects[length++] = std::move(val) ;
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
					return objects;
				}
				const_iterator begin() const {
					return objects;
				}
				iterator end() {
					return objects + length;
				}
				const_iterator end() const {
					return objects + length;
				}

			private:
				std::size_t length;
				std::size_t capacity ;
				Object *objects;
		};
}

int main(){
	samarth::vector<int> v { 1, 2, 3 };
	std::cout << v[1] << std::endl;
	//std::cout << v[5] << std::endl;         //Will throw exception.
}
