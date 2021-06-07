/* This implementation of stack is a container adapter that gives the 
 * functionality of a stack. Which means it is a wrapper around any 
 * container which supports a push_back(), pop_back() and back()
 */

#ifndef SAMARTH_STACK_ADAPTER
#define SAMARTH_STACK_ADAPTER

#include<stdexcept>
#include<utility>
#include<vector>


namespace samarth {

	template<typename Object, typename SequenceContainerType = std::vector<Object>>
	class stack
	{
		private:
			SequenceContainerType cont;
		public:
			stack(): cont{} {}

			stack( const SequenceContainerType & other_cont ): cont{ other_cont } {} 

			stack(SequenceContainerType &&other_cont ): cont{ std::move(other_cont) } {} 

			stack( const stack &oth ): cont{ oth.cont } {}
			stack& operator = (const stack &oth){
				if(this == &oth) return *this;
				cont = oth.cont;
				return *this;
			}

			stack(stack &&oth) noexcept : cont{ std::move(oth.cont) } {}
			stack& operator = (stack &&oth) noexcept{
				if(this == &oth) return *this;
				cont = std::move(oth.cont);
				return *this;
			}

			~stack() = default;

			bool empty(){
				return cont.empty();
			}

			std::size_t size(){
				return cont.size();
			}

			void push(const Object &val){
				cont.push_back(val);
			}
			void push(Object &&val){
				cont.push_back(std::move(val));
			}

			Object& top(){
				return cont.back();
			}

			void pop(){
				cont.pop_back();
			}
			
			void clear(){
				cont.clear();
			}
	};
}

#endif
