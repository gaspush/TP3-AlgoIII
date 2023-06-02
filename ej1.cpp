#include <vector>
#include <iostream>
#include <tuple>
#include <queue>
using namespace std;

int casos, n, m, k, salida, llegada;
vector<tuple<int,int,int>> kaes;
vector<int> distancias, predecesores;
vector<vector<tuple<int,int>>> adyacencias;

bool const comparar(const tuple<int,int*> a, const tuple<int,int*> b){
    return get<1>(a) > get<1>(b);
}
priority_queue<tuple<int,int*>, vector<tuple<int,int*>>, decltype(&comparar)> Q(comparar);


void dijkstra(){

    for (int i = 1; i <= n; i++){
        tuple<int,int*> temp = {i,&distancias[i]};
        Q.emplace(temp);

        cout << get<0>(Q.top());
    }
    
}

int main(){
    cin >> casos;

    for (int c = 0; c < casos; c++){

        cin >> n >> m >> k >> salida >> llegada;

        predecesores = vector<int> (n+1,-1);
        distancias = vector<int> (n+1,1000*n);
        adyacencias = vector<vector<tuple<int,int>>> (n+1);

        distancias[salida] = 0;

        for (int i = 0; i < m; i++){
            int u, v, w;
            cin >> u >> v >> w;
            tuple<int,int> tup = {v,w};
            adyacencias[u].emplace_back(tup);
        
        }

        for (int i = 0; i < k; i++){
            int u, v, w;
            cin >> u >> v >> w;
            tuple<int,int,int> tup = {u,v,w};
            kaes.emplace_back(tup);
        }

        dijkstra();

    }
    return 0;
}