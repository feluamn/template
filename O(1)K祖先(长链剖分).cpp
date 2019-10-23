#include<bits/stdc++.h>
#define LL long long
#define P pair<int, int>
const LL N = 3e5 + 10;
const LL mod = 998244353;
const LL inf = 1e18;
using namespace std;
template<typename tp> inline void read(tp &x)
{
    x=0; char c=getchar(); bool f=0;
    for(;c<'0'||c>'9';f|=(c=='-'),c = getchar());
    for(;c>='0'&&c<='9';x=(x<<3)+(x<<1)+c-'0',c = getchar());
    if(f) x=-x;
}
int n, m, last, q, k;
int highbit[N];
namespace LCS//long chain split
{
    #define son(_) node[_].son
    #define fa(_) node[_].fa[0]
    struct Edge { int next, to; } edge[N << 1];
    int head[N], cnt, dfns;
    void add(int from, int to) { edge[++cnt] = {head[from], to}; head[from] = cnt; }
    void insert(int from, int to) { add(from, to); add(to, from); }
    struct Node
    {
        int dep, max_dep, son, fa[22], top, dfn, len;
        vector<int> up, down;
    } node[N];
    void dfs1(int now)
    {
        for (int i = 1; i <= 20; i++)
            node[now].fa[i] = node[node[now].fa[i - 1]].fa[i - 1];
        for (int i = head[now]; i; i = edge[i].next)
        {
            int to = edge[i].to;
            if (to == fa(now))
                continue;
            fa(to) = now;
            node[to].dep = node[to].max_dep = node[now].dep + 1;
            dfs1(to);
            if (node[to].max_dep > node[now].max_dep)
                node[now].max_dep = node[to].max_dep, son(now) = to;
        }
        node[now].len = node[now].max_dep - node[now].dep;
    }
    void dfs2(int now)
    {
        node[now].dfn = ++dfns;
        if (son(fa(now)) != now || !fa(now))
        {
            node[now].top = now;
            int flag = now;
            node[now].up.push_back(now);
            node[now].down.push_back(now);
            for (int i = 1; i <= node[now].len; i++)
                flag = fa(flag), node[now].up.push_back(flag);
            flag = now;
            for (int i = 1; i <= node[now].len; i++)
                flag = son(flag), node[now].down.push_back(flag);
        }
        else
            node[now].top = node[fa(now)].top;
        if(son(now)) dfs2(son(now));
        for (int i = head[now]; i; i = edge[i].next)
        {
            int to = edge[i].to;
            if (to == fa(now) || to == son(now))
                continue;
            dfs2(to);
        }
    }
    int find(int now, int k)
    {
        int gfa = node[node[now].fa[highbit[k]]].top;
        if(!k) gfa = node[now].top;
        if(node[gfa].len < k / 2 || gfa == 0) return 0;
        if (node[now].dep - node[gfa].dep > k)
            return node[gfa].down[node[now].dep - node[gfa].dep - k];
        else
            return node[gfa].up[k - node[now].dep + node[gfa].dep];
    }
}
using namespace LCS;
signed main()
{
    read(n);
    for (int i = 1, u, v; i < n; i++)
        read(u), read(v), insert(u, v);
    node[1].dep = 1;
    dfs1(1), dfs2(1);
    for (int i = 1; i <= n; i++)
    {
        int flag = i;
        while (flag) flag >>= 1, highbit[i]++;
        highbit[i]--;
    }
    // for(int i=1;i<=n;i++) cout<<node[i].top
    read(m);
    while(m--)
    {
        read(q), read(k);
        q ^= last, k ^= last;
        printf("%d\n",last = find(q,k));
    }
    return 0;
}

