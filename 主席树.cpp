#pragma GCC diagnostic error "-std=c++11"
#include<map>
#include<cmath>
#include<cstdio>
#include<iostream>
#include<algorithm>
#define LL long long
#define P pair<int,int>
const LL N=1e5+10;
const LL mod=2147483648;
const double eps=1e-12;
using namespace std;
template<typename tp> inline void read(tp &x)
{
    x=0; char c=getchar(); bool f=0;
    for(;c<'0'||c>'9';f|=(c=='-'),c = getchar());
    for(;c>='0'&&c<='9';x=(x<<3)+(x<<1)+c-'0',c = getchar());
    if(f) x=-x;
}
int n,m;
int x[N],to[N],tot;
namespace Chairman_tree
{
	int siz,root[N*20];
	struct Node{int ch[2],siz;}node[N*20];
	void build(int &now,int l,int r)
	{
		now=++siz;node[now].siz=0;
		if(l==r) return;
		int mid=(l+r)>>1;
		build(node[now].ch[0],l,mid);
		build(node[now].ch[1],mid+1,r);
	}
	void change(int &now,int l,int r,int last,int k)
	{
		now=++siz;
		node[now].ch[0]=node[last].ch[0];node[now].ch[1]=node[last].ch[1];
		node[now].siz=node[last].siz+1;
		if(l==r) return;
		int mid=(l+r)>>1;
		if(k<=mid) change(node[now].ch[0],l,mid,node[last].ch[0],k);
		else change(node[now].ch[1],mid+1,r,node[last].ch[1],k);
	}
	int query(int L,int R,int l,int r,int k)
	{
		if(l==r) return l;
		int mid=(l+r)>>1,sum=node[node[R].ch[0]].siz-node[node[L].ch[0]].siz;
		if(k<=sum) return query(node[L].ch[0],node[R].ch[0],l,mid,k);
		else return query(node[L].ch[1],node[R].ch[1],mid+1,r,k-sum);
	}
}
using namespace Chairman_tree;
int main()
{
	read(n),read(m);
	for(int i=1;i<=n;i++) read(x[i]),to[i]=x[i];
	sort(to+1,to+n+1);tot=unique(to+1,to+n+1)-to-1;
	for(int i=1,tmp;i<=n;i++) x[i]=lower_bound(to+1,to+tot+1,x[i])-to;
	build(root[0],1,tot);
	for(int i=1;i<=n;i++) change(root[i],1,tot,root[i-1],x[i]);
	for(int i=1,l,r,k;i<=m;i++) read(l),read(r),read(k),printf("%d\n",to[query(root[l-1],root[r],1,tot,k)]);
    return 0;
}
