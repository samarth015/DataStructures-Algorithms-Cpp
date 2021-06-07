#ifndef SAMARTH_ARRAY
#define SAMARTH_ARRAY

#include<utility>
#include<stdexcept>

namespace samarth {

	template<typename Object,std::size_t Size>
	class array
	{
		private:
			Object arr[Size];
	
		public:

			array() = default;

			template<typename ...InitList>
			array(InitList ...init_list): arr{init_list...} {}

			array(const array &other): array() {
				static_assert( other.size() == Size, "array size mismatch.");
				for(std::size_t i{}; i < Size; i++){
					arr[i] = other.arr[i];
				}
			}
				
			array & operator = (const array &other){
				if(this == &other) return *this;
				static_assert( other.size() == Size, "array size mismatch.");
				for(std::size_t i{}; i < Size; i++){
					arr[i] = other.arr[i];
				}
				return *this;
			}
	
			array(array &&other) noexcept: array() {
				static_assert( other.size() == Size, "array size mismatch.");
				for(std::size_t i{}; i < Size; i++){
					arr[i] = std::move(other.arr[i]);
				}
			}

			array & operator = (array &&other) noexcept {
				if(this == &other) return *this;
				static_assert( other.size() == Size, "array size mismatch.");
				for(std::size_t i{}; i < Size; i++){
					arr[i] = std::move(other.arr[i]);
				}
				return *this;
			}
	
			~ array() = default;

			Object& operator [] (std::size_t ind){
				return arr[ind];
			}

			using iterator = Object*;
			using const_iterator = const Object*;

			iterator begin(){
				return arr;
			}
			const_iterator begin() const {
				return arr;
			}
			iterator end(){
				return arr + Size;
			}
			const_iterator end() const {
				return arr + Size;
			}

			constexpr bool empty() const{
				return Size == 0;
			}

			constexpr std::size_t size() const {
				return Size;
			}

			Object& front(){
				return *arr;
			}

			Object& back(){
				return arr[Size-1];
			}
	};
}

#endif
