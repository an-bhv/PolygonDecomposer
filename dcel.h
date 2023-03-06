#pragma once

namespace dcel{

	class vertex;
	class edge;
	class face;

    class vertex{
		public:
			int x;
			int y;
			edge* inc_edge;
			vertex(int x, int y);
	};
    class edge{
		public:
			vertex *org, *dest;
			edge *twin, *next, *prev;
			face *left;

			static edge* create_edge(vertex *u, vertex *v);

			static void link_edge(edge* e1, edge* e2);

			static void add_edge(vertex* u, vertex* v);

			edge(vertex *u, vertex *v);
	};

    class face{
		public:
			edge *inc_edge;
			
			void traverse_face();
			face(edge* e);
	};
	
}


/*

	adding new edges -> modify faces and all 
	check angle -> will use the same logic to check if convex polygon and to eliminate vertex if notch -> basically cross product thingy
	remove edge -> optional

*/