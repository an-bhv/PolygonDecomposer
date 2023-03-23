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
vertex* build(vector<pair<double,double>>& inp,int n){

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
	return (((v2->y - v0->y)*(v1->x - v0->x) - (v1->y - v0->y)*(v2->x - v0->x)) > 0.0);
}

bool check_collinear(vertex* v0,vertex* v1,vertex* v2){
	return (((v2->y - v0->y)*(v1->x - v0->x) - (v1->y - v0->y)*(v2->x - v0->x)) == 0.0);
}


deque<vertex*> obtain_notches(vertex* v){
	edge* e0 = v->inc_edge;
	edge* prev_edge = e0;
	edge* e = v->inc_edge->next;
	deque<vertex*> notches;

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
	double ymin, ymax;
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
		}
		if(a->y <= point->y && b->y >= point->y && check_collinear(a, b, point)){
			return true;
		}
	}
	return num_intersect%2 == 1;
}

void visualize(set<face*> faces,string name){

	//list out vertices and edges
	// set<pair<double,double>> points;
	// set<array<double,4>> edges;
	// double mx =-1,mn =0;
	ofstream out;
	out.open(name);

	// cout<<"-----VIS----\n";
	for(auto face: faces){
		edge* e = face->inc_edge;
		// cout<<face<<"\n";
		// print_vertex(e->org);
		// print_vertex(e->dest);
		// points.insert({e->org->x,e->org->y});
		// edges.insert({e->org->x,e->org->y,e->dest->x,e->dest->y});

		// mx = max({e->org->x,e->org->y,mx});
		out<<e->org->x<<","<<e->org->y<<"\n";
		e = e->next;
		while(e!=face->inc_edge){
			// cout<<"===\n";
			// print_vertex(e->org);
			// print_vertex(e->dest);
			// points.insert({e->org->x,e->org->y});
			// edges.insert({e->org->x,e->org->y,e->dest->x,e->dest->y});
			// mx = max({e->org->x,e->org->y,mx})
			out<<e->org->x<<", "<<e->org->y<<"\n";
			e = e->next;
		}
		out<<"\n";
	}

	// for(auto p: points){
	// 	cout<<p.first<<" "<<p.second<<"\n";
	// }

	//output svg file

	

	// mx += (0.1)*mx;
	// mn -= (0.1)*mn;
	// out <<"<?xml version=\"1.0\" standalone=\"no\"?> \
	// <svg viewBox = \""<<mn<<" "<<mn<<" "<<mx<<" "<<mx<<"\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">\n";
	// out<<"<g transform=\"scale(1,-1)\" > <g transform=\"translate(0,"<<-mx/2<<")\">\n";
	// for(auto e: edges){
	// 	out<<"<line x1=\""<<e[0]<<"\" y1=\""<<e[1]<<"\" x2=\""<<e[2]<<"\" y2=\""<<e[3]<<"\" stroke = \"black\" stroke-width=\"0.002\"/>\n";
	// }
	// for(auto point: points){
	// 	out<<"<circle cx=\""<<point.first<<"\" cy=\""<<point.second<<"\" r=\"0.002\" fill=\"red\"/>\n";
	// }
	
	// out<<"</g></g></svg>";
	out.close();

}



int main(){

	freopen("input.txt","r", stdin);
	int n;std::cin>>n; //number of points
	int flip;cin>>flip; //flip the input if anti clockwise
	std::vector<pair<double,double>> vertices(n);
	for(int i=0;i<n;i++){
		cin>>vertices[i].first>>vertices[i].second;
	}

	if(flip) reverse(vertices.begin(),vertices.end());

	vertex* v0 = build(vertices,n);
	std::vector<vertex*> prev_pol,cur_pol;
	prev_pol.push_back(v0);

	// deque<vertex*> notches = obtain_notches(v0);

	set<face*> faces;
	faces.insert(v0->inc_edge->left);
	visualize(faces,"in.txt");
	int i =0;

	vector<edge*> diagonals;

	while(n>3){

		// visualize(faces,"output"+ to_string(i) +".svg");
		i++;
		vertex* v1 = prev_pol.back();
		vertex* v2 = v1->inc_edge->dest;

		// cout<<"----v1 and v2-----\n";
		// print_vertex(v1);
		// print_vertex(v2);
		// cout<<"-----\n";
		cur_pol = {v1,v2};
		vertex* candidate = v2->inc_edge->dest;

		double xmin = min(v1->x,v2->x),xmax = max(v1->x,v2->x), ymin = min(v1->y,v2->y), ymax = max(v1->y,v2->y);

		while(!check_reflex(cur_pol[cur_pol.size()-2],cur_pol[cur_pol.size()-1],candidate) && !check_reflex(cur_pol[cur_pol.size()-1],candidate,v1) && !check_reflex(candidate,v1,v2) && cur_pol.size()<n){
			cur_pol.push_back(candidate);
			xmin = min(xmin, candidate->x); 
			xmax = max(xmax, candidate->x);
			ymin = min(ymin, candidate->y); 
			ymax = max(ymax, candidate->y);
			// cout<<"---------CANDIDATE----------\n";
			// cout<<candidate->x<<" "<<candidate->y<<"\n";
			// notches.erase(candidate);
			candidate = candidate->inc_edge->dest;
		}

		// cout<<cur_pol.size()<<"\n";

		// cout<<"-----BOUNDING RECT------\n";
		// printf("{%d,%d} {%d,%d}\n",xmin,ymin,xmax,ymax);
		// cout<<"----------\n";
		if(cur_pol.size()==n){
			faces.insert(v1->inc_edge->left);
			faces.insert(v1->inc_edge->twin->left);
			break;
		}
		deque<vertex*> LPVS;
		// for(auto notch: notches) LPVS.push_back(notch);
		// // cout<<LPVS.size()<<"huh\n";
		// cout<<"--------NOTCH-------"<<endl;
		// for(auto &x: notches) cout<<x->x<<" "<<x->y<<endl;

		deque<vertex*> temp = obtain_notches(v1);

		for(auto x: temp){
			if(find(cur_pol.begin(),cur_pol.end(),x)==cur_pol.end()) LPVS.push_back(x);
		}


		while(!LPVS.empty()){
			// cout<<"--------LPVS-------"<<endl;
			// for(auto &x: LPVS) cout<<x->x<<" "<<x->y<<endl;
			bool backward = false;
			// cout<<endl;


			while(!backward && !LPVS.empty()){
				vertex* notch = LPVS.front();
				do{
					notch = LPVS.front();
					//print_vertex(notch);
					if(!(notch->x <= xmax && notch->x >= xmin && notch->y <= ymax && notch->y >= ymin)){
						//cout<<notch->x<<" "<<notch->y<<" "<<" is not in the rectangle!!!"<<endl;
						LPVS.pop_front();
					}
				}while(!(notch->x <= xmax && notch->x >= xmin && notch->y <= ymax && notch->y >= ymin) && !LPVS.empty());

				if(!LPVS.empty()){
				
					if(check_in_pol(cur_pol,notch)){
						//cout<<notch->x<<" "<<notch->y<<" "<<" is in the polygon!!!"<<endl;

						set<vertex*> VTR;
						bool side = check_reflex(cur_pol.back(),notch,v1) || check_collinear(cur_pol.back(),notch,v1);
						VTR.insert(cur_pol.back());
						for(auto v: cur_pol){
							if((check_reflex(v,notch,v1)==side || check_collinear(v,notch,v1)) && v!=v1){
								VTR.insert(v);
								//cout<<"in VTR "<<endl;
							}
							//print_vertex(v);
						}

						// cout<<"----VTR----"<<endl;
						// for(auto v: VTR) print_vertex(v);
						// cout<<"-----"<<endl;
						vector<vertex*> temp;
						for(auto v: cur_pol){
							if(!VTR.count(v)){
								temp.push_back(v);
							}
						}
						cur_pol = temp;
						backward = true;
						// bool side = check_reflex(cur_pol.back(),notch,v1);
						// while(cur_pol.size()>2 && (check_reflex(cur_pol.back(),notch,v1)==side || check_collinear(cur_pol.back(),notch,v1))){
						// 	cur_pol.pop_back();
						// }
					}
					deque<vertex*> temp;
					for(auto v: LPVS) if(v!=notch) temp.push_back(v);
					LPVS = temp;
				}

			}
			
			

		}
		//cout<<"SIZEEEEEE: " << cur_pol.size()<<"-" << endl;
		if(cur_pol.back()!=v2){
			//cout<<"----ADDING EDGE-----\n";
			// print_vertex(v1);
			// print_vertex(v2);
			// print_vertex(cur_pol.back());
			edge::add_edge(cur_pol.back(),v1);

			diagonals.push_back(v1->inc_edge->twin);

			v1->inc_edge->left->traverse_face();
			v1->inc_edge->twin->left->traverse_face();
			faces.insert(v1->inc_edge->left);
			faces.insert(v1->inc_edge->twin->left);


			n = n - cur_pol.size() + 2;
			//cout << n << "\n";
			// cout<<"here\n";
		}

		prev_pol = cur_pol;

	}
	//cout << "\n\n\n\n";
	for(auto f: faces) { //we n
		//cout<<f<<"*************\n";
		f->traverse_face();
	}

	visualize(faces,"output.txt");
	cout<<"[~]MERGING...";
	//MERGING!!!!!!!


	for(auto d: diagonals){

		//check if the diagonal is inessential

		vertex* v0 = d->twin->prev->org;
		vertex* v1 = d->dest;
		vertex* v2 = d->next->dest;

		if(check_reflex(v0,v1,v2)){
			continue;
		}

		v0 = d->prev->org;
		v1 = d->twin->dest;
		v2 = d->twin->next->dest;

		if(check_reflex(v0,v1,v2)){
			continue;
		}

		face* deleted_face = edge::remove_edge(d);
		faces.erase(deleted_face);
		delete deleted_face;
	}

	
	visualize(faces,"merged.txt");


	cout<<"[~]Exiting...";
}