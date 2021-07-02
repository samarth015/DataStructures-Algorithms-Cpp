#ifndef SAMARTH_EXPRESSION_TREE
#define SAMARTH_EXPRESSION_TREE

#include <cmath>
#include <stack>
#include <utility>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <string_view>

namespace samarth {

	class expr_tree
	{
		private:
			class tree_node
			{
				public:
					std::string term;
					tree_node *left;
					tree_node *right;

					tree_node() = delete;
					tree_node(std::string term, tree_node *left, tree_node *right):
						term{term},
						left{left},
						right{right}
					{}
					tree_node(const tree_node &other) = delete;
					tree_node(tree_node &&other) noexcept = delete;
					~tree_node() = default;
			};

			bool is_operator( char symbol ) const {
				static std::string opers { "+-^*/" };
				return opers.find( symbol ) != std::string::npos ;
			}

			bool is_operator( std::string_view term ) const {
				return term.size() == 1 and is_operator(term[0]);
			}

			tree_node *root;

		public:
			expr_tree(std::string postfix_expr){
				std::istringstream iss { postfix_expr };
				std::stack<tree_node*> st;
				std::string term;
				while(iss >> term){
					if(is_operator(term)){
						tree_node *right_operand { st.top() };
						st.pop();
						tree_node *left_operand { st.top() };
						st.pop();
						tree_node *subtree { new tree_node{term, left_operand, right_operand}};
						st.push(subtree);
					}
					else {
						st.push(new tree_node{term, nullptr, nullptr});
					}
				}
				root = st.top();
			}

			expr_tree() = delete;
			expr_tree(const expr_tree &other) = delete;
			expr_tree(expr_tree &&other) noexcept = delete;
			~expr_tree() = default;

		private: 
			void print(tree_node* subtree_root, std::size_t depth = 0) const {
				if(subtree_root == nullptr) return;

				print(subtree_root->right, depth+1);

				std::string padding (depth * 3, ' ');
				std::cout << padding << subtree_root->term << std::endl;

				print(subtree_root->left, depth+1);
			}

			long double eval_binary_operation( long double left_op, char Operator, long double right_op ) const {
				switch(Operator){
					case '+':
						return left_op + right_op;
					case '-':
						return left_op - right_op;
					case '*':
						return left_op * right_op;
					case '/':
						return left_op / right_op;
					case '^':
						return std::pow(left_op, right_op);
				}
				throw std::invalid_argument {"Invalid Operator used for eval_binary_operation"};
			}

			long double evaluate_expression(tree_node *subtree_root) const {
				std::string_view term { subtree_root->term };
				if(is_operator(term)){

					long double left_op { evaluate_expression(subtree_root->left) };
					long double right_op { evaluate_expression(subtree_root->right) };
					const char oper { term[0] };

					return eval_binary_operation(left_op, oper, right_op);
				}
				else {
					return std::stold(subtree_root->term);
				}
			}

			void print_infix_expression(tree_node *node) const {
				if(is_operator(node->term[0])){
					std::cout << "(" ;
					print_infix_expression(node->left);
					std::cout << " " << node->term << " " ;
					print_infix_expression(node->right);
					std::cout << ")" ;
				}
				else{
					std::cout << node->term;
				}
			}

			void print_postfix_expression(tree_node *node) const {
				if(node == nullptr) return;
				print_postfix_expression(node->left);
				print_postfix_expression(node->right);
				std::cout << node->term << " ";
			}

			void print_prefix_expression(tree_node *node) const {
				if(node == nullptr) return;
				std::cout << node->term << " ";
				print_prefix_expression(node->left);
				print_prefix_expression(node->right);
			}

		public:
			void print() const {
				std::cout << std::setfill(' ') << std::setw(3);   //output formatting
				print(root);
			}

			void print_infix_expression() const {
				std::cout << "Infix : ";
				print_infix_expression(root);
				std::cout << std::endl;
			}

			void print_postfix_expression() const {
				std::cout << "Postfix : ";
				print_postfix_expression(root);
				std::cout << std::endl;
			}

			void print_prefix_expression() const {
				std::cout << "Prefix : ";
				print_prefix_expression(root);
				std::cout << std::endl;
			}

			long double evaluate_expression() const {
				return evaluate_expression(root);
			}
	};

}

#endif
