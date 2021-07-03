/*

   Show that the maximum number of nodes in a binary tree of height h is 2^(h+1) − 1.

*/

/*  	Answer 
 
 
		When tree has maximum possible nodes, all levels/heights are fully filled.

		Each level has a number of nodes equal to a power of two.

		(root) 0   --   2^0                        0             1
			   1   --   2^1                    0       0         2
			   2   --   2^2                  0   0   0   0       4
			   3   --   2^3       		    0 0 0 0 0 0 0 0      8
			   ...
			   ...
		(leaf) h   --   2^h  

		Total number of leaves = 2^0 + 2^1 + 2^2 + 2^3 .... 2^h
							   = 1 + 2 + 4 + 8 ... 2^h
							   = 2^(h+1) - 1        (Use geometric series formula)

*/
