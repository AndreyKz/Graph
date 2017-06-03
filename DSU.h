#include <vector>
#include <algorithm>
using namespace std;
class DSU
{
private:
	vector <int> p;
	vector <int> rank;
public:
	
	DSU();
	DSU(int);
	~DSU();

	int find(int x);
	void unite(int x, int y);
};
