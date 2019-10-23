#pragma GCC optimize("2,Ofast,inline")
#include <bits/stdc++.h>
#define LL long long
#define P pair<int, int>
const LL N = 2e6 + 10;
const LL inf = 0x7f;
const LL mod = 998244353;
using namespace std;
template <typename tp>
inline void read(tp &x)
{
    x = 0; char c = getchar(); bool f = 0;
    for (; c < '0' || c > '9'; f |= (c == '-'), c = getchar()) ;
    for (; c >= '0' && c <= '9'; x = (x << 3) + (x << 1) + c - '0', c = getchar()) ;
    if (f) x = -x;
}
struct Node{ int ch[26], link, maxn;} node[N];
struct Edge{int next,to;} edge[N];
int head[N],cntt;
void add(int from,int to){edge[++cntt]={head[from],to};head[from]=cntt;}
int cnt, tail, len, ans, num;
char str[11][N];
int vals[N],val[N];
inline void insert(int c)
{
    int p = tail, np = ++cnt;
    node[np].maxn = node[p].maxn + 1, tail = np;
    for (; p && !node[p].ch[c]; p = node[p].link) node[p].ch[c] = np;
    if (!p) return (void)(node[np].link = 1);
    int q = node[p].ch[c];
    if (node[p].maxn + 1 == node[q].maxn) node[np].link = q;
    else
    {
        int nq = ++cnt;
        node[nq] = node[q];
        node[nq].maxn = node[p].maxn + 1;
        node[np].link = node[q].link = nq;
        for (; node[p].ch[c] == q; p = node[p].link)
            node[p].ch[c] = nq;
    }
}
void dfs(int wei,int now,int steps,int num,int len)
{
    val[now]=max(steps,val[now]);
    if(wei==len) return;
    while(!node[now].ch[str[num][wei]-'a']&&now>1) 
        now=node[now].link,steps=node[now].maxn;
    if(!node[now].ch[str[num][wei]-'a'])
        dfs(wei+1,now,steps,num,len);
    else 
        dfs(wei+1,node[now].ch[str[num][wei]-'a'],steps+1,num,len);
}
void dfs_zz(int now)
{
    for(int i=head[now];i;i=edge[i].next)
    {
        dfs_zz(edge[i].to);
        val[now]=max(val[now],min(node[now].maxn,val[edge[i].to]));
    }
    vals[now]=min(vals[now],val[now]);
}
void dfs_anss(int now)
{
    if(vals[now]!=inf&&now!=1)
        ans=max(ans,vals[now]);
    for(int i=head[now];i;i=edge[i].next)
        dfs_anss(edge[i].to);
}
int main()
{
    // freopen("in", "r", stdin);
    while (~scanf("%s", str[++num])); num--;
    cnt = 1, tail = 1;
    len = strlen(str[1]);
    for (int i = 0; i < len; i++) insert(str[1][i] - 'a');
    for(int i=2;i<=cnt;i++)
        add(node[i].link,i);
    memset(vals,0x7f,sizeof(vals));
    for(int cas=2;cas<=num;cas++)
    {
        memset(val,0,sizeof(val));
        dfs(0,1,0,cas,strlen(str[cas]));
        // for(int i=1;i<=cnt;i++) cout<<i<<" "<<val[i]<<endl;
        dfs_zz(1);
    }
    dfs_anss(1);
    printf("%lld\n", ans);
    return 0;
}
