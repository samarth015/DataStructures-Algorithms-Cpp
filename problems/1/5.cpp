/*

	Write a recursive function that returns the number of 1 in the binary representation
	of N. Use the fact that this is equal to the number of 1 in the representation of N/2,
	plus 1, if N is odd.

*/

//Answer

#include <iostream>
#include <vector>

std::size_t num_of_ones_in_binary(std::size_t N){
	if(N==0) return 0;
	return N%2 + num_of_ones_in_binary(N/2);
}

int main() {

	for(std::size_t i{}; i <= 16; i++)
		std::cout << i << " : " << num_of_ones_in_binary(i) << std::endl;

}
