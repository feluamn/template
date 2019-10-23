#pragma GCC diagnostic error "-std=c++11"
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
int n,m,ans,zz;
int xx[N],head[N],cnt;
int vis[N],dfn[N],low[N],num,scc[N],sccn,cost[N],flag[N];
stack<int> st;
struct Edge{int next,to;}edge[N*5];
inline void add(int from,int to)
{
    edge[++cnt].next=head[from];
    edge[cnt].to=to;
    head[from]=cnt;
}
void dfs(int now)
{
    vis[now]=1;st.push(now);
    dfn[now]=low[now]=++num;
    for(int i=head[now];i;i=edge[i].next)
    {
        int to=edge[i].to;
        if(!vis[to]) dfs(to),low[now]=min(low[now],low[to]);
        else if(!scc[to]) low[now]=min(low[now],dfn[to]);
    }
    if(dfn[now]==low[now])
    {
        sccn++;
        while(true)
        {
            int fron=st.top();st.pop();
            cost[sccn]+=xx[fron];
            scc[fron]=sccn;
            if(fron==now) break;
        }
    }
}
void tarjan() {for(int i=1;i<=n;i++) if(!vis[i]) dfs(i);}
int head_small[N],cnt_small;
Edge edge1[N*5];
void add_small(int from,int to)
{
    edge1[++cnt_small].next=head_small[from];
    edge1[cnt_small].to=to;
    head_small[from]=cnt_small;
}
int dfs_ans(int now)
{
    int maxn=0;
    for(int i=head_small[now];i;i=edge1[i].next)
    {
        int to=edge1[i].to;
        maxn=max(maxn,dfs_ans(to));
    }
    return maxn+cost[now];
}
signed main()
{
    read(n),read(m);
    for(int i=1;i<=n;i++) read(xx[i]);
    for(int i=1,u,v;i<=m;i++) read(u),read(v),add(u,v);
    tarjan();
    for(int i=1;i<=n;i++)
        for(int j=head[i];j;j=edge[j].next)
            if(scc[i]!=scc[edge[j].to])
                add_small(scc[i],scc[edge[j].to]);
    // for(int i=1;i<=n;i++) printf("%d ",scc[i]);puts("");
    // for(int i=1;i<=sccn;i++) printf("%d ",cost[i]);puts("");
    ans=dfs_ans(scc[1]);
    printf("%d\n",ans);
    return 0;
}

