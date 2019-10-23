#pragma GCC diagnostic error "-std=c++11"
#pragma GCC target("avx")
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include<set>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<cstdio>
#include<time.h>
#include<vector>
#include<cstring>
#include<stdlib.h>
#include<iostream>
#include<algorithm>
#define LL long long
using namespace std;
const LL N=1e4+10;
const LL mod=1e9+7;
const LL inf=0x3f3f3f3f;
namespace FastIO
{
    template<typename tp> inline void read(tp &x)
    {
        x=0; register char c=getchar(); register bool f=0;
        for(;c<'0'||c>'9';f|=(c=='-'),c = getchar());
        for(;c>='0'&&c<='9';x=(x<<3)+(x<<1)+c-'0',c = getchar());
        if(f) x=-x;
    }
    template<typename tp> inline void write(tp x)
    {
        if (x==0) return (void) (putchar('0'));
        if (x<0) putchar('-'),x=-x;
        LL pr[20]; register LL cnt=0;
        for (;x;x/=10) pr[++cnt]=x%10;
        while (cnt) putchar(pr[cnt--]+'0');
    }
    template<typename tp> inline void writeln(tp x)
    {
        write(x);
        putchar('\n');
    }
}
using namespace FastIO;
struct High_precision
{
    int a[10000],len;
    bool minus;
    High_precision(int x = 0 )
    {
        for(int i=0;i<10000;i++)
            a[i]=0;
        len=0;
        while(x)
        {
            a[++len]=x%10;
            x/=10;
        }
        minus=0;
    }
    bool operator < (High_precision b) const
    {
        if(len==b.len)
        {
            for(int i=len;i>=1;i--)
                if(a[i]<b.a[i]) return true;
                else if(a[i]>b.a[i]) return false;
            return false;
        }
        return len<b.len;
    }
    void equal (High_precision b)
    {
        len=b.len;
        for(int i=1;i<=len;i++)
            a[i]=b.a[i];
        minus=b.minus;
    }
    High_precision operator + (High_precision b)
    {
        High_precision ans;
        ans.len=max(len,b.len)+1;
        for(int i=1;i<=ans.len;i++)
        {
            ans.a[i]+=a[i]+b.a[i];
            ans.a[i+1]+=ans.a[i]/10;
            ans.a[i]%=10;
        }
        while(ans.len>1&&!ans.a[ans.len])
            ans.len--;
        return ans;
    }
    High_precision operator - (High_precision b)
    {
        if(*this<b)
        {
            High_precision ans=b-(*this);
            ans.minus=1;
            return ans;
        }
        High_precision ans;
        ans.len=max(len,b.len);
        for(int i=1;i<=ans.len;i++)
        {
            if(a[i]<b.a[i])
            {
                a[i+1]--;
                a[i]+=10;
            }
            ans.a[i]+=a[i]-b.a[i];
        }
        while(ans.len>1&&!ans.a[ans.len])
            ans.len--;
        return ans;
    }
    High_precision operator * (High_precision b)
    {
        High_precision ans;
        ans.len=len+b.len;
        for(int i=1;i<=b.len;i++)
        {
            for(int j=1;j<=len;j++)
            {
                ans.a[i+j-1]+=b.a[i]*a[j];
                ans.a[i+j]+=ans.a[i+j-1]/10;
                ans.a[i+j-1]%=10;
            }
            if(ans.a[b.len+len])
            {
                ans.a[b.len+len+1]+=ans.a[b.len+len]/10;
                ans.a[b.len+len]%=10;
            }
        }
        while(ans.len>1&&!ans.a[ans.len])
            ans.len--;
        return ans;
    }
    High_precision operator / (const int &b)
    {
        if(*this<High_precision(b)) return High_precision(0);
        High_precision ans;
        ans.len=len;
        int r=0;
        for(int i=ans.len;i>=1;i--)
        {
            r=r*10+a[i];
            ans.a[i]=r/b;
            r%=b;
        }
        while(ans.len>1&&!ans.a[ans.len])
            ans.len--;
        return ans;
    }
    High_precision operator /(High_precision b)
    {
        if(*this<b) return High_precision(0);
        High_precision ans;
        ans.len=len-b.len+1;
        for(int i=ans.len;i>=1;i--)
        {
            for(int j=1;j<=9;j++)
            {
                ans.a[i]++;
                if(*this<(ans*b))
                {
                    ans.a[i]--;
                    break;
                }
            }
            if(ans.a[ans.len]==0)
                ans.len--;
        }
        while(ans.len>1&&!ans.a[ans.len])
            ans.len--;
        return ans;
    }
    void in()//输入->a.in();
    {
        string s;
        cin>>s;
        len=s.length();
        for(int i=0;i<len;i++)
            a[len-i]=s[i]-'0';
    }
    void out(bool h)//输出->a.out(1);
    {
        if(minus) printf("-");
        for(int i=len;i>=1;i--)
            printf("%d",a[i]);
        if(h) printf("\n");
    }
};
main()
{
    return 0;
}

