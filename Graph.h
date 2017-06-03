#include <vector>
#include <string>
#include <set>
#include <queue>
#include <stack>
#include <tuple>
using namespace std;

class Graph
{
public:
	Graph();
	Graph(int num, char gform);
	~Graph();

	void readGraph(const string fileName);
	void addEdge(int from, int to, int weight = 0);
	void removeEdge(int from, int to);
	int changeEdge(int from, int to, int newWeight);
	void transformToAdjList();
	void transformToAdjMatrix();
	void transformToListOfEdges();
	void writeGraph(const string file_name);
	Graph getSpaningTreePrima();
	Graph getSpaningTreeKruscal();
	Graph getSpaningTreeBoruvka();


private:
	char graph_form;
	int n, m, d, w;

	vector<vector<int> > graph_m;
	vector<vector<int> > graph_l;
	vector<vector<pair<int, int> > > graph_lw;
	vector<pair<int, int> > graph_e;
	vector<tuple<int, int, int> > graph_ew;

};
