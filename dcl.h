#pragma once
#include<bits/stdc++.h>
using namespace std;

namespace dcel{

    class vertex;
    class edge;
    class face;

    class vertex
    {
    public:
        int x;
        int y;
        edge* inc_edge;

        vertex(int x, int y)
        {
            this->x = x;
            this->y = y;
        }

    };

    class edge
    {
    public:
        vertex *org, *dest;
        edge *twin, *next, *prev;
        face *left;


        static edge* create_edge(vertex *u, vertex *v)
        {
            edge *e1 = new edge(u, v);
            edge *e2 = new edge(v, u);
			
            e1->twin = e2;
            e2->twin = e1;

            return e1;
        }


        static void link_edge(edge* e1, edge* e2){
			e1->next = e2;
			e2->prev = e1;
			e1->twin->prev = e2->twin;
			e2->twin->next = e1->twin;
        }
        
        edge(vertex *u, vertex *v)
        {
            org = u;
            dest = v;
        }
    };

    class face
    {
    public:
        edge *inc_edge;
        
		void traverse_face(){
			inc_edge->left = this;
			edge* e = inc_edge->next;
			while(e!=inc_edge){
				e->left = this;
				e = e->next;
			}
		}

        face(edge* e)
        {
            inc_edge = e;
			traverse_face();
		}

    };



}


/*

	adding new edges -> modify faces and all 
	check angle -> will use the same logic to check if convex polygon and to eliminate vertex if notch -> basically cross product thingy
	remove edge -> optional

*/