#include<bits/stdc++.h>
#define LL long long
const LL N=3e7+10;
const LL inf=2147483647;
using namespace std;
template<typename tp> inline void read(tp &x)
{
    x=0; char c=getchar(); bool f=0;
    for(;c<'0'||c>'9';f|=(c=='-'),c = getchar());
    for(;c>='0'&&c<='9';x=(x<<3)+(x<<1)+c-'0',c = getchar());
    if(f) x=-x;
}
namespace Treap
{
    int a,b,c,d,e;
    int cnt=0,root[N];
    struct Node{int key,siz,p,ch[2];} node[N];
    void new_node(int key) {node[++cnt].key=key,node[cnt].p=rand(),node[cnt].siz=1;}
    void updata(int now) {node[now].siz=node[node[now].ch[0]].siz+node[node[now].ch[1]].siz+1;}
    int merge(int x,int y)
    {
        if(!node[x].siz) return y; if(!node[y].siz) return x;
        int _root=++cnt;
        if(node[x].p<node[y].p) {node[_root]=node[x];node[_root].ch[1]=merge(node[_root].ch[1],y);updata(_root);return _root;}
        else {node[_root]=node[y];node[_root].ch[0]=merge(x,node[_root].ch[0]);updata(_root);return _root;}
    }
    void split_key(int now,int &x,int &y,int k)
    {
        if(!node[now].siz) {x=y=0;return;}
        if(node[now].key<=k) {x=++cnt;node[x]=node[now];split_key(node[x].ch[1],node[x].ch[1],y,k);updata(x);}
        else {y=++cnt;node[y]=node[now];split_key(node[y].ch[0],x,node[y].ch[0],k);updata(y);}
    }
    int val(int now,int k)
    {
        if(k==node[node[now].ch[0]].siz+1) return node[now].key;
        else if(k<node[node[now].ch[0]].siz+1) return val(node[now].ch[0],k);
        else return val(node[now].ch[1],k-node[node[now].ch[0]].siz-1);
    }
    int ranks(int &root,int k,int ret=0) {split_key(root,a,b,k-1); ret=node[a].siz+1; root=merge(a,b); return ret;}
    void insert(int &root,int k) {split_key(root,a,b,k);new_node(k);root=merge(a,merge(cnt,b));}
    void Delete(int &root,int k) {split_key(root,a,b,k);split_key(a,c,d,k-1);d=merge(node[d].ch[0],node[d].ch[1]);root=merge(merge(c,d),b);}
    int pre(int &root,int k,int ret=-inf) {split_key(root,a,b,k-1);if(node[a].siz) ret=val(a,node[a].siz);root=merge(a,b);return ret;}
    int suf(int &root,int k,int ret=inf) {split_key(root,a,b,k);if(node[b].siz) ret=val(b,1);root=merge(a,b);return ret;}
}
using namespace Treap;
int n,m,num,k;
signed main()
{
    read(n);
    for(int i=1;i<=n;i++)
    {
        read(m),read(num),read(k); root[i]=root[m];
        if(num==1) insert(root[i],k);
        if(num==2) Delete(root[i],k);
        if(num==3) printf("%d\n",ranks(root[i],k));
        if(num==4) printf("%d\n",val(root[i],k));
        if(num==5) printf("%d\n",pre(root[i],k));
        if(num==6) printf("%d\n",suf(root[i],k));
    }
    return 0;
}
