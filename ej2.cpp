#include <vector>
#include <iostream>
#include <tuple>
#include <queue>
using namespace std;

int n,m,casos;
vector<int> votos;  
vector<vector<int>> amistades,capacidad;
int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(n);
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
}
int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, 2});

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


int main(){
    cin >> casos;

    for (int c = 0; c < casos; c++){

        cin >> n >> m; //2 <= n <= 300 estud. m amistades
        votos=vector<int> (n);
        amistades=vector<vector<int>> (n+2);
        /*
        //predecesores = ;
        //distancias = vector<int> (n+1,1000*n);
        //distanciasT = vector<int> (n+1,1000*n); //para correr Dijks desde t
        //adyacencias = 
        s---atodos los que votan X
        t---atodos los que votan y
        distancias[salida] = 0;
        distanciasT[llegada] = 0;
        */
        for (int i = 0; i < n; i++){
            int opinion;
            cin >> opinion;
            votos[i]=opinion;
            if (opinion){
                amistades[0].emplace_back(i);
                amistades[i].emplace_back(0);
            }else{
                amistades[n+1].emplace_back(i);
                amistades[i].emplace_back(n+1);
            }
        }

        for (int i = 0; i < m; i++){
            int u, v;
            cin >> u >> v;
            
            amistades[u].emplace_back(v);
            amistades[v].emplace_back(u);
        }

        

    }
    return 0;
}
