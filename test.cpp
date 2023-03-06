#include<iostream>
#include<stdio.h>
#include<vector>
#include "dcel.h"

using namespace std;
using dcel::edge;
using dcel::vertex;
using dcel::face;


vertex* build(vector<pair<int,int>>& inp,int n){

	vertex* prev = new vertex(inp[0].first,inp[0].second);
	vertex* v0 = prev;
	prev = new vertex(inp[1].first,inp[1].second);
	edge* prevedge = edge::create_edge(v0,prev);
	edge* e0 = prevedge;
	v0->inc_edge = e0;
	for(int i=2;i<n;i++){
		vertex* v = new vertex(inp[i].first,inp[i].second);
		edge* e = edge::create_edge(prev,v);
		// prevedge->next = e;
		// e->prev = prevedge;
		edge::link_edge(prevedge,e);
		prev->inc_edge = e; 
		prev = v;
		prevedge = e;
			
	}
	
    edge* e = edge::create_edge(prev,v0);
	edge::link_edge(prevedge,e);
	edge::link_edge(e,e0);        
	prev->inc_edge = e;
	face* f1 = new face(e0);
	face* f2 = new face(e0->twin);

	return v0;
}

bool check_reflex(vertex* v0,vertex* v1,vertex* v2){
	return (((v2->y - v0->y)*(v1->x - v0->x) - (v1->y - v0->y)*(v2->x - v0->x)) > 0);
}

bool check_collinear(vertex* v0,vertex* v1,vertex* v2){
	return (((v2->y - v0->y)*(v1->x - v0->x) - (v1->y - v0->y)*(v2->x - v0->x)) == 0);
}

vector<vertex*> obtain_notches(vertex* v){
	edge* e0 = v->inc_edge;
	edge* prev_edge = e0;
	edge* e = v->inc_edge->next;
	vector<vertex*> notches;

	while(true){
		if(check_reflex(prev_edge->org,e->org,e->dest)){
			notches.push_back(e->org);
		}
        prev_edge = e;
		e = e->next;
        if(e==e0) break;
	}

	return notches;

}

bool check_in_pol(vector<vertex*> &cur_pol , vertex* point){
	int num_intersect = 0;
	int ymin, ymax;
	vertex* a;
	vertex* b;
	for(int i=0; i<cur_pol.size(); i++){
		a = cur_pol[i];
		b = cur_pol[(i+1)%cur_pol.size()];
		if(a->y > b->y){
			swap(a,b);
		}
		if(a->y <= point->y && b->y > point->y && !check_reflex(a, b, point)){
			num_intersect++;
			cout << i << endl;
			if(check_collinear(cur_pol[i], cur_pol[i+1], point)){
				return true;
			}
		}
			
	}
	return num_intersect%2 == 1;
}

int main(){
	freopen("input.txt", "r", stdin);
	int n;std::cin>>n; //number of points
	std::vector<pair<int,int>> vertices(n);
	int x, y;
	for(int i=0;i<n;i++){
		cin>>vertices[i].first>>vertices[i].second;
	}
	vertex* v0 = build(vertices,n);
    return 0;
}