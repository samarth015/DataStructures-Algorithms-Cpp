/*
   The Josephus problem is the following game: N people, numbered 1 to N, are sitting
   in a circle. Starting at person 1, a hot potato is passed. After M passes, the person
   holding the hot potato is eliminated, the circle closes ranks, and the game con-
   tinues with the person who was sitting after the eliminated person picking up the
   hot potato. The last remaining person wins. Thus, if M = 0 and N = 5, players
   are eliminated in order, and player 5 wins. If M = 1 and N = 5, the order of
   elimination is 2, 4, 1, 5.
   a. Write a program to solve the Josephus problem for general values of M and N.
   Try to make your program as efﬁcient as possible. Make sure you dispose of
   cells.
   b. What is the running time of your program?
   c. If M = 1, what is the running time of your program? How is the actual speed
   affected by the delete routine for large values of N (N > 100,000)?
   */



/* Answers
	 a) Perhaps the author expects this question to be solved by iterating through a 
	 dynamic array in circles ,until all except one value is eliminated ,since he advices
	 the reader to dispose of the cells. However, I have solved the problem in two ways
	 1) using std::queues, which handle memory itself. 
	 2) Direct method through mathematical formula, which requires constant memory.

	 b) The running time is O(N*M) for simulation and O(1) for Direct solution. 

	 c) if M = 1 the running time is O(N). delete will be called 2*(N-1) times, because when M = 1 
	 alternate elements are deleted so its 2 deletes to remove each element and a total of N-1 elements
	 are deleted. If a delete takes c time so time taken is c * 2 * (N-1).
	 Direct solution does not use delete.

 */

#include <iostream>
#include <list>
#include <queue>
#include <cmath>

void JosephusProblemSimulation( std::size_t N, std::size_t M ){
	std::queue<std::size_t, std::list<std::size_t>> players {};

	for( std::size_t i{1}; i <= N; i++) players.push(i);

std::cout << "Order of Elimination : ";

	while( N-- - 1 ){
		for( std::size_t i{1}; i <= M; i++){
			players.push(players.front());
			players.pop();
		}
		std::cout << players.front() << " ";
		players.pop();
	}
	std::cout << std::endl;
	std::cout << players.front() << std::endl;
}

void JosephusProblemDirect( std::size_t N, std::size_t M){
	double a { std::log10(N) / std::log10(M) };
	long long b = std::floor(a);
	long long l = N - std::pow( M, b);
	std::cout << ( M*l + 1 ) << " ";
}

int main() {

	JosephusProblemSimulation(5,1);
	JosephusProblemSimulation(5,0);

}
