#include <iostream>
#include <vector>
#include <fstream>
#include <list>
#include <queue>
#define maxn 1000
using namespace std;
int n,m,total,s,t;
struct data
{
    int v,f,c;// v : cung; f : gia tri luong; c : kha nang thong qua
};
vector <data> e;// e : do thi
vector<int>g[maxn];// g : ma tran chua cung va kha nang thong qua
int dd[maxn],cnt,d[maxn],pos[maxn];
queue<int> q;
bool bfs()
{
    		// hang doi chua cac nut se duyet
    dd[s]=++cnt;		// mang chua cac nut da duyet
    while(!q.empty()) q.pop();
    q.push(s);
    while(!q.empty())
    {
        int u=q.front();
        pos[u]=0;
        q.pop();
        for (int i=0; i<(int)g[u].size(); i++)
        {
            int id=g[u][i];
            int v=e[id].v;
            if (e[id].f==e[id].c||dd[v]==cnt) continue;
            dd[v]=cnt;
            d[v]=d[u]+1;
            q.push(v);
        }
    }
    return dd[t]==cnt;
}
int dfs(int u,int flow)
{
    if (u==t||flow==0) return flow;
    for (pos[u]<0; pos[u]<g[u].size(); pos[u]++)
    {
        int id=g[u][pos[u]];
        int v=e[id].v;
        if (d[v]!=d[u]+1||e[id].f==e[id].c) continue;
        int get=dfs(v,min(flow,e[id].c-e[id].f));
        if (get)
        {
	        e[id].f+=get;
	        e[id^1].f-=get;
	    	return get;
        }
    }
    return 0;
}
void addE(int u,int v,int c)
{
	g[u].push_back(e.size());
	data x;
	x.v=v;
	x.c=c;
	x.f=0;
	e.push_back(x);
	g[v].push_back(e.size());
	x.v=u;
	x.c=0;
	x.f=0;
	e.push_back(x);
}
long long maxflow()
{
	    while(bfs())
	    {
	    	while(int x=dfs(s,t))
	        {
	            total+=x;
	        }
	    }
		return total;
}
int main()
{
	ifstream fin;
	fin.open("C:\\Users\\Thien Huong\\OneDrive\\Desktop\\DOAN1\\Bai1\\Data\\1_in.txt",ios_base::in);
	ofstream fout;
	fout.open("C:\\Users\\Thien Huong\\OneDrive\\Desktop\\DOAN1\\Bai1\\Data\\1_out.txt",ios_base::out);
    fin>>m>>n;
    if(fin.fail()) cout<<"File khong ton tai.";
    else
	{
    	int a[maxn],d=0;
	    for (int i=0; i<m; ++i)
	    {
	        int u,v,w;
	        fin>>u>>v>>w;
	        a[i]=u;
	        addE(u,v,w);
	    }
	    for(int i=0;i<m;i++)if (a[i]==0)	d=1;
	    if(d==0)
	    {
	    	s=1;	t=n;
		}
	    else 
		{
	    	s=0;	t=n-1;
		}
		cout<<maxflow();
		fout<<maxflow();
	}
    return 0;
}
