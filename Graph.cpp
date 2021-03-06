#include "Graph.h"
#include "DSU.h"
#include <iostream>
#include <fstream>
#include <sstream>

#define GRAPH_AdjMatrix 'C'
#define GRAPH_AdjList 'L'
#define GRAPH_ListOfEdges 'E'

using namespace std;

Graph::Graph() 
{
	graph_form = 0;
	n = m = d = w = 0;
}

Graph::Graph(int num, char gform)
{
	graph_form = gform;
	n = num;
	m = 0;
	d = 0;
	w = 1;

	switch (graph_form){
	case GRAPH_AdjMatrix:
	{
				graph_m.resize(n);
				for (int i = 0; i < n; i++)
				{
					for (int j = 0; j < n; j++)
					{
						graph_m[i].push_back(0);
					}
				}
				break;
	}
	case GRAPH_AdjList:
	{
				graph_lw.resize(n);
				break;
	}
	case GRAPH_ListOfEdges:
	{
				break;
	}
	}
}

Graph::~Graph() {}

void Graph::readGraph(string fileName)
{
	ifstream f_input;
	f_input.open(fileName);

	f_input >> graph_form;

	switch (graph_form)
	{
		case GRAPH_AdjMatrix:
		{
					f_input >> n >> d >> w; 

					int t;
					for (int i = 0; i < n; i++)
					{
						graph_m.resize(n);
						for (int j = 0; j < n; j++)
						{
							f_input >> t;
							graph_m[i].push_back(t);
							if (graph_m[i][j])
								m++;
						}
					}
					m /= 2;
					break;
		}

		case GRAPH_AdjList:
		{
					f_input >> n >> d >> w;

					string f_line;
					getline(f_input, f_line);

					if (w)
					{
						graph_lw.resize(n);

						for (int i = 0; i < n; i++)
						{
							getline(f_input, f_line);
							istringstream iss(f_line);
							int vertex, weight;

							while (iss >> vertex) {
								iss >> weight;
								graph_lw[i].push_back(make_pair(vertex, weight));
								m++;
							};
						};
					}
					else
					{
						graph_l.resize(n);

						for (int i = 0; i < n; i++)
						{
							getline(f_input, f_line);
							istringstream iss(f_line);
							int vertex, weight;

							while (iss >> vertex)
							{
								graph_l[i].push_back(vertex);
								m++;
							}
						}
					}
					break;
		}
		case GRAPH_ListOfEdges:
		{
					f_input >> n >> m >> d >> w;

					int v1, v2;

					if (w)
					{
						int weight;
						
						for (int i = 0; i < m; i++)
						{
							f_input >> v1 >> v2 >> weight;
							graph_ew.push_back(make_tuple(v1, v2, weight));
						}
					}
					else
					{
						for (int i = 0; i < m; i++)
						{
							f_input >> v1 >> v2;
							graph_e.push_back(make_pair(v1, v2));
						}
					}
					break;

		}
	}
	f_input.close();
}

void Graph::addEdge(int from, int to, int weight)
{

	if (!w)
	{
		weight = 1;
	}
	
	switch (graph_form)
	{
		case GRAPH_AdjMatrix:
		{
				   --from;
				   --to;
				   graph_m[from][to] = weight;
				   if (!d)
				   {
					   graph_m[to][from] = weight;
				   };
				   break;
		}
		
		case GRAPH_AdjList:
		{
				   if (w)
				   {
					   graph_lw[from - 1].push_back(make_pair(to, weight));
					   /*if (!d)
					   {
						   graph_lw[to - 1].push_back(make_pair(from, weight));
					   }*/
				   }
				   else
				   {
					   graph_l[from - 1].push_back(to);
					   /*if (!d)
					   {
						   graph_l[to - 1].push_back(from);
					   }*/
				   }
				   break;
		}

		case GRAPH_ListOfEdges:
		{
				   if (w)
				   {
					   graph_ew.push_back(make_tuple(from, to, weight));
					   /*if (!d)
					   {
						   graph_ew.push_back(make_tuple(to, from, weight));
					   }*/
				   }
				   else
				   {
					   graph_e.push_back(make_pair(from, to));
					   /*if (!d)
					   {
						   graph_e.push_back(make_pair(to, from));
					   }*/
				   }

				   m++;
				   break;
		}
	}
}

void Graph::removeEdge(int from, int to)
{
	switch (graph_form)
	{
		case GRAPH_AdjMatrix:
		{
					--from;
					--to;
					
					graph_m[from][to] = 0;
					if (!d)
					{
						graph_m[to][from] = 0;
					}
					break;
		}

		case GRAPH_AdjList:
		{
				   if (w)
				   {
					   int i = 0;
					   while ( i < graph_lw[from - 1].size())
					   {
						   if (graph_lw[from - 1][i].first == to)
						   {
							   graph_lw[from - 1][i].first = 0;
							   graph_lw[from - 1][i].second = 0;
						   }
						   i++;
					   }
					   if (!d)
					   {
						   int i = 0;
						   while (i < graph_lw[to - 1].size())
						   {
							   if (graph_lw[to - 1][i].first == from)
							   {
								   graph_lw[to - 1][i].first = 0;
								   graph_lw[to - 1][i].second = 0;
							   }
							   i++;
						   }
					   }
				   }
				   else
				   {
					   int i = 0;
					   while (i < graph_l[from].size())
					   {
						   if (graph_l[from][i] == to)
						   {
							   graph_l[from][i] = 0;
							   graph_l[from][i] = 0;
						   }
						   i++;
					   }
					   if (!d)
					   {
						   int i = 0;
						   while (i < graph_l[to].size())
						   {
							   if (graph_l[to][i] == from)
							   {
								   graph_l[to][i] = 0;
								   graph_l[to][i] = 0;
							   }
							   i++;
						   }
					   }
				   }
				   break;
		}

		case GRAPH_ListOfEdges:
		{
					if (w)
					{
						int i = 0;
						while (i < graph_ew.size())
						{
							if (get<0>(graph_ew[i]) == from && get<1>(graph_ew[i]) == to)
							{
								get<0>(graph_ew[i]) = 0;
								get<1>(graph_ew[i]) = 0;
								get<2>(graph_ew[i]) = 0;

							}

							i++;
						}
						if (!d)
						{
							while (i < graph_ew.size())
							{
								if (get<0>(graph_ew[i]) == to && get<1>(graph_ew[i]) == from)
								{
									get<0>(graph_ew[i]) = 0;
									get<1>(graph_ew[i]) = 0;
									get<2>(graph_ew[i]) = 0;

								}

								i++;
							}
						}
					}
					else
					{
						int i = 0;
						while (i < graph_e.size())
						{
							if (graph_e[i].first == from && graph_e[i].second == to)
							{
								graph_e[i].second = 0;
								graph_e[i].first = 0;

							}
							i++;
						}
						/*if (!d)
						{
							while (i < graph_e.size())
							{
								if (graph_e[i].first == to && graph_e[i].second == from)
								{
									graph_e[i].second = 0;
									graph_e[i].first = 0;

								}
								i++;
							}
						}*/
					}
					break;
		}
	}
}

int Graph::changeEdge(int from, int to, int newWeight)
{
	switch (graph_form)
	{
		case GRAPH_AdjMatrix:
		{
				   --from;
				   --to;
				   
				   int oldWeight = 0;
				   
				   if (w){
					   oldWeight = graph_m[from][to];
					   graph_m[from][to] = newWeight;
					   if (!d)
					   {
						   graph_m[to][from] = newWeight;
					   }
				   }
				  
				   return oldWeight;
		}

		case GRAPH_AdjList:
		{
				   int oldWeight;

				   if (w)
				   {
					   for (int i = 0; i < graph_lw[from - 1].size(); i++)
					   {
						   if (graph_lw[from - 1][i].first == to)
						   {
							   oldWeight = graph_lw[from - 1][i].second;

							   graph_lw[from - 1][i].second = newWeight;
						   }
					   }
					   if (!d)
					   {
						   for (int i = 0; i < graph_lw[to - 1].size(); i++)
						   {
							   if (graph_lw[to - 1][i].first == to)
							   {

								   graph_lw[to - 1][i].second = newWeight;
							   }
						   }
					   }
				   }
				   return oldWeight;
		}

		case GRAPH_ListOfEdges:
		{
				   int oldWeight;
				   if (w)
				   {
					   for (int i = 0; i < graph_ew.size(); i++)
					   {
						   if (get<0>(graph_ew[i]) == from && get<1>(graph_ew[i]) == to)
						   {
							   oldWeight = get<2>(graph_ew[i]);

							   get<2>(graph_ew[i]) = newWeight;
						   }
					   }
					   if (!d)
					   {
						   for (int i = 0; i < graph_ew.size(); i++)
						   {
							   if (get<0>(graph_ew[i]) == to && get<1>(graph_ew[i]) == from)
							   {

								   get<2>(graph_ew[i]) = newWeight;
							   }
						   }
					   }
					   return oldWeight;
				   }
		}
	}
}

void Graph::transformToAdjMatrix()
{
	if (graph_form == 'C') return;
	
	graph_m.clear();

	graph_m.resize(n);
	for (int i = 0; i < n; i++)
	{
		graph_m[i].resize(n);
		for (int j = 0; j < n; j++)
		{
			graph_m[i][j] = 0;
		}
	}
	
	switch (graph_form)
	{
		case GRAPH_AdjList:
		{
				   if (w)
				   {
					   for (int i = 0; i < graph_lw.size(); i++)
					   {
						   for (int j = 0; j < graph_lw[i].size(); j++)
						   {
							   if (graph_lw[i][j].first != 0)
							   {
								   graph_m[i][graph_lw[i][j].first - 1] = graph_lw[i][j].second;
								   if (!d)
								   {
									   graph_m[graph_lw[i][j].first - 1][i] = graph_lw[i][j].second;
								   }
							   }
						   }
					   }
				   }
				   else
				   {
					   for (int i = 0; i < graph_l.size(); i++)
					   {
						   for (int j = 0; j < graph_l[i].size(); j++)
						   {
							   if (graph_l[i][j] != 0)
							   {
								   graph_m[i][graph_l[i][j] - 1] = 1;
								   if (!d)
								   {
									   graph_m[graph_l[i][j] - 1][i] = 1;
								   }
							   }
						   }
					   }
				   }
				   break;
		}
		
		case GRAPH_ListOfEdges:
		{
				   if (w)
				   {
					   for (int i = 0; i < graph_ew.size(); i++)
					   {
						   if (get<0>(graph_ew[i]) != 0)
						   {
							   graph_m[get<0>(graph_ew[i]) - 1][get<1>(graph_ew[i]) - 1] = get<2>(graph_ew[i]);
							   if (!d)
							   {
								   graph_m[get<1>(graph_ew[i]) - 1][get<0>(graph_ew[i]) - 1] = get<2>(graph_ew[i]);
							   }
						   }
					   }
					}
				   else
				   {
					   for (int i = 0; i < graph_e.size(); i++)
					   {
						   if (graph_e[i].first != 0)
						   {
							   graph_m[graph_e[i].first - 1][graph_e[i].second - 1] = 1;
							   if (!d)
							   {
								   graph_m[graph_e[i].second - 1][graph_e[i].first - 1] = 1;
							   }
						   }
					   }
				   }
				   break;
		}
	}

	graph_form = GRAPH_AdjMatrix;
}

void Graph::transformToAdjList()
{
	if (graph_form == GRAPH_AdjList) return;

	if (w)
	{
		graph_lw.clear();
		graph_lw.resize(n);
	}
	else
	{
		graph_l.clear();
		graph_l.resize(n);
	}

	switch (graph_form)
	{
		case GRAPH_AdjMatrix:
		{
					if (w)
					{
						for (int i = 0; i < graph_m.size(); i++)
						{
							for (int j = 0; j < graph_m[i].size(); j++)
							{
								if (graph_m[i][j])
								{
									graph_lw[i].push_back(make_pair(j + 1, graph_m[i][j]));
								}
							}
						}
					}
					else
					{
						for (int i = 0; i < graph_m.size(); i++)
						{
							for (int j = 0; j < graph_m[i].size(); j++)
							{
								if (graph_m[i][j])
								{
									graph_l[i].push_back(j + 1);
								}
							}
						}
					}
					break;
		}
		case GRAPH_ListOfEdges:
		{
				   if (w)
				   {
					   graph_lw.resize(n);
					   for (int i = 0; i < graph_ew.size(); i++) {
						   bool next = false;
						   for (int j = 0; j < graph_lw[get<0>(graph_ew[i]) - 1].size(); j++) {
							   if (graph_lw[get<0>(graph_ew[i]) - 1][j].first == get<1>(graph_ew[i])) {
								   next = true;
								   break;
							   }
						   }
						   if (next)
							   continue;

						   graph_lw[get<0>(graph_ew[i]) - 1].push_back(make_pair(get<1>(graph_ew[i]), get<2>(graph_ew[i])));
						   if (!d) {
							   graph_lw[get<1>(graph_ew[i]) - 1].push_back(make_pair(get<0>(graph_ew[i]), get<2>(graph_ew[i])));
						   }
					   }
				   }
				   else
				   {
					   graph_l.resize(n);
					   for (int i = 0; i < graph_e.size(); i++) {
						   bool next = false;
						   for (int j = 0; j < graph_l[graph_e[i].first - 1].size(); j++) {
							   if (graph_l[graph_e[i].first - 1][j] == graph_e[i].second) {
								   next = true;
								   break;
							   }
						   }
						   if (next)
							   continue;

						   graph_l[graph_e[i].first - 1].push_back(graph_e[i].second);
						   if (!d) {
							   graph_l[graph_e[i].second - 1].push_back(graph_e[i].first);
						   }
					   }
				   }
				   break;
		}

	}
	graph_form = GRAPH_AdjList;

}

void Graph::transformToListOfEdges()
{
	if (graph_form == GRAPH_ListOfEdges) return;

	char old = graph_form;
	graph_ew.clear();
	graph_e.clear();
	graph_form = GRAPH_ListOfEdges;

	m = 0;

	switch (old)
	{
		case GRAPH_AdjMatrix:
		{
				   if (w)
				   {
					   for (int i = 0; i < graph_m.size(); i++)
					   {
						   for (int j = 0; j < graph_m[i].size(); j++)
						   {
							   if (graph_m[i][j])
							   {
								   addEdge(i + 1, j + 1, graph_m[i][j]);
							   }
						   }
					   }
				   }
				   else
				   {
					   for (int i = 0; i < graph_m.size(); i++)
					   {
						   for (int j = 0; j < graph_m[i].size(); j++)
						   {
							   if (graph_m[i][j])
							   {
								   graph_e.push_back(make_pair(i + 1, j + 1));
								   m++;
							   }
						   }
					   }
				   }
				   break;
		}

		case GRAPH_AdjList:
		{
				   if (w) {
					   for (int i = 0; i < graph_lw.size(); i++) {
						   for (int j = 0; j < graph_lw[i].size(); j++) {
							   graph_ew.push_back(make_tuple(i + 1, graph_lw[i][j].first, graph_lw[i][j].second));
							   m++;
						   }
					   }
				   }
				   else {
					   for (int i = 0; i < graph_l.size(); i++) {
						   for (int j = 0; j < graph_l[i].size(); j++) {
							   graph_e.push_back(make_pair(i + 1, graph_l[i][j]));
							   m++;
						   }
					   }
				   }
				   break;
		}
	}
}

void Graph::writeGraph(const string file_name)
{
	ofstream f_output;
	f_output.open(file_name);

	f_output << graph_form;
	
	switch(graph_form)
	{
		case GRAPH_AdjMatrix:
		{
				   f_output << " " << n << endl;
				   f_output << d << " " << w << endl;

				   for (int i = 0; i < graph_m.size(); i++)
				   {
					   for (int j = 0; j < graph_m[i].size(); j++)
					   {
						   f_output << graph_m[i][j] << " ";
					   }
					   f_output << endl;
				   }
				   break;
		}

		case GRAPH_AdjList:
		{
				   f_output << " " << n << endl;
				   f_output << d << " " << w << endl;

				   if (w)
				   {
					   for (int i = 0; i < n; i++)
					   {
						   for (int j = 0; j < graph_lw[i].size(); j++)
						   {
							   f_output << graph_lw[i][j].first << " " << graph_lw[i][j].second << " ";
						   }

						   f_output << endl;
					   }
				   }
				   else
				   {
					   for (int i = 0; i < n; i++)
					   {
						   for (int j = 0; j < graph_l[i].size(); j++)
						   {
							   f_output << graph_l[i][j] << " ";
						   }

						   f_output << endl;
					   }
				   }
				   break;
		}

		case GRAPH_ListOfEdges:
		{
				   f_output << " " << n << " " << m << endl;
				   f_output << d << " " << w << endl;

				   if (w) {
					   for (int i = 0; i < m; i++) {
						   f_output << get<0>(graph_ew[i]) << " " << get<1>(graph_ew[i]) << " " << get<2>(graph_ew[i]) << endl;
					   }
				   }
				   else {
					   for (int i = 0; i < m; i++) {
						   f_output << graph_e[i].first << " " << graph_e[i].second << endl;
					   }
				   }
				   break;
		}
	}
}

int Graph::checkEuler_c(bool &circleExist)
{
	DSU dsu = DSU(n);
	int OddVertex = 0;
	int check = 0;
	int init_vertex;
	for (int i = 0; i < graph_m.size(); i++)
	{
		check = 0;

		for (int j = 0; j < graph_m[i].size(); j++)
		{
			if (graph_m[i][j] > 0)
			{
				++check;
			}
		}
		if (check % 2 == 1)
		{
			++OddVertex;
			init_vertex = i; 
		}
	}
	if ((OddVertex > 2) && (OddVertex == 1))
	{
		return 0;
	}
	else
	{
		if (OddVertex == 2)
		{
			circleExist = false;
		}
	}

	for (int i = 0; i < graph_m.size(); i++)
	{
		for (int j = 0; j < graph_m[i].size(); j++)
		{
			if (graph_m[i][j] > 0)
			{
				if (dsu.find(j) != dsu.find(i))
				{
					dsu.unite(i,j);
				}
			}
		}
	}
	
	for (int i = 1; i < graph_m.size(); i++)
	{
		if (dsu.find(i) != dsu.find(i - 1))
		{
			return 0;
		}
	}

	if (OddVertex == 0)
	{
		circleExist = true;
		init_vertex = 1;
		return init_vertex;
	}
	else
	{
		if (OddVertex == 2)
		{
			return ++init_vertex;
		}
		return 0;
	}
}

int Graph::checkEuler_l(bool &circleExist)
{
	DSU dsu = DSU(n);
	int OddVertex = 0;
	int check = 0;
	int init_vertex;
	if (w)
	{
		for (int i = 0; i < graph_lw.size(); i++)
		{
			if (graph_lw[i].size() % 2 == 1)
			{
				++OddVertex;
				init_vertex = i;
			}
		}
		if ((OddVertex > 2) && (OddVertex == 1))
		{
			return 0;
		}
		else
		{
			if (OddVertex == 2)
			{
				circleExist = false;
			}
		}

		for (int i = 0; i < graph_lw.size(); i++)
		{
			for (int j = 0; j < graph_lw[i].size(); j++)
			{
				if (dsu.find(graph_lw[i][j].first-1) != dsu.find(i))
				{
					dsu.unite(i, j);
				}
			}
		}

		for (int i = 1; i < graph_lw.size(); i++)
		{
			if (dsu.find(i) != dsu.find(i - 1))
			{
				return 0;
			}
		}
	}
	else
	{
		for (int i = 0; i < graph_l.size(); i++)
		{
			if (graph_l[i].size() % 2 == 1)
			{
				++OddVertex;
				init_vertex = i;
			}
		}
		if ((OddVertex > 2) && (OddVertex == 1))
		{
			return 0;
		}
		else
		{
			if (OddVertex == 2)
			{
				circleExist = false;
			}
		}

		for (int i = 0; i < graph_l.size(); i++)
		{
			for (int j = 0; j < graph_l[i].size(); j++)
			{
				if (dsu.find(graph_l[i][j]-1) != dsu.find(i))
				{
					dsu.unite(i, j);
				}
			}
		}

		for (int i = 1; i < graph_l.size(); i++)
		{
			if (dsu.find(i) != dsu.find(i - 1))
			{
				return 0;
			}
		}
	}

	if (OddVertex == 0)
	{
		circleExist = true;
		init_vertex = 1;
		return init_vertex;
	}
	else
	{
		if (OddVertex == 2)
		{
			return ++init_vertex;
		}
		return 0;
	}
}

int Graph::checkEuler(bool &circleExist)
{
	switch (graph_form)
	{
	case GRAPH_AdjMatrix:
	{
			   return checkEuler_c(circleExist);
			   break;
	}
	case GRAPH_AdjList:
	{
			   return checkEuler_l(circleExist);
			   break;
	}
	case GRAPH_ListOfEdges:
	{
			   int k;
			   this->transformToAdjList();
			   k =  checkEuler_l(circleExist);
			   this->transformToListOfEdges();
			   return k;
			   break;
	}
	}
}

bool Graph::bfs(int first_v, int second_v, set <pair<int, int>> visited)
{
	switch (graph_form)
	{
	case GRAPH_AdjMatrix:
	{
			   queue<int> q;
			   q.push(first_v);
			   vector<bool> used(n);
			   //vector<int> d(n), p(n);
			   used[first_v] = true;
			  // p[first_v] = -1;
			   while (!q.empty()) {
				   int v = q.front();
				   q.pop();
				   for (size_t i = 0; i < graph_m[v].size(); ++i) {
					   if (graph_m[v][i] > 0)
					   {
						   bool visited_e = false;
						   if (v < i)
							   visited_e = visited.find(make_pair(v, i)) != visited.end();
						   else
							   visited_e = visited.find(make_pair(i, v)) != visited.end();
						   if (!used[i] && (v != first_v || i != second_v) && !visited_e)
						   {
							   used[i] = true;
							   if (i == second_v) return false;
							   q.push(i);
							   //d[to] = d[v] + 1;
							   //p[to] = v;
						   }
					   }
				   }
			   }
			   return(true);
	}

	case GRAPH_AdjList:
	{
			   queue<int> q;
			   q.push(first_v);
			   vector<bool> used(n);
			   //vector<int> d(n), p(n);
			   used[first_v] = true;
			  // p[first_v] = -1;
			   if (w)
			   {
				   while (!q.empty()) {
					   int v = q.front();
					   q.pop();
					   for (size_t i = 0; i < graph_lw[v].size(); ++i) {
						   int to = graph_lw[v][i].first - 1;
						   bool visited_e = false;
						   if (v < to)
							   visited_e = visited.find(make_pair(v, to)) != visited.end();
						   else
							   visited_e = visited.find(make_pair(to, v)) != visited.end();
						   if (!used[to] && (v != first_v || to != second_v) && !visited_e)
						   {
							   used[to] = true;
							   if (to == second_v) return false;
							   q.push(to);
							   //d[to] = d[v] + 1;
							   //p[to] = v;
						   }
					   }
				   }
			   }
			   else
			   {
				   while (!q.empty()) {
					   int v = q.front();
					   q.pop();
					   for (size_t i = 0; i < graph_l[v].size(); ++i) {
						   int to = graph_l[v][i] - 1;
						   bool visited_e = false;
						   if (v < to)
							   visited_e = visited.find(make_pair(v, to)) != visited.end();
						   else
							   visited_e = visited.find(make_pair(to, v)) != visited.end();
						   if (!used[to] && (v != first_v || to != second_v) && !visited_e)
						   {
							   used[to] = true;
							   if (to == second_v) return false;
							   q.push(to);
							   //d[to] = d[v] + 1;
							   //p[to] = v;
						   }
					   }
				   }
			   }
			   return(true);
	}
	}
}

vector<int> Graph::getEuleranTourFleri()
{
	int init_vertex;
	int k;
	bool circleExist;
	vector<int> res;
	bool tr = false;

	if (graph_form == GRAPH_ListOfEdges)
	{
		tr = true;
		this->transformToAdjList();
	}

	k = checkEuler(circleExist);
	if (circleExist)
	{
		init_vertex = 0;
	}
	else
	{
		if (k != 0)
		{
			init_vertex = k - 1;
		}
		else
		{
			return res;
		}
	}

	
		switch (graph_form)
		{
		case GRAPH_AdjMatrix:
		{
								if (!w)
								{
									set <pair<int, int>> visited;
									int check = 0;
									int v = init_vertex;
									res.push_back(v);
									while (check < m)
									{
										int bridge = -1;
										int old_v = v;
										for (int i = 0; i < graph_l[v].size(); i++)
										{
											int to = graph_l[v][i] - 1;

											bool visited_e = false;
											if (v < to)
												visited_e = visited.find(make_pair(v, to)) != visited.end();
											else
												visited_e = visited.find(make_pair(to, v)) != visited.end();
											if (visited_e)
												continue;
											if (!bfs(v, to, visited))
											{
												res.push_back(to);
												if (v < to)
													visited.insert(make_pair(v, to));
												else
													visited.insert(make_pair(to, v));
												++check;
												v = to;
												old_v = v;
												continue;
											}
											else
											{
												bridge = to;
											}
										}

										if (bridge != -1 && old_v == v)
										{
											res.push_back(bridge);
											if (v < bridge)
												visited.insert(make_pair(v, bridge));
											else
												visited.insert(make_pair(bridge, v));
											++check;
											v = bridge;
										}
									}
									for (int i = 0; i < res.size(); i++)
										cout << res[i] << " ";
									return res;
								}
								else
								{
									set <pair<int, int>> visited;
									int check = 0;
									int v = init_vertex;
									res.push_back(v);
									while (check < m)
									{
										int bridge = -1;
										int old_v = v;
										for (int i = 0; i < graph_l[v].size(); i++)
										{
											int to = graph_l[v][i] - 1;

											bool visited_e = false;
											if (v < to)
												visited_e = visited.find(make_pair(v, to)) != visited.end();
											else
												visited_e = visited.find(make_pair(to, v)) != visited.end();
											if (visited_e)
												continue;
											if (!bfs(v, to, visited))
											{
												res.push_back(to);
												if (v < to)
													visited.insert(make_pair(v, to));
												else
													visited.insert(make_pair(to, v));
												++check;
												v = to;
												continue;
											}
											else
											{
												bridge = to;
											}
										}
										if (bridge != -1 && old_v == v)
										{
											res.push_back(bridge);
											if (v < bridge)
												visited.insert(make_pair(v, bridge));
											else
												visited.insert(make_pair(bridge, v));
											++check;
											v = bridge;
										}
										old_v = v;
									}
									for (int i = 0; i < res.size(); i++)
										cout << res[i] << " ";
									return res;
								}
				   break;
		}
		case GRAPH_AdjList:
		{
							  if (!w)
							  {
								  set <pair<int, int>> visited;
								  int check = 0;
								  int v = init_vertex;
								  res.push_back(v);
								  while (check < m)
								  {
									  int bridge = -1;
									  int old_v = v;
									  for (int i = 0; i < graph_l[v].size(); i++)
									  {
										  int to = graph_l[v][i] - 1;
										  
										  bool visited_e = false;
										  if (v < to)
											  visited_e = visited.find(make_pair(v, to)) != visited.end();
										  else
											  visited_e = visited.find(make_pair(to, v)) != visited.end();
										  if (visited_e)
											  continue;
										  if (!bfs(v, to, visited))
										  {
											  res.push_back(to);
											  if (v < to)
												  visited.insert(make_pair(v, to));
											  else
												  visited.insert(make_pair(to, v));
											  ++check;
											  v = to;
											  continue;
										  }
										  else
										  {
											  bridge = to;
										  }
									  }

									  if (bridge != -1 && old_v == v)
									  {
										  res.push_back(bridge);
										  if (v < bridge)
											  visited.insert(make_pair(v, bridge));
										  else
											  visited.insert(make_pair(bridge, v));
										  ++check;
										  v = bridge;
									  }
									  old_v = v;
								  }
								  for (int i = 0; i < res.size(); i++)
									  cout << res[i] << " ";
								  if (tr)
									  this->transformToListOfEdges();
								  return res;
							  }
							  else
							  {
								  set <pair<int, int>> visited;
								  int check = 0;
								  int v = init_vertex;
								  res.push_back(v);
								  while (check < m)
								  {
									  int bridge = -1;
									  int old_v = v;
									  for (int i = 0; i < graph_lw[v].size(); i++)
									  {
										  int to = graph_lw[v][i].first - 1;

										  bool visited_e = false;
										  if (v < to)
											  visited_e = visited.find(make_pair(v, to)) != visited.end();
										  else
											  visited_e = visited.find(make_pair(to, v)) != visited.end();
										  if (visited_e)
											  continue;
										  if (!bfs(v, to, visited))
										  {
											  res.push_back(to);
											  if (v < to)
												  visited.insert(make_pair(v, to));
											  else
												  visited.insert(make_pair(to, v));
											  ++check;
											  v = to;
											  continue;
										  }
										  else
										  {
											  bridge = to;
										  }
									  }
									  if (bridge != -1 && old_v == v)
									  {
										  res.push_back(bridge);
										  if (v < bridge)
											  visited.insert(make_pair(v, bridge));
										  else
											  visited.insert(make_pair(bridge, v));
										  ++check;
										  v = bridge;
									  }
									  old_v = v;
								  }
								  for (int i = 0; i < res.size(); i++)
									  cout << res[i] << " ";
								  if (tr)
									  this->transformToListOfEdges();
								  return res;
							  }
							  break;
		}
		}
}

vector<int> Graph:: getEuleranTourEffective()
{
	set <pair<int, int>> visited;
	vector<int> res;
	stack<int> q;
	int init_vertex;
	int k;
	bool circleExist;

	bool tr = false;
	if (graph_form == GRAPH_ListOfEdges) 
	{
		this->transformToAdjList();
		tr = true;
	}
	k = checkEuler(circleExist);
	if (circleExist)
	{
		init_vertex = 0;
	}
	else
	{
		if (k != 0)
		{
			init_vertex = k - 1;
		}
		else
		{
			return res;
		}
	}

	q.push(init_vertex - 1);
	while (!q.empty()) 
	{
		int v = q.top();
		if (graph_form == GRAPH_AdjMatrix) 
		{
			for (int i = 0; i < graph_m[v].size(); i++) 
			{
				int to = i;
				if (v == to)
					continue;

				bool visited_e = false;
				if (v < to)
					visited_e = visited.find(make_pair(v, to)) != visited.end();
				else
					visited_e = visited.find(make_pair(to, v)) != visited.end();

				if (graph_m[v][to] && !visited_e) {
					if (v < to)
						visited.insert(make_pair(v, to));
					else
						visited.insert(make_pair(to, v));

					q.push(to);
					break;
				}
			}
		}
		else if (graph_form == GRAPH_AdjList) {
			if (!w) {
				for (int i = 0; i < graph_l[v].size(); i++) {
					int to = graph_l[v][i] - 1;

					bool visited_e = false; 
					if (v < to)
						visited_e = visited.find(make_pair(v, to)) != visited.end();
					else
						visited_e = visited.find(make_pair(to, v)) != visited.end();

					if (!visited_e) {
						if (v < to)
							visited.insert(make_pair(v, to));
						else
							visited.insert(make_pair(to, v));

						q.push(to);
						break;
					}
				}
			}
			else {
				for (int i = 0; i < graph_lw[v].size(); i++) {
					int to = graph_lw[v][i].first - 1;

					bool visited_e = false;
					if (v < to)
						visited_e = visited.find(make_pair(v, to)) != visited.end();
					else
						visited_e = visited.find(make_pair(to, v)) != visited.end();

					if (!visited_e) { 
						if (v < to)
							visited.insert(make_pair(v, to));
						else
							visited.insert(make_pair(to, v));

						q.push(to);
						break;
					}
				}
			}
		}

		if (v == q.top()) 
		{
			q.pop();
			res.push_back(v);
		}
	}

	if (tr) {
		this->transformToListOfEdges();
	}

	return res;
}

Graph Graph::getSpaningTreePrima()
{
	Graph res_graph = Graph(n, graph_form);   
	bool tr = false;

	int max_w = 0;
	switch (graph_form)
	{
	case GRAPH_AdjMatrix:
	{
				for (int i = 0; i < n; i++)
				{
					for (int j = 0; j < n; j++)
					{
						if (graph_m[i][j] > max_w)
						{
							max_w = graph_m[i][j];
						}
					}
				}
				break;
	}
	case GRAPH_AdjList:
	{
				for (int i = 0; i < n; i++)
				{
					for (int j = 0; j < graph_lw[i].size(); j++)
					{
						if (graph_lw[i][j].second > max_w)
						{
							max_w = graph_lw[i][j].second;
						}
					}
				}
				break;
	}
	case GRAPH_ListOfEdges:
	{
				for (int i = 0; i < graph_ew.size(); i++)
				{
					if (get<2>(graph_ew[i]) > max_w)
					{
						max_w = get<2>(graph_ew[i]);
					}
				}
				break;
	}
	}
	vector <bool> visited(n, false);     
	vector <int> min_e(n, ++max_w);    
	vector <int> trans(n, -1);         
	int ResCost = 0;             

	if (graph_form == GRAPH_AdjMatrix)
	{
		min_e[0] = 0;

		for (int i = 0; i < n; i++)
		{
			int v = -1;
			for (int j = 0; j < n; j++)
			{
				if (!visited[j] && (v == -1 || min_e[j] < min_e[v]))
				{
					v = j;
				}
			}

			visited[v] = true;
			for (int to = 0; to < n; to++)
			{
				if (!visited[to] && graph_m[v][to] != 0 && graph_m[v][to] < min_e[to])
				{
					min_e[to] = graph_m[v][to];
					trans[to] = v;
				}
			}
		}

		for (int i = 0; i < n; i++)
		{
			if (trans[i] != -1)
			{
				res_graph.addEdge(trans[i] + 1, i + 1, graph_m[trans[i]][i]);
				ResCost += graph_m[trans[i]][i];
			}
		}
	}
	else if (graph_form == GRAPH_AdjList || graph_form == GRAPH_ListOfEdges) 
	{
		set <pair<int, int> > edges;
		if (graph_form == GRAPH_ListOfEdges)
		{
			tr = true;
			this->transformToAdjList();
		}

		int k = 0;
		while (k < n) 
		{
			min_e[k] = 0;
			edges.insert(make_pair(0, k));

			while (!edges.empty()) 
			{
				int v = edges.begin()->second;
				edges.erase(edges.begin());
				visited[v] = true;

				for (size_t j = 0; j < graph_lw[v].size(); j++) 
				{
					int to = graph_lw[v][j].first - 1;
					int	cost = graph_lw[v][j].second;
					if (!visited[to] && cost < min_e[to]) 
					{
						edges.erase(make_pair(min_e[to], to));
						min_e[to] = cost;
						trans[to] = v;
						edges.insert(make_pair(min_e[to], to));
					}
				}
			}
			while (k < n && visited[k]) 
			{
				k++;
			}
		}

		for (int i = 0; i < n; i++) 
		{
			if (trans[i] != -1) 
			{
				res_graph.addEdge(trans[i] + 1, i + 1, min_e[i]);
				ResCost += min_e[i];
			}
		}
	}

	cout << "Prim: " << ResCost << endl;
	if (tr)
		transformToListOfEdges();
	return res_graph;
}

bool EdgeSort(const tuple<int, int, int>& vertex1, const tuple<int, int, int>& vertex2) 
{
	return get<2>(vertex1) < get<2>(vertex2);
}

Graph Graph::getSpaningTreeKruscal()
{
	char oldform = GRAPH_ListOfEdges;
	if (graph_form != GRAPH_ListOfEdges)
	{
		oldform = graph_form;
		this->transformToListOfEdges();
	}
	Graph res_graph = Graph(n, oldform);
	int res_cost = 0;
	DSU dsu = DSU(n);
	sort(graph_ew.begin(), graph_ew.end(), EdgeSort);

	for (int i = 0; i < m; i++) 
	{
		int vert1 = get<0>(graph_ew[i]);
		int	vert2 = get<1>(graph_ew[i]);
		int	weight = get<2>(graph_ew[i]);

		if (dsu.find(vert1) != dsu.find(vert2)) 
		{
			res_cost += weight;
			dsu.unite(vert1, vert2);
			res_graph.addEdge(vert1, vert2, weight);
		}
	}
	switch (oldform) {
	case GRAPH_AdjMatrix:
	{
						this->transformToAdjMatrix();
						break;
	}
	case GRAPH_AdjList:
	{
						this->transformToAdjList();
						break;
	}
	}

	cout << "Krs: " << res_cost << endl;
	return res_graph;
}

Graph Graph::getSpaningTreeBoruvka()
{
	Graph res_graph = Graph(n, graph_form);

	DSU dsu = DSU(n);
	vector <int> min_e(n);
	vector <int> trans(n);
	int res_cost = 0;

	int max = 0; 
	switch (graph_form)
	{
	case GRAPH_AdjMatrix:
	{
							for (int i = 0; i < graph_m.size(); i++) {
								for (int j = 0; j < graph_m[i].size(); j++) {
									if (graph_m[i][j] > max)
										max = graph_m[i][j] + 1;
								}
							}
							break;
	}
	case GRAPH_ListOfEdges:
	{
							  for (int i = 0; i < graph_ew.size(); i++)
							  {
								  if (get<2>(graph_ew[i]) > max)
									  max = get<2>(graph_ew[i]) + 1;
							  }
							  break;
	}
	case GRAPH_AdjList:
	{
						  for (int i = 0; i < graph_lw.size(); i++)
						  {
							  for (int j = 0; j < graph_lw[i].size(); j++)
							  {
								  if (graph_lw[i][j].second > max)
									  max = graph_lw[i][j].second + 1;
							  }
						  }
						  break;
	}
	}

	int resgraph_m = 0;
	while (resgraph_m < n - 1) 
	{
		for (int i = 0; i < min_e.size(); i++) 
		{
			min_e[i] = max;
		}

		for (int i = 0; i < trans.size(); i++) 
		{
			trans[i] = -1;
		}

		switch (graph_form)
		{
		case GRAPH_AdjMatrix:
		{
								for (int i = 0; i < n; i++)
								{
									for (int j = 0; j < n; j++)
									{
										int vert1 = dsu.find(i);
										int vert2 = dsu.find(j);
										int weight = graph_m[i][j];
										if (weight != 0 && vert1 != vert2)
										{
											if (min_e[vert1] > weight)
											{
												min_e[vert1] = weight;
												trans[vert1] = vert2;
											}
											if (min_e[vert2] > weight)
											{
												min_e[vert2] = weight;
												trans[vert2] = vert1;
											}
										}
									}
								}
								break;
		}
		case GRAPH_AdjList:
		{
							  for (int i = 0; i < n; i++)
							  {
								  for (int j = 0; j < graph_lw[i].size(); j++)
								  {
									  int vert1 = dsu.find(i);
									  int vert2 = dsu.find(graph_lw[i][j].first - 1);
									  int weight = graph_lw[i][j].second;
									  if (vert1 != vert2)
									  {
										  if (min_e[vert1] > weight)
										  {
											  min_e[vert1] = weight;
											  trans[vert1] = vert2;
										  }
										  if (min_e[vert2] > weight)
										  {
											  min_e[vert2] = weight;
											  trans[vert2] = vert1;
										  }
									  }
								  }
							  }
							  break;
		}
		case GRAPH_ListOfEdges:
		{
								  for (int i = 0; i < graph_ew.size(); i++)
								  {
									  int vert1 = dsu.find(get<0>(graph_ew[i]) - 1);
									  int vert2 = dsu.find(get<1>(graph_ew[i]) - 1);
									  int weight = get<2>(graph_ew[i]);
									  if (vert1 != vert2)
									  {
										  if (min_e[vert1] > weight)
										  {
											  min_e[vert1] = weight;
											  trans[vert1] = vert2;
										  }
										  if (min_e[vert2] > weight)
										  {
											  min_e[vert2] = weight;
											  trans[vert2] = vert1;
										  }
									  }
								  }
								  break;
		}
		}

		bool check = true;
		for (int i = 0; i < n; i++) {
			if (trans[i] != -1)
				check = false;
		}
		if (check) break;

		for (int i = 0; i < min_e.size(); i++) 
		{
			if ((trans[i] != -1) && (dsu.find(i) != dsu.find(trans[i])) && (min_e[i] != max))
			{
				res_graph.addEdge(i + 1, trans[i] + 1, min_e[i]);
				res_cost += min_e[i];
				dsu.unite(i, trans[i]);
				resgraph_m++;
			}
		}
	}

	cout << "Bor: " << res_cost << endl;
	return res_graph;
}
