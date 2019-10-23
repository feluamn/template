#pragma GCC optimize("2,Ofast,inline")
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
namespace _FFT
{
	const double pi = acos(-1.0);
    int A, B, n, L, R[N];
    struct C
    {
        double r, i;
        C(){}
        C(double a,double b) {r=a; i=b;}
        C operator + (C x) { return C(r + x.r, i + x.i);}
        C operator - (C x) { return C(r - x.r, i - x.i);}
        C operator * (C x) { return C(r * x.r - i * x.i, r * x.i + i * x.r);}
    } w[N], a[N], b[N];
	void init()
	{
		for(n=1,L=0;n<=A+B;n<<=1,L++);
		for(int i=0;i<n;i++)
		{
			R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
			w[i]=C(cos(2.0*i*pi/n),sin(2.0*i*pi/n));
		}
	}
    void FFT(C x[], int n)
    {
        for (int i = 0; i < n; i++)
            if (R[i] > i)
                swap(x[R[i]], x[i]);
        for (int t = n >> 1, d = 1; d < n; d <<= 1, t >>= 1)
            for (int i = 0; i < n; i += (d << 1))
                for (int j = 0; j < d; j++)
                {
                    C tmp = w[t * j] * x[i + j + d];
                    x[i + j + d] = x[i + j] - tmp;
                    x[i + j] = x[i + j] + tmp;
                }
    }
	void IFFT(C x[],C y[],int n)
	{
		for(int i=0;i<n;i++)
			x[i]=x[i]*y[i],w[i].i=-w[i].i;
	    FFT(x,n);
	}
}
using namespace _FFT;
signed main()
{
    read(A),read(B);A++,B++;
    for(int i=0;i<A;i++) scanf("%lf",&a[i].r);
    for(int i=0;i<B;i++) scanf("%lf",&b[i].r);
	init();
    FFT(a,n);FFT(b,n);
	IFFT(a,b,n);
    for(int i=0;i<=A+B-2;i++)
        printf("%d ",int(a[i].r/n+0.5));
    return 0;
}
