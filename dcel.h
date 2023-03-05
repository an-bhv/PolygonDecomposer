#pragma once
#include<bits/stdc++.h>
using namespace std;

namespace dcel{

    template<typename _T> class vertex;
    template<typename _T> class edge;
    template<typename _T> class face;

    template<typename _T> class vertex
    {
    private:
    public:
        _T x;
        _T y;
        std::vector<edge<_T>*> inc_edge;

        vertex(_T x, _T y)
        {
            this->x = x;
            this->y = y;
        }

        vertex* next(){
            return inc_edge[0]->dest;
        }

    };

    class edge
    {
    private:
    public:
        vertex<_T> *org, *dest;
        edge<_T> *twin, *next, *prev;
        face<_T> *left;//missing


        static edge<_T>* link(vertex<_T> *u, vertex<_T> *v)
        {
            edge<_T> *e1 = new edge(u, v);
            edge<_T> *e2 = new edge(v, u);

            e1->twin = e2;
            e2->twin = e1;

            return e1;
        }
        
        edge(vertex<_T> *u, vertex<_T> *v)
        {
            org = u;
            dest = v;
        }
    };

    template<typename _T> class face
    {
    private:
    public:
        edge<_T> *inc_edge;
        
        face(edge<_T>* e)
        {
            inc_edge = e;
        }
    };


    //reads polygon file and build dcel, return pointer to first vertex
    template <typename _T>
    vertex<_T>* build(const char* path){
        freopen(path,"r", stdin);
        int n;std::cin>>n; //number of points

        _T x,y;std::cin>>x>>y;
        vertex<_T>* prev = new vertex(x,y);
        vertex<_T>* v0 = prev;

        for(int i=1;i<n;i++){
            cin>>x>>y;
            vertex<_T>* v = new vertex(x,y);
            edge<_T>* e = edge<_T>::link(prev,v); 
            prev->inc_edge.push_back(e); 
            prev = v;
        }
        edge<_T>* e = edge<_T>::link(prev,v0);
        prev->inc_edge.push_back(e);

        return v0;
    }
}