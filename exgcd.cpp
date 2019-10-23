LL n,m,d=100000000000000000,x,y;
void ext_gcd(LL a,LL b,LL &d,LL &x,LL &y)
{
    if (b==0)
    {
        d=a;x=1;y=0;
        return;
    }
    ext_gcd(b,a%b,d,y,x);
    y-=a/b*x;
}
main()
{
    read(m),read(n);
    ext_gcd(m,n,d,x,y);
    if((x+n)%n*m%n!=1)
        return 0*puts("-1\n");
    writeln((x+n)%n);
    return 0;
}
