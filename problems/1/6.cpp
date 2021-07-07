/*

	Write the routines with the following declarations:
		void permute( const string & str );
		void permute( const string & str, int low, int high );
	The ﬁrst routine is a driver that calls the second and prints all the permutations of
	the characters in string str . If str is "abc" , then the strings that are output are abc ,
	acb , bac , bca , cab , and cba . Use recursion for the second routine.

*/
//Answer

#include <iostream>
#include <string>
#include <vector>

void permute(const std::string &str, int low, int high){
	if(low >= high - 1){
		std::cout << str << std::endl;
	}
	else{
		std::string new_string (str);
		for(int i{low}; i < high; i++){
			std::swap(new_string[low], new_string[i]); 
			permute(new_string, low + 1, high);
		}
	}
}

void permute(const std::string &str){
	permute(str, 0, str.size());
}

int main() {
	std::string abcd {"abcd"};
	std::string abc {"abc"};
	permute(abc);
	std::cout << std::endl;
	permute(abcd);
}
