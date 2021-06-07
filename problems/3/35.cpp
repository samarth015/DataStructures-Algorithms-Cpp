/*

	   One way to implement a queue is to use a circular linked list. In a circular linked
	list, the last node’s next pointer points at the ﬁrst node. Assume the list does not
	contain a header and that we can maintain, at most, one iterator corresponding to
	a node in the list. For which of the following representations can all basic queue
	operations be performed in constant worst-case time? Justify your answers.

		a. Maintain an iterator that corresponds to the ﬁrst item in the list.
		b. Maintain an iterator that corresponds to the last item in the list.

*/



// ANSWER

// Assuming the linked list to be singly(only forward links) option b will allow us to perform 
// queue operations in constant time. While option a will only be able to do the operations in linear time.

// When we have an iterator corresponding to the first item, to enqueue you need to traverse to
// the last item as only forward links are present in nodes and you cannot traverse backwards.
// Similarly with dequeue, you need to traverse to the last item.

// In both operations, the last node’s next must be set to the new last node(after enqueue) or the next
// first node(after dequeue) to maintain the circular nature.

// When we hold a iterator to the last item, all operations are done in constant time as we are already 
// at the end.
