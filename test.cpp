#include<bits/stdc++.h>
#include "dcl.h"
using namespace std;

int main(){
    dcel::vertex* v = dcel::build("input.txt");
    cout<<v->x<<" "<<v->y;

    dcel::edge* e0 = v->inc_edge;

    dcel::edge* e = e0;

    do{
        cout<<"here\n";
        cout<<(e->org)->x <<" "<<(e->org)->y<<"\n";
        e = e->next;
    }while(e!=e0);
    cout<<(e->org)->x <<" "<<(e->org)->y<<"\n";
    cout<<"end";
    return 0;
}