/*

	c. Write a program to convert a postﬁx expression to inﬁx.

*/

#include <iostream>
#include <vector>
#include <array>
#include <stack>
#include <string>

bool is_operator( std::string term ){
	static std::string opers { "+-^*/" };
	return term.size() == 1 and opers.find( term ) != std::string::npos ;
}

std::string postfix_to_infix_converter(std::string expr){
	std::stack<std::string> st {};
	std::string term{};

	for(const char ch: expr){
		if(ch == ' '){
			if(is_operator(term)){
				std::string right_operand {st.top()};
				st.pop();
				std::string binary_operation = "(" + st.top() + " " + term + " " + right_operand + ")";
				st.pop();
				st.push(binary_operation);
			}
			else{
				st.push(term);
			}
			term.clear();
		}
		else {
			term.push_back(ch);
		}
	}
	return st.top();
}

int main() {


	std::array<const char*,11> tests = {
		"10 10 10 * 10 / + ",                   //10 + 10 * 10 / 10
		"3 4 5 2 ^ * * 6 / 7 + 8 - ",           //3*(4*5^2) / 6+7-8
		"5 2 ^ ",                       		//5^2
		"2 2 3 ^ ^ ",                   		//2 ^ 2 ^ 3
		"1 2 + 3 + ",                   		//1+ 2 + 3
		"a b c * + d e * + ",                   //a+b*c+(d*e)
		"a b - c - ",                   		//a-b-c
		"a b c ^ / d - ",                       //a/b^c-d
		"A B C / D E + * + F - ",               //(A+B/C*(D+E)-F)
		"1 3 + 7 9 10 - * + ",                  //1+3 + 7 * (9 - 10)
		"18 6 4 8 6 3 + - - - - ",              //18-[6-{4-(8-(6+3))}]
	};

	for( size_t i{}; i < tests.size() ; i++ ) {
		std::cout << tests[i] << "  :  " << postfix_to_infix_converter( tests[i] ) <<  std::endl;
	}

}
