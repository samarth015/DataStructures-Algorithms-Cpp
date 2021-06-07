/*
   Write a program to check for balancing symbols in the following languages:
   a. Pascal ( begin / end , () , [] , {} ).
   b. C++ ( / *   * / , () , [] , {} ).
   c. Explain how to print out an error message that is likely to reﬂect the probable
   cause.
*/

// c) Whenever a condition to test balance of symbols fails, we print the appropriate message.
// 	  For example, if we encounter a closing brace but the stack is empty the expression is invalid
// 	  since there was no opening brace for this closing brace and we tell the user the same.

//   This is a generic solution that can check the symbol balance for any languages( not just c++ and pascal)
//   The user just needs to provide the opening and closing symbol list.

#include <iostream>
#include <algorithm>
#include <string_view>
#include <array>
#include <stack>
#include <vector>
#include <utility>

using namespace std;
using symbol_list = const std::vector<std::string_view> ;
using symbol_stack = std::stack<std::string>;

string_view corresponding_opening_symbol(string_view close_sym, symbol_list opening_list, symbol_list& closing_list){

	std::size_t i{};
	for(auto sym : closing_list){
		if(sym == close_sym)
			return opening_list[i];
		i++;
	}

	throw std::invalid_argument {"The argument to corresponding_opening_symbol must be a valid closing bracket" };
}

// If a symbol in the symbol list starts from the provided index,
// returns the end position of the symbol in expression.
// Return the same index otherwise.
std::size_t get_end_of_symbol(std::size_t start_pos, string_view expr, symbol_list& sym_lis){
	for( auto symbol : sym_lis ){
		std::size_t j{};
		bool symbol_found {true};
		while( j < symbol.size() and j < expr.size() ){
			if( expr[start_pos + j] != symbol[j] ) {
				symbol_found = false;
				break;
			}
			j++;
		}
		if(symbol_found) return start_pos + symbol.size();
	}
	return start_pos;
}

void symbols_are_balanced(string_view expr, symbol_list& opening_symbol_list, symbol_list& closing_symbol_list){

	symbol_stack st {};

	std::size_t i{};
	while(i < expr.size()){
		bool is_opening_symbol, is_closing_symbol;

		auto end_pos = get_end_of_symbol(i, expr, opening_symbol_list);
		is_opening_symbol = end_pos != i;

		if( !is_opening_symbol ){
			end_pos = get_end_of_symbol(i, expr, closing_symbol_list);
			is_closing_symbol = end_pos != i;
		}

		if(is_opening_symbol){
			string symbol (expr.begin() + i, expr.begin() + end_pos );
			st.push( std::move(symbol) );
			i = end_pos;
		}	
		else if (is_closing_symbol){
			string symbol (expr.begin() + i, expr.begin() + end_pos );
			if(st.empty()){
				std::cout << "Extra closing symbol : '" << symbol
						  << "' at position --> " << i 
						  << std::endl;
				return;
			}
			if(st.top() != corresponding_opening_symbol(symbol, opening_symbol_list, closing_symbol_list)){
				std::cout << "Symbol mismatch : '" << symbol 
					   	  << "' at position --> " << i 
						  << " does not match with '" << st.top() << "'."
						  <<   std::endl;
				return;
			}
				st.pop(); 
				i = end_pos;
			}
		else{
			i++;
		}
	}
	if(!st.empty()) std::cout << "Extra opening symbol : '" << st.top() << "'" <<std::endl;
	else std::cout << "BALANCED" << std::endl;
}

int main(){
	//The opening symbol must correspond with its closing symbol in the two arrays and
	//the symbols longest in length must be listed first or the program might not work properly.
	symbol_list cpp_opening {"/*", "{","[","("};
	symbol_list cpp_closing {"*/", "}","]",")"};
	symbol_list pascal_opening { "begin", "(*", "{","[","("};
	symbol_list pascal_closing { "end", "*)",  "}","]",")"};

	cout << std::boolalpha ;

	const std::size_t N {5};

	std::array<const char*,N> cpp_tests { 
		"#include <iostream>\n"
			"using namespace std;\n"
			"int main()\n"
			"{\n"
			"int firstNumber, secondNumber, sumOfTwoNumbers;\n"
			"cout << \"Enter two integers: \";\n"
			"cin >> firstNumber >> secondNumber;\n"
			"/* sum of two numbers in stored in variable sumOfTwoNumbers */\n"
			"sumOfTwoNumbers = firstNumber + secondNumber;\n"
			"/* Prints sum */\n"
			"cout << firstNumber << \" + \" <<  secondNumber << \" = \" << sumOfTwoNumbers;     \n"
			"return 0;\n"
			"}"
			,

			"#include<iostream> \n"
			"int main()\n"
			"std::cout<< \"hello world\" std::endl;\n"
			"}\n"
			,

			"int main({"
			"return 0;}\n"
			,

			"int main(]{"
			"return 0;}\n"
			,

			"int main(){\n"
			"/* This is a simple program\n"
			"return 0;"
	};

	std::array<const char*,2> pascal_tests {
		"program HelloWorld;\n"
		"uses crt;\n"

		"(* Here the main program block starts *)\n"
		"begin\n"
		   "writeln('Hello, World!');\n"
		   "readkey;\n"
		"end. \n"
		,

		"program Project1;\n"

		"{$APPTYPE CONSOLE}\n"
		"var\n"
		"a, b: Integer;\n"
		"begin\n"
		"a := 244;\n"
		"b := 835;\n"

		"// Get the sum of a and b\n"
		"Writeln(a, ' + ', b, ' = ', a + b);\n"

		"Write('Press any key to continue...');\n"
		"Readln;\n"
		"\n"

	};

	for( auto test : cpp_tests ){
		cout << test << endl;
		symbols_are_balanced(test, cpp_opening, cpp_closing);
		cout << endl;
	}

	for( auto test : pascal_tests ){
		cout << test << endl;
		symbols_are_balanced(test, pascal_opening, pascal_closing);
		cout << endl;
	}
}
