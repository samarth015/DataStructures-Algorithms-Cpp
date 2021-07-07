/*

   Design a class template, OrderedCollection , that stores a collection of Comparable s
   (in an array), along with the current size of the collection. Provide public functions
   isEmpty , makeEmpty , insert , remove , findMin , and findMax . findMin and findMax return
   references to the smallest and largest, respectively, Comparable in the collection.
   Explain what can be done if these operations are performed on an empty collection.

*/

//Answer

#include <iostream>
#include <random>

template<typename Comparable, std::size_t MaxSize>
class OrderedCollection
{
	public:
		Comparable array[MaxSize];
		std::size_t Size;

		OrderedCollection(): Size{} {}

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

		void insert(const Comparable &data){
			std::size_t i{Size};

			while(i > 0 and array[i-1] > data){
				array[i] = std::move(array[i-1]);
				i--;
			}

			array[i] = data;
			Size++;
		}

		void remove(const Comparable &data){
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

		bool contains(const Comparable &data) const{
			for(std::size_t i{}; i < Size; i++) if(array[i] == data) return true;
			return false;
		}

		Comparable& findMax(){
			return array[Size-1];
		}

		Comparable& findMin(){
			return array[0];
		}
};

int main(){

	OrderedCollection<int,100> ocol;
	for(std::size_t i{}; i < 10; i++) ocol.insert(rand() % 100);

	for(std::size_t i{}; i < ocol.Size; i++) std::cout << ocol.array[i] << std::endl;

	std::cout << "Max : " << ocol.findMax() << std::endl;
	std::cout << "Min : " << ocol.findMin() << std::endl;
}

