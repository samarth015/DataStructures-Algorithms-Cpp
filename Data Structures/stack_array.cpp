#ifndef SAMARTH_STACK_ARR
#define SAMARTH_STACK_ARR

#include<utility>
#include<stdexcept>

namespace samarth {

	template<typename Object>
		class stackarr
		{
			private:
				std::size_t length, cap;
				Object* array;

				void assert_underflow_safe() const {
					if( empty() ) throw std::out_of_range{ "Stack Underflow. No element in stack." };
				}

				void assert_overflow_safe() const {
					if( length == cap ) throw std::out_of_range{ "Stack Overflow. Stack is full. No space for more elements." };
				}

			public:
				stackarr(): stackarr(100) {}
				stackarr( std::size_t cap ): length{}, cap{cap}, array{ new Object[cap] } {}

				stackarr( const stackarr &oth ): stackarr(oth.capacity) {
					length = oth.length;
					for( std::size_t i{}; i < length ; i++ )
						array[i] = oth.array[i];
				}
				
				stackarr& operator = (const stackarr &oth){
					if(this == &oth) return *this;
					stackarr tmp {oth};
					std::swap( *this, tmp );
					return *this;
				}

				stackarr(stackarr &&oth) noexcept: length{oth.length}, cap{oth.cap}, array{oth.array} {
					oth.length = 0;
					oth.cap = 0;
					oth.array = nullptr;
				}
				stackarr& operator = (stackarr &&oth) noexcept{
					if(this == &oth) return *this;
					if(array) delete[] array;

					array = oth.array;
					length = oth.length;
					cap = oth.cap;

					oth.array = nullptr;
					oth.length = 0;
					oth.cap = 0;
					return *this;
				}
					
				~stackarr() {
					if(array) delete[] array;
				}

				bool empty() const  {
					return length == 0;
				}

				void clear(){
					length = 0;
				}

				std::size_t size() const {
					return length;
				}

				std::size_t capacity() const {
					return cap;
				}


				void push( const Object &oth) {
					assert_overflow_safe();
					array[length++] = oth;
				}
				void push( Object &&oth) {
					assert_overflow_safe();
					array[length++] = std::move(oth);
				}

				const Object& top() const {
					assert_underflow_safe();
					return array[length-1];
				}
				Object& top() {
					assert_underflow_safe();
					return array[length-1];
				}

				void pop() {
					assert_underflow_safe();
					length--;
				}
		};
}

#endif
