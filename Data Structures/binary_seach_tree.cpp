#ifndef SAMARTH_BINARY_SEARCH_TREE
#define SAMARTH_BINARY_SEARCH_TREE

#include<utility>
#include<tuple>      //To return 3 types in find_node_and_parent.
#include<stdexcept>
#include<iostream>
#include<iomanip>

namespace samarth {

	template<typename Comparable>
		class binary_search_tree
		{
			private:
				class tree_node
				{
					public:
						Comparable data;
						tree_node *left;
						tree_node *right;

						tree_node() = delete;
						tree_node(const Comparable &data, tree_node *left, tree_node *right):
							data{data},
							left{left},
							right{right}
						{}
						tree_node(Comparable &&data, tree_node *left, tree_node *right):
							data{data},
							left{left},
							right{right}
						{}
						tree_node(const Comparable &data): tree_node{data, nullptr, nullptr} {}
						tree_node(Comparable &&data): tree_node{std::move(data), nullptr, nullptr} {}

						tree_node(const tree_node &other) = delete;
						tree_node(tree_node &&other) noexcept = delete;
						~tree_node() = default;
				};


				tree_node *root;
				std::size_t Size;

				enum class relation_to_parent {left_child, right_child, no_parent};

				void clear(tree_node *subtree_root){
					if(subtree_root){
						clear(subtree_root->left);
						clear(subtree_root->right);
						delete subtree_root;
					}
				}

				std::size_t get_subtree_size(tree_node *subtree_root) const {
					if(subtree_root)
						return 1 + get_subtree_size(subtree_root->left) + get_subtree_size(subtree_root->right);
					else
						return 0;
				}

				void remove_subtree(tree_node* subtree_root, tree_node *parent, relation_to_parent relation){
					if(subtree_root == root){
						root = nullptr;
						Size = 0;
					}
					else {
						if(relation == relation_to_parent::left_child) parent->left = nullptr;
						else parent->right = nullptr;
						Size -= get_subtree_size(subtree_root);
					}
					clear(subtree_root);
				}

				tree_node* init_copy_construct_tree(tree_node *subtree_root){
					if(subtree_root == nullptr) return nullptr;
					else{
						return new tree_node{ subtree_root->data,
							init_copy_construct_tree(subtree_root->left),
							init_copy_construct_tree(subtree_root->right)
						};
					}
				}

				tree_node* find_node(const Comparable& data, tree_node *subtree_root) const {
					if(subtree_root == nullptr)
						return nullptr;
					else if(data < subtree_root->data)
						return find_node(data, subtree_root->left);
					else if(subtree_root->data < data)
						return find_node(data, subtree_root->right);
					else 
						return subtree_root;
				}


				//Finds a node containing the provided data, its parent and its relationship to its parent ie left or right child of parent.
				//If node dosent exist, returns nullptr, the node that should have been parent if such a node existed,
				//and its relation to that parent.
				std::tuple<tree_node*,tree_node*,relation_to_parent>
					find_node_and_parent(const Comparable& data,
							tree_node *subtree_root, 
							tree_node *parent = nullptr,
							relation_to_parent relation = relation_to_parent::no_parent ) const {
						if(subtree_root == nullptr) 
							return {nullptr, parent, relation};
						if(data < subtree_root->data)
							return find_node_and_parent(data, subtree_root->left, subtree_root, relation_to_parent::left_child);
						else if(subtree_root->data < data)
							return find_node_and_parent(data, subtree_root->right, subtree_root, relation_to_parent::right_child);
						else
							return {subtree_root, parent, relation};
					}

				void print(tree_node* subtree_root, std::size_t depth = 0) const {
					if(subtree_root == nullptr) return;

					print(subtree_root->right, depth + 1);
					std::string padding (depth*3, ' ');
					std::cout << padding << subtree_root->data << std::endl;
					print(subtree_root->left, depth + 1);
				}

			public:
				binary_search_tree(): root{nullptr}, Size{} {}

				binary_search_tree(const binary_search_tree &other): binary_search_tree() {
					if(other.root == nullptr) {
						root = nullptr;
					}
					else {
						root = init_copy_construct_tree(other.root);
						Size = other.Size;
					}
				}

				binary_search_tree & operator = (const binary_search_tree &other){
					if(this == &other) return *this;
					binary_search_tree temp {other};
					std::swap(other, *this);
					return *this;
				}

				binary_search_tree(binary_search_tree &&other) noexcept: root{other.root}, Size{other.Size} {
					other.root = nullptr;
					other.Size = 0;
				}

				binary_search_tree & operator = (binary_search_tree &&other) noexcept {
					if(this == &other) return *this;
					clear();

					root = other.root;
					Size = other.Size;

					other.root = nullptr;
					other.Size = 0;
					return *this;
				}

				~binary_search_tree(){
					clear(root);
				}

				void clear(){
					clear(root);
					root = nullptr;
					Size = 0;
				}

				bool empty() const {
					return Size == 0;
				}

				std::size_t size() const {
					return Size;
				}

				const Comparable& max() const {
					if(root == nullptr) throw std::runtime_error {"BST container is empty"};
					tree_node *curr {root};
					while(curr->right) curr = curr->right;
					return curr->data;
				}

				const Comparable& min() const {
					if(root == nullptr) throw std::runtime_error {"BST container is empty"};
					tree_node *curr {root};
					while(curr->left) curr = curr->left;
					return curr->data;
				}


				void insert(const Comparable &data){
					auto [ subtree, parent, relation ] {find_node_and_parent(data, root)};
					if(subtree == nullptr){
						tree_node* new_node = new tree_node{data};
						if(relation == relation_to_parent::no_parent) 
							root = new_node;     //Only root node has no parent.
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
						tree_node* new_node = new tree_node{std::move(data)};
						if( relation == relation_to_parent::no_parent ) 
							root = new_node;    //Only root node has no parent.
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

				void remove_subtree(const Comparable &data){
					auto [ subtree, parent, relation ] {find_node_and_parent(data, root)};
					if(subtree) remove_subtree(subtree, parent, relation);
				}

				void remove_element(const Comparable &data){
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

						delete curr;
					}
					else {
						tree_node *new_child;

						if(node->left) new_child = node->left;
						else if(node->right) new_child = node->right;
						else new_child = nullptr;

						if(relation == relation_to_parent::left_child)
							parent->left = new_child;
						else
							parent->right = new_child;

						delete node;
					}

					Size--;
				}

				void print() const {
					std::cout << std::setfill(' ') << std::setw(3);   //output formatting
					print(root);
				}
		};
}
#endif  //SAMARTH_BINARY_SEARCH_TREE
