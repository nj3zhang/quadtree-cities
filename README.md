# quadtree-cities
Implemented a quad tree in C++ to store various cities by their x,y coordinates and stores relevant information about each city

Makefile included to compile on linux. Run 'Make' to create an excecutable.

Commands:
      insert: `i *city_info*`
      search: `s *x;y*`
      maximum value of attribute start at node xy in direction specified: q_max x;y;d;attr
      minimum value of attribute start at node xy in direction specified: q_min x;y;d;attr
      total value of attribute start at node xy in direction specified: q_total x;y;d;attr
      in order traversal and print: print
      size of the tree: size
      clear the entire tree: clear

Command exmaples:
Insert: i Toronto;-79.42;43.66;5213000;2157;3396
        i Montreal;-73.58;45.5;3678000;1219;3215
        i Vancouver;-123.13;49.25;2313328;2028;3734
Search:
        s -79.42;43.66
Maximum of attribute in direction and coordinate specified:
        q_max -79.42;43.66;NE;p
Minimum of attribute in direction and coordinate specified:
        q_min -79.42;43.66;NE;p
Total value of attribute in direction and coordinate specified:
        q_total -79.42;43.66;NE;p
Size of tree: 
        size
In order print: 
         print
