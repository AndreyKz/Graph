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

	void MakeSet(int x);
	int Find(int x);
	void Union(int x, int y);
};
