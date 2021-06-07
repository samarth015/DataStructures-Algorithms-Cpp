/*
 
   a. Propose a data structure that supports the stack push and pop operations and a
	third operation findMin , which returns the smallest element in the data structure,
	all in O(1) worst-case time.

	 b. Prove that if we add the fourth operation deleteMin which ﬁnds and removes the
	smallest element, then at least one of the operations must take (log N) time.
	(This requires reading Chapter 7.)

*/

#include <iostream>
#include <vector>
#include <stack>
#include <limits>

//N is the max possible size of the stack.
//The last element of the array stores a dummy with largest possible value of Object type
//to eliminate special cases in push.

template<typename Object, std::size_t N>
class stack_track_min{
	private:
		Object array[N+1];
		std::size_t length;
		std::stack<std::size_t> min_index;

		void assert_overflow_safe(){
			if(length == N) throw std::runtime_error {"Stack Overflow."};
		}

		void assert_underflow_safe(){
			if(length == 0) throw std::runtime_error {"Stack Underflow."};
		}

	public:
		stack_track_min():length{}, min_index{} {
			array[N] = std::numeric_limits<Object>::max();
			min_index.push(N);
		}

		void push(const Object &val){
			assert_overflow_safe();
			array[length++] = val;
			if(array[min_index.top()] > array[length-1])
				min_index.push(length - 1);
		}

		Object& top(){
			assert_underflow_safe();
			return array[length - 1];
		}

		Object& get_min(){
			assert_underflow_safe();
			return array[min_index.top()];
		}

		void pop(){
			assert_underflow_safe();
			if(length - 1 == min_index.top()) min_index.pop();
			length--;
		}

		bool empty() const {
			return length == 0;
		}

		std::size_t size() const{
			return length;
		}
};

int main() {
	stack_track_min<int, 10> dst {};
	dst.push(100);
	dst.push(30);
	dst.push(200);

	std::cout << "Top, size and getmin :" << std::endl;
	std::cout << dst.top() << std::endl;
	std::cout << dst.size() << std::endl;
	std::cout << dst.get_min() << std::endl;
}
