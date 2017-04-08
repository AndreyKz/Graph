#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Graph::Graph() {}

Graph::~Graph() {}

void Graph::readGraph(string fileName)
{
	ifstream f_input;
	f_input.open(fileName);

	f_input >> graph_form;

	switch (graph_form)
	{
		case 'C':
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
						}
					}
					break;
		}

		case 'L':
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
							}
						}
					}
					break;
		}
		case 'E':
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
		case'C':
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
		
		case'L':
		{
				   if (w)
				   {
					   graph_lw[from - 1].push_back(make_pair(to, weight));
					   if (!d)
					   {
						   graph_lw[to - 1].push_back(make_pair(from, weight));
					   }
				   }
				   else
				   {
					   graph_l[from - 1].push_back(to);
					   if (!d)
					   {
						   graph_l[to - 1].push_back(from);
					   }
				   }
				   break;
		}

		case'E':
		{
				   if (w)
				   {
					   graph_ew.push_back(make_tuple(from, to, weight));
				   }
				   else
				   {
					   graph_e.push_back(make_pair(from, to));
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
		case 'C':
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

		case'L':
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
						   i = 0;
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
						   i = 0;
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

		case 'E':
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
						if (!d)
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
						}
					}
					break;
		}
	}
}

int Graph::changeEdge(int from, int to, int newWeight)
{
	switch (graph_form)
	{
		case'C':
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

		case'L':
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

		case'E':
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
		case'L':
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
		
		case'E':
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

	graph_form = 'C';
}

void Graph::transformToAdjList()
{
	if (graph_form == 'L') return;

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
		case 'C':
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
		case'E':
		{
				   if (w)
				   {
					   for (int i = 0; i < graph_ew.size(); i++)
					   {
						   if (get<0>(graph_ew[i]) != 0)
						   {
							   graph_lw[get<0>(graph_ew[i]) - 1].push_back(make_pair(get<1>(graph_ew[i]), get<2>(graph_ew[i])));
						   }
					   }
				   }
				   else
				   {
					   for (int i = 0; i < graph_e.size(); i++)
					   {
						   if (graph_e[i].first != 0)
						   {
							   graph_l[graph_e[i].first - 1].push_back(graph_e[i].second);
						   }
					   }
				   }
				   break;
		}

	}
	graph_form = 'L';

}

void Graph::transformToListOfEdges()
{
	if (graph_form == 'E') return;

	graph_ew.clear();
	graph_e.clear();

	m = 0;

	switch (graph_form)
	{
		case'C':
		{
				   if (w)
				   {
					   for (int i = 0; i < graph_m.size(); i++)
					   {
						   for (int j = 0; j < graph_m[i].size(); j++)
						   {
							   if (graph_m[i][j])
							   {
								   graph_ew.push_back(make_tuple(i + 1, j + 1, graph_m[i][j]));
								   m++;
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

		case'L':
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

	graph_form = 'E';
}

void Graph::writeGraph(const string file_name)
{
	ofstream f_output;
	f_output.open(file_name);

	f_output << graph_form;
	
	switch(graph_form)
	{
		case'C':
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

		case'L':
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

		case'E':
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
