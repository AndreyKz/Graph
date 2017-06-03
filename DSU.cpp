#include "DSU.h"

DSU::DSU() {};
DSU::DSU(int num) 
{
	p.resize(num+1);
	for (int i = 0; i < p.size(); i++) {
		p[i] = i;
	}
	rank.resize(num+1);
	fill(rank.begin(), rank.end(), 1);
};
DSU::~DSU() {};

int DSU::find(int x)
{
	return (x == p[x] ? x : p[x] = find(p[x]));
}

void DSU::unite(int x, int y)
{
	if ((x = find(x)) == (y = find(y)))
		return;

	if (rank[x] <  rank[y])
		p[x] = y;
	else
		p[y] = x;

	if (rank[x] == rank[y])
		++rank[x];
}
