/*

For each node in the tree of Figure 4.74:
	a. Name the parent node.
	b. List the children.
	c. List the siblings.
	d. Compute the depth.
	e. Compute the height.

*/

/* Answer
			 	parent      	siblings   	        depth          height
	 A        	 None              None               0               4 
	 B            A                 C                 1               3
	 C            A                 B                 1               2
	 D            B                 E                 2               1
	 E            B                 D                 2               2
	 F            C                None               2               1
	 G            D                 H                 3               0
	 H            D                 G                 3               0
	 I            E                 J                 3               0
	 J            E                 I                 3               1 
	 K            F                None               3               0
	 L            J                 M                 4               0
	 M            J                 L                 4               0

 */
