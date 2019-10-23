namespace Graham
{
	int n;
	struct Node{double x,y;int name;}node[N];
	vector<Node> v;
	void read_node()
	{
		for(int i=0;i<n;i++)
		{
			scanf("%lf%lf",&node[i].x,&node[i].y);
			if(node[i].y<node[0].y)
				swap(node[i].x,node[0].x),swap(node[i].y,node[0].y);
		}
		n--;
	}
	double Cross_product(Node a,Node b,Node c){return (b.x-a.x)*(c.y-b.y)-(c.x-b.x)*(b.y-a.y);}
	bool cmp(Node a,Node b)
	{
		double angle=(a.x-node[0].x)*(b.y-node[0].y)-(b.x-node[0].x)*(a.y-node[0].y);
		if(angle==0)return abs(a.x-node[0].x)<abs(b.x-node[0].x); 
		if(angle<0)return false;
		return true;
	}
	double solve()
	{
		double ans=0;v.push_back(node[0]);
		sort(node+1,node+n+1,cmp);
		for(int i=1;i<=n;i++)
		{
			while(v.size()>1&&Cross_product(v[v.size()-2],v[v.size()-1],node[i])<=0) 
				v.pop_back();
			v.push_back(node[i]);
		}
		v.push_back(node[0]);
		for(int i=0;i<v.size()-1;i++)
			ans+=sqrt(pow(abs(v[i].x-v[i+1].x),2)+pow(abs(v[i].y-v[i+1].y),2));
		return ans;
	}
}
using namespace Graham;
