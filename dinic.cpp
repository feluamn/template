#pragma GCC optimize("2,Ofast,inline")
#pragma GCC diagnostic error "-std=c++11"
#include<bits/stdc++.h>
#define LL long long
#define P pair<int,int>
const LL N=6e4+10;
const LL mod=1e9+7;
const LL inf=998244353;
const double eps=1e-9;
using namespace std;
template<typename tp> inline void read(tp &x)
{
    x=0; char c=getchar(); bool f=0;
    for(;c<'0'||c>'9';f|=(c=='-'),c = getchar());
    for(;c>='0'&&c<='9';x=(x<<3)+(x<<1)+c-'0',c = getchar());
    if(f) x=-x;
}
int n,m,s,t,sum;
struct Edge{int next,to,flow;}edge[N*10];
int head[N],cnt=1,dep[N],cur[N];
queue<int> q;
void add(int from,int to,int flow){edge[++cnt]={head[from],to,flow};head[from]=cnt;}
void insert(int from,int to,int flow){add(from,to,flow);add(to,from,0);}
bool BFS()
{
    memset(dep,-1,sizeof(dep));
    q.push(s);dep[s]=0;
    while(!q.empty())
    {
        int now=q.front();q.pop();
        for(int i=head[now];i;i=edge[i].next)
        {
            int to=edge[i].to;
            if(!edge[i].flow) continue;
            if(dep[to]==-1) dep[to]=dep[now]+1,q.push(to);
        }
    }
    return dep[t]!=-1;
}
int DFS(int now,int flow)
{
    if(now==t||!flow) return flow;
    int used=0;
    for(int &i=cur[now];i;i=edge[i].next)
    {
        int to=edge[i].to;
        if(dep[to]==dep[now]+1&&edge[i].flow)
        {
            int flag=DFS(to,min(flow-used,edge[i].flow));
            if(flag>0)
            {
                edge[i].flow-=flag;
                edge[i^1].flow+=flag;
                used+=flag;
            }
        }
    }
    return used;
}
int dinic(int ret=0) 
{ 
    while(BFS()) 
    {
        memcpy(cur, head, sizeof(int) * (n + m + 1));
        ret+=DFS(s,inf); 
    }
    return ret;
}
signed main()
{
    read(n),read(m);
    s=0,t=n+m+1;
    for(int i=1,w;i<=n;i++)
        read(w),insert(s,i,w);
    for(int i=1,u,v,w;i<=m;i++)
    {
        read(u),read(v),read(w);
        sum+=w;
        insert(u,n+i,inf);
        insert(v,n+i,inf);
        insert(n+i,t,w);
    }
    printf("%d\n",sum-dinic());
    return 0;
}