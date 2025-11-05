// Name : Rutuja Vishwas Bobade
// PRN : 123B1F012

// Assignment 3: Scenario: Emergency Relief Supply Distribution A devastating flood has hit multiple villages in a remote area, and the government,along with NGOs, is organizing an emergency relief operation. A rescue team has a limitedcapacity boat that can carry a maximum weight of W kilograms. The boat must transport critical supplies, including food, medicine, and drinking water, from a relief center to the affected villages.Each type of relief item has: 
// ● A weight (wi) in kilograms. 
// ● Utility value (vi) indicating its importance (e.g., medicine has higher value than food). 
// ● Some items can be divided into smaller portions (e.g., food and water), while others must be taken as a whole (e.g., medical kits). 
// As the logistics manager, you must: 
// 1. Implement the Fractional Knapsack algorithm to maximize the total utility value of the supplies transported. 
// 2. Prioritize high-value items while considering weight constraints. 
// 3. Allow partial selection of divisible items (e.g., carrying a fraction of food packets). 
// 4. Ensure that the boat carries the most critical supplies given its weight limit W. 

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
