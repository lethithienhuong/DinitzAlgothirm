#include<math.h>
#include<cstring>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#define oo 111111111
using namespace std;
typedef pair<int, int> II;
typedef vector<int> VI;
// Dinic
#define maxn 1311
#define maxe (1 << 20)
struct Dinic{
    int s, t, E, adj[maxe], cap[maxe], flow[maxe], next[maxe],
    last[maxn], que[maxn], level[maxn], run[maxn];
    
    void init(int _s, int _t)
	{
        s = _s; t = _t; E = 0;
        memset(last, -1, sizeof(last)); //thay cac ki tu cua last = -1
    }
    
    void add(int u, int v, int c1, int c2)
	{
        adj[E] = v; cap[E] = c1; flow[E] = 0; next[E] = last[u]; last[u] = E++;
        adj[E] = u; cap[E] = c2; flow[E] = 0; next[E] = last[v]; last[v] = E++;
    }
    
    bool bfs()
	{
        memset(level, -1, sizeof(level));
        level[s] = 0;
        int size = 0; que[size++] = s;
        for(int i=0;i< size;i++)
		{
            for(int u = que[i], e = last[u]; e != -1; e = next[e]){
                int v = adj[e];
                if(level[v] == -1 && flow[e] < cap[e]){
                    level[v] = level[u] + 1;
                    que[size++] = v;
                }
            }
        }
        return level[t] != -1;
    }
    
    int dfs(int u, int bot)
	{
        if(u == t) return bot;
        for(int &e = run[u]; e != -1; e = next[e]){
            int v = adj[e], delta;
            if(level[v] == level[u] + 1 && flow[e] < cap[e] && (delta = dfs(v, min(bot, cap[e] - flow[e]))) > 0)
			{
                flow[e] += delta;
                flow[e ^ 1] -= delta;
                return delta;
            }
        }
        return 0;
    }
    
    long long maxflow()
	{
        long long total = 0;
        while(bfs()){
            memcpy(run, last, sizeof(last));
            //for(int delta = dfs(s, oo); delta > 0; delta = dfs(s, oo)) total += delta;
			while(int x = dfs(s, oo))	total += x;
        }
        return total;
    } 
}dinic;
 
int n, m, x;
char s[11111];
vector<pair<int, int> > V1[300], V2[300];
 
int main(){
	ifstream fin;
	fin.open("C:\\Users\\Thien Huong\\OneDrive\\Desktop\\DOAN1\\Bai4\\Data\\1_in.txt");
	ofstream fout;
	fout.open("C:\\Users\\Thien Huong\\OneDrive\\Desktop\\DOAN1\\Bai4\\Data\\1_out.txt");
	if(fin.fail()) cout<<"khong ton tai file.";
	else
	{
		fin>>n>>m;
		fin.ignore();//xoa bo nho dem(ki tu enter)
	    dinic.init(0, 2 * n + 2 * m + 1);
	    for(int i=1;i<= m;i++) dinic.add(n + i, n + m + i, 1, 0);
	    for(int i=1;i<= n;i++) dinic.add(0, i, 1, 0);
	    for(int i=1;i<= n;i++) dinic.add(n + m + m + i, n + n + m + m + 1, 1, 0);
	    for(int i=1;i<= n;i++)
		{	
	    	fin.getline(s,255);
	    	istringstream iss(s);
	      while(iss >> x)
			{
	            V1[x].push_back(make_pair(dinic.E, i));
	            dinic.add(i, n + x, 1, 0);
	        }
	    }
	    for(int i=1;i<= n;i++)
		{
			fin.getline(s, 255);
	    	istringstream iss(s);
	        while(iss >> x)
			{
	            V2[x].push_back(make_pair(dinic.E, i));
	            dinic.add(n + m + x, n + m + m + i, 1, 0);
	        }
	    }
	    dinic.maxflow();
	    for(int i=1;i<= m;i++)
		{
	        int t1 = 0, t2 = 0;
	        for(int j=0;j< (V1[i].size());j++) if(dinic.flow[V1[i][j].first]) t1 = V1[i][j].second;
	        for(int j=0;j< (V2[i].size());j++) if(dinic.flow[V2[i][j].first]) t2 = V2[i][j].second;
	        cout<<t1<<" "<<t2<<"\n";
	        fout<<t1<<" "<<t2<<"\n";
    	}
	}
}
 
