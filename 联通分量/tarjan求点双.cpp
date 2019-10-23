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
int n,m,anss;
int head[N],cnt=1;
int vis[N],dfn[N],low[N],num;
int cant[N*5],ans[N];
struct Edge{int next,to;}edge[N*5];
inline void add(int from,int to)
{
    edge[++cnt].next=head[from];
    edge[cnt].to=to;
    head[from]=cnt;
}
void dfs(int now,int fa)
{
    vis[now]=1;
    dfn[now]=low[now]=++num;
    for(int i=head[now];i;i=edge[i].next)
    {
        int to=edge[i].to; if(to==fa) continue;
        if(!vis[to]) dfs(to,now),low[now]=min(low[now],low[to]);
        else low[now]=min(low[now],dfn[to]);
    }
    for(int i=head[now];i;i=edge[i].next)
    {
        int to=edge[i].to; if(to==fa) continue;
        if(low[to]>dfn[now]) cant[i]=cant[i^1]=1;
    }
}
void tarjan(){for(int i=1;i<=n;i++) if(!vis[i]) dfs(i,i);}
void dfs_ans(int now,int zu)
{
    ans[now]=zu;
    for(int i=head[now];i;i=edge[i].next)
    {
        int to=edge[i].to;
        if(ans[to]||cant[i]) continue;
        dfs_ans(to,zu);
    }
}
int main()
{
    read(n),read(m);
    for(int i=1,u,v;i<=m;i++) read(u),read(v),add(u,v),add(v,u);
    tarjan();
    for(int i=1;i<=n;i++) if(!ans[i]) anss++,dfs_ans(i,i);
    printf("%d\n",anss);
    for(int i=1;i<=n;i++) printf("%d ",ans[i]);puts("");
    return 0;
}
