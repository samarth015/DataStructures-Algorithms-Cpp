/*
 
	a. Write a program to convert an inﬁx expression that includes ( , ) , + , - , * , and /
	to postﬁx.

	b. Add the exponentiation operator to your repertoire.
  
 */ 

#include <array>
#include <iostream>
#include <string_view>
#include "stack"

bool is_opening_bracket( char bkt ){
	return bkt == '(' || bkt == '{' || bkt == '[' ;
}

bool is_closing_bracket( char bkt ){
	return bkt == ')' || bkt == '}' || bkt == ']' ;
}

bool is_operator( char symbol){
	std::string opers {"+-^/*"};
	return opers.find( symbol ) != std::string::npos ;
}

std::uint8_t get_priority( const char oper ){

	if( is_opening_bracket(oper) ) return 0;
	switch(oper){
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
			return 2;
		case '^':
			return 3;
	}

	throw std::invalid_argument { "get_priority can take only : '+-*/^(' as arguments." };
}


void add_stacktop_to_postfix_expression( std::stack<char> &opers, std::string &expr){
	expr.push_back(opers.top());
	expr.push_back(' ');
	opers.pop();
}

void add_term_to_postfix_expression( std::string &term, std::string &expr ){
	if( term.empty() ) return;
	expr.append(term);
	expr.push_back(' ');
	term.clear();
}

bool both_are_power_operator( const char oper1, const char oper2 ){
	return oper1 == '^' && oper2 =='^';
}

std::string infix_to_postix_convert( std::string_view infix_expr ){

	std::string postfix_expr {};
	std::stack<char> opers;
	std::string term {};

	for( const char ch : infix_expr ){
		if( ch == ' ') continue;

		else if(  is_operator(ch) ) {

			add_term_to_postfix_expression( term, postfix_expr);

			while( !opers.empty() && (get_priority(ch) <=  get_priority( opers.top() )) && !both_are_power_operator(opers.top(),ch)){
				add_stacktop_to_postfix_expression( opers, postfix_expr); 
			}

			opers.push( ch );
		}

		else if(is_opening_bracket(ch)){

			add_term_to_postfix_expression( term, postfix_expr);
			opers.push( ch );
		}


		else if(is_closing_bracket(ch)) {

			add_term_to_postfix_expression( term, postfix_expr);

			while( !is_opening_bracket(opers.top()) ){
				add_stacktop_to_postfix_expression( opers, postfix_expr); 
			}

			opers.pop();
		}

		else {
			term.push_back(ch);
		}
	}

	if(!term.empty()){ 
		add_term_to_postfix_expression( term, postfix_expr);
	}

	while( !opers.empty() ){
		add_stacktop_to_postfix_expression( opers, postfix_expr); 
	}	

	return postfix_expr ;
}

int main(){

	const std::size_t N{ 11 };    //Number of test cases.

	std::array<const char*,N>tests = {
		"10 + 10 * 10 / 10"     ,         //10 10 10 * 10 / +
		"3*(4*5^2) / 6+7-8"     ,         //3 4 5 2 ^ * * 6 / 7 + 8 -
		"5^2"                   ,         //5 2 ^ 
		"2 ^ 2 ^ 3"             ,           //2 2 3 ^ ^ 
			"1+ 2 + 3 "         ,           //1 2 + 3 +    
		"a+b*c+(d*e)"           ,          //a b c * + d e * +
		"a-b-c"                 , 				//ab – c –
		"a/b^c-d"               ,  			//abc^/d-
		"(A+B/C*(D+E)-F)"       ,     //A B C / D E + * + F -
		"1+3 + 7 * (9 - 10)"    ,   //1 3 + 7 9 10 - * + 
		"18-[6-{4-(8-(6+3))}]"       //18 6 4 8 6 3 + - - - -
	};

	for( size_t i{}; i < tests.size() ; i++ ) {
		std::cout << tests[i] << "  :  " << infix_to_postix_convert( tests[i] ) <<  std::endl;
	}
}
