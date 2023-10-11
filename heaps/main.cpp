#include <iostream>
#include <vector>
#include <algorithm>

class MaxHeap {
private:
    std::vector<int> heap;

public:
    void insert(int value) {
        heap.push_back(value);
        std::push_heap(heap.begin(), heap.end());
    }

    void deleteMax() {
        if (!heap.empty()) {
            std::pop_heap(heap.begin(), heap.end());
            heap.pop_back();
        }
    }

    void printMax() {
        if (!heap.empty()) {
            std::cout << heap.front() << std::endl;
        } else {
            std::cout << std::endl;
        }
    }
};

int main() {
    int number_of_queries;
    std::cin >> number_of_queries;

    MaxHeap maxHeap;
    std::string command;
    int value;

    for (int i = 0; i < number_of_queries; ++i) {
        std::cin >> command;
        if (command == "INSERT") {
            std::cin >> value;
            maxHeap.insert(value);
        } else if (command == "DELETE") {
            maxHeap.deleteMax();
        } else if (command == "PRINT") {
            maxHeap.printMax();
        }
    }

    return 0;
}
