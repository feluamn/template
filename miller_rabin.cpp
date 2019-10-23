#include <bits/stdc++.h>
#define LL long long
#define P pair<int, int>
#define Fengexian cout<<"WZY%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl
const LL N = 1e5 + 10;
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
int n,m;
LL KSM(LL a,LL b,LL p,LL ret=1)
{
	while(b)
	{
		if(b&1) ret=ret*a%p;
		a=a*a%p;
		b>>=1;
	}
	return ret;
}
bool witness(LL a,LL p)
{
	LL s=0,t=p-1;
	while(!(t&1))
		t>>=1,s++;
	LL x=KSM(a,t,p);
	if(x==1||x==p-1) return false;
	while(s--)
	{
		x=x*x%p;
		if(x==p-1) return false;
	}
	return true;
}
bool miller_rabin(LL p)
{
	if(p==2) return true;
	if(p==1||p%2==0) return false;
	for(int i=1;i<=20;i++)
	{
		LL rnd=rand()%(p-1)+1;
		if(witness(rnd,p))
			return false;
	}
	return true;
}
signed main()
{
	srand(time(0));
	read(m),read(n);
	for(int i=1,p;i<=n;i++)
	{
		read(p);
		if(miller_rabin(p)) puts("Yes");
		else puts("No");
	}
	return 0;
}

