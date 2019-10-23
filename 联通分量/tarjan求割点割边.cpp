#include<bits/stdc++.h>
#define LL long long
#define P pair<int,int>
const LL N=1e5+10;
const LL mod=998244353;
using namespace std;
template<typename tp> inline void read(tp &x)
{
    x=0; char c=getchar(); bool f=0;
    for(;c<'0'||c>'9';f|=(c=='-'),c = getchar());
    for(;c>='0'&&c<='9';x=(x<<3)+(x<<1)+c-'0',c = getchar());
    if(f) x=-x;
}
int n,m,ans;
int head[N],cnt;
int vis[N],dfn[N],low[N],num;
struct Edge{int next,to;}edge[N*5];
inline void add(int from,int to)
{
    edge[++cnt].next=head[from];
    edge[cnt].to=to;
    head[from]=cnt;
}
int GD[N],num_GD;
vector<P> GB; 
void dfs(int now,int fa)
{
    vis[now]=1;
    dfn[now]=low[now]=++num; int son=0;
    for(int i=head[now];i;i=edge[i].next)
    {
        int to=edge[i].to;if(to==fa) continue;
        if(!vis[to]) 
        {
            dfs(to,now);
            low[now]=min(low[now],low[to]);
            if(low[to]>=dfn[now]) son++;
        }
        else low[now]=min(low[now],dfn[to]);
    }
    for(int i=head[now];i;i=edge[i].next)
    {
        int to=edge[i].to;if(to==fa) continue;
        if(low[to]>dfn[now]) 
            GB.push_back(P(min(to,now),max(to,now)));
    }
    if(son>=2||(son==1&&fa)) GD[++num_GD]=now;
}
void tarjan() {for(int i=1;i<=n;i++) if(!vis[i]) dfs(i,0);}
signed main()
{
    read(n),read(m);
    for(int i=1,u,v;i<=m;i++) read(u),read(v),add(u,v),add(v,u);
    tarjan();
    sort(GD+1,GD+num_GD+1);
    for(int i=1;i<=num_GD;i++) printf("%d ",GD[i]); 
    if(num_GD==0) puts("Null"); else puts("");
    sort(GB.begin(),GB.end());
    int siz=GB.size();
    for(int i=0;i<siz;i++) printf("%d %d\n",GB[i].first,GB[i].second);
    return 0;
}
