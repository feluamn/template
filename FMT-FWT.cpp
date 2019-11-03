namespace FWT
{
	int inv2;
	LL KSM(int a,int b,LL ret=1) { while(b) { if(b&1) ret=ret*a%mod; a=a*a%mod; b>>=1;} return ret;}
	void add(int &a,int b) {a+=b; a-=(a>=mod?mod:0); a+=(a<0?mod:0);}
	void FWT_AND(int n,int *a,int sign)
	{
		for(int l=2,m=l>>1;l<=n;l<<=1,m=l>>1)
			for(int i=0;i<n;i+=l)
				for(int j=0;j<m;j++)
					add(a[i+j],sign*a[i+j+m]);
	}
	void FWT_OR(int n,int *a,int sign)
	{
		for(int l=2,m=l>>1;l<=n;l<<=1,m=l>>1)
			for(int i=0;i<n;i+=l)
				for(int j=0;j<m;j++)
					add(a[i+j+m],sign*a[i+j]);
	}
	void FWT_XOR(int n,int *a,int sign)
	{
		inv2=KSM(2,mod-2);
		for(int l=2,m=l>>1;l<=n;l<<=1,m=l>>1)
			for(int i=0;i<n;i+=l)
				for(int j=0;j<m;j++)
				{
					int x=a[i+j],y=a[i+j+m];
					a[i+j]=x+y,a[i+j+m]=(x-y);
					if(sign==-1)
					{
						a[i+j]=a[i+j]*inv2%mod;
						a[i+j+m]=a[i+j+m]*inv2%mod;
					}
				}
	}
	/*
	void solve(int n,int *a,int *b)
	{
		AND/OR/XOR(n,a,1);
		AND/OR/XOR(n,b,1);
		for(int i=0;i<n;i++) a[i]=a[i]*b[i]%mod;
		AND/OR/XOR(n,a,-1);
	}
	*/
};
namespace FMT
{
	void FMT(int n,int *a,int sign)
	{
		int m=1<<n;
		for(int j=0;j<n;j++)
			for(int i=0;i<m;i++)
				if(i>>j&1)
					a[i]+=sign*a[i^1<<j];
	}
	void subset_conv(int n,int (*f)[1<<20],int (*g)[1<<20],int (*h)[1<<20]) //子集卷积
	{
		int m=1<<n;
		for(int i=0;i<=n;i++)
		{
			FMT(n,f[i],1),FMT(n,g[i],1);
			for(int s=0;s<m;s++)
				for(int j=0;j<=i;j++)
					h[i][s] = (1ll * f[j][s] * g[i-j][s] + h[i][s]) % mod;
			FMT(n,h[i],-1);
		}
		// for each s : h_s = h[__builtin_popcount(s)][s])
	}	
};
