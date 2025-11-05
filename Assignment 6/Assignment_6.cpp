// Name : Rutuja Vishwas Bobade
// PRN : 123B1F012

// Scenario: Disaster Relief Resource Allocation :A massive earthquake has struck a remote region, and a relief organization is transporting 
// essential supplies to the affected area. The organization has a limited-capacity relief truck that can carry a maximum weight of W kg. They have N different types of essential items, each with a specific weight and an associated utility value (importance in saving lives and meeting 
// urgent needs). Since the truck has limited capacity, you must decide which items to include to maximize the total utility value while ensuring the total weight does not exceed the truck's limit. Your Task as a Logistics Coordinator: 
// 1. Model this problem using the 0/1 Knapsack approach, where each item can either be included in the truck (1) or not (0). 
// 2. Implement an algorithm to find the optimal set of items that maximizes utility while staying within the weight constraint. 
// 3. Analyze the performance of different approaches (e.g., Brute Force, Dynamic Programming, and Greedy Algorithms) for solving this problem efficiently. 
// 4. Optimize for real-world constraints, such as perishable items (medicines, food) having priority over less critical supplies. Extend the model to consider multiple trucks or real-time decision-making for dynamic supply chain management. 

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Item {
    string name;
    int weight;
    int utility;
    bool perishable; 
};

int main() {
    int W = 50; 
    vector<Item> items = {
        {"Medicine", 10, 60, true},
        {"Food", 20, 100, true},
        {"Blankets", 30, 120, false},
        {"Water", 15, 50, true},
        {"Tents", 25, 80, false}
    };
    int N = items.size();

    sort(items.begin(), items.end(), [](const Item &a, const Item &b) {
        if (a.perishable != b.perishable)
            return a.perishable > b.perishable; 
        return (double)a.utility/a.weight > (double)b.utility/b.weight; 
    });

    vector<vector<int>> Value(N+1, vector<int>(W+1, 0));
    for (int i=1; i<=N; ++i) {
        for (int w=0; w<=W; ++w) {
            if (items[i-1].weight <= w)
                Value[i][w] = max(Value[i-1][w], Value[i-1][w-items[i-1].weight]+items[i-1].utility);
            else
                Value[i][w] = Value[i-1][w];
        }
    }

    int w = W;
    vector<int> chosen;
    for (int i=N; i>=1; --i) {
        if (Value[i][w] != Value[i-1][w]) {
            chosen.push_back(i-1);
            w -= items[i-1].weight;
        }
    }

    cout << "Max utility value attainable: " << Value[N][W] << endl;
    cout << "Items to include in relief truck:" << endl;
    int totalWt = 0;
    for (int idx : chosen) {
        cout << "  - " << items[idx].name << " (Wt: " << items[idx].weight << "kg, Utility: " << items[idx].utility
             << (items[idx].perishable ? ", Perishable" : "") << ")" << endl;
        totalWt += items[idx].weight;
    }
    cout << "Total weight: " << totalWt << "kg\n";

    return 0;
}
