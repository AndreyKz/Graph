const int MAXN = 10000;

class DSU
{
private:
	
	int p[MAXN], rank[MAXN];

public:
	
	DSU();
	DSU(int);
	~DSU();

	void MakeSet(int x);
	int Find(int x);
	void Union(int x, int y);
};
