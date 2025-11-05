// Name : Rutuja Vishwas Bobade
// PRN : 123B1F012

// Scenario: 
// A logistics company, SwiftCargo, specializes in delivering packages across multiple cities. To optimize its delivery process, the company divides the transportation network into multiple stages (warehouses, transit hubs, and final delivery points). Each package must follow the most cost-efficient or fastest route from the source to the destination while passing through these predefined stages. As a logistics optimization engineer, you must: 
// 1. Model the transportation network as a directed, weighted multistage graph with multiple intermediate stages. 
// 2. Implement an efficient algorithm (such as Dynamic Programming or Dijkstra‘s Algorithm) to find the optimal delivery route. 
// 3. Ensure that the algorithm scales for large datasets (handling thousands of cities and routes).
// 4. Analyze and optimize route selection based on real-time constraints, such as traffic conditions, weather delays, or fuel efficiency Constraints & Considerations: 
// ● The network is structured into N stages, and every package must pass through at least 
// one node in each stage. 
// ● There may be multiple paths with different costs/times between stages. 
// ● The algorithm should be flexible enough to handle real-time changes (e.g., road closures or rerouting requirements). 
// ● The system should support batch processing for multiple delivery requests. 

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

struct Edge {
    int to;
    double cost;
};

int main() {
    int stages = 4;
    vector<int> stageNodes = {1, 3, 3, 1};
    int totalNodes = 0;
    vector<int> stageStart(stages);
    for (int i = 0; i < stages; ++i) {
        stageStart[i] = totalNodes;
        totalNodes += stageNodes[i];
    }

    vector<vector<Edge>> graph(totalNodes);
    // Sample input edges
    vector<tuple<int,int,double>> edges = {
        {0,1,1},
        {0,2,2},
        {0,3,3},
        {1,4,4},
        {1,5,11},
        {2,4,9},
        {2,5,5},
        {2,6,16},
        {3,6,2},
        {4,7,18},
        {5,7,13},
        {6,7,2}
    };

    for (auto& tup : edges)
        graph[get<0>(tup)].push_back({get<1>(tup), get<2>(tup)});

    vector<double> minCost(totalNodes, numeric_limits<double>::infinity());
    vector<int> nextNode(totalNodes, -1);
    for (int i = stageStart[stages-1]; i < totalNodes; ++i)
        minCost[i] = 0;

    for (int s = stages-2; s >= 0; --s) {
        for (int node = stageStart[s]; node < stageStart[s]+stageNodes[s]; ++node) {
            for (const Edge& e : graph[node]) {
                if (minCost[node] > e.cost + minCost[e.to]) {
                    minCost[node] = e.cost + minCost[e.to];
                    nextNode[node] = e.to;
                }
            }
        }
    }

    cout << "Best costs from Stage-0 nodes:\n";
    for (int node = stageStart[0]; node < stageStart[0]+stageNodes[0]; ++node)
        cout << "Node " << node << ": cost = " << minCost[node] << "\n";

    cout << "Path from 0 : ";
    int curr = 0; double routeCost = 0;
    cout << curr;
    while (nextNode[curr] != -1) {
        cout << " -> " << nextNode[curr];
        for (const Edge& e : graph[curr]) {
            if (e.to == nextNode[curr]) routeCost += e.cost;
        }
        curr = nextNode[curr];
    }
    cout << "\nTotal route cost (sum edges): " << routeCost << "\n";

    cout << "\nUpdating cost of edge (3, 6) from 2 to 99 to force path change...\n";
    for (Edge& e : graph[3]) if (e.to == 6) e.cost = 99;

    fill(minCost.begin(), minCost.end(), numeric_limits<double>::infinity());
    fill(nextNode.begin(), nextNode.end(), -1);
    for (int i = stageStart[stages-1]; i < totalNodes; ++i)
        minCost[i] = 0;

    for (int s = stages-2; s >= 0; --s) {
        for (int node = stageStart[s]; node < stageStart[s]+stageNodes[s]; ++node) {
            for (const Edge& e : graph[node]) {
                if (minCost[node] > e.cost + minCost[e.to]) {
                    minCost[node] = e.cost + minCost[e.to];
                    nextNode[node] = e.to;
                }
            }
        }
    }

    cout << "\nAfter update, best costs from Stage-0 nodes:\n";
    for (int node = stageStart[0]; node < stageStart[0]+stageNodes[0]; ++node)
        cout << "Node " << node << ": cost = " << minCost[node] << "\n";

    cout << "Path from 0 : ";
    curr = 0; routeCost = 0;
    cout << curr;
    while (nextNode[curr] != -1) {
        cout << " -> " << nextNode[curr];
        for (const Edge& e : graph[curr]) {
            if (e.to == nextNode[curr]) routeCost += e.cost;
        }
        curr = nextNode[curr];
    }
    cout << "\nTotal route cost (sum edges): " << routeCost << "\n";

    return 0;
}
