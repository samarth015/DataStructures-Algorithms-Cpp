#ifndef SAMARTH_TREE_GENERIC
#define SAMARTH_TREE_GENERIC

#include<utility>
#include<stdexcept>
#include<iostream>

namespace samarth {

	template<typename Object>
		class tree
		{
			private:
				struct tree_node
				{
					public:
						Object data;
						tree_node* last_entered_child;
						tree_node* next_sibling;

						tree_node() = delete;
						tree_node(const Object &data, tree_node* next_sibling):
							data{data},
							last_entered_child{nullptr},
							next_sibling{next_sibling}
						{}
						tree_node(Object &&data, tree_node* next_sibling):
							data{std::move(data)},
							last_entered_child{nullptr},
							next_sibling{next_sibling}
						{}

						tree_node(const tree_node &other) = delete;
						tree_node(tree_node &&other) noexcept = delete;
						~tree_node() = default;
				};


				tree_node *root;

			public:
				tree(): root{nullptr} {}
				tree(const Object &data): root{ new tree_node {data, nullptr} } {}
				tree(Object &&data): root{ new tree_node {std::move(data), nullptr} } {}
				tree(const tree &other) = delete;
				tree(tree &&other) noexcept = delete;

				~tree(){
					clear();
				}

			private:
				tree_node* find_node(const Object& data, tree_node* subtree_root ) const {
					if(subtree_root == nullptr) return nullptr;
					if(subtree_root->data == data) return subtree_root;
					tree_node* siblings_search_result = find_node(data, subtree_root->next_sibling);
					if(siblings_search_result) return siblings_search_result;
					tree_node* child_search_result = find_node(data, subtree_root->last_entered_child);
					if(child_search_result) return child_search_result;
					return nullptr;
				}

				void clear(tree_node *subtree_root){
					if(subtree_root == nullptr) return;
					clear(subtree_root->next_sibling);
					clear(subtree_root->last_entered_child);
					delete subtree_root;
				}

				void print(tree_node* subtree_root, std::size_t depth) const {
					if(subtree_root == nullptr) return;
					std::string padding (depth*4, ' ');
					std::cout << padding << subtree_root->data << std::endl ;
					print(subtree_root->last_entered_child, depth+1);
					print(subtree_root->next_sibling, depth);
				}

			public:
				void print() const {
					print(root,0);
				}

				void print(const Object &subtree_root_data) const {
					tree_node *subtree_root { find_node(subtree_root_data, root) };
					if(subtree_root == nullptr) return;
					std::cout << subtree_root->data << std::endl ;
					print(subtree_root->last_entered_child, 1);
				}

				void add_root(const Object &root_data){
					if(root) 
						root->data = root_data;
					else 
						root = new tree_node{root_data, nullptr};
				}

				void add_to_node_as_child(const Object &parent_data, const Object &child_data){
					tree_node* parent { find_node(parent_data, root) };
					parent->last_entered_child = new tree_node{ child_data, parent->last_entered_child };
				}

				void clear(){
					clear(root);
				}
		};
}

#endif
