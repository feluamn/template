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
int n, m, p;
namespace HLD
{
    //SegmentTree
    int val[N << 2], vals[N];LL sum[N << 2], tag[N << 2];
    void push_down(int now, int l, int r)
    {
        int mid = (l + r) >> 1;
        sum[now << 1] += tag[now] * (mid - l + 1);
        tag[now << 1] += tag[now];
        sum[(now << 1) | 1] += tag[now] * (r - mid);
        tag[(now << 1) | 1] += tag[now];
        tag[now] = 0;
    }
    void bulit(int now, int l, int r)
    {
        if (l == r) { sum[now]=vals[l]; return; }
        int mid = (l + r) >> 1;
        bulit(now << 1, l, mid);
        bulit((now << 1) | 1, mid + 1, r);
        sum[now] = sum[now << 1] + sum[(now << 1) | 1];
    }
    void change(int now, int l, int r, int ql, int qr, int k)
    {
        if (l >= ql && r <= qr) { sum[now] += (r - l + 1) * k; tag[now] += k; return; }
        if (l > qr || r < ql) return;
        push_down(now,l,r);
        int mid = (l + r) >> 1;
        change(now << 1, l, mid, ql, qr, k);
        change((now << 1) | 1, mid + 1, r, ql, qr, k);
        sum[now] = sum[now << 1] + sum[(now << 1) | 1];
    }
    LL query(int now, int l, int r, int ql, int qr)
    {
        push_down(now, l, r);
        if (l >= ql && r <= qr) return sum[now];
        if (l > qr || r < ql) return 0;
        int mid = (l + r) >> 1;
        return query(now << 1, l, mid, ql, qr) + query((now << 1) | 1, mid + 1, r, ql, qr);
    }
    //HLD
    int head[N], cnt, dfns, chains, rt, top[N];
    struct Node { int siz, fa, depth, dfn, max_son, chain, max_dfn; } node[N];
    struct Edge { int next, to;} edge[N];
    void add(int from, int to) { edge[++cnt] = {head[from], to}; head[from] = cnt;}
    void insert(int from, int to) { add(from, to); add(to, from);}
    void dfs1(int now)
    {
        node[now].siz = 1;
        for (int i = head[now]; i; i = edge[i].next)
        {
            int to = edge[i].to;
            if (to == node[now].fa) continue;
            node[to].fa = now; node[to].depth = node[now].depth + 1;
            dfs1(to);
            node[now].siz += node[to].siz;
            if (!node[now].max_son || node[node[now].max_son].siz < node[to].siz)
                node[now].max_son = to;
        }
    }
    void dfs2(int now)
    {
        node[now].dfn = node[now].max_dfn = ++dfns;
        if (!node[now].fa || node[node[now].fa].max_son != now)
            node[now].chain = ++chains, top[chains] = now;
        else
            node[now].chain = node[node[now].fa].chain;
        if (node[now].max_son)
            dfs2(node[now].max_son),node[now].max_dfn=node[node[now].max_son].max_dfn;
        for (int i = head[now]; i; i = edge[i].next)
        {
            int to = edge[i].to;
            if (to == node[now].fa || to == node[now].max_son) continue;
            dfs2(to);
            node[now].max_dfn = max(node[to].max_dfn, node[now].max_dfn);
        }
    }
    void split()
    {
        node[rt].depth = 1;
        dfs1(rt); dfs2(rt);
    }
    void add_chain(int x, int y, int k)
    {
        while (node[x].chain != node[y].chain)
        {
            if (node[top[node[x].chain]].depth < node[top[node[y].chain]].depth) swap(x, y);
            change(1, 1, n, node[top[node[x].chain]].dfn, node[x].dfn, k);
            x = node[top[node[x].chain]].fa;
        }
        if (node[x].depth > node[y].depth) swap(x, y);
        change(1, 1, n, node[x].dfn, node[y].dfn, k);
    }
    LL get_sum(int x, int y, LL ret = 0)
    {
        while (node[x].chain != node[y].chain)
        {
            if (node[top[node[x].chain]].depth < node[top[node[y].chain]].depth) swap(x, y);
            ret += query(1, 1, n, node[top[node[x].chain]].dfn, node[x].dfn);
            x = node[top[node[x].chain]].fa;
        }
        if (node[x].depth > node[y].depth) swap(x, y);
        ret += query(1, 1, n, node[x].dfn, node[y].dfn);
        return ret % p;
    }
} // namespace HLD
using namespace HLD;
signed main()
{
    read(n), read(m), read(rt), read(p);
    for (int i = 1; i <= n; i++) read(val[i]);
    for (int i = 1, u, v; i < n; i++) read(u), read(v), insert(u, v);
    split();
    for(int i=1;i<=n;i++) vals[node[i].dfn]=val[i];
    bulit(1, 1, n);
    for (int cas = 1; cas <= m; cas++)
    {
        int opt, x, y, z; read(opt);
        if (opt == 1) { read(x), read(y), read(z); add_chain(x, y, z); }
        if (opt == 2) { read(x), read(y); printf("%lld\n", get_sum(x, y)); }
        if (opt == 3) { read(x), read(y); change(1, 1, n, node[x].dfn, node[x].max_dfn, y); }
        if (opt == 4) { read(x); printf("%lld\n", query(1, 1, n, node[x].dfn, node[x].max_dfn) % p);}
    }
    return 0;
}
