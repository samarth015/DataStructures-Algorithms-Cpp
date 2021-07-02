
#include "randint.cpp"
#include "../binary_seach_tree.cpp"
#include <iostream>

using namespace std;

int main(){
	samarth::binary_search_tree<int> bst;
	std::cout << "Filling BST with the following 30 values : " << std::endl;
	for(int i{}; i < 30; i++){
		int ran = randint();
		std::cout << ran << " " ;
		bst.insert(ran);
	}
	std::cout << std::endl;

	std::cout << "\n--- TREE --- " << std::endl;
	bst.print();

	std::cout << "\nTree by level order" << std::endl;
	bst.print_by_lever_order();

	std::cout << "\nSize : " << std::endl;
	std::cout << bst.size() << std::endl;
	std::cout << "\nMin and max values :" << std::endl;
	std::cout << bst.max() << std::endl;
	std::cout << bst.min() << std::endl;

	std::cout << std::boolalpha;
	std::cout << "\nContains 93 : " << bst.contains(93) <<std::endl;
	std::cout << "Contains 111 : " << bst.contains(111) <<std::endl;


	std::cout << "\nRemoving 44" << std::endl;
	bst.remove_element(44);  
	bst.print();
	std::cout << "\nRemoving 14" << std::endl;
	bst.remove_element(14);  
	bst.print();

	std::cout << "\nRemoving subtree with root of value 59" << std::endl;
	bst.remove_subtree(59);
	bst.print();
	std::cout << "Size : " << std::endl;
	std::cout << bst.size() << std::endl;

	std::cout << "Copy construction : " << std::endl ;
	samarth::binary_search_tree<int> bst2 { bst };
	bst2.print();

	std::cout << "\nCalling clear" << std::endl;
	bst.clear();
	std::cout << "\nSize : " << std::endl;
	std::cout << bst.size() << std::endl;
}
