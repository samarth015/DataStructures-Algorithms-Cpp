/*

	Write a program to solve the selection problem. Let k = N/2. Draw a table showing
	the running time of your program for various values of N.

*/

//Answer

#include<iostream>
#include<iomanip>
#include<set>
#include<random>
#include<chrono>
#include<vector>
#include<algorithm>

std::vector<int> generate_vector_of_random_ints(std::size_t Size){
	std::vector<int> vec;
	for(std::size_t i{}; i < Size; i++)
		vec.push_back(rand()%100);	
	return vec;
}

int get_kth_by_bst(const std::vector<int>& vec, std::size_t k){
	std::multiset<int,std::greater<int>> st{vec.begin(), vec.end()};
	auto it {st.begin()};
	std::advance(it,k-1);
	return *it;
}

int get_kth_by_sorting(const std::vector<int>& vec, std::size_t k){

	std::vector<int> tmp {vec.begin(), vec.begin() + k};
	std::sort(tmp.begin(), tmp.end(), [](auto a, auto b){ return a > b; });
	for(std::size_t i{k}; i < vec.size(); i++){
		if(vec[i] > tmp.back()){
			std::size_t j{k-1};
			while(j > 0 && tmp[j] < vec[i]){
				tmp[j] = tmp[j-1];
				j--;
			}
			tmp[j] = vec[i];
		}
	}
	return tmp.back();
}

int main() {
	std::size_t N {500};
	std::cout << "       N       ---       bst     sorting" << std::endl;
	for(std::size_t i{0}; i < 8; i++ , N*=2 ){
		std::vector<int> nums(generate_vector_of_random_ints(N));
		std::cout << std::setw(10) << N << "     --- "; 
		std::size_t k {N/2};

		int a,b;
		auto start = std::chrono::system_clock::now();
		a = get_kth_by_bst(nums, k);
		auto end = std::chrono::system_clock::now();
		std::cout << std::setw(10) << (end - start).count() << " "; 

		start = std::chrono::system_clock::now();
		b = get_kth_by_sorting(nums, k);
		end = std::chrono::system_clock::now();
		std::cout << std::setw(10) << (end - start).count() << std::endl;
	}
}
