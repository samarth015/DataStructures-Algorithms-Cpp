/*

	Write a program to solve the word puzzle problem.

*/

//Answer

// Reading a list of 8.9K english words of length >= 4 from file 2_words_list.txt in the same directory.
// Data source - https://www.mit.edu/~ecprice/wordlist.10000

#include <iostream>
#include <array>
#include <fstream>
#include <unordered_set>
#include <random>

constexpr std::size_t rows { 75 };
constexpr std::size_t cols { 125 };

using PuzzleGrid = std::array<std::array<char, cols>, rows>;

void word_puzzle_solve(const PuzzleGrid &puzzle){
	std::ifstream words_file { "./2_words_list.txt" };
	std::unordered_set<std::string> dictionary {};
	std::string word;
	while(words_file >> word) dictionary.insert(word);

	std::cout << "Start     End     Word" << std::endl;

	for(std::size_t i{}; i < rows; i++){
		for(std::size_t j{}; j < cols; j++){
			std::string word {""};
			for(std::size_t k{j}; k < cols; k++){
				word.push_back(puzzle[i][k]);
				if(dictionary.find(word) != dictionary.end()){
					std::cout << "(" << i << ", " << j << ") "  
							  << "(" << i  << ", " << k << ")    "  
							  << word << std::endl;
				}
			}
		}
	}

	for(std::size_t j{}; j < cols; j++){
		for(std::size_t i{}; i < rows; i++){
			std::string word {""};
			for(std::size_t k{i}; k < rows; k++){
				word.push_back(puzzle[k][j]);
				if(dictionary.find(word) != dictionary.end()){
					std::cout << "(" << i << ", " << j << ") "  
							  << "(" << k  << ", " << j << ")    "  
							  << word << std::endl;
				}
			}
		}
	}
}

PuzzleGrid generate_puzzle(){
	PuzzleGrid puzzle;
	for(std::size_t i{}; i < rows; i++){
		for(std::size_t j{}; j < cols; j++){
			puzzle[i][j] = 'a' + (rand() % ('z' - 'a' + 1));
		}
	}
	return puzzle;
}

void print_puzzle(const PuzzleGrid& puzzle){

	std::cout << "PUZZLE\n" << std::endl;
	for(std::size_t i{}; i < rows; i++){
		for(std::size_t j{}; j < cols; j++)
			std::cout << puzzle[i][j];
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int main() {
	PuzzleGrid puzzle {generate_puzzle()};

	print_puzzle(puzzle);

	word_puzzle_solve(puzzle);
}
