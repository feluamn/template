namespace LCT
{
	#define lson(_) (node[_].ch[0])
	#define rson(_) (node[_].ch[1])
	#define fa(_) (node[_].fa)
	struct Node { int val, _xor, ch[2], fa, tag; } node[N];
	void Anatomy(int now)
	{
		printf("%d:\n",now);
		printf("   val = %d\n",node[now].val);
		printf("   ch[0] = %d\n",node[now].ch[0]);
		printf("   ch[1] = %d\n",node[now].ch[1]);
		printf("   fa = %d\n",node[now].fa);
		printf("   tag = %d\n",node[now].tag);
	}
	void updata(int now) { node[now]._xor = node[now].val ^ node[lson(now)]._xor ^ node[rson(now)]._xor;}
	int IsRight(int now) { return rson(fa(now)) == now;}
	int IsRoot(int now) { return rson(fa(now)) != now && lson(fa(now)) != now;}
	void push_down(int now)
	{
		if(node[now].tag)
		{
			node[rson(now)].tag ^= 1;
			swap(lson(lson(now)), rson(lson(now)));
			node[lson(now)].tag ^= 1;
			swap(lson(rson(now)), rson(rson(now)));
			node[now].tag = 0;
		}
	}
	void rotate(int now)
	{
		int fa = fa(now), gfa = fa(fa), k = IsRight(now), sons = node[now].ch[k ^ 1];
		if(!IsRoot(fa)) node[gfa].ch[IsRight(fa)] = now; 
		node[fa].ch[k] = sons; 
		if(sons) node[sons].fa = fa;
		node[now].fa = gfa;
		node[now].ch[k ^ 1] = fa; node[fa].fa = now;
		updata(fa); // updata(now);
	}
	int Aux[N]; //Auxiliary
	void Splay(int now, int num = 0)
	{
		Aux[++num] = now;
		for(int i = now; !IsRoot(i); i = fa(i)) Aux[++num] = fa(i);
		for(int i = num; i >= 1; --i) push_down(Aux[i]);
		while(!IsRoot(now))
		{
			if(!IsRoot(fa(now)))
			{
				if(IsRight(now)==IsRight(fa(now))) rotate(fa(now));
				else rotate(now);
			}
			rotate(now);
		}
		updata(now);
	}
	void Access(int now)
	{
		for(int i = 0 ; now; now = fa(i = now))
		{
			Splay(now);
			rson(now) = i, updata(now);
		}
	}
	int find_fa(int now)
	{
		Access(now);
		for(Splay(now); lson(now); now = lson(now)) push_down(now);
		Splay(now); return now;
	}
	void make_root(int now) { Access(now); Splay(now); node[now].tag ^= 1; swap(lson(now), rson(now));}
	void link(int from, int to)
	{
		make_root(from);
		if(find_fa(to) != from) fa(from) = to; 
	}
	void cut(int from, int to)
	{
		make_root(from);
		if(find_fa(to) == from && fa(to) == from && lson(to) == 0)
			fa(to) = rson(from) = 0, updata(from);
	}
	void split(int x, int y)
	{
		make_root(x);
		Access(y);
		Splay(y);
	}
}
using namespace LCT;
