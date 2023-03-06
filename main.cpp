#include <bits/stdc++.h>
#include "dcel.h"

using namespace std;
using dcel::edge;
using dcel::vertex;
using dcel::face;

//reads polygon file and build dcel, return pointer to first vertex
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
		edge::link_edge(e->twin,prevedge->twin);
		prev->inc_edge = e; 
		prev = v;
		prevedge = e;
			
	}
	
	edge* e = edge::create_edge(prev,v0);
	edge::link_edge(prevedge,e);
	edge::link_edge(e->twin,prevedge->twin);
	edge::link_edge(e,e0);        
	edge::link_edge(e0->twin,e->twin);        
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


set<vertex*> obtain_notches(vertex* v){
	edge* e0 = v->inc_edge;
	edge* prev_edge = e0;
	edge* e = v->inc_edge->next;
	set<vertex*> notches;

	while(true){
		if(check_reflex(prev_edge->org,e->org,e->dest)){
			notches.insert(e->org);
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

	freopen("input.txt","r", stdin);
	int n;std::cin>>n; //number of points
	std::vector<pair<int,int>> vertices(n);
	for(int i=0;i<n;i++){
		cin>>vertices[i].first>>vertices[i].second;
	}
	vertex* v0 = build(vertices,n);

	std::vector<vertex*> prev_pol,cur_pol;
	prev_pol.push_back(v0);

	set<vertex*> notches = obtain_notches(v0);

	vector<face*> faces;


	while(n>3){
		vertex* v1 = prev_pol.back();
		vertex* v2 = v1->inc_edge->dest;

		cur_pol = {v1,v2};

		vertex* candidate = v2->inc_edge->dest;

		int xmin = min(v1->x,v2->x),xmax = min(v1->x,v2->x), ymin = min(v1->y,v2->y), ymax = max(v1->y,v2->y);

		while(!check_reflex(cur_pol[cur_pol.size()-2],cur_pol[cur_pol.size()-1],candidate) && !check_reflex(cur_pol[cur_pol.size()-1],candidate,v1) && !check_reflex(candidate,v1,v2) && cur_pol.size()<n){
			cur_pol.push_back(candidate);
			xmin = min(xmin, candidate->x); 
			xmax = max(xmax, candidate->x);
			ymin = min(ymin, candidate->y); 
			ymax = max(ymax, candidate->y);

			candidate = candidate->inc_edge->dest;
		}

		if(cur_pol.size()!=n){
			vector<vertex*> LPVS;
			for(auto notch: notches) LPVS.push_back(notch);

			while(!LPVS.empty()){
				vertex* notch = LPVS.back();
				if(notch->x <= xmax && notch->x >= xmin && notch->y <= ymax && notch->y >= ymin){
					if(check_in_pol(cur_pol,notch)){
						bool side = check_reflex(cur_pol.back(),notch,v1);
						while(!cur_pol.empty() && (check_reflex(cur_pol.back(),notch,v1)==side || check_collinear(cur_pol.back(),notch,v1))){
							cur_pol.pop_back();
						}
					}
				}
				LPVS.pop_back();
			}
		}


		if(cur_pol.back()!=v2){
			notches.erase(cur_pol.back());
			edge::add_edge(cur_pol.back(),v1);
			faces.push_back(v1->inc_edge->left);
			n = n - cur_pol.size() + 2;
		}

		prev_pol = cur_pol;

	}



	//go through all faces and make an adjacency list



}