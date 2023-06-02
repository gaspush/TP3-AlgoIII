#include <vector>
#include <iostream>
#include <tuple>
using namespace std;

int casos, n, m, k, salida, llegada;
vector<tuple<int,int,int>> kaes;


int main(){
    cin >> casos;

    for (int i = 0; i < casos; i++){

        cin >> n >> m >> k >> salida >> llegada;

        for (int j = 0; j < m; j++){
            
        }

        for (int j = 0; j < k; j++){
            int u, v, w;
            cin >> u >> v >> w;
            tuple<int,int,int> tup = make_tuple(u,v,w);
            kaes.emplace_back(tup);
        }


    }
    return 0;
}