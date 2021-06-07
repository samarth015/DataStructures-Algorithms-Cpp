/*
 
	 Write a program to evaluate a postﬁx expression.
 
*/

#include <stack>
#include <string_view>
#include <sstream>
#include <array>
#include <iostream>

bool is_operator( std::string_view term ){
	static std::string operators { "+-*/" };
	return term.size() == 1 && operators.find( term ) != std::string::npos ;
}

long double eval_binary_operation( long double left_op, char Operator, long double right_op ) {
	switch(Operator){
		case '+':
			return left_op + right_op;
		case '-':
			return left_op - right_op;
		case '*':
			return left_op * right_op;
		case '/':
			return left_op / right_op;
	}
	throw std::invalid_argument {"Invalid Operator used for eval_binary_operation"};
}

long double evaluate_postfix_expression( std::string_view expression ){

	std::stack<long double> st {};
	std::string term;

	for( const char ch : expression ){
		if( ch == ' '  ){
			if( is_operator( term ) ){

				char Operator { term[0] };
				long double right_op{ st.top() }; 
				st.pop();
				long double left_op{ st.top() }; 
				st.pop();
				long double result { eval_binary_operation( left_op, Operator, right_op)} ;

				st.push( result );
			}
			else {
				std::stringstream ss { term };
				long double number;
				ss >> number;
				st.push( number );
			}

			term.clear();
		}
		else{
			term.push_back(ch);
		}
	}

	return st.top();
}


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
		auto result { evaluate_postfix_expression(tests[i]) };
		std::cout << (result == answers[i] ? "Passed" : "Failed" ) << " : " 
				  << tests[i] << "  =  " << result <<  std::endl;
	}
}

