#pragma GCC optimize("2,Ofast,inline")
#include <bits/stdc++.h>
#define LL long long
#define P pair<int, int>
const LL N = 1e6 + 10;
const LL inf = 2147483647;
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
namespace _NTT
{
    int A, B, n, L, R[N];
    LL a[N], b[N], w[N];
    LL KSM(LL a, LL b, LL ret = 1)
    {
        while (b)
        {
            if (b & 1)
                ret = ret * a % mod;
            a = a * a % mod;
            b >>= 1;
        }
        return ret;
    }
    void NTT(LL x[], int n)
    {
        for (int i = 0; i < n; i++)
            if (R[i] > i)
                swap(x[R[i]], x[i]);
        for (int t = n >> 1, d = 1; d < n; d <<= 1, t >>= 1)
            for (int i = 0; i < n; i += (d << 1))
                for (int j = 0; j < d; j++)
                {
                    LL tmp = w[t * j] * x[i + j + d] % mod;
                    x[i + j + d] = (x[i + j] - tmp + mod) % mod;
                    x[i + j] = (x[i + j] + tmp) % mod;
                }
    }
}
using namespace _NTT;
string str;
signed main()
{
    cin>>str; A = str.length();
    for (int i = 0; i < A; i++) a[i] = str[A - i - 1] - '0';
    cin >> str; B = str.length();
    for (int i = 0; i < B; i++) b[i] = str[B - i - 1] - '0';
    for (n = 1, L = 0; n <= A + B; n <<= 1, L++) ;
    for (int i = 0; i < n; i++) R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));
    w[0] = 1; w[1] = KSM(3, (mod - 1) / n);
    for (int i = 2; i < n; i++) w[i] = w[i - 1] * w[1] % mod;
    NTT(a, n); NTT(b, n);
    for (int i = 0; i < n; i++) a[i] = a[i] * b[i];
    w[0] = 1; w[1] = KSM(w[1], mod - 2);
    for (int i = 2; i < n; i++) w[i] = w[i - 1] * w[1] % mod;
    NTT(a, n);
    LL inv = KSM(n, mod - 2);
    for (int i = 0; i < n; i++) a[i] = a[i] * inv % mod;
    for (int i = 0; i < n - 1; i++) a[i + 1] += a[i] / 10, a[i] %= 10;
    for (int i = n, flag = 0; i >= 0; i--)
    {
        if (a[i]) flag = 1;
        if (flag) printf("%d", a[i]);
    }
    puts("");
    return 0;
}
