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
