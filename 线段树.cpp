#include <bits/stdc++.h>
#define LL long long
#define int LL
#define P pair<int, int>
const LL N = 1e6 + 10;
const LL mod = 998244353;
const LL inf = 0x3f3f3f3f;
const double eps = 1e-9;
using namespace std;
template <typename tp>
inline void read(tp &x)
{
	x = 0; char c = getchar(); bool f = 0;
	for (; c < '0' || c > '9'; f |= (c == '-'), c = getchar()) ;
	for (; c >= '0' && c <= '9'; x = (x << 3) + (x << 1) + c - '0', c = getchar()) ;
	if (f) x = -x;
}
int n, m;
int val[N << 2], tag[N << 2], vals[N], sum[N << 2];
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
	if (l == r) { read(sum[now]); return; }
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
int query(int now, int l, int r, int ql, int qr)
{
	push_down(now, l, r);
	if (l >= ql && r <= qr) return sum[now];
	if (l > qr || r < ql) return 0;
	int mid = (l + r) >> 1;
	return query(now << 1, l, mid, ql, qr) + query((now << 1) | 1, mid + 1, r, ql, qr);
}
signed main()
{
	read(n), read(m);
	bulit(1, 1, n);
	for (int cas = 1; cas <= m; cas++)
	{
		int opt, x, y, k;
		read(opt), read(x), read(y);
		if (opt == 1)
		{
			read(k);
			change(1, 1, n, x, y, k);
		}
		if (opt == 2)
			printf("%ld\n", query(1, 1, n, x, y));
	}
	return 0;
}
