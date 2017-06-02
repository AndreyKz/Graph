#include "DSU.h"

DSU::DSU() {};
DSU::DSU(int) {};
DSU::~DSU() {};

void DSU::MakeSet(int x)
{
	p[x] = x;
	rank[x] = 0;
}

int DSU::Find(int x)
{
	return (x == p[x] ? x : p[x] = Find(p[x]));
}

void DSU::Union(int x, int y)
{
	if ((x = Find(x)) == (y = Find(y)))
		return;

	if (rank[x] <  rank[y])
		p[x] = y;
	else
		p[y] = x;

	if (rank[x] == rank[y])
		++rank[x];
}
