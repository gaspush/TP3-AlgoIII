#include <vector>
#include <iostream>
#include <fstream>
#include <tuple>
#include <queue>
#include <chrono>
using namespace std;

long long inf = 1e10;
int casos, n, m, k, salida, llegada;                        // Parametros de entrada
vector<long long> distanciasS, distanciasT;                       // Vectores para registrar las distancias de S a todos y de todos a T
vector<bool> procesados;                                    // Indica si un nodo fue procesado por Dijkstra (tendremos nodos repetidos en la queue)
vector<vector<tuple<int,int>>> adyacenciasS, adyacenciasT;  // Lista de adyacencias normal e inversa (para calcular las distancias de todos a T)

bool const comparar(const tuple<int,long long> a, const tuple<int,long long> b){
    return get<1>(a) > get<1>(b);
}

int getMin(vector<tuple<int,long long>> &vec){
    int res = get<0>(vec[0]);
    long long dist = get<1>(vec[0]);
    int index = 0;
    for (int i = 0; i < vec.size(); i++){
        tuple<int, long long> tup = vec[i];
        if (get<1>(tup) < dist) {
            res = get<0>(tup);
            dist = get<1>(tup);
            index = i;
        }
    }
    vec.erase(vec.begin()+index);
    return res;
}

void decreaseKey(vector<tuple<int, long long>> &vec, int nodo, vector<long long>& dist){
    for (int i = 0; i < vec.size(); i++){
        if (get<0>(vec[i]) == nodo) get<1>(vec[i]) = dist[i];
    }
}

void dijkstraPQ(vector<long long> &dist, vector<vector<tuple<int,int>>> &ady){

    priority_queue<tuple<int,long long>, vector<tuple<int,long long>>, decltype(&comparar)> Q(comparar); 

    for (int i = 1; i <= n; i++){           // Creamos un cola de prioridad de tuplas <nodo, distancia a S>
        tuple<int,long long> temp = {i,dist[i]};
        Q.push(temp);
    }
    while (!Q.empty())
    {
        int a=get<0>(Q.top());
        Q.pop();
        if (procesados[a]) continue;        // Como la cola de prioridad no se actualiza, tendremos nodos repetidos...
        procesados[a]=true;                 // y debemos chequear no estar analizando un nodo ya procesado.
        for (auto u : ady[a]) {
            int b = get<0>(u), w = get<1>(u);
            if (dist[a]+w < dist[b]) {
                dist[b] = dist[a]+w;
                tuple<int,long long> temp = {b,dist[b]};  // Insertamos en la cola una nueva tupla con la distancia mejorada que se encontro
                Q.push(temp);
            }
        }
    }
}

void dijkstraVEC(vector<long long> &dist, vector<vector<tuple<int,int>>> &ady){

    vector<tuple<int,long long>> vec;

    for (int i = 1; i <= n; i++){           // Creamos un cola de prioridad de tuplas <nodo, distancia a S>
        tuple<int,long long> temp = {i,dist[i]};
        vec.push_back(temp);
    }
    while (!vec.empty())
    {
        int a = getMin(vec);

        if (procesados[a]) continue;        // Como la cola de prioridad no se actualiza, tendremos nodos repetidos...
        procesados[a]=true;                 // y debemos chequear no estar analizando un nodo ya procesado.
        for (auto u : ady[a]) {
            int b = get<0>(u), w = get<1>(u);
            if (dist[a]+w < dist[b]) {
                dist[b] = dist[a]+w;
                decreaseKey(vec,b,dist);
            }
        }
    }
}

int main(){
    string path1 = "timepos_PQ.txt";
    string path2 = "tiempos_VEC.txt";

    ofstream tiemposPQ; tiemposPQ.open(path1);
    ofstream tiemposVEC; tiemposVEC.open(path2);

    tiemposPQ << "n, tiempo\n";
    tiemposVEC << "n, tiempo\n";


    cin >> casos;

    for (int c = 0; c < casos; c++){

        cin >> n >> m >> k >> salida >> llegada;

        procesados = vector<bool> (n+1, false);
        distanciasS = vector<long long> (n+1,inf); // Inicializamos las distancias en un numero mayor
        distanciasT = vector<long long> (n+1,inf); // a la distancia del maximo camino posible (n-1 * 1000)
        adyacenciasS = vector<vector<tuple<int,int>>> (n+1);
        adyacenciasT = vector<vector<tuple<int,int>>> (n+1);

        distanciasS[salida] = 0;
        distanciasT[llegada] = 0;

        for (int i = 0; i < m; i++){
            int u, v, w;
            cin >> u >> v >> w;
            tuple<int,int> tup = {v,w};
            tuple<int,int> tup2 = {u,w}; 
            adyacenciasS[u].emplace_back(tup);
            adyacenciasT[v].emplace_back(tup2); // Calculando las distancias de T a todos en el grafo invertido, tenemos la distancia de todos a T en el original
        }

        auto startPQ = chrono::high_resolution_clock::now();
        dijkstraPQ(distanciasS,adyacenciasS);
        procesados.assign(n+1,false);
        dijkstraPQ(distanciasT,adyacenciasT);        
        auto stopPQ = chrono::high_resolution_clock::now();
        chrono::duration<double> diffPQ = stopPQ - startPQ;
        double timePQ = diffPQ.count();

        procesados.assign(n+1,false);

        auto startVEC = chrono::high_resolution_clock::now();
        dijkstraVEC(distanciasS,adyacenciasS);
        procesados.assign(n+1,false);
        dijkstraVEC(distanciasT,adyacenciasT);
        auto stopVEC = chrono::high_resolution_clock::now();
        chrono::duration<double> diffVEC = stopVEC - startVEC;
        double timeVEC = diffVEC.count();


        tiemposPQ  << n << "," << timePQ << "\n";
        tiemposVEC << n << "," << timeVEC << "\n";

        long long distanciaMinima = distanciasS[llegada];

        for(int i = 0; i < k; i++){         // Revisamos para cada una de las calles bidireccionales entre U y V con peso W...
            int u, v, w;
            cin >> u >> v >> w;

            long long distUV = distanciasS[u] + distanciasT[v] + w;
            long long distVU = distanciasS[v] + distanciasT[u] + w;

            if (distUV < distanciaMinima) distanciaMinima = distUV; // ...si la distancia mejora recorriendo S -> U -> V -> T
            if (distVU < distanciaMinima) distanciaMinima = distVU; //          o si es conveniente recorrer S -> V -> U -> T
        }

        if (distanciaMinima == inf) cout << -1 << endl; // Si la distancia no cambio desde su inicializacion, el nodo T no es alcanzable desde S
        else cout << distanciaMinima << endl;

    }
    return 0;
}
