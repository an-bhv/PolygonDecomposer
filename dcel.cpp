#include<iostream>
#include<stdio.h>
#include<vector>
#include "dcel.h"
using namespace dcel;



vertex::vertex(int x, int y)
{
	this->x = x;
	this->y = y;
}


edge* edge::create_edge(vertex *u, vertex *v)
{
	edge *e1 = new edge(u, v);
	edge *e2 = new edge(v, u);
	
	e1->twin = e2;
	e2->twin = e1;

	return e1;
}

void edge::link_edge(edge* e1, edge* e2){
	e1->next = e2;
	e2->prev = e1;
}

void edge::add_edge(vertex* u, vertex* v){
	edge* new_edge = edge::create_edge(u,v);

	edge::link_edge(u->inc_edge->prev,new_edge);
	edge::link_edge(v->inc_edge->prev,new_edge->twin);
	edge::link_edge(new_edge,v->inc_edge);
	edge::link_edge(new_edge->twin,u->inc_edge);

	new_edge->left = v->inc_edge->left;
	face* new_face = new face(new_edge->twin);

}

edge::edge(vertex *u, vertex *v)
{
	org = u;
	dest = v;
}



void face::traverse_face(){
	std::cout<<this<<"\n-------------\n";
	std::cout<<inc_edge->org->x << " " << inc_edge->org->y<<", ";
	std::cout<<inc_edge->dest->x << " " << inc_edge->dest->y <<"\n";
	edge* e = inc_edge->next;
	while(e!=inc_edge){
		e->left = this;
		std::cout<<e->org->x << " " << e->org->y<<", ";
		std::cout<<e->dest->x << " " << e->dest->y <<"\n";
		e = e->next; 
	}
}

face::face(edge* e)
{
	inc_edge = e;
	inc_edge->left = this;
	traverse_face();
}

