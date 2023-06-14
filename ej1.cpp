#include <vector>
#include <iostream>
#include <tuple>
#include <queue>
using namespace std;

int casos, n, m, k, salida, llegada;
vector<tuple<int,int,int>> kaes;
vector<int> distancias, predecesores, procesado, predecesoresT, distanciasT, procesadoT;
vector<vector<tuple<int,int>>> adyacencias;
vector<vector<tuple<int,int>>> adyacenciasT;

bool const comparar(const tuple<int,int> a, const tuple<int,int> b){
    return get<1>(a) > get<1>(b);
}

priority_queue<tuple<int,int>, vector<tuple<int,int>>, decltype(&comparar)> Qs(comparar);
priority_queue<tuple<int,int>, vector<tuple<int,int>>, decltype(&comparar)> Qt(comparar);

void dijkstra(){

    for (int i = 1; i <= n; i++){
        tuple<int,int> temp = {i,distancias[i]};
        Qs.push(temp);
    }
    while (!Qs.empty())
    {
        int a=get<0>(Qs.top());
        Qs.pop();
        if (procesado[a]) continue;
        procesado[a]=true;
        for (auto u : adyacencias[a]) {
            int b = get<0>(u), w = get<1>(u);
            predecesores[b]=a;
            if (distancias[a]+w < distancias[b]) {
                distancias[b] = distancias[a]+w;
                tuple<int,int> temp = {b,distancias[b]};
                Qs.push(temp);
            }
        }
    }
}
void dijkstra2(){

    for (int i = 1; i <= n; i++){
        tuple<int,int> temp = {i,distanciasT[i]};
        Qt.emplace(temp);
    }
    while (!Qt.empty())
    {
        int a=get<0>(Qt.top());
        Qt.pop();
        if (procesadoT[a]) continue;
        procesadoT[a]=true;
        for (auto u : adyacenciasT[a]) {
            int b = get<0>(u), w = get<1>(u);
            if (distanciasT[a]+w < distanciasT[b]) {
                distanciasT[b] = distanciasT[a]+w;
                tuple<int,int> temp = {b,distanciasT[b]};
                Qt.push(temp);
            }            
        }
    }    
}

int main(){
    cin >> casos;

    for (int c = 0; c < casos; c++){

        cin >> n >> m >> k >> salida >> llegada;

        predecesores = vector<int> (n+1,-1);
        predecesoresT = vector<int> (n+1,-1);
        procesado = vector<int> (n+1, false);
        procesadoT = vector<int> (n+1,false);
        distancias = vector<int> (n+1,1000*n);
        distanciasT = vector<int> (n+1,1000*n); //para correr Dijks desde t
        adyacencias = vector<vector<tuple<int,int>>> (n+1);
        adyacenciasT = vector<vector<tuple<int,int>>> (n+1);

        distancias[salida] = 0;
        distanciasT[llegada] = 0;

        for (int i = 0; i < m; i++){
            int u, v, w;
            cin >> u >> v >> w;
            tuple<int,int> tup = {v,w};
            tuple<int,int> tup2 = {u,w}; // grafo dado vuelta para correr Dijks desde t
            adyacencias[u].emplace_back(tup);
            adyacenciasT[v].emplace_back(tup2); 
        }

        for (int i = 0; i < k; i++){
            int u, v, w;
            cin >> u >> v >> w;
            tuple<int,int,int> tup = {u,v,w};
            kaes.emplace_back(tup);
        }

        dijkstra();
        dijkstra2();

    }
    return 0;
}
