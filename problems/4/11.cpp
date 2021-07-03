/*

   Write an implementation of the set class, with associated iterators using a binary
   search tree. Add to each node a link to the parent node.

*/

#include<utility>
#include<tuple>      //To return 3 types in find_node_and_parent.
#include<queue>
#include<stdexcept>
#include<iostream>
#include<iomanip>
#include<random>

template<typename Comparable>
class set
{
	private:
		class tree_node
		{
			public:
				Comparable data;
				tree_node *left;
				tree_node *right;
				tree_node *parent;

				tree_node() = delete;
				tree_node(const Comparable &data, tree_node *left, tree_node *right, tree_node* parent):
					data{data},
					left{left},
					right{right},
					parent{parent}
				{}
				tree_node(Comparable &&data, tree_node *left, tree_node *right, tree_node* parent):
					data{data},
					left{left},
					right{right},
					parent{parent}
				{}
				tree_node(const Comparable &data, tree_node *parent): tree_node{data, nullptr, nullptr, parent} {}
				tree_node(Comparable &&data, tree_node *parent): tree_node{std::move(data), nullptr, nullptr, parent} {}

				tree_node(const tree_node &other) = delete;
				tree_node(tree_node &&other) noexcept = delete;
				~tree_node() = default;
		};

		//check default init

	public:
		class iterator
		{
			private:
				tree_node *node;
				set *cont_ptr;

			public:
				iterator(): node{nullptr}, cont_ptr{nullptr} {}

				iterator(tree_node *node, set *cont_ptr): node{node}, cont_ptr{cont_ptr} {}

				iterator(const iterator &other): node{other.node}, cont_ptr{other.cont_ptr} {}

				iterator & operator = (const iterator &other){
					if(*this == other) return *this;
					node = other.node;
					cont_ptr = other.cont_ptr;
					return *this;
				}

				iterator(iterator &&other) noexcept: node{other.node}, cont_ptr{other.cont_ptr}{
					other.node = nullptr;
					other.cont_ptr = nullptr;
				}

				iterator & operator = (iterator &&other) noexcept {
					if(*this == other) return *this;
					node = other.node;
					cont_ptr = other.cont_ptr;

					other.node = nullptr;
					other.cont_ptr = nullptr;
					return *this;
				}

				~iterator() = default;

				Comparable& operator * (){
					return node->data;
				}

				Comparable* operator -> (){
					return node;
				}

				bool operator==(const iterator &oth){
					return oth.node == this->node;
				}

				bool operator!=(const iterator &oth){
					return oth.node != this->node;
				}

			private:

				bool is_root(tree_node *node) const{
					return node->parent == nullptr;
				}
				bool has_left_parent(tree_node* node) const{    //node is right child to parent
					return node->parent->right == node;
				}

				bool has_right_parent(tree_node* node) const{    //node is left child to parent
					return node->parent->left == node;
				}

				tree_node* next(tree_node* node) const{
					if(node->right){
						node = node->right;
						while(node->left) node = node->left;
						return node;
					}
					else if(node == cont_ptr->max_node){
						return cont_ptr->end_sentinal_node;
					}
					else if(has_right_parent(node)){
						return node->parent;
					}
					else{
						while(has_left_parent(node)){
							node = node->parent;
						}
						return node->parent;
					}
				}

				tree_node* previous(tree_node *node) const{
					if(node->left){
						node = node->left;
						while(node->right) node = node->right;
						return node;
					}
					else if(node == cont_ptr->end_sentinal_node)
						return cont_ptr->max_node;
					else if(has_left_parent(node))
						return node->parent;
					else{
						while(has_right_parent(node)){
							node = node->parent;
						}
						return node->parent;
					}
				}

			public:
				iterator& operator++(){
					node = next(node);
					return *this;
				}

				iterator operator++(int){
					iterator tmp {*this};
					++(*this);
					return tmp;
				}
				iterator& operator--(){
					node = previous(node);
					return *this;
				}

				iterator operator--(int){
					iterator tmp {*this};
					--(*this);
					return tmp;
				}
		};

		class const_iterator {
			private:
				iterator it;

			public:
				const_iterator(): it{} {}
				const_iterator(tree_node* node, set *cont_ptr): it{node, cont_ptr} {}
				const_iterator(const const_iterator &other): it{other.it} {}
				const_iterator & operator = (const const_iterator &other){
					it = other.it;
					return *this;
				}
				const_iterator(const_iterator &&other) noexcept: it{std::move(other.it)} {}
				const_iterator & operator = (const_iterator &&other) noexcept {
					it = std::move(other.it);
					return *this;
				}
				~ const_iterator() = default;

				const Comparable& operator*() {
					return *it;
				}

				const Comparable* operator->() {
					return it.operator->();
				}

				bool operator==(const const_iterator &oth){
					return it == oth.it;
				}

				bool operator!=(const const_iterator &oth){
					return it != oth.it;
				}

				const_iterator& operator++(){
					++it;
					return *this;
				}

				const_iterator operator++(int){
					const_iterator tmp {*this};
					++it;
					return tmp;
				}

				const_iterator& operator--(){
					--it;
					return *this;
				}

				const_iterator operator--(int){
					const_iterator tmp {*this};
					--it;
					return tmp;
				}
		};

	private:
		enum class relation_to_parent {left_child, right_child, no_parent};

		void clear(tree_node *subroot){
			if(subroot){
				clear(subroot->left);
				clear(subroot->right);
				delete subroot;
			}
		}

		std::size_t get_subtree_size(tree_node *subroot) const {
			if(subroot)
				return 1 + get_subtree_size(subroot->left) + get_subtree_size(subroot->right);
			else
				return 0;
		}

		tree_node* init_copy_construct_tree(tree_node *subroot, tree_node *parent = nullptr){
			if(subroot == nullptr) return nullptr;
			else{
				tree_node *new_node = new tree_node{subroot->data, parent};
				tree_node *left = init_copy_construct_tree(subroot->left, new_node);
				tree_node *right = init_copy_construct_tree(subroot->right, new_node);
				new_node->left = left;
				new_node->right = right;
				return new_node;
			}
		}

		tree_node* find_node(const Comparable& data, tree_node *subroot) const {
			if(subroot == nullptr)
				return nullptr;
			else if(data < subroot->data)
				return find_node(data, subroot->left);
			else if(subroot->data < data)
				return find_node(data, subroot->right);
			else 
				return subroot;
		}


		//Finds a node containing the provided data, its parent and its relationship to its parent ie left or right child of parent.
		//If node dosent exist, returns nullptr, the node that should have been parent if such a node existed,
		//and its relation to that parent.
		std::tuple<tree_node*,tree_node*,relation_to_parent>
			find_node_and_parent(const Comparable& data,
					tree_node *subroot, 
					tree_node *parent = nullptr,
					relation_to_parent relation = relation_to_parent::no_parent ) const {
				if(subroot == nullptr) 
					return {nullptr, parent, relation};
				if(data < subroot->data)
					return find_node_and_parent(data, subroot->left, subroot, relation_to_parent::left_child);
				else if(subroot->data < data)
					return find_node_and_parent(data, subroot->right, subroot, relation_to_parent::right_child);
				else
					return {subroot, parent, relation};
			}

		void print(tree_node* subroot, std::size_t depth = 0) const {
			if(subroot == nullptr) return;

			print(subroot->right, depth + 1);
			std::string padding (depth*3, ' ');
			std::cout << padding << subroot->data << std::endl;
			print(subroot->left, depth + 1);
		}

		tree_node *root;
		tree_node *min_node;
		tree_node *max_node;
		tree_node *end_sentinal_node;
		std::size_t Size;

	public:
		set(): 
			root{nullptr}, 
			min_node{nullptr}, 
			max_node{nullptr},
			end_sentinal_node{ new tree_node{Comparable{},nullptr} },
			Size{}
		{}

		set(const set &other): set() {
			if(other.root) {

				root = init_copy_construct_tree(other.root);
				Size = other.Size;

				tree_node *curr {root};
				while(curr->left) curr = curr->left;
				min_node = curr;

				curr = root;
				while(curr->right) curr = curr->right;
				max_node = curr;
			}
		}

		set & operator = (const set &other){
			if(this == &other) return *this;
			set temp {other};
			std::swap(other, *this);
			return *this;
		}

		set(set &&other) noexcept:
			root{other.root},
			min_node{other.min_node},
			max_node{other.max_node},
			end_sentinal_node{other.end_sentinal_node},
			Size{other.Size} 
		{
			other.root = nullptr;
			other.min_node = nullptr;
			other.max_node = nullptr;
			other.end_sentinal_node = nullptr;
			other.Size = 0;
		}

		set & operator = (set &&other) noexcept {
			if(this == &other) return *this;
			clear(root);
			delete end_sentinal_node;

			root = other.root;
			min_node = other.min_node;
			max_node = other.max_node;
			end_sentinal_node = other.end_sentinal_node;
			Size = other.Size;

			other.root = nullptr;
			other.min_node = nullptr;
			other.max_node = nullptr;
			other.end_sentinal_node = nullptr;
			other.Size = 0;
			return *this;
		}

		~set(){
			clear(root);
			delete end_sentinal_node;
		}

		void clear(){
			clear(root);
			root = nullptr;
			min_node = nullptr;
			max_node = nullptr;
			Size = 0;
		}

		bool empty() const {
			return Size == 0;
		}

		std::size_t size() const {
			return Size;
		}

		const Comparable& max() const {
			if(empty()) throw std::runtime_error {"BST container is empty"};
			return max_node->data;
		}

		const Comparable& min() const {
			if(empty()) throw std::runtime_error {"BST container is empty"};
			return min_node->data;
		}

		void insert(const Comparable &data){
			auto [ subtree, parent, relation ] {find_node_and_parent(data, root)};
			if(subtree == nullptr){
				tree_node* new_node = new tree_node{data, parent};

				if(not empty() and data < min()) min_node = new_node;
				if(not empty() and data > max()) max_node = new_node;

				if(relation == relation_to_parent::no_parent){  //Only root node has no parent. Which means set is empty.
					max_node = min_node = root = new_node;     
				}
				else if(relation == relation_to_parent::left_child)
					parent->left = new_node;
				else 
					parent->right = new_node;

				Size++;
			}
		}

		void insert(Comparable &&data){
			auto [ subtree, parent, relation ] {find_node_and_parent(data, root)};
			if(subtree == nullptr){
				tree_node* new_node = new tree_node{std::move(data), parent};

				if(not empty() and new_node->data < min()) min_node = new_node;
				if(not empty() and new_node->data > max()) max_node = new_node;

				if( relation == relation_to_parent::no_parent ) {
					max_node = min_node = root = new_node;    //Only root node has no parent.
				}
				else if(relation == relation_to_parent::left_child)
					parent->left = new_node;
				else 
					parent->right = new_node;

				Size++;
			}
		}

		bool contains(const Comparable &data) const {
			tree_node *node { find_node(data, root) };
			return node != nullptr;
		}

		void erase(const Comparable &data){
			auto [ node, parent, relation ] {find_node_and_parent(data, root)};

			if(node == nullptr) return;

			if(node->left and node->right){
				tree_node *curr {node->left}, *prev_curr{node};
				while(curr->right){
					prev_curr = curr;
					curr = curr->right;
				}

				node->data = std::move(curr->data);
				if(prev_curr == node) node->left = curr->left;
				else prev_curr->right = curr->left;

				if(curr == min_node) min_node = node;

				delete curr;
			}
			else {
				tree_node *successor;

				if(node->left) successor = node->left;
				else if(node->right) successor = node->right;
				else successor = nullptr;

				if(relation == relation_to_parent::no_parent)
					root = successor;
				else if(relation == relation_to_parent::left_child)
					parent->left = successor;
				else
					parent->right = successor;

				if(successor) successor->parent = parent;

				if(node == min_node){
					if(min_node->right) min_node = min_node->right;
					else min_node = parent;
				}

				if(node == max_node){
					if(max_node->left) max_node = max_node->left;
					else max_node = parent;
				}

				delete node;
			}
			Size--;
		}

		void print() const {
			std::cout << std::setfill(' ') << std::setw(3);   //output formatting
			print(root);
		}

		iterator begin(){
			return iterator{min_node, this};
		}
		iterator end(){
			return iterator{end_sentinal_node, this};
		}
		const_iterator begin() const{
			return const_iterator{min_node, this};
		}
		const_iterator end() const{
			return const_iterator{end_sentinal_node, this};
		}

};


int main() {
	
	set<int> st;
	for(int i{}; i<20; i++){
		st.insert(rand() % 100);
	}
	st.print();

	set<int>::iterator it {st.begin()};

	std::cout <<"First element : " << *it << std::endl;
	it++; it++;
	std::cout <<"Third element : " << *it << std::endl;
	it--;
	std::cout <<"Second element : " << *it << std::endl;

	std::cout << "Range based for loop -- " << std::endl;
	for(auto n : st) std::cout << n << std::endl;
	
	std::cout << "Iterating in reverse -- " << std::endl;

	auto it2 {--st.end()};
	do{
		std::cout << *it2 << std::endl;
		it2--;
	}while(it2 != st.begin());
}
