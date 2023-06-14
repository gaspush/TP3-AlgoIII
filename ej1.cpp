#include <vector>
#include <iostream>
#include <tuple>
#include <queue>
using namespace std;

int casos, n, m, k, salida, llegada;                //Parametros de entrada
vector<tuple<int,int,int>> kaes;                    //Vector para las calles bidireccionales 
vector<int> distanciasS, distanciasT;               //Vectores para registrar las distancias de S a todos y de todos a T
vector<bool> procesados;                            //Indica si un nodo fue procesado por Dijkstra (tendremos nodos repetidos en la queue)
vector<vector<tuple<int,int>>> adyacenciasS;        //Lista de adyacencias
vector<vector<tuple<int,int>>> adyacenciasT;        //Lista de adyacencias inversa

bool const comparar(const tuple<int,int> a, const tuple<int,int> b){
    return get<1>(a) > get<1>(b);
}

void dijkstra(vector<int> &dist, vector<vector<tuple<int,int>>> &ady){

    priority_queue<tuple<int,int>, vector<tuple<int,int>>, decltype(&comparar)> Q(comparar);

    for (int i = 1; i <= n; i++){
        tuple<int,int> temp = {i,dist[i]};
        Q.push(temp);
    }
    while (!Q.empty())
    {
        int a=get<0>(Q.top());
        Q.pop();
        if (procesados[a]) continue;
        procesados[a]=true;
        for (auto u : ady[a]) {
            int b = get<0>(u), w = get<1>(u);
            if (dist[a]+w < dist[b]) {
                dist[b] = dist[a]+w;
                tuple<int,int> temp = {b,dist[b]};
                Q.push(temp);
            }
        }
    }
}

int main(){
    cin >> casos;

    for (int c = 0; c < casos; c++){

        cin >> n >> m >> k >> salida >> llegada;

        procesados = vector<bool> (n+1, false);
        distanciasS = vector<int> (n+1,1000*n); // Inicializamos las distancias en un numero mayor
        distanciasT = vector<int> (n+1,1000*n); // a la distancia del maximo camino posible (n-1 * 1000)
        adyacenciasS = vector<vector<tuple<int,int>>> (n+1);
        adyacenciasT = vector<vector<tuple<int,int>>> (n+1);
        kaes.clear();

        distanciasS[salida] = 0;
        distanciasT[llegada] = 0;

        for (int i = 0; i < m; i++){
            int u, v, w;
            cin >> u >> v >> w;
            tuple<int,int> tup = {v,w};
            tuple<int,int> tup2 = {u,w}; 
            adyacenciasS[u].emplace_back(tup);
            adyacenciasT[v].emplace_back(tup2); 
        }

        for (int i = 0; i < k; i++){
            int u, v, w;
            cin >> u >> v >> w;
            tuple<int,int,int> tup = {u,v,w};
            kaes.emplace_back(tup);
        }

        dijkstra(distanciasS,adyacenciasS);
        procesados.assign(n+1,false);
        dijkstra(distanciasT,adyacenciasT);

        int distanciaMinima = distanciasS[llegada];

        for(int i = 0; i < kaes.size(); i++){
            tuple<int,int,int> calle = kaes[i];
            int u = get<0>(calle);
            int v = get<1>(calle);
            int w = get<2>(calle);
            
            int distUV = distanciasS[u] + distanciasT[v] + w;
            int distVU = distanciasS[v] + distanciasT[u] + w;

            if (distUV < distanciaMinima) distanciaMinima = distUV;
            if (distVU < distanciaMinima) distanciaMinima = distVU;
        }

        if (distanciaMinima == 1000*n) cout << -1 << endl;
        else cout << distanciaMinima << endl;

    }
    return 0;
}
