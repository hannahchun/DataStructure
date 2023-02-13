#include <iostream>
#include <queue>

using namespace std;

std::priority_queue<int> pq;

int main() {
    int arr[6] = { 20, 12, 42, 3, 7, 10 };
 
    // define priority queue
    priority_queue<int> pq;
 
    // print array
    cout << "Array: ";
    for (int a : arr) {
        cout << a << ' ';
    }
    cout << endl;

    // insert elements of the array into a priority queue
    for (int i = 0; i < 6; i++) {
        pq.push(arr[i]);
    }
 
    // print priority queue
    cout << "Priority Queue: ";
    while (!pq.empty()) {
        cout << pq.top() << ' ';
        pq.pop();
    }
    cout << endl;

    return 0;
}