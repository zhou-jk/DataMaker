#include<iostream>
#include<cstdio>
#include<cassert>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#include<windows.h>
#include<random>
#include<functional>
using namespace std;
namespace DataMaker
{
	static mt19937 myrand(GetTickCount());
	unsigned rand()
	{
		return myrand();
	}
	unsigned int rand(unsigned int l,unsigned int r)
	{
		return myrand()%(r-l+1)+l;
	}
	unsigned long long brand()
	{
		return ((unsigned long long)rand()<<30)+((unsigned long long)rand()<<15)+((unsigned long long)rand()<<8)+((unsigned long long)rand()<<4)+((unsigned long long)rand()<<2)+((unsigned long long)rand()<<1);
	}
	unsigned long long brand(unsigned long long l,unsigned long long r)
	{
		return brand()%(r-l+1)+l;
	}
	template<typename T>
	void rand_shuffle(T _begin,T _end)
	{
		for(int i=1;i<=10;i++)
			shuffle(_begin,_end,myrand);
		return;
	}
	vector<pair<int,int> >rand_tree(int n)
	{
		vector<int>fa(n+1);
		for(int i=0;i<=n;i++)
			fa[i]=i;
		function<int(int v)>getf=[&](int v)->int
		{
			if(v==fa[v]) return v;
			fa[v]=getf(fa[v]);
			return fa[v];
		};
		function<void(int u,int v)>merge=[&](int u,int v)->void
		{
			int f1=getf(u),f2=getf(v);
			if(f1!=f2) fa[f2]=f1;
			return;
		};
		vector<pair<int,int> >edge;
		for(int i=1;i<=n-1;i++)
		{
			int u=rand(1,n),v=rand(1,n);
			while(getf(u)==getf(v)) u=rand(1,n),v=rand(1,n);
			edge.emplace_back(u,v);
		}
		rand_shuffle(edge.begin(),edge.end());
		return edge;
	}
	vector<pair<int,int> >rand_graph(int n,int m)
	{
		assert(m>=n-1);
		vector<pair<int,int> >edge=rand_tree(n);
		for(int i=1;i<=m-(n-1);i++)
		{
			int u=rand(1,n),v=rand(1,n);
			while(u==v) u=rand(1,n),v=rand(1,n);
			edge.emplace_back(u,v);
		}
		rand_shuffle(edge.begin(),edge.end());
		return edge;
	}
}
