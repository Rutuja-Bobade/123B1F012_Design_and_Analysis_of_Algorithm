// Name : Rutuja Vishwas Bobade
// PRN : 123B1F012

// Assignment 1 : Design and implement a sorting algorithm using Merge Sort to efficiently arrange customer orders based on their timestamps. The solution should handle a large dataset (up to 1 million  orders) with minimal computational overhead. Additionally, analyze the time complexity and compare it with traditional sorting techniques. 

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>
using namespace std;

struct Order {
    string name;
    time_t timestamp;
};

void printOrders(const vector<Order>& orders) {
    cout << left << setw(15) << "Customer Name" 
         << " | " << setw(25) << "Timestamp" << endl;
    cout << string(45, '-') << endl;

    for (const auto &o : orders) {
        cout << left << setw(15) << o.name 
             << " | " << setw(25) << ctime(&o.timestamp);
    }
    cout << endl;
}

// Merge Sort
void merge(vector<Order>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<Order> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].timestamp <= R[j].timestamp)
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(vector<Order>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Bubble Sort
void bubbleSort(vector<Order>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].timestamp > arr[j + 1].timestamp) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

int main() {
    vector<Order> orders = {
        {"Alice", 1729500000},
        {"Bob", 1729400000},
        {"Charlie", 1729550000},
        {"David", 1729300000},
        {"Ella", 1729600000}
    };

    cout << "Unsorted Orders:\n";
    printOrders(orders);

    vector<Order> mergeSorted = orders;
    mergeSort(mergeSorted, 0, mergeSorted.size() - 1);
    cout << "\nMerge Sorted Orders:\n";
    printOrders(mergeSorted);

    vector<Order> bubbleSorted = orders;
    bubbleSort(bubbleSorted);
    cout << "\nBubble Sorted Orders:\n";
    printOrders(bubbleSorted);

    return 0;
}
