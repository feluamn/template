#pragma GCC optimize("2,Ofast,inline")
#pragma GCC diagnostic error "-std=c++11"
#include <bits/stdc++.h>
#define LL long long
#define P pair<int, int>
const LL N = 1e5 + 10;
const int inf = 0x3f3f3f3f;
using namespace std;
template <typename tp>
inline void read(tp &x)
{
    x = 0; char c = getchar(); bool f = 0;
    for (; c < '0' || c > '9'; f |= (c == '-'), c = getchar()) ;
    for (; c >= '0' && c <= '9'; x = (x << 3) + (x << 1) + c - '0', c = getchar()) ;
    if (f) x = -x;
}
int n,m,V[N];
namespace MATRIX
{
    struct Matrix {LL s[2][2];};
    Matrix operator * (Matrix a,Matrix b)
    {
        Matrix ret;
        ret.s[0][0]=max(a.s[0][0]+b.s[0][0],a.s[0][1]+b.s[1][0]);
        ret.s[0][1]=max(a.s[0][0]+b.s[0][1],a.s[0][1]+b.s[1][1]);
        ret.s[1][0]=max(a.s[1][0]+b.s[0][0],a.s[1][1]+b.s[1][0]);
        ret.s[1][1]=max(a.s[1][0]+b.s[0][1],a.s[1][1]+b.s[1][1]);
        return ret;
    }
}
namespace HLD
{
    using namespace MATRIX;
    //HLD
    Matrix vals[N<<2];
    int dp[N][2];
    struct Node{int dfn,fa,siz,chain,depth,max_son;}node[N];
    struct Edge{int next,to;}edge[N<<2];
    int head[N],cnt,dfns,chains,top[N],bot[N];
    void add(int from,int to) { edge[++cnt]={head[from],to}; head[from]=cnt;}
    void insert(int from,int to) { add(from,to); add(to,from);}
    void dfs1(int now)
    {
        node[now].siz=1;
        for(int i=head[now];i;i=edge[i].next)
        {
            int to=edge[i].to;
            if(to==node[now].fa) continue;
            node[to].fa=now; node[to].depth=node[now].depth+1;
            dfs1(to);
            node[now].siz+=node[to].siz;
            if(!node[now].max_son||node[node[now].max_son].siz<node[to].siz) 
                node[now].max_son=to;
        }
    }
    void dfs2(int now)
    {
        node[now].dfn=++dfns;
        dp[now][0]=0;dp[now][1]=V[now];
        if(!node[now].fa||node[node[now].fa].max_son!=now) 
            node[now].chain=++chains,top[chains]=bot[chains]=now;
        else node[now].chain=node[node[now].fa].chain,bot[node[now].chain]=now;
        if(node[now].max_son) 
        {
            dfs2(node[now].max_son);
            dp[now][0]+=max(dp[node[now].max_son][1],dp[node[now].max_son][0]);
            dp[now][1]+=dp[node[now].max_son][0];
        }
        for(int i=head[now];i;i=edge[i].next)
        {
            int to=edge[i].to;
            if(to==node[now].fa||to==node[now].max_son) continue;
            dfs2(to);
            dp[now][0]+=max(dp[to][1],dp[to][0]);
            dp[now][1]+=dp[to][0];
        }
        int g0=dp[now][0]-(node[now].max_son ? max(dp[node[now].max_son][1],dp[node[now].max_son][0]) : 0);
        int g1=dp[now][1]-(node[now].max_son ? dp[node[now].max_son][0] : 0);
        vals[node[now].dfn]={g0,g0,g1,-inf};
    }
    //ST
    Matrix val[N<<2];
    void built(int now,int l,int r)
    {
        if(l==r) {val[now]=vals[l];return;}
        int mid=(l+r)>>1;
        built(now<<1,l,mid);
        built(now<<1|1,mid+1,r);
        val[now]=val[now<<1]*val[now<<1|1];
    }
    void Modify(int now,int l,int r,int k)
    {
        if(l==r){val[now]=vals[l];return;}
        int mid=(l+r)>>1;
        if(k<=mid) Modify(now<<1,l,mid,k);
        else Modify(now<<1|1,mid+1,r,k);
        val[now]=val[now<<1]*val[now<<1|1];
    }
    Matrix query(int now,int l,int r,int ql,int qr)
    {
        if(l==ql&&r==qr) return val[now];
        int mid=(l+r)>>1;
        if(qr<=mid) return query(now<<1,l,mid,ql,qr);
        if(ql>mid) return query(now<<1|1,mid+1,r,ql,qr);
        return query(now<<1,l,mid,ql,mid)*query(now<<1|1,mid+1,r,mid+1,qr);
    }
    Matrix get_chain(int now) {return query(1,1,n,node[top[node[now].chain]].dfn,node[bot[node[now].chain]].dfn);}
    void change(int now,int w)
    {
        vals[node[now].dfn].s[1][0]+=w-V[now];V[now]=w;
        while(now)
        {
            Matrix a=get_chain(now);
            Modify(1,1,n,node[now].dfn);
            Matrix b=get_chain(now);
            now=node[top[node[now].chain]].fa;
            if(!now) break;
            int now0 = now;now=node[now].dfn;
            vals[now].s[0][0]+=max(b.s[0][0],b.s[1][0])-max(a.s[0][0],a.s[1][0]);
            vals[now].s[0][1]=vals[now].s[0][0];
            vals[now].s[1][0]+=b.s[0][0]-a.s[0][0];
            now=now0;
        }
    }
}
using namespace HLD;
signed main()
{
    read(n),read(m);
    memset(dp,0,sizeof(dp));
    for(int i=1;i<=n;i++) read(V[i]);
    for(int i=1,u,v;i<n;i++) read(u),read(v),insert(u,v);
    dfs1(1); dfs2(1);
    built(1, 1, n);
    for(int cas=1,u,w;cas<=m;cas++)
    {
        read(u),read(w);
        change(u,w);
        Matrix ret=get_chain(1);
        printf("%lld\n",max(ret.s[0][0],ret.s[1][0]));
    }
    return 0;
}
