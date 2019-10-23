namespace Treap
{
	int cnt=0,root;
	struct Node {LL key;int siz,p,ch[2];}node[N];
	Node new_node(LL key)
	{
		node[++cnt].key=key;
		node[cnt].p=rand();
		node[cnt].siz=1;
	}
	void updata(int now)
	{
		int l=node[now].ch[0],r=node[now].ch[1];
		node[now].siz=node[l].siz+node[r].siz+1;
	}
	int merge(int x,int y)
	{
		if(node[x].siz==0) return y;
		if(node[y].siz==0) return x;
		if(node[x].p<node[y].p)
		{
			node[x].ch[1]=merge(node[x].ch[1],y);
			updata(x);return x;
		}
		else
		{
			node[y].ch[0]=merge(x,node[y].ch[0]);
			updata(y);return y;
		}
	}
	void split_k(int now,int &x,int &y,int k)
	{
		if(node[now].siz==0) {x=y=0;return;}
		if(node[node[now].ch[0]].siz+1<=k) x=now,split_k(node[now].ch[1],node[now].ch[1],y,k-node[node[now].ch[0]].siz-1);
		else y=now,split_k(node[now].ch[0],x,node[now].ch[0],k);
		updata(now);
	}
	void split_key(int now,int &x,int &y,LL k)
	{
		if(node[now].siz==0) {x=y=0;return;}
		if(node[now].key<=k) x=now,split_key(node[now].ch[1],node[now].ch[1],y,k);
		else y=now,split_key(node[now].ch[0],x,node[now].ch[0],k);
		updata(now);
	}
	int a,b,c,d,e,f;
}
using namespace Treap;
