#include<cstring>
#include<iostream>
#include<fstream>
#include<vector>
#define ep 0.00001
#define oo 111111111
#define rep(i, n) for(int i = 0; i < n; i++)
#define FOR(i, a, b) for(int i = a; i <= b; i++)
using namespace std;
typedef long long ll;
 
// Dinic
 
#define maxn 1111
#define maxe 100111
 
struct Dinic{
    int s, t, E, adj[maxe], cap[maxe], flow[maxe], next[maxe], last[maxn],
    que[maxn], level[maxn], run[maxn];
    
    void init(int _s, int _t){
        s = _s; t = _t;
        E = 0; 
        memset(last, -1, sizeof(last));
    } 
    
    void add(int u, int v, int c1, int c2){
        adj[E] = v; cap[E] = c1; flow[E] = 0; next[E] = last[u]; last[u] = E++;
        adj[E] = u; cap[E] = c2; flow[E] = 0; next[E] = last[v]; last[v] = E++;
    }
    
    bool bfs(){
        memset(level, -1, sizeof(level));
        level[s] = 0;
        int size = 0; que[size++] = s;
        rep(i, size){
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
    
    int dfs(int u, int bot){
        if(u == t) return bot;
        for(int &e = run[u]; e != -1; e = next[e]){
            int v = adj[e], delta;
            if(level[v] == level[u] + 1 && flow[e] < cap[e] && (delta = dfs(v, min(bot, cap[e] - flow[e]))) > 0){
                flow[e] += delta;
                flow[e ^ 1] -= delta;
                return delta;
            } 
        }
        return 0;
    }
 
    ll maxflow(){
        ll total = 0;
        while(bfs()){
            memcpy(run, last, sizeof(last));
            for(int delta = dfs(s, oo); delta > 0; delta = dfs(s, oo)) total += delta;
        }
        return total;
    }
 
} dinic;
 
int main(){
   // OPEN();
    //printf("%d",int(ceil(log2(double(2)))));
     int n, m, num, so, u, v;
    ifstream fin;
	fin.open("C:\\Users\\Thien Huong\\OneDrive\\Desktop\\DOAN1\\Bai5\\Data\\1_in.txt",ios_base::in);
	ofstream fout;
	fout.open("C:\\Users\\Thien Huong\\OneDrive\\Desktop\\DOAN1\\Bai5\\Data\\1_out.txt",ios_base::out);
    //fin>>n>>m;
    if(fin.fail()) cout<<"File khong ton tai.";
    else
    {
    	fin>>n>>m;
	    if(m == 1) num = n + 1;
	    else num = n * (2 * m - 2) + 1;
	    dinic.init(0, num);
	    for(int i= 1;i<= n;i++)
		{
	        dinic.add(0, i, 1, 0);
	        dinic.add(num - i, num, 1, 0);
	    }
	   for(int i=0;i<m - 1;i++)
	   {
	       for(int j=1;j<= n;j++){
	            u = i * 2 * n + j;
	            fin>>so;
	            for(int t=0;t<so;t++){
	                fin>>v;
	                v = i * 2 * n + n + v;
	                dinic.add(u, v, 1, 0);    
	            }
	            u = i * 2 * n + n + j;
	            v = (i + 1) * 2 * n + j;
	            if(i < m - 2) dinic.add(u, v, 1, 0);
	        }
	    }
	    //cout<<dinic.maxflow();
	    fout<<dinic.maxflow();
	}
}
