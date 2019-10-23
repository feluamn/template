#include<bits/stdc++.h>
#define LL long long
#define P pair<int,int>
const LL N=5e3+10;
const LL mod=998244353;
const LL inf=0x3f3f3f3f;
const double eps=1e-9;
using namespace std;
template<typename tp> inline void read(tp &x)
{
    x=0; char c=getchar(); bool f=0;
    for(;c<'0'||c>'9';f|=(c=='-'),c = getchar());
    for(;c>='0'&&c<='9';x=(x<<3)+(x<<1)+c-'0',c = getchar());
    if(f) x=-x;
}
int n,m,k,ans;
int G[510][510],match[510];
int x[N],y[N],slack[N];
bool visx[510],visy[510];
bool find(int now)
{
    visx[now]=1;
    for(int i=1;i<=n;i++)
    {
        if(visy[i]) continue;
        int need=x[now]+y[i]-G[now][i];
        if(!need)
        {
            visy[i]=1;
            if(match[i]==-1||find(match[i]))
            {
                match[i]=now;
                return true;
            }
        }
        else slack[i]=min(slack[i],need);
    }
    return false;
}
void updata()
{
    int d=inf;
    for(int i=1;i<=n;i++) if(!visy[i]) d=min(d,slack[i]);
    for(int i=1;i<=n;i++)
    {
        if(visx[i]) x[i]-=d;
        if(visy[i]) y[i]+=d;
    }   
}
void KM()
{
    for(int i=1;i<=n;i++)
    {
        memset(slack,inf,sizeof slack);
        while(true)
        {
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            if(find(i)) break;
            else updata();
        }
    }
}
signed main()
{
    read(n),read(m),read(k);
    for(int i=1,u,v,w;i<=k;i++)
        read(u),read(v),read(w),G[u][v]=w;
    n=m;
    for(int i=1;i<=n;i++)
    {
        x[i]=y[i]=0;match[i]=-1;
        for(int j=1;j<=n;j++)
            x[i]=max(x[i],G[i][j]);
    }
    KM();
    for(int i=1;i<=n;i++)
        ans+=G[match[i]][i];
    printf("%d\n",ans);
    return 0;
}