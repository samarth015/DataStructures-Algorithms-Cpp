
/* This implementation of queue is a container adapter that gives the 
 * functionality of a queue. Which means it is a wrapper around any 
 * container which supports a push_back(), pop_front(), front() and back().
 */
#ifndef SAMARTH_QUEUE_ADAPTER
#define SAMARTH_QUEUE_ADAPTER

#include<stdexcept>
#include<utility>
#include<deque>

namespace samarth {

	template<typename Object, typename SequenceContainerType = std::deque<Object>>
	class queue
	{
		private:
			SequenceContainerType cont;
		public:
			queue(): cont{} {}

			queue( const SequenceContainerType & other_cont ): cont{other_cont} {} 

			queue(SequenceContainerType &&other_cont ): cont{ std::move(other_cont) } {} 

			queue( const queue &oth ): cont{ oth.cont } {}
			queue& operator = (const queue &oth){
				cont = oth.cont;
			}

			queue(queue &&oth) noexcept : cont{ std::move(oth.cont) } {}
			queue& operator = (queue &&oth) noexcept{
				cont = std::move(oth.cont);
			}

			~queue() = default;

			bool empty(){
				return cont.empty();
			}

			std::size_t size(){
				return cont.size();
			}

			void enqueue(const Object &val){
				cont.push_back(val);
			}
			void enqueue(Object &&val){
				cont.push_back(std::move(val));
			}

			Object& back(){
				return cont.back();
			}
			const Object& back() const {
				return cont.back();
			}

			Object& front(){
				return cont.front();
			}
			const Object& front() const {
				return cont.front();
			}

			void dequeue(){
				cont.pop_front();
			}
			
			void clear(){
				cont.clear();
			}
	};
}

#endif
