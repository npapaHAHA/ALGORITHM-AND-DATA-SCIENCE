#include <bits/stdc++.h>
using namespace std;

const int MAX_V = 10000;
const int MAX_E = 200000;
const int INF   = 1e9;

int N,M,wCost,bCost,gCost;
int head[MAX_V], nxt[MAX_E], to[MAX_E], cap[MAX_E], ecnt=0;
int level_[MAX_V], it_[MAX_V], S, T;

void addEdge(int u,int v,int c){
    to[ecnt]=v; cap[ecnt]=c; nxt[ecnt]=head[u]; head[u]=ecnt++;
    to[ecnt]=u; cap[ecnt]=0; nxt[ecnt]=head[v]; head[v]=ecnt++;
}
bool bfs(){
    fill(level_,level_+T+1,-1);
    queue<int> q; level_[S]=0; q.push(S);
    while(!q.empty()){
        int v=q.front(); q.pop();
        for(int e=head[v]; e!=-1; e=nxt[e]){
            if(cap[e]&&level_[to[e]]==-1){
                level_[to[e]]=level_[v]+1;
                q.push(to[e]);
            }
        }
    }
    return level_[T]!=-1;
}
int dfs(int v,int f){
    if(!f||v==T) return f;
    for(int &i=it_[v]; i!=-1; i=nxt[i]){
        int e=i, u=to[e];
        if(cap[e]&&level_[u]==level_[v]+1){
            int p=dfs(u,min(f,cap[e]));
            if(p){ cap[e]-=p; cap[e^1]+=p; return p; }
        }
    }
    return 0;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if(!(cin>>N>>M>>wCost>>bCost>>gCost)) return 0;
    vector<string> g(N);
    for(auto &s:g) cin>>s;

    auto id=[&](int r,int c){return r*M+c;};
    int V=N*M; S=V; T=V+1;
    fill(head,head+T+1,-1);

    for(int r=0;r<N;++r)for(int c=0;c<M;++c){
        int v=id(r,c);
        if(g[r][c]=='W'){ addEdge(S,v,0); addEdge(v,T,bCost); }
        else            { addEdge(S,v,wCost); addEdge(v,T,0); }
    }

    int dr[2]={0,1}, dc[2]={1,0};
    for(int r=0;r<N;++r)for(int c=0;c<M;++c){
        int v=id(r,c);
        for(int k=0;k<2;++k){
            int nr=r+dr[k], nc=c+dc[k];
            if(nr<N&&nc<M){
                int u=id(nr,nc);
                addEdge(v,u,gCost);
                addEdge(u,v,gCost);
            }
        }
    }

    long long flow=0;
    while(bfs()){
        for(int i=0;i<=T;++i) it_[i]=head[i];
        while(int p=dfs(S,INF)) flow+=p;
    }
    cout<<flow<<"\n";
    return 0;
}
