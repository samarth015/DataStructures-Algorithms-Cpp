/*

	Show that in a binary tree of N nodes, there are N + 1 nullptr links representing
	children.

*/

//Answer
//
// Each node has 2 links so there are a total of 2 * N links.
// Each node has one link pointing to it (of its parent) except the root node.
// So there are a N - 1 links that point to nodes (Non nullptr).
// Number of nullptr links = 2N - (N - 1) = N + 1
