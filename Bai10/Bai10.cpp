#include <cstdio>
#include <vector>
#include <algorithm>
#include<iostream>
#include<fstream>
using namespace std;
const int INF = 1e9 +7;
int N, M;
struct Edge {//tao canh
    int from, to, cap, flow, index;
    Edge(int from, int to, int cap, int flow, int index) :
        from(from), to(to), cap(cap), flow(flow), index(index) {}
};

struct Dinic {//xay dung do thi
    int N;
    vector<vector<Edge> > G;
    vector<Edge *> dad;
    vector<int> Q;
    // N = so dinh
    Dinic(int N) : N(N), G(N), dad(N), Q(N) {}
  	// them 1 canh tu mang ban dau tu s den t
    void AddEdge(int from, int to, int cap) {
        G[from].push_back(Edge(from, to, cap, 0, G[to].size()));
        if (from == to) G[from].back().index++;
        G[to].push_back(Edge(to, from, 0, 0, G[from].size() - 1));// them 1 phan tu dau tien
    }
	//Xoa bo luong khong nam trong luong cuc dai
     int BlockingFlow(int s, int t) {// dfs
        fill(dad.begin(), dad.end(), (Edge *) NULL);
        dad[s] = &G[0][0] - 1;
    
        int head = 0, tail = 0;
        Q[tail++] = s;
        while (head < tail) {
            int x = Q[head++];
            for (int i = 0; i < G[x].size(); i++) {
                Edge &e = G[x][i];
                if (!dad[e.to] && e.cap - e.flow > 0) {
                    dad[e.to] = &G[x][i];
                    Q[tail++] = e.to;
                }
            }
        }
        if (!dad[t]) return 0;

        int totflow = 0;
        for (int i = 0; i < G[t].size(); i++) {
            Edge *start = &G[G[t][i].to][G[t][i].index];
            int amt = INF;
            for (Edge *e = start; amt && e != dad[s]; e = dad[e->from]) {
                if (!e) { amt = 0; break; }
                amt = min(amt, e->cap - e->flow);
            }
            if (amt == 0) continue;
            for (Edge *e = start; amt && e != dad[s]; e = dad[e->from]) {
                e->flow += amt;
                G[e->to][e->index].flow -= amt;
            }
            totflow += amt;
        }
        return totflow;
    }
	//Goi luong cuc dai. s,t dua vao 0
    // de thanh luong phai xet tat ca cac canh ke voi no
    // dung luong > 0 (dung luong bang 0 la canh du).

    int GetMaxFlow(int s, int t) {
        int totflow = 0;
        while (int flow = BlockingFlow(s, t))
            totflow += flow;
        return totflow;
    }
};
int main() {
	ifstream fin;
	fin.open("C:\\Users\\Thien Huong\\OneDrive\\Desktop\\DOAN1\\Bai10\\Data\\text1.txt",ios_base::in);
	ofstream fout;
	fout.open("C:\\Users\\Thien Huong\\OneDrive\\Desktop\\DOAN1\\Bai10\\Data\\outtext1.txt",ios_base::out);
	if(fin.fail()) cout<<"File kh ton tai";
    else{
    	fin>>N>>M;
    	Dinic D(N);
    	for(int i = 1;i <= M;i++){
        	int A, B, C;
        	fin>>A>>B>>C;
        	D.AddEdge(A-1, B-1, C);
        	D.AddEdge(B-1, A-1, C);
    	}
    	fout<<D.GetMaxFlow(0,N-1);
		fout.close();
    	//cout<<D.GetMaxFlow(0,N-1)<<"\n";
	}
    return 0;
}
