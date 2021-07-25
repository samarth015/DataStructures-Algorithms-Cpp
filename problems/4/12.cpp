/*

   Write an implementation of the map class by storing a data member of type
	map<pair<KeyType,ValueType>> .


*/

#include<utility>
#include<tuple>      //To return 3 types in find_node_and_parent.
#include<stdexcept>
#include<iostream>
#include<random>

template<typename key_type, typename value_type>
class map
{
	using key_val = std::pair<key_type,value_type>;
	private:
		class tree_node
		{
			public:
				key_val data;
				tree_node *left;
				tree_node *right;
				tree_node *parent;

				tree_node() = delete;
				tree_node(const key_val &data, tree_node *left, tree_node *right, tree_node* parent):
					data{data},
					left{left},
					right{right},
					parent{parent}
				{}
				tree_node(key_val &&data, tree_node *left, tree_node *right, tree_node* parent):
					data{data},
					left{left},
					right{right},
					parent{parent}
				{}
				tree_node(const key_val &data, tree_node *parent): tree_node{data, nullptr, nullptr, parent} {}
				tree_node(key_val &&data, tree_node *parent): tree_node{std::move(data), nullptr, nullptr, parent} {}

				tree_node(const tree_node &other) = delete;
				tree_node(tree_node &&other) noexcept = delete;
				~tree_node() = default;
		};

	public:
		class iterator
		{
			private:
				tree_node *node;
				map *cont_ptr;

			public:
				iterator(): node{nullptr}, cont_ptr{nullptr} {}

				iterator(tree_node *node, map *cont_ptr): node{node}, cont_ptr{cont_ptr} {}

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

				key_val& operator * (){
					return node->data;
				}

				key_val* operator -> (){
					return &node->data;
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
				template<typename,typename> friend class map;
		};

		class const_iterator {
			private:
				iterator it;

			public:
				const_iterator(): it{} {}
				const_iterator(tree_node* node, map *cont_ptr): it{node, cont_ptr} {}
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

				const key_val& operator*() {
					return *it;
				}

				const key_val* operator->() {
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

		std::size_t get_subtree_size(tree_node *subroot) const{
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

		tree_node* find_node(const key_type& key, tree_node *subroot) const {
			if(subroot == nullptr)
				return nullptr;
			else if(key < (subroot->data).first)
				return find_node(key, subroot->left);
			else if((subroot->data).first < key)
				return find_node(key, subroot->right);
			else 
				return subroot;
		}


		//Finds a node containing the provided data, its parent and its relationship to its parent ie left or right child of parent.
		//If node dosent exist, returns nullptr, the node that should have been parent if such a node existed,
		//and its relation to that parent.
		std::tuple<tree_node*,tree_node*,relation_to_parent>
			find_node_and_parent(const key_type& key,
					tree_node *subroot, 
					tree_node *parent = nullptr,
					relation_to_parent relation = relation_to_parent::no_parent ) const {
				if(subroot == nullptr) 
					return {nullptr, parent, relation};
				if(key < (subroot->data).first)
					return find_node_and_parent(key, subroot->left, subroot, relation_to_parent::left_child);
				else if((subroot->data).first < key)
					return find_node_and_parent(key, subroot->right, subroot, relation_to_parent::right_child);
				else
					return {subroot, parent, relation};
			}

		void erase(tree_node *node, tree_node *parent, relation_to_parent relation){
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

		tree_node *root;
		tree_node *min_node;
		tree_node *max_node;
		tree_node *end_sentinal_node;
		std::size_t Size;

	public:
		map(): 
			root{nullptr}, 
			min_node{nullptr}, 
			max_node{nullptr},
			end_sentinal_node{ new tree_node{key_val{},nullptr} },
			Size{}
		{}

		map(const map &other): map() {
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

		map & operator = (const map &other){
			if(this == &other) return *this;
			map temp {other};
			std::swap(other, *this);
			return *this;
		}

		map(map &&other) noexcept:
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

		map & operator = (map &&other) noexcept {
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

		~map(){
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

		value_type& operator [] (const key_type &key){
			tree_node *node {find_node(key,root)};
			if(node == nullptr){
				auto it = insert( {key, value_type{}} ); 
				return (*it).second;
			}
			else{
				return (node->data).second;
			}
		}

		const key_val& max() const {
			if(empty()) throw std::runtime_error {"BST container is empty"};
			return max_node->data;
		}

		const key_val& min() const {
			if(empty()) throw std::runtime_error {"BST container is empty"};
			return min_node->data;
		}

		iterator insert(const key_val &data){
			auto [ subtree, parent, relation ] {find_node_and_parent(data.first, root)};
			if(subtree == nullptr){
				tree_node* new_node = new tree_node{data, parent};

				if(not empty() and data < min()) min_node = new_node;
				if(not empty() and data > max()) max_node = new_node;

				if(relation == relation_to_parent::no_parent){  //Only root node has no parent. Which means map is empty.
					max_node = min_node = root = new_node;     
				}
				else if(relation == relation_to_parent::left_child)
					parent->left = new_node;
				else 
					parent->right = new_node;
				Size++;

				return { new_node, this };
			}
			else {
				(subtree->data).second = data.second;
				return { subtree, this };
			}
		}

		iterator insert(key_val &&data){
			auto [ subtree, parent, relation ] {find_node_and_parent(data.first, root)};
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

				return { new_node, this };
			}
			else {
				(subtree->data).second = data.second;
				return { subtree, this };
			}
		}

		iterator find(const key_type &key) {
			tree_node *node { find_node(key, root) };
			if(node != nullptr)
				return {node, this};
			else
				return end();
		}

		iterator erase(const key_type &key){
			auto [ node, parent, relation ] {find_node_and_parent(key, root)};

			if(node == nullptr) return end();

			iterator it {node, this};
			it = ++it;

			erase(node, parent, relation);

			return it;
		}

		iterator erase(iterator it){
			tree_node *node {it.node};
			tree_node *parent {node->parent};

			relation_to_parent rel;
			if(parent == nullptr) rel = relation_to_parent::no_parent;
			else if(parent->left == node) rel = relation_to_parent::left_child;

			it++;

			erase(node, parent, rel);

			return it;
		}

		iterator erase(iterator start, iterator finish){
			while(start != finish){
				start = erase(start);
			}
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

	map<int,int> st;
	for(int i{}; i<100; i++){
		st.insert({rand() % 10, rand()%1000+100});
	}

	map<int,int>::iterator it {st.begin()};

	std::cout <<"\nFirst pair : " << (*it).first << " : " <<  (*it).second << std::endl;
	it++; it++;
	std::cout <<"Third pair : " << (*it).first << " : " <<  (*it).second << std::endl;
	it--;
	std::cout <<"Second pair : " << (*it).first << " : " <<  (*it).second << std::endl;

	std::cout << "\nRange based for loop -- " << std::endl;
	for(auto [key, val] : st) std::cout << key << " : " << val << std::endl;

	std::cout << "\nFinding val for key 5 -> " ;
	std::cout << (*st.find(5)).second << std::endl;
	
	std::cout << "\nFinding val for key 9 -> " ;
	std::cout << (*st.find(9)).second << std::endl;

	std::cout << "\nRemoving even keys" << std::endl;
	std::vector<int> evens;
	for(int i{}; i < 9 ;i+=2) st.erase(i);
	std::cout << std::endl;

	for(auto [key, val] : st) std::cout << key << " : " << val << std::endl;
	
	std::cout << "\nAdding new pairs (69,96) (-15,15)" << std::endl;
	st[69] = 96;
	st[-15] = 15;

	for(auto [key, val] : st) std::cout << key << " : " << val << std::endl;

	std::cout << "\nGetting values of keys 1,5,9 using []" << std::endl;

	std::cout << 1 << " : "  << st[1] << std::endl;
	std::cout << 5 << " : "  << st[5] << std::endl;
	std::cout << 9 << " : "  << st[9] << std::endl;
}
