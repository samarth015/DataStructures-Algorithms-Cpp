// Circular Queue

#ifndef SAMARTH_CIRCULAR_QUEUE
#define SAMARTH_CIRCULAR_QUEUE

#include<utility>
#include<stdexcept>

namespace samarth {

	template<typename Object>
		class queuearr
		{
			private:
				std::size_t cap, length, head, tail;
				Object *array;

				void assert_queue_has_space(){
					if( isfull() ) throw std::runtime_error {"Queue is full."};
				}

				void assert_queue_is_not_empty(){
					if( empty() ) throw std::runtime_error {"Queue is empty."};
				}
		
			public:
				queuearr(std::size_t cap):
					cap{cap},
					length{},
					head{},
					tail{cap-1}, 
					array{ new Object[cap] }
				{}

				queuearr(): queuearr(100) {}
		
				queuearr(const queuearr &other): queuearr(other.cap) {
					if(other.length == 0) return ;
					length = other.length;

					this->array[0] = other.array[head];
					tail = 0;

					std::size_t curr{other.head+1};

					while( curr != other.tail + 1 ){
						this->array[++tail] = other.array[curr];
						curr = (curr+1) % other.cap;
					}
				}
		
				queuearr & operator = (const queuearr &other){
					if(this == &other) return *this;
					queuearr tmp {other};
					std::swap(tmp, *this);
					return this;
				}
		
				queuearr(queuearr &&other) noexcept :
					cap{other.cap},
					length{other.length},
					head{other.head},
					tail{other.tail},
					array{other.array}
				{ 
					other.cap = 0;
					other.length = 0;
					other.head = 0;
					other.tail = 0;
					other.array = nullptr;
				}
		
				queuearr & operator = (queuearr &&other) noexcept {
					if(this == &other) return *this;

					if(array) delete[] array;

					cap = other.cap;
					length = other.length;
					head = other.head;
					tail = other.tail;
					array = other.array;
					 
					other.cap = 0;
					other.length = 0;
					other.head = 0;
					other.tail = 0;
					other.array = nullptr;

					return *this;
				}
		
				~ queuearr(){
					if(array) delete[] array;
				}

				void clear(){
					length = 0;
					head = 0;
					tail = cap - 1;
				}

				bool empty() const {
					return length == 0;
				}

				bool isfull() const {
					return length == cap;
				}

				std::size_t capacity() const {
					return cap;
				}

				std::size_t size() const {
					return length;
				}

				Object& front(){
					assert_queue_is_not_empty();
					return array[head];
				}
				const Object& front() const {
					assert_queue_is_not_empty();
					return array[head];
				}
				Object& back(){
					assert_queue_is_not_empty();
					return array[tail];
				}
				const Object& back() const {
					assert_queue_is_not_empty();
					return array[tail];
				}

				void enqueue(const Object & val){
					assert_queue_has_space();
					tail = (tail+1) % cap;
					array[tail] = val;
					length++;
				}
				void enqueue(Object && val) {
					assert_queue_has_space();
					tail = (tail+1) % cap;
					array[tail] = std::move(val);
					length++;
				}

				void dequeue(){
					assert_queue_is_not_empty();
					head = (head+1) % cap;
					length--;
				}
		};
}

#endif
