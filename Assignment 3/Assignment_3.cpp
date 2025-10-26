#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Item {
    string name;
    double weight;
    double value;
    bool divisible;
};

bool cmp(const Item& a, const Item& b) {
    double r1 = a.value / a.weight;
    double r2 = b.value / b.weight;
    return r1 > r2;
}

void fractionalKnapsack(double W, vector<Item>& items) {
    sort(items.begin(), items.end(), cmp);

    double totalValue = 0.0, totalWeight = 0.0;
    cout << left << setw(15) << "Item"
         << setw(10) << "Taken"
         << setw(10) << "Weight"
         << setw(10) << "Value"
         << endl;
    cout << string(45, '-') << endl;

    for (const auto& item : items) {
        if (W <= 0)
            break;
        if (item.divisible) {
            double take = min(W, item.weight);
            totalValue += take * item.value / item.weight;
            totalWeight += take;
            W -= take;
            cout << left << setw(15) << item.name
                 << setw(10) << fixed << setprecision(2) << (take/item.weight)*100 << "%" 
                 << setw(10) << take
                 << setw(10) << take * item.value / item.weight
                 << endl;
        } else {
            if (item.weight <= W) {
                totalValue += item.value;
                totalWeight += item.weight;
                W -= item.weight;
                cout << left << setw(15) << item.name
                     << setw(10) << "100%"
                     << setw(10) << item.weight
                     << setw(10) << item.value
                     << endl;
            } else {
                cout << left << setw(15) << item.name
                     << setw(10) << "0%"
                     << setw(10) << "0"
                     << setw(10) << "0"
                     << endl;
            }
        }
    }
    cout << "\nTotal weight loaded: " << totalWeight << " kg\n";
    cout << "Total utility value: " << totalValue << endl;
}

int main() {
    double W = 50;
    vector<Item> items = {
        {"Food", 30, 45, true},
        {"Water", 20, 40, true},
        {"MedicineKit", 10, 100, false},
        {"Blankets", 15, 10, false}
    };

    cout << "Boat Capacity: " << W << " kg\n";
    cout << "Selected Supplies:\n";
    fractionalKnapsack(W, items);

    return 0;
}
