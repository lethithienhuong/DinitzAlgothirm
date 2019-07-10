#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<queue>
#define maxn 1005
using namespace std;
int n,m,res,s,t;// n : so dinh, n : so canh, res:gia tri cua luong,s:chi so dinh phat, t: chi so dinh thu
struct data
{
    int v,f,c;// v : cung; f : gia tri luong; c : kha nang thong qua
};
vector <data> e;// e : do thi
vector<int>g[maxn];// g : ma tran chua cung va kha nang thong qua
int dd[maxn],cnt,dist[maxn],pos[maxn];// dd:ma tran chua cac dinh da xet,cnt:dinh da xet;
//d:do dai duong di ngan nhat;pos:xau
int addE(int u,int v,int w){
	g[u].push_back(e.size());//day u ra neu dinh cuoi khac t
        data x;//do thi x
        x.v=v;
        x.c=w;
        x.f=0;
        e.push_back(x);
        g[v].push_back(e.size());
        x.v=u;
        x.c=0;
        x.f=0;
        e.push_back(x);
}
bool bfs()// tim kiem theo chieu rong
{
    queue<int> q;// hang doi q chua danh sach cac dinh cho duyet
    dd[s]=++cnt;
    while(!q.empty()) q.pop();// neu q con dinh lay dinh ra khoi hang doi
    q.push(s);//day dinh s vao hang doi
    while(!q.empty())
    {
        int u=q.front();// tra ve 1 hang so tham chieu trong hang doi
        pos[u]=0;
        q.pop();
        for (int i=0; i<(int)g[u].size(); ++i)
        {
            int id=g[u][i];// kha nang thong qua con du
            int v=e[id].v;
            if (e[id].f==e[id].c||dd[v]==cnt) continue;
            dd[v]=cnt;
            dist[v]=dist[u]+1;//do thi tang
            q.push(v);
        }
    }
    return dd[t]==cnt;
}
int dfs(int u,int low)// tim kiem theo chieu sau
{
    if (u==t||low==0) return low;// u : dinh da ghe tham; low:
    for (; pos[u]<g[u].size(); ++pos[u])
    {
        int id=g[u][pos[u]];
        int v=e[id].v;
        if (dist[v]!=dist[u]+1||e[id].f==e[id].c) continue;
        int get=dfs(v,min(low,e[id].c-e[id].f));//dinh ke duoc xet
        if (get)
        {
	        e[id].f+=get;// neu thong qua them dinh get khong thi loai
	        e[id^1].f-=get;
	    	return get;
        }
    }
    return 0;
}
int main()
{
	ifstream fin;
	fin.open("C:\\Users\\Thien Huong\\OneDrive\\Desktop\\DOAN1\\Bai9\\Data\\text1.txt",ios_base::in);
	ofstream fout;
	fout.open("C:\\Users\\Thien Huong\\OneDrive\\Desktop\\DOAN1\\Bai9\\Data\\outtext1.txt",ios_base::out);
	if(fin.fail()) cout<<"File kh ton tai";
    else{
    	fin>>n>>m>>s>>t;
    	for (int i=1; i<=m; ++i)
    	{
        int u,v,w;
        fin>>u>>v>>w;
        addE(u,v,w);
    	}	
    }
    
    while(bfs())
    {
    	while(int x=dfs(s,10000000))
        {
            res+=x;
        }
    }
    fout<<res;
    fout.close();
    cout<<res;
    return 0;
}
