#include <bits/stdc++.h>

using namespace std;

class vertex;
class edge;
class face;

class vertex
{
    public:
    int id;

    vertex(int i)
    {
        id = i;
    }
};

class edge
{
    public:
    vertex *org, *dest;
    edge *twin, *next, *prev;
    face *left;

    static edge* link(vertex *u, vertex *v)
    {
        edge *e1 = new edge(u, v);
        edge *e2 = new edge(v, u);

        e1->twin = e2;
        e2->twin = e1;

        return e1;
    }

    private:
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

    face(edge* e)
    {
        inc_edge = e;
    }
};

int main()
{
    ;
}