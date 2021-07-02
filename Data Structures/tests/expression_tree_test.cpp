#include <array>
#include "../expression_tree.cpp"
#include <iostream>

using namespace std;

int main(){
	const std::size_t N{ 5 };    //Number of test cases.

	std::array<const char*,N>tests = {
	 "5 3 + 6 2 / * 3 5 * + " , 
	 "6 5 2 3 + 8 * + 3 + * ", 
	 "1 2 3 * + " , 
	 "2 2 * 3 4 * + " ,
	 "2 3 1 * + 9 - " , 
	};

	std::array<const long double,N> answers = {39, 288, 7, 16, -4};

	std::cout << std::boolalpha ;
	for( size_t i{}; i < tests.size() ; i++ ) {
		samarth::expr_tree extr { tests[i] };
		auto result { extr.evaluate_expression() };
		if( result == answers[i] ){
			std::cout << "Passed : " << tests[i] << " = " << result << std::endl;
			extr.print_infix_expression();
			extr.print_postfix_expression();
			extr.print_prefix_expression();
			std::cout << "-- Expression Tree --" << std::endl;
			extr.print();
			std::cout << std::endl;
		}
		else {
			std::cout << "Failed : " << tests[i] << std::endl;
		}
	}
}
