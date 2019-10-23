// luogu-judger-enable-o2
#pragma GCC optimize("3,Ofast")
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
LL T,n,maxn,sb;
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
	for(int i=1;i<=10;i++)
	{
		LL rnd=rand()%(p-1)+1;
		if(witness(rnd,p))
			return false;
	}
	return true;
}
LL times(LL a,LL b,LL p,LL ret=0)
{
	while(b)
	{
		if(b&1) ret=(ret+a);
		ret>p?ret-=p:0;
		b>>=1;
		(a<<=1)>p?a-=p:0;
	}
	return ret;
}
LL f(LL x,LL seed,LL p,LL ret=0) 
{
	ret=times(x,x,p);
	ret=(ret+seed)%p;
	return ret;
}
LL pollard_rho(LL p,LL seed)
{
	for(LL x=rand(),y=x,cnt=1,up=2;;)
	{
		x=f(x,seed,p);
		if(x==y) return p;
		LL flag=__gcd(abs(x-y),p);
		if(1<flag&&flag<p) return flag;
		if(++cnt==up)
			y=x,up<<=1;
	}
}
void work(LL p)
{
	if(p==1) return;
	if(maxn>=p) return;
	if(miller_rabin(p))
	{
		maxn=p;
		return;
	}
	LL x=p;
	while(x>=p) 
		x=pollard_rho(x,rand()%(n-1)+1);
	while(p>=x&&p%x==0)
	{
		p/=x;
		if(p<x) break;
	}
	work(p);
	work(x);
}
signed main()
{
	srand(time(0));
	read(T);
	while(T--)
	{
		read(n);maxn=0;
		if(miller_rabin(n)) 
		{
			puts("Prime");
			continue;
		}
		work(n);
		printf("%lld\n",maxn);
	}
	return 0;
}

