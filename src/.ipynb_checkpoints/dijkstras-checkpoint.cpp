#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>
#include "dijkstras.h"
using namespace std;


vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    // graph is a vector of vector<edges>
    int adjl_size = G.size();

    vector<int> dist(adjl_size, INF);
    previous.assign(adjl_size, -1);
    vector<bool> visited(adjl_size, 0);

    //min heap
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});

    dist[source] = 0;
    
    while (!pq.empty()){
        auto [currDis, currVert] = pq.top();
        pq.pop();

        if (!visited[currVert]){
            visited[currVert] = 1; // (pos bool : visited)

            // loops through edges adjacent to curr
            for (Edge e : G[currVert]){
                int neighbor = e.dst;
                int cost = e.weight;
                
                if (!visited[neighbor] && dist[currVert] + cost < dist[neighbor]){
                    previous[neighbor] = currVert;
                    dist[neighbor] = dist[currVert] + cost;
                    pq.push({dist[neighbor], neighbor});
                }
            }
        }
    }
    return dist;
}


vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    if (distances[destination] == INF) { return path; }    
    for (int i = destination; i != -1; i = previous[i]) {
        path.push_back(distances[i]);
    }

    reverse(path.begin(), path.end());
    return path;
}


void print_path(const vector<int>& v, int total) {
    for(int i = 0; i < v.size(); ++i){cout << v[i] << " ";}
    cout << endl << "Total cost is " << total << endl;
}

