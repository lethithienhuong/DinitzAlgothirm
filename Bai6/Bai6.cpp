#include<vector>
#include<iostream>
#include<fstream>
#define FORE(i,v) for (__typeof((v).begin()) i=(v).begin();i!=(v).end();i++)
using namespace std;
const int INF=(int)1e9+7;
class DinicFlow{
	private:
	vector<int> dist,head,q,work;//dist:do dai duong di ngan nhat,head:dinh phat,q:hang doi,work:dinh dang xet
	vector<int> capa,flow,next,point;//capa:kha nang thong qua,flow:luong;next:dinh tiep theo can xet,point:dinh xet;
	int n,m;//n:so dinh, m:so canh
	public:
		//buoc 1
	DinicFlow(){//ham dung khong tham so
		n=0;m=0;
	}
	DinicFlow(int n,int _m) {// ham dung tham so
		this->n=n;
		this->m=0;
		dist=vector<int>(n+7);// duong di ngan nhat
		head=vector<int>(n+7,-1);// dinh dau kha nang thong luong bang -1
		q=vector<int>(n+7); // hang doi rong
		work=vector<int>(n+7);// dinh can xet
		int m=2*_m;
		capa=vector<int>(m+7);
		flow=vector<int>(m+7,0);// luong voi gia tri thong luong ban dau =0
		next=vector<int>(m+7);
		point=vector<int>(m+7);		
	}
	void addedge(int u,int v,int c1,int c2) // them canh vao do thi
	{// c1: gia tri thong luong u->v;c2 nguoc lai
		point[m]=v;capa[m]=c1;flow[m]=0;next[m]=head[u];head[u]=m;m++;
		point[m]=u;capa[m]=c2;flow[m]=0;next[m]=head[v];head[v]=m;m++;
	}
	bool bfs(int s,int t) //tim kiem theo chieu rong
	{//s:dinh phat, t: dinh thu
		FORE(it,dist) *it=-1;// khong co canh ke
		int sz=1;
		q[0]=s;dist[s]=0;// day s vao hang doi, duong di ngan nhat = 0
		for(int x = 0;x<sz;x++) {
			int u=q[x];
			for (int i=head[u];i>=0;i=next[i])
				if (dist[point[i]]<0 && flow[i]<capa[i]) {//
					dist[point[i]]=dist[u]+1;
					q[sz]=point[i];
					sz++;
				}
		}
		return (dist[t]>=0);
	}
	int dfs(int s,int t,int f)//tim kiem theo chieu sau
	 {
		if (s==t) return (f);
		for (int &i=work[s];i>=0;i=next[i])
			if (dist[point[i]]==dist[s]+1 && flow[i]<capa[i]) {
				int d=dfs(point[i],t,min(f,capa[i]-flow[i])) ;
				if (d>0) {
					flow[i]+=d;
					flow[i^1]-=d;
					return (d);
				}
			}
		return 0;
	}
	int maxflow(int s,int t) {
		int ret=0;
		while (bfs(s,t)) {
			for(int i=1;i<=n;i++) work[i]=head[i];
			while (true) {
				int d=dfs(s,t,INF);
				if (d<=0) break;
				ret+=d;
			}
		}
		return ret;
	}
};
int m,n,k;
DinicFlow g;
int main(void) {
	int m,n,k;
	DinicFlow g;
	ifstream fin;
	fin.open("C:\\Users\\Thien Huong\\OneDrive\\Desktop\\DOAN1\\Bai6\\Data\\text1.txt",ios_base::in);
	ofstream fout;
	fout.open("C:\\Users\\Thien Huong\\OneDrive\\Desktop\\DOAN1\\Bai6\\Data\\outtext1.txt",ios_base::out);
	if(fin.fail()) cout<<"File kh ton tai";
    else{
    	fin>>m>>n>>k;
		g=DinicFlow(m+n+2,m+n+k);
		for(int i=1;i<=m;i++) {
			int t;
			fin>>t;
			g.addedge(m+n+1,i,t,0);		
		}	
		for(int i=1;i<=n;i++) {
			int t;
			fin>>t;
			g.addedge(m+i,m+n+2,t,0);			
		}
		for(int i=0;i<k;i++) {
			int x,y;
			fin>>x>>y;
			g.addedge(x,m+y,INF,0);//buoc 2
		}
		fout<<g.maxflow(m+n+1,m+n+2);
		//cout<<g.maxflow(m+n+1,m+n+2);
		fout.close();
	}	
	return 0;
}
