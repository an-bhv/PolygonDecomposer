/* 
*	Anubhav Sharma (2020A7PS1892H)
*	Sreeram Yerasani (2020A7PS0052H)
*	Varun Vaddiraju (2020A7PS0173H)
*	Rohith Paul (2020A7PS2044H)
* 
* dcel_CPP_FILE
------------------------------------------*/
#include <iostream>
#include <stdio.h>
#include <vector>
#include "dcel.h"
using namespace dcel;

/** 
* @brief Default constructor for the vertex object in the DCEL structure.
* 
* @param x x-coordinate of the vertex to be created.
* @param y y-coordinate of the vertex to be created.
*/
vertex::vertex(double x, double y)
{
    this->x = x;
    this->y = y;
}

/** 
* @brief Method to create an edge-twin pair between two vertices which returns the edge between
* the given vertices.
*
* @param u 	source vertex for the edge.
* @param v	destination vertex for the edge.
* @retval edge*	pointer to the directed edge created between the source and destination vertices.
*/
edge *edge::create_edge(vertex *u, vertex *v)
{
    edge *e1 = new edge(u, v);
    edge *e2 = new edge(v, u);

    e1->twin = e2;
    e2->twin = e1;

    return e1;
}

/** 
* @brief Method to link two consecutive edges in a DCEL structure.
*
* @param e 	source vertex for the edge.
* @param f	destination vertex for the edge.
* @return void
*/
void edge::link_edge(edge *e, edge *f)
{
    e->next = f;
    f->prev = e;
}

/** 
* @brief Method to add a diagnol between two vertices which already have edges starting
* at them.
*
* @param u 	source vertex for the daignol.
* @param v	destination vertex for the diagnol.
* @return void
*/
void edge::add_edge(vertex *u, vertex *v)
{
    edge *new_edge = edge::create_edge(u, v);

    edge::link_edge(u->inc_edge->prev, new_edge);
    edge::link_edge(v->inc_edge->prev, new_edge->twin);
    edge::link_edge(new_edge, v->inc_edge);
    edge::link_edge(new_edge->twin, u->inc_edge);

    face *old_face = v->inc_edge->left;
    v->inc_edge = new_edge->twin;

    face *new_face = new face(new_edge);
    old_face->inc_edge = new_edge->twin;
    new_edge->twin->left = old_face;

    old_face->traverse_face();
}

/** 
* @brief Method to remove a diagnol from the DCEL structure which connects two faces.
*
* @param e 	the edge being removed from the DCEL.
* @retval face*	the new face created from removing the diagnol.
*/
face *edge::remove_edge(edge *e)
{
    edge::link_edge(e->twin->prev, e->next);
    edge::link_edge(e->prev, e->twin->next);

    face *deleted_face = e->left;
    edge *twin = e->twin;
    face *kept_face = twin->left;
    if (kept_face->inc_edge == twin)
        kept_face->inc_edge = twin->next;
	
    delete e;
    delete twin;
    kept_face->traverse_face();

    return deleted_face;
}

/** 
* @brief Default constructor for the edge object in the DCEL structure.
* 
* @param u sorce vertex of the edge being created.
* @param v destination vertex of the edge being created.
*/
edge::edge(vertex *u, vertex *v)
{
    org = u;
    dest = v;
}

/** 
* @brief A linker method to link all the edges connected to current face object.
*
* @return void
*/
void face::traverse_face()
{
    edge *e = inc_edge->next;
    while (e != inc_edge)
    {
        e->left = this;
        e = e->next;
    }
}

/** 
* @brief Default constructor for the face object in the DCEL structure.
* 
* @param e one of the edge which is incident to this face.
*/
face::face(edge *e)
{
    inc_edge = e;
    inc_edge->left = this;
    traverse_face();
}