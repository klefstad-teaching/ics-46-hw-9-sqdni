#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>
#include "dijkstras.h"
using namespace std;

/*

g++ -std=c++20 -c src/dijkstras.cpp -o dj.o 
g++ -std=c++20 -g -fsanitize=address src/dijkstras_main.cpp -o hw9 dj.o
./hw9

*/


int main(){
    Graph G;
    file_to_graph("src/small.txt", G);
    int src = 3;
    vector<int> prev;
    vector<int> dijkstra_path = dijkstra_shortest_path(G, src, prev);
    for (int v : dijkstra_path) { cout << v << " "; }

    int destination = 1;
    vector<int> short_path = extract_shortest_path(dijkstra_path, prev, destination);
    print_path(short_path, short_path.size());
    return 0;
}