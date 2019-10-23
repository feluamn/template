#pragma GCC diagnostic error "-std=c++11"
#include <bits/stdc++.h>
#define LL long long
#define P pair<int, int>
const LL N = 1e6 + 10;
const LL inf = 2147483647;
using namespace std;
template <typename tp>
inline void read(tp &x)
{
    x = 0; char c = getchar(); bool f = 0;
    for (; c < '0' || c > '9'; f |= (c == '-'), c = getchar()) ;
    for (; c >= '0' && c <= '9'; x = (x << 3) + (x << 1) + c - '0', c = getchar()) ;
    if (f) x = -x;
}
LL n,x[N],c[N],p[N],s[N],sp[N],dp[N];
int l,r,de[N];
double slope(int x,int y)
{
    return (double)1*(dp[y]+s[y]-dp[x]-s[x])/(sp[y]-sp[x]);
}
signed main()
{
    read(n);
    for(int i=1;i<=n;i++) read(x[i]),read(p[i]),read(c[i]);
    for(int i=1;i<=n;i++) s[i]+=s[i-1]+x[i]*p[i],sp[i]=sp[i-1]+p[i];
    for(int i=1;i<=n;i++)
    {
        while(l<r&&slope(de[l],de[l+1])<x[i]) l++;
        dp[i]=dp[de[l]]-s[i]+s[de[l]]+x[i]*(sp[i]-sp[de[l]])+c[i];
        while(l<r&&slope(de[r-1],i)<slope(de[r-1],de[r])) r--;
        de[++r]=i;
    }
    printf("%lld\n",dp[n]);
    return 0;
}
