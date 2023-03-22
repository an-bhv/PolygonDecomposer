#include <bits/stdc++.h>
#include "dcel.h"

using namespace std;
using dcel::edge;
using dcel::vertex;
using dcel::face;


void print_vertex(vertex* v){
	cout<<"{"<<v->x<<" ,"<<v->y<<"}\n";
}
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
			if(check_collinear(cur_pol[i], cur_pol[i+1], point)){
				return true;
			}
		}
			
	}
	return num_intersect%2 == 1;
}

void visualize(set<face*> faces,string name){

	//list out vertices and edges
	set<pair<int,int>> points;
	set<array<int,4>> edges;
	int mx =-1,mn =0;
	// cout<<"-----VIS----\n";
	for(auto face: faces){
		edge* e = face->inc_edge;
		// cout<<face<<"\n";
		// print_vertex(e->org);
		// print_vertex(e->dest);
		points.insert({e->org->x,e->org->y});
		edges.insert({e->org->x,e->org->y,e->dest->x,e->dest->y});
		mx = max({e->org->x,e->org->y,mx});
		e = e->next;
		while(e!=face->inc_edge){
			// cout<<"===\n";
			// print_vertex(e->org);
			// print_vertex(e->dest);
			points.insert({e->org->x,e->org->y});
			edges.insert({e->org->x,e->org->y,e->dest->x,e->dest->y});
			mx = max({e->org->x,e->org->y,mx});
			e = e->next;
		}
	}

	for(auto p: points){
		cout<<p.first<<" "<<p.second<<"\n";
	}

	//output svg file
	ofstream out;
	out.open(name);
	mx +=10;
	mn -=5;
	out <<"<?xml version=\"1.0\" standalone=\"no\"?> \
	<svg viewBox = \""<<mn<<" "<<mn<<" "<<mx<<" "<<mx<<"\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">\n";

	for(auto e: edges){
		out<<"<line x1=\""<<e[0]<<"\" y1=\""<<e[1]<<"\" x2=\""<<e[2]<<"\" y2=\""<<e[3]<<"\" stroke = \"black\" stroke-width=\"0.2\"/>\n";
	}
	for(auto point: points){
		out<<"<circle cx=\""<<point.first<<"\" cy=\""<<point.second<<"\" r=\"0.2\" fill=\"red\"/>\n";
	}

	out<<"</svg>";
	out.close();

}



int main(){

	freopen("input.txt","r", stdin);
	int n;std::cin>>n; //number of points
	int flip;cin>>flip; //flip the input if anti clockwise
	std::vector<pair<int,int>> vertices(n);
	for(int i=0;i<n;i++){
		cin>>vertices[i].first>>vertices[i].second;
	}

	if(flip) reverse(vertices.begin(),vertices.end());

	vertex* v0 = build(vertices,n);
	std::vector<vertex*> prev_pol,cur_pol;
	prev_pol.push_back(v0);

	set<vertex*> notches = obtain_notches(v0);

	set<face*> faces;

	visualize({v0->inc_edge->left},"input.svg");


	cout<<endl;
	while(n>3){
		cout<<"n = "<<n<<"\n";
		vertex* v1 = prev_pol.back();
		vertex* v2 = v1->inc_edge->dest;

		cout<<"----v1 and v2-----\n";
		print_vertex(v1);
		print_vertex(v2);
		cout<<"-----\n";
		cur_pol = {v1,v2};
		vertex* candidate = v2->inc_edge->dest;

		int xmin = min(v1->x,v2->x),xmax = max(v1->x,v2->x), ymin = min(v1->y,v2->y), ymax = max(v1->y,v2->y);

		while(!check_reflex(cur_pol[cur_pol.size()-2],cur_pol[cur_pol.size()-1],candidate) && !check_reflex(cur_pol[cur_pol.size()-1],candidate,v1) && !check_reflex(candidate,v1,v2) && cur_pol.size()<n){
			cur_pol.push_back(candidate);
			xmin = min(xmin, candidate->x); 
			xmax = max(xmax, candidate->x);
			ymin = min(ymin, candidate->y); 
			ymax = max(ymax, candidate->y);
			cout<<"---------CANDIDATE----------\n";
			cout<<candidate->x<<" "<<candidate->y<<"\n";
			notches.erase(candidate);
			candidate = candidate->inc_edge->dest;
		}

		// cout<<cur_pol.size()<<"\n";

		cout<<"-----BOUNDING RECT------\n";
		printf("{%d,%d} {%d,%d}\n",xmin,ymin,xmax,ymax);
		cout<<"----------\n";
		if(cur_pol.size()==n){
			faces.insert(v1->inc_edge->left);
			faces.insert(v1->inc_edge->twin->left);
			break;
		}
		deque<vertex*> LPVS;
		for(auto notch: notches) LPVS.push_back(notch);
		// cout<<LPVS.size()<<"huh\n";
		cout<<"--------NOTCH-------"<<endl;
		for(auto &x: notches) cout<<x->x<<" "<<x->y<<endl;
		while(!LPVS.empty()){
			cout<<"--------LPVS-------"<<endl;
			for(auto &x: LPVS) cout<<x->x<<" "<<x->y<<endl;
			cout<<endl;
			vertex* notch = LPVS.front();
			if(notch->x <= xmax && notch->x >= xmin && notch->y <= ymax && notch->y >= ymin){
				cout<<notch->x<<" "<<notch->y<<" "<<" is in the rectangle!!!"<<endl;
				if(check_in_pol(cur_pol,notch)){
					cout<<notch->x<<" "<<notch->y<<" "<<" is in the polygon!!!"<<endl;
					bool side = check_reflex(cur_pol.back(),notch,v1);
					while(cur_pol.size()>2 && (check_reflex(cur_pol.back(),notch,v1)==side || check_collinear(cur_pol.back(),notch,v1))){
						cur_pol.pop_back();
					}
				}else printf("Not in pol\n");
			}
			LPVS.pop_front();
		}
		cout<<"SIZEEEEEE: " << cur_pol.size()<<"-" << endl;
		if(cur_pol.back()!=v2){
			cout<<"----ADDING EDGE-----\n";
			print_vertex(v1);
			print_vertex(v2);
			print_vertex(cur_pol.back());
			edge::add_edge(cur_pol.back(),v1);
			if(check_reflex(cur_pol.back()->inc_edge->dest,cur_pol.back(),v1)){
				notches.insert(cur_pol.back());
			}
			faces.insert(v1->inc_edge->left);
			faces.insert(v1->inc_edge->twin->left);
			n = n - cur_pol.size() + 2;
			cout << n << "\n";
			// cout<<"here\n";
		}

		prev_pol = cur_pol;

	}
	cout << "\n\n\n\n";
	for(auto f: faces) { //we n
		cout<<f<<"*************\n";
		f->traverse_face();
	}

	visualize(faces,"output.svg");

	cout<<"[~]Exiting...";
}