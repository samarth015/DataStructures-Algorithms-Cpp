/*
  According to the C++ standard, for the vector , a call to push_back , pop_back , insert ,
or erase invalidates (potentially makes stale) all iterators viewing the vector . Why?

*/


/*
   Answer
   vector is a dynamic container which stores its objects in a dynamically allocated array.(contiguous
   memory block)
   Insertion and removal of objects might cause the complete reallocation of the block and moving of 
   all the objects in the current block into the new block.
   This causes iterators of the vector to be invalidated as they continue to point to the old block.

   push_back - If an element is pushed and the block of memory is full. A new block will be allocated and
   iterator vector will be invalidated.

   pop_back - If an iterator is pointing to some element and pop_back() is called a number of times such
   that the element being pointed to is popped, the iterator will be invalidated.

   insert - Like push_back, insertion might causes complete reallocation invalidating iterators.

   erase - If an iterator falls within the half-open range given to erase, it will be invalidated.
   The elements are also moved within the memory block which will invalidate an iterator.

*/
