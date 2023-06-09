#include <vector>
#include <iostream>
#include <queue>
#include <stdio.h>

using namespace std;

const int INF=1e9;

int n,m,casos;
vector<vector<int>> amistades,capacidad;

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});
    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : amistades[cur]) {
            if (parent[next] == -1 && capacidad[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacidad[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}
int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(n+2);
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacidad[prev][cur] -= new_flow;
            capacidad[cur][prev] += new_flow;
            cur = prev;
        }
    }
    return flow;
}

int main(){
    scanf("%d%d",&n,&m);
//2 <= n <= 300 estud. m amistades
    while (n!=0 || m!=0){
    
        capacidad=vector<vector<int>> (n+2,vector<int>(n+2,0));
        amistades=vector<vector<int>> (n+2);
       
        
        for (int i = 1; i <= n; i++){
            int opinion;
            scanf("%d",&opinion);
            if (opinion){
                amistades[0].emplace_back(i);
                amistades[i].emplace_back(0);
                capacidad[0][i] = 1;
                capacidad[i][0] = 1;
            }else{
                amistades[n+1].emplace_back(i);
                amistades[i].emplace_back(n+1);
                capacidad[n+1][i] = 1;
                capacidad[i][n+1] = 1;
            }
        }

        for (int i = 0; i < m; i++){
            int u, v;
            scanf("%d%d",&u,&v);
            
            amistades[u].emplace_back(v);
            amistades[v].emplace_back(u);
            capacidad[u][v] = 1;
            capacidad[v][u] = 1;
        }
        int capacidadMinima = maxflow(0,n+1);
        printf("%d\n",capacidadMinima);

        scanf("%d",&n);
        scanf("%d",&m);

    }
    return 0;
}


