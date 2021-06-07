/*

	Show how to implement three stacks in one array.

*/

// The multi_stack implementation here works with multiple stacks using the same array.
// We will use it to work with 3 stacks on one array as the question requires.
// N is the number of stacks an M is the capacity of each stack.

#include <iostream>
#include <vector>

template<typename Object, std::size_t N, std::size_t M>
class multi_stack{
	private:
		Object array[N*M];
		std::size_t head_index[N];    //This stores the index of the head on the array for each stack.

		void assert_overflow_safe(std::size_t stack_id){
			if(head_index[stack_id] >= N*M) throw std::runtime_error {"Stack Overflow."};
		}

		void assert_underflow_safe(std::size_t stack_id){
			if(head_index[stack_id] < N) throw std::runtime_error {"Stack Underflow."};
		}
	
	public:
		multi_stack(){
			for(std::size_t i{}; i < N; i++) head_index[i] = i;
		}

		void push(std::size_t id, const Object &val){
			assert_overflow_safe(id);
			array[head_index[id]] = val;
			head_index[id] += N;
		}

		void pop(std::size_t id, const Object &val){
			assert_underflow_safe(id);
			head_index[id] -= N;
		}

		Object& top(std::size_t id){
			assert_underflow_safe(id);
			return array[ head_index[id] - N ];
		}

		std::size_t size(std::size_t id) const{
			return head_index[id] / N;
		}

		bool empty(std::size_t id) const {
			return head_index[id] < N;
		}
};

int main() {
	multi_stack<int,3,10> dst {};
	dst.push(0,10);
	dst.push(1,20);
	dst.push(0,30);
	dst.push(0,40);
	dst.push(2,50);
	dst.push(2,60);
	dst.push(1,100);

	std::cout << "A top and size :" << std::endl;
	std::cout << dst.top(0) << std::endl;
	std::cout << dst.size(0) << std::endl;

	std::cout << "B top and size :" << std::endl;
	std::cout << dst.top(1) << std::endl;
	std::cout << dst.size(1) << std::endl;

	std::cout << "C top and size :" << std::endl;
	std::cout << dst.top(2) << std::endl;
	std::cout << dst.size(2) << std::endl;
}
