/*

	Write a function to output an arbitrary double number (which might be negative)
	using only printDigit for I/O.

*/

//Answer

#include <iostream>

//Function that only prints a single digit at a time.
void printDigit(int digit){
	if( 0 <= digit and digit <= 9)
		std::cout << digit;
}

void printInt(int num){
	if( num < 10 ){
		printDigit(num);
	}
	else{
		printInt(num/10);
		printDigit(num % 10);
	}
}

const std::size_t precision { 5 };

void printDouble(double num){

	if(num < 0){
		std::cout << '-';
		num *= -1;
	}

	long long integer_part { static_cast<long long>(num) };
	double fractional_part { num - integer_part };

	printInt(integer_part);

	std::cout << '.' ;

	for(std::size_t i{}; i < precision; i++) 
		fractional_part *= 10;

	printInt(fractional_part);
}

int main() {
	double num {};
	std::cin >> num;
	printDouble(num);
}
