
namespace samarth{
	template<typename ForwardIterator, typename Object>
		ForwardIterator find(ForwardIterator begin, ForwardIterator end, const Object &x ){

			for( auto curr_it {begin}; curr_it != end; curr_it++)
				if( *curr_it == x ) return curr_it;

			return end;
		}
	template<typename ForwardIterator, typename Predicate>
		ForwardIterator find_if(ForwardIterator begin, ForwardIterator end, const Predicate &pre){

			for( auto curr_it {begin}; curr_it != end; curr_it++)
				if( pre(*curr_it) ) return curr_it;

			return end;
		}
}
