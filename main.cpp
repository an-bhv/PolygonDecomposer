/*
*	Anubhav Sharma (2020A7PS1892H)
*	Sreeram Yerasani (2020A7PS0052H)
*	Varun Vaddiraju (2020A7PS0173H)
*	Rohith Paul (2020A7PS2044H)
* 
* main_CPP_FILE
-------------------------------------------------------*/
#include <bits/stdc++.h>
#include "dcel.h"

using namespace std;
using dcel::edge;
using dcel::face;
using dcel::vertex;

/** 
 * @brief Build function:
 * Takes an input of points and returns the starting vertex of the built DCEL structured
 * polygon made from the given points.
 * 
 * @param inp 	the vector of cyclic list of points read from input.
 * @param n		total number of points in the cyclic list.
 * @retval vertex*	the starting vertex of the DCEL polygon.
*/
vertex *build(vector<pair<double, double>> &inp, int n)
{
	vertex *prev = new vertex(inp[0].first, inp[0].second);
	vertex *v0 = prev;
	prev = new vertex(inp[1].first, inp[1].second);

	edge *prevedge = edge::create_edge(v0, prev);
	edge *e0 = prevedge;
	v0->inc_edge = e0;
	for (int i = 2; i < n; i++)
	{
		vertex *v = new vertex(inp[i].first, inp[i].second);
		edge *e = edge::create_edge(prev, v);

		edge::link_edge(prevedge, e);
		edge::link_edge(e->twin, prevedge->twin);
		prev->inc_edge = e;
		prev = v;
		prevedge = e;
	}

	edge *e = edge::create_edge(prev, v0);
	edge::link_edge(prevedge, e);
	edge::link_edge(e->twin, prevedge->twin);
	edge::link_edge(e, e0);
	edge::link_edge(e0->twin, e->twin);

	prev->inc_edge = e;
	face *f1 = new face(e0);
	face *f2 = new face(e0->twin);

	return v0;
}

/** 
 * @brief Check reflex function:
 * Function to calculate if three vertices form a reflex angle at the second vertex in
 * the counterclockwise order of angle measurement.
 * 
 * @param v0 	first vertex in cyclic order.
 * @param v1	second vertex in cyclic order.
 * @param v2	third vertex in cyclic order.
 * @retval bool	returns true if the vertices form a reflex angle at v1.
*/
bool check_reflex(vertex *v0, vertex *v1, vertex *v2)
{
	return (((v2->y - v0->y) * (v1->x - v0->x) - (v1->y - v0->y) * (v2->x - v0->x)) > 0.0);
}

/** 
 * @brief Check	collinear function:
 * Function to calculate if three vertices are collinear with respect to each other.
 * 
 * @param v0 	first vertex in cyclic order.
 * @param v1	second vertex in cyclic order.
 * @param v2	third vertex in cyclic order.
 * @retval bool	returns true if the vertices are collinear.
*/
bool check_collinear(vertex *v0, vertex *v1, vertex *v2)
{
	return (((v2->y - v0->y) * (v1->x - v0->x) - (v1->y - v0->y) * (v2->x - v0->x)) == 0.0);
}

/** 
 * @brief Obtain notches function:
 * Function to retrieve all the notches given a starting point of a polygon in cyclic order.
 * 
 * @param v 	first vertex of the polygon sin cyclic order.
 * @retval deque<vertex *>	returns a dequeue of all the notches in a given polygon.
*/
deque<vertex *> obtain_notches(vertex *v)
{
	edge *e0 = v->inc_edge;
	edge *prev_edge = e0;
	edge *e = v->inc_edge->next;
	deque<vertex *> notches;

	while (true)
	{
		if (check_reflex(prev_edge->org, e->org, e->dest))
		{
			notches.push_back(e->org);
		}
		prev_edge = e;
		e = e->next;
		if (e == e0)
			break;
	}

	return notches;
}

/** 
 * @brief Check in pol function:
 * A check function which checks if a given point is within a given polygon in form
 * of a list of vertices.
 * 
 * @param cur_pol	first vertex of the polygon sin cyclic order.
 * @param point		a vertex object to check if it's within the polygon.
 * @retval deque<vertex *>	returns a dequeue of all the notches in a given polygon.
*/
bool check_in_pol(vector<vertex *> &cur_pol, vertex *point)
{
	int num_intersect = 0;
	double ymin, ymax;
	vertex *a;
	vertex *b;
	for (int i = 0; i < cur_pol.size(); i++)
	{
		a = cur_pol[i];
		b = cur_pol[(i + 1) % cur_pol.size()];
		if (a->y > b->y)
		{
			swap(a, b);
		}
		if (a->y <= point->y && b->y > point->y && !check_reflex(a, b, point))
		{
			num_intersect++;
		}
		if (a->y <= point->y && b->y >= point->y && check_collinear(a, b, point))
		{
			return true;
		}
	}
	return num_intersect % 2 == 1;
}

/** 
 * @brief Visualize function:
 * A helper function to write all the face data into a text file which can be read to
 * visualize a given polygon decomposition or any set of faces.
 * 
 * @param faces		a set of all the faces to be visualized.
 * @param name		a path parameter to which the data is written.
 * @return void
*/
void visualize(set<face *> faces, string name)
{
	ofstream out;
	out.open(name);

	for (auto face : faces)
	{
		edge *e = face->inc_edge;

		out << e->org->x << "," << e->org->y << "\n";
		e = e->next;
		while (e != face->inc_edge)
		{
			out << e->org->x << "," << e->org->y << "\n";
			e = e->next;
		}
		out << "\n";
	}
	out.close();
}

/** 
 * @brief Main function:
 * Main function which reads input polygon, decomposes the polygon and merges the decomposed
 * polygon in the end.
 * 
 * @retval int returns 0 on exit.
*/
int main()
{
	/**
	 *< First takes input of points in either clockwise or anti-clockwise
	 * order and builds a DCEL structure using the build function.
	 */
	freopen("input.txt", "r", stdin);
	int n;
	std::cin >> n;
	int flip;
	cin >> flip;
	std::vector<pair<double, double>> vertices(n);
	for (int i = 0; i < n; i++)
	{
		cin >> vertices[i].first >> vertices[i].second;
	}

	/**
	 *< Uses a flag called 'flip' to check the order in the input and changes the order of the vertices accordingly
	 * before building the DCEL.
	 */
	if (flip)
		reverse(vertices.begin()+1, vertices.end());

	vertex *v0 = build(vertices, n);
	std::vector<vertex *> prev_pol, cur_pol;
	prev_pol.push_back(v0);

	set<face *> faces;
	faces.insert(v0->inc_edge->left);
	visualize(faces, "in.txt");
	int i = 0;

	vector<edge *> diagonals;

	/**
	 *< Begins MP1 algo described in the given paper and continues until the number of vertices remaining is
	 * less than or equal to 3.
	 */
	while (n > 3)
	{
		i++;
		vertex *v1 = prev_pol.back();
		vertex *v2 = v1->inc_edge->dest;

		cur_pol = {v1, v2};
		vertex *candidate = v2->inc_edge->dest;

		double xmin = min(v1->x, v2->x),
			   xmax = max(v1->x, v2->x),
			   ymin = min(v1->y, v2->y),
			   ymax = max(v1->y, v2->y);

		/**
		 *< Checks for sufficient condition to move the current vertex pointer front for the given
		 * algorithm and continues after failing a set conditions.
		 */
		while (!check_reflex(cur_pol[cur_pol.size() - 2], cur_pol[cur_pol.size() - 1], candidate) 
			&& !check_reflex(cur_pol[cur_pol.size() - 1], candidate, v1) 
			&& !check_reflex(candidate, v1, v2) 
			&& cur_pol.size() < n)
		{
			cur_pol.push_back(candidate);
			xmin = min(xmin, candidate->x);
			xmax = max(xmax, candidate->x);
			ymin = min(ymin, candidate->y);
			ymax = max(ymax, candidate->y);

			candidate = candidate->inc_edge->dest;
		}

		/**
		 *< End case I for ending the MP1 algorithm, i.e, when our check case of current polygon size is
		 * equal to the total number of vertices left to decompose.
		 */
		if (cur_pol.size() == n)
		{
			faces.insert(v1->inc_edge->left);
			faces.insert(v1->inc_edge->twin->left);
			break;
		}

		deque<vertex *> LPVS;
		deque<vertex *> temp = obtain_notches(v1);

		/**
		 *< Iterates through a list of notches and removes any vertices in the current polygon
		 */
		for (auto x : temp)
		{
			if (find(cur_pol.begin(), cur_pol.end(), x) == cur_pol.end())
				LPVS.push_back(x);
		}

		/**
		 *< Sub-routine to check till all the notches in LPVS set are handled
		 * to check if they lie inside the polygon generated by current polygon.
		 * 
		 *< If they are, then the current polygon is reduced till they are not inside and then
		 * the current polygon is decomposed. 
		 */
		while (!LPVS.empty())
		{
			bool backward = false;
			while (!backward && !LPVS.empty())
			{
				vertex *notch = LPVS.front();
				do
				{
					notch = LPVS.front();
					if (!(notch->x <= xmax && notch->x >= xmin && notch->y <= ymax && notch->y >= ymin))
					{
						LPVS.pop_front();
					}
				} while (!(notch->x <= xmax && notch->x >= xmin && notch->y <= ymax && notch->y >= ymin) && !LPVS.empty());

				if (!LPVS.empty())
				{
					if (check_in_pol(cur_pol, notch))
					{
						set<vertex *> VTR;
						bool side = check_reflex(cur_pol.back(), notch, v1) || check_collinear(cur_pol.back(), notch, v1);
						VTR.insert(cur_pol.back());
						for (auto v : cur_pol)
						{
							if ((check_reflex(v, notch, v1) == side || check_collinear(v, notch, v1)) && v != v1)
							{
								VTR.insert(v);
							}
						}

						vector<vertex *> temp;
						for (auto v : cur_pol)
						{
							if (!VTR.count(v))
							{
								temp.push_back(v);
							}
						}
						cur_pol = temp;
						backward = true;
					}
					deque<vertex *> temp;
					for (auto v : LPVS)
						if (v != notch)
							temp.push_back(v);
					LPVS = temp;
				}
			}
		}

		/**
		 *< If the size of the current set of vertices is greater than 2 then we decompose
		 * the set to a convex polygon and continue.
		 */
		if (cur_pol.back() != v2)
		{
			edge::add_edge(cur_pol.back(), v1);

			diagonals.push_back(v1->inc_edge->twin);

			v1->inc_edge->left->traverse_face();
			v1->inc_edge->twin->left->traverse_face();
			faces.insert(v1->inc_edge->left);
			faces.insert(v1->inc_edge->twin->left);

			n = n - cur_pol.size() + 2;
		}

		/**
		 *< Set the previours set of vertices to the current set and continue iterations till
		 * final decomposition is done.
		 */
		prev_pol = cur_pol;
	}

	/**
	 *< Writes face data after intitial decomposition into an "output.txt" file
	 * for later visualization.
	 */
	visualize(faces, "output.txt");

	/**
	 *< Sub-routine for implemention the merging process described in the given paper. 
	 */
	for (auto d : diagonals)
	{
		vertex *v0 = d->twin->prev->org;
		vertex *v1 = d->dest;
		vertex *v2 = d->next->dest;

		if (check_reflex(v0, v1, v2))
		{
			continue;
		}

		v0 = d->prev->org;
		v1 = d->twin->dest;
		v2 = d->twin->next->dest;

		if (check_reflex(v0, v1, v2))
		{
			continue;
		}

		/**
		 *< Calls function to delete a non-essential diagnol 
		 * as a part of the merging process.
		 */
		face *deleted_face = edge::remove_edge(d);
		faces.erase(deleted_face);
		delete deleted_face;
	}

	/**
	 *< Writes face data after merging process into an "output.txt" file 
	 * for later visualization.
	 */
	visualize(faces, "merged.txt");

	return 0;
}