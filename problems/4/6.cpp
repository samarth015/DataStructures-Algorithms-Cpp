/*

   A full node is a node with two children. Prove that the number of full nodes plus
   one is equal to the number of leaves in a nonempty binary tree.


*/

/* Answer
  
   Let num of : Leaves = L
   				Half Nodes = H
				Full Nodes = F
				Total Nodes = N

				We know that num of nullptr links = N + 1

				Each half node has one nullptr and a leaf has two.
				So  H + 2L = N + 1

				Also N = L + H + F

				Solving the two eq we get F + 1 = L
*/
