
/*

	Write routines to implement two stacks using only one array. Your stack routines
	should not declare an overﬂow unless every slot in the array is used.

*/


// Each double_stack will have two stacks. Stack A and B

#include <iostream>
#include <vector>

template<typename Object, std::size_t N>
class double_stack{
	private:
		Object array[N];
		std::size_t Ahead, Bhead;

		void assert_overflow_safe(){
			if(Ahead - 1 == Bhead) throw std::runtime_error {"Stack Overflow."};
		}

		void A_assert_underflow_safe(){
			if(Ahead == 0) throw std::runtime_error {"Stack A Underflow."};
		}

		void B_assert_underflow_safe(){
			if(Bhead == N-1) throw std::runtime_error {"Stack B Underflow."};
		}

	public:
		double_stack():Ahead{0}, Bhead{N-1} {}

		void A_push(const Object &val){
			assert_overflow_safe();
			array[Ahead++] = val;
		}

		void B_push(const Object &val){
			assert_overflow_safe();
			array[Bhead--] = val;
		}

		Object& A_top(){
			A_assert_underflow_safe();
			return array[Ahead - 1];
		}

		Object& B_top(){
			B_assert_underflow_safe();
			return array[Bhead + 1];
		}

		void A_pop(){
			A_assert_underflow_safe();
			Ahead--;
		}

		void B_pop(){
			B_assert_underflow_safe();
			Bhead++;
		}

		std::size_t A_size() const{
			return Ahead;
		}

		std::size_t B_size() const{
			return N - Bhead - 1;
		}
};

int main() {
	double_stack<int, 10> dst {};
	dst.A_push(10);
	dst.A_push(20);
	dst.A_push(30);

	dst.B_push(40);
	dst.B_push(50);
	dst.B_push(60);
	dst.B_push(100);

	std::cout << "A top and size :" << std::endl;
	std::cout << dst.A_top() << std::endl;
	std::cout << dst.A_size() << std::endl;

	std::cout << "B top and size :" << std::endl;
	std::cout << dst.B_top() << std::endl;
	std::cout << dst.B_size() << std::endl;

}
