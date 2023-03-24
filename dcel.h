/* 
*	Anubhav Sharma (2020A7PS1892H)
*	Sreeram Yerasani (2020A7PS0052H)
*	Varun Vaddiraju (2020A7PS0173H)
*	Rohith Paul (2020A7PS2044H)
* 
* dcel_HEADER_FILE
----------------------------------------------*/
#pragma once

namespace dcel
{
    /** Class protoypes for DCEL
     */
    class vertex;
    class edge;
    class face;

    /*! Vertex Class of a DCEL!*/
    class vertex
    {
    public:
        double x;    					/*!< x-coordinate of a vertex */
        double y;    					/*!< y-coordinate of a vertex */
        edge *inc_edge;        			/*!< an edge incident on the vertex */

        vertex(double x, double y);		//!< constructor with two input for the vertex
    };

    /*! Edge Class of a DCEL!*/
    class edge
    {
    public:
        vertex *org;			/*!< source of an edge*/
		vertex *dest;        	/*!< destination of an edge*/
        edge *twin;				/*!< twin edge linked to an edge*/
		edge *next;				/*!< next edge linked to an edge*/
		edge *prev;				/*!< previous edge linked to an edge*/
        face *left;				/*!< face incident to an edge*/

        static edge *create_edge(vertex *u, vertex *v);		//!< static method for creating an edge-twin pair

        static void link_edge(edge *e, edge *f);			//!< static method for linking two consecutive edges

        static void add_edge(vertex *u, vertex *v);			//!< static method for creating a diagnol between two vertices

        static face *remove_edge(edge *e);					//!< static method for removing a diagnol between two vertices

        edge(vertex *u, vertex *v);							//!< constructor with two endpoints for an edge
    };

    /*! Face Class of a DCEL!*/
    class face
    {
    public:
        edge *inc_edge;			/*!< edge incident to a face*/

        void traverse_face();	//!< method to link a face to all incident edges

        face(edge *e);			//!< constructor with a single incident edge to the face
    };

}