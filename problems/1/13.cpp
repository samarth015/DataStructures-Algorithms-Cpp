/*

	Design a class template, Collection , that stores a collection of Object s (in an array),
	along with the current size of the collection. Provide public functions isEmpty ,
	makeEmpty , insert , remove , and contains . contains(x) returns true if and only if an
	Object that is equal to x is present in the collection.

*/

//Answer

#include <iostream>

template<typename Object, std::size_t MaxSize>
class Collection
{
	public:
		Object array[MaxSize];
		std::size_t Size;

		Collection(): Size{} {}

		bool isEmpty() const{
			return Size == 0;
		}

		bool isFull() const{
			return Size == MaxSize;
		}

		std::size_t getSize() const{
			return Size;
		}

		void makeEmpty(){
			Size = 0;
		}

		void insert(const Object &data){
			array[Size++] = data;
		}

		void remove(const Object &data){
			std::size_t i{}, j{};
			while(i < Size){
				if(array[i] != data){
					if(i==j) j++;
					else array[j++] = std::move(array[i]);
				}
				i++;
			}
			Size = j;
		}

		bool contains(const Object &data) const{
			for(const Object & obj : array) if(obj == data) return true;
			return false;
		}
};


int main() {

	Collection<std::string, 100> col;	

	col.insert("Samarth");
	col.insert("kabeer");
	col.insert("someone");
	col.insert("something");
	col.insert("Samarth");

	std::cout << col.Size << std::endl;

	for(std::size_t i{}; i < col.Size; i++){
		std::cout << col.array[i] << std::endl;
	}
	std::cout << std::endl;

	col.remove("Samarth");
	col.remove("someone");

	for(std::size_t i{}; i < col.Size; i++){
		std::cout << col.array[i] << std::endl;
	}
	std::cout << col.Size << std::endl;
}
