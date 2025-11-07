// Name : Rutuja Vishwas Bobade
// PRN : 123B1F012

// Scenario: Smart Traffic Management for Emergency Vehicles 
// A smart city is implementing an intelligent traffic management system to assist ambulances in reaching hospitals as quickly as possible. The city‘s road network is represented as a graph, where: 
// ● Intersections (junctions) are nodes. 
// ● Roads between intersections are edges with weights representing travel time (in minutes) considering traffic congestion. An ambulance is currently at Source (S) and needs to reach the nearest hospital (Destination D) in the shortest possible time. Due to dynamic traffic conditions, the weight of each road segment may change in real time. As a transportation engineer, you are assigned to: 
// 1. Implement Dijkstra‘s algorithm to find the shortest path from the ambulance's current location (S) to all possible hospitals. 
// 2. Account for dynamic weight updates as traffic conditions change. 
// 3. Optimize the system to work efficiently for a large city with thousands of intersections and roads. 
// 4. Provide a visual representation of the optimal path for navigation. Expected Outcome: 
// The system should suggest the quickest route for the ambulance, updating dynamicallybased on real-time traffic conditions, ensuring minimal response time to emergencies. 


#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>
#include <set>
#include <algorithm>
#include <iomanip>
using namespace std;

class Graph {
public:
    struct Edge {
        int to;
        double weight;
    };
    unordered_map<int, vector<Edge>> adj;

    void updateWeight(int from, int to, double newWeight) {
        for (auto &edge : adj[from]) if (edge.to == to) edge.weight = newWeight;
        for (auto &edge : adj[to]) if (edge.to == from) edge.weight = newWeight;
    }

    void addEdge(int from, int to, double weight, bool bidirectional=true) {
        adj[from].push_back({to, weight});
        if (bidirectional) adj[to].push_back({from, weight});
    }

    void printAllEdges() const {
        cout << "\nRoad Segment Travel Times:\n";
        set<pair<int,int>> printed;
        for (const auto &kv : adj) {
            int from = kv.first;
            for (const auto &e : kv.second) {
                int to = e.to;
                if (!printed.count({min(from,to), max(from,to)})) {
                    cout << "Intersection " << from << " <-> " << to << " : " << e.weight << " min\n";
                    printed.insert({min(from,to), max(from,to)});
                }
            }
        }
        cout << endl;
    }
};

vector<int> dijkstra(const Graph& graph, int src, const set<int>& hospitals, double& totTime, int& nearestHospital) {
    unordered_map<int, double> minDist;
    unordered_map<int, int> prev;
    set<int> visited;
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    for (const auto &kv : graph.adj) minDist[kv.first] = numeric_limits<double>::infinity();
    minDist[src] = 0.0;
    pq.push({0.0, src});
    nearestHospital = -1;
    double shortestTime = numeric_limits<double>::infinity();
    while (!pq.empty()) {
        double dist = pq.top().first;
        int u = pq.top().second; pq.pop();
        if (visited.count(u)) continue;
        visited.insert(u);
        if (hospitals.count(u) && dist < shortestTime) {
            shortestTime = dist;
            nearestHospital = u;
        }
        for (const auto& edge : graph.adj.at(u)) {
            int v = edge.to;
            double weight = edge.weight;
            if (dist + weight < minDist[v]) {
                minDist[v] = dist + weight;
                prev[v] = u;
                pq.push({minDist[v], v});
            }
        }
    }
    vector<int> path;
    totTime = shortestTime;
    if (nearestHospital != -1) {
        int node = nearestHospital;
        while (node != src) {
            path.push_back(node);
            node = prev[node];
        }
        path.push_back(src);
        reverse(path.begin(), path.end());
    }
    return path;
}

void printPath(const vector<int>& path, const Graph& city, double totTime) {
    cout << "Optimal Path: ";
    for (size_t i = 0; i < path.size(); ++i) {
        cout << "Intersection " << path[i];
        if (i != path.size()-1) cout << " -> ";
    }
    cout << "\nTotal travel time: " << totTime << " min\n";
    cout << "Segment details:\n";
    for (size_t i = 1; i < path.size(); ++i) {
        int u = path[i-1], v = path[i];
        double w = -1;
        for (const auto& e : city.adj.at(u)) if (e.to == v) w = e.weight;
        cout << "  " << u << " -> " << v << " : " << w << " min\n";
    }
    cout << endl;
}

int main() {
    Graph city;
    city.addEdge(1, 2, 5);
    city.addEdge(2, 3, 5);
    city.addEdge(1, 4, 10);
    city.addEdge(4, 5, 6);
    city.addEdge(3, 5, 2);
    city.addEdge(5, 6, 3);

    set<int> hospitals = {3, 6};
    int ambulance_source = 1;

    cout << "STEP 1) Initial Road Costs\n";
    city.printAllEdges();

    cout << "STEP 2) Initial Optimal Path:\n";
    double totTime;
    int nearestHospital;
    vector<int> path = dijkstra(city, ambulance_source, hospitals, totTime, nearestHospital);
    printPath(path, city, totTime);

    cout << "STEP 3) Real-time Traffic Simulation: Increase cost 2 <-> 3 to 20 min\n";
    city.updateWeight(2, 3, 20); 
    city.printAllEdges();

    cout << "STEP 4) Real-time Optimal Path:\n";
    path = dijkstra(city, ambulance_source, hospitals, totTime, nearestHospital);
    printPath(path, city, totTime);

    return 0;
}
