#include<iostream>
#include<vector>
#include<queue>
#include<assert.h>
#include<fstream>
#define MAX   111
#define FORE(i,v) for (__typeof((v).begin()) i=(v).begin();i!=(v).end();i++)
#define fi   first
#define se   second
using namespace std;
const int INF=(int)1e9+7;
typedef pair<int,int> ii;
class DinicFlow {
	private:	
	vector<int> dist,head,q,work;
	vector<int> capa,flow,next,point;
	int n,m;
	public:
	DinicFlow() {
		n=0;m=0;
	}
	DinicFlow(int n,int _m) {
		this->n=n;
		this->m=0;
		dist=vector<int>(n+7);
		head=vector<int>(n+7,-1);
		q=vector<int>(n+7);
		work=vector<int>(n+7);
		int m=2*_m;
		capa=vector<int>(m+7);
		flow=vector<int>(m+7,0);
		next=vector<int>(m+7);
		point=vector<int>(m+7);
	}
	void addedge(int u,int v,int c1,int c2) {
		point[m]=v;capa[m]=c1;flow[m]=0;next[m]=head[u];head[u]=m;m++;
		point[m]=u;capa[m]=c2;flow[m]=0;next[m]=head[v];head[v]=m;m++;		
	}
	bool bfs(int s,int t) {
		FORE(it,dist) *it=-1;
		int sz=1;
		q[0]=s;dist[s]=0;
		for(int x = 0;x<sz;x++) {
			int u=q[x];
			for (int i=head[u];i>=0;i=next[i])
				if (dist[point[i]]<0 && flow[i]<capa[i]) {
					dist[point[i]]=dist[u]+1;
					q[sz]=point[i];
					sz++;
				}
		}
		return (dist[t]>=0);
	}
	int dfs(int s,int t,int f) {
		if (s==t) return (f);
		for (int &i=work[s];i>=0;i=next[i])
			if (dist[point[i]]==dist[s]+1 && flow[i]<capa[i]) {
				int d=dfs(point[i],t,min(f,capa[i]-flow[i]));
				if (d>0) {
					flow[i]+=d;
					flow[i^1]-=d;
					return (d);
				}
			}
		return 0;
	}
	int maxflow(int s,int t,vector<int> &v) {
		int ret=0;
		while (bfs(s,t)) {
			for(int i=1;i<=n;i++) work[i]=head[i];
			while (true) {
				int d=dfs(s,t,INF);
				if (d<=0) break;
				ret+=d;
			}
		}
		v.clear();
		for(int i=1;i<=n;i++) if (dist[i]>=0) v.push_back(i);
		//printf("MaxFlow %d\n",ret);
		return ret;
	}
};
vector<ii> g[MAX];
int d[MAX];
bool src[MAX];
int n,m,s,t;
void loadgraph(void) {
	ifstream fin;
	fin.open("C:\\Users\\Thien Huong\\OneDrive\\Desktop\\DOAN1\\Bai7\\Data\\text1.txt",ios_base::in);
	if(fin.fail()) cout<<"File kh ton tai"
    else{
    	fin>>n>>m;
		for(int i=0;i<m;i++) {
			int u,v,c;
			fin>>u>>v>>c;
			g[u].push_back(ii(v,c));
			g[v].push_back(ii(u,c));
		}
		fin>>s>>t;
	}
	
}
bool bfs(int s,int t,int x) {
	queue<int> q;
	while (!q.empty()) q.pop();
	memset(d,-1,sizeof d);
	q.push(s);
	d[s]=0;
	while (!q.empty()) {
		int u=q.front();q.pop();
		if (u==t) return (true);
		FORE(it,g[u]) if (it->se>x) {
			int v=it->fi;
			if (d[v]<0) {
				d[v]=d[u]+1;
				q.push(v);
			}
		}
	}
	return false;
}
int findtime(void) {
	int l=0;
	int r=INF;
	while (true) {
		if (l==r) return (r);
		if (r-l==1) {
			if (!bfs(s,t,l)) return (l);
			else return (r);
		}
		int m=(l+r)>>1;
		if (!bfs(s,t,m)) r=m;
		else l=m+1;
	}
}
void process(void) {
	ofstream fout;
	fout.open("C:\\Users\\Thien Huong\\OneDrive\\Desktop\\DOAN1\\Bai7\\Data\\outtext1.txt",ios_base::out);
	int ans=findtime();	
	DinicFlow G=DinicFlow(n,m);
	for(int i=1;i<=n;i++) FORE(it,g[i]) {
		int j=it->fi;
		int cst;
		if (it->se<=ans) cst=1; else cst=INF;
		if (i<j) G.addedge(i,j,cst,cst);
	}
	vector<int> v;	
	vector<ii> res;
	assert(G.maxflow(s,t,v)<INF);	
	FORE(it,v) src[*it]=true;
	FORE(it,v) FORE(jt,g[*it]) if (!src[jt->fi]) res.push_back(ii(*it,jt->fi));
	if(fout.fail()) cout<<"file out kh ton tai";
	else{
		//cout<<res.size() << "\n";
		fout<< res.size() << "\n";
		FORE(it,res) {
			//cout<< it->fi<<" "<<it->se << "\n";
			fout<< it->fi<<" "<<it->se << "\n";
		}
		fout.close();
	}
}
int main(void) {
		cout<<"START\n";
		loadgraph();
		process();
		cout<<"end";
	return 0;
}
