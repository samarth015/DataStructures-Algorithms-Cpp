#ifndef SAMARTH_QUEUE_LINKED_LIST 
#define SAMARTH_QUEUE_LINKED_LIST 

#include<utility>
#include<stdexcept>


namespace samarth {

	template<typename Object>
		class queuell
		{
			private:
				struct node
				{
						Object data;
						node *next;

						node(const Object &data): data{data}, next{nullptr} {}
						node(Object &&data): data{std::move(data)}, next{nullptr} {}

						node() = delete;
						node(const node &other) = delete;
						node(node &&other) noexcept = delete;
						~ node() = default;
				};

				void assert_queue_not_empty() {
					if(empty()) throw std::runtime_error {"Queue is empty."};
				}

				std::size_t length;
				node *head, *tail;
		
			public:
				queuell():
					length{},
					head{nullptr},
					tail{nullptr}
				{}
		
				queuell(const queuell &other): queuell()
				{
					if(other.length == 0) return;
					length = other.length;
					head = tail = new node{ head->data };

					if( other.length == 1) return ;

					node *oth_curr{other.head};
					do{
						oth_curr = oth_curr->next;
						tail = tail->next = new node { oth_curr->data};
					}while( oth_curr != other.tail );
				}
		
				queuell & operator = (const queuell &other){
					if(this == &other) return *this;
					queuell tmp { other };
					std::swap(*this, tmp);
					return *this;
				}
		
				queuell(queuell &&other) noexcept:
					length{other.length},
					head{other.head},
					tail{other.tail}
				{}
		
				queuell & operator = (queuell &&other) noexcept {
					if(this == &other) return *this;

					clear();

					length = other.length;
					head = other.head;
					tail = other.tail;

					other.length = 0;
					other.head = 0;
					other.tail = 0;
						
					return *this;
				}
		
				~ queuell(){
					clear();
				}

				void clear(){
					if(empty()) return ;
					while( head != tail ){
						node *temp{ head };
						head = head->next;
						delete temp;
					}
					length = 0;
				}
				
				bool empty() const {
					return length == 0;
				}

				std::size_t size() const {
					return length;
				}

				Object& front() {
					assert_queue_not_empty();
					return head->data;
				}
				const Object& front() const {
					assert_queue_not_empty();
					return head->data;
				}

				Object& back() {
					assert_queue_not_empty();
					return tail->data;
				}
				const Object& back() const {
					assert_queue_not_empty();
					return tail->data;
				}

				void enqueue(const Object &val){
					node* new_node = new node{ val};
					if( empty() )
						head = tail = new_node;
					else
						tail = tail->next = new_node;
					length++;
				}

				void enqueue(Object &&val){
					node* new_node = new node{ std::move(val)};
					if( empty() )
						head = tail = new_node;
					else
						tail = tail->next = new_node;
					length++;

				}

				void dequeue() {
					assert_queue_not_empty();
					node *temp = head;
					head = head->next;
					delete temp;
					length--;
				}
		};
}

#endif
