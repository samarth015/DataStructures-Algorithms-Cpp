#include "randint.cpp"
#include "../tree_generic.cpp"
#include <iostream>

using namespace std;

int main(){
	//Using samarth::tree this way to represent directories and files
	//works properly only when every directory and file name is unique.

	samarth::tree<std::string> directory_tree ;

	directory_tree.add_root("/usr");

	directory_tree.add_to_node_as_child("/usr", "bill");
	directory_tree.add_to_node_as_child("/usr", "alex");
	directory_tree.add_to_node_as_child("/usr", "mark");

	directory_tree.add_to_node_as_child("bill", "course_bill");
	directory_tree.add_to_node_as_child("bill", "work_bill");

	directory_tree.add_to_node_as_child("course_bill","cop3212");

	directory_tree.add_to_node_as_child("cop3212", "fall1");
	directory_tree.add_to_node_as_child("cop3212", "fall2");

	directory_tree.add_to_node_as_child("fall1", "prog1.r");
	directory_tree.add_to_node_as_child("fall1", "prog2.r");

	directory_tree.add_to_node_as_child("fall2", "prog.r");
	directory_tree.add_to_node_as_child("fall2", "grades");

	directory_tree.add_to_node_as_child("alex", "junk_");

	directory_tree.add_to_node_as_child("mark", "junk");
	directory_tree.add_to_node_as_child("mark", "course");
	directory_tree.add_to_node_as_child("mark", "book");

	directory_tree.add_to_node_as_child("book", "ch1.r");
	directory_tree.add_to_node_as_child("book", "ch2.r");
	directory_tree.add_to_node_as_child("book", "ch3.r");

	directory_tree.add_to_node_as_child("course", "cop3530");

	directory_tree.add_to_node_as_child("cop3530", "spr");
	directory_tree.add_to_node_as_child("cop3530", "fall");
	directory_tree.add_to_node_as_child("cop3530", "sum");

	directory_tree.add_to_node_as_child("sum", "_syl.r");
	directory_tree.add_to_node_as_child("spr", "Syl.r");
	directory_tree.add_to_node_as_child("fall", "syl.r");

	std::cout << "PRINTING CONTENTS OF '/usr' " << std::endl;
	directory_tree.print();

	std::cout << "\n\n\nPRINTING CONTENTS OF 'mark' " << std::endl;
	directory_tree.print("mark");
}
