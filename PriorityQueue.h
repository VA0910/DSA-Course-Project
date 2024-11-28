// Manual implementation of Priority Queue
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <utility>
#include <vector>

using namespace std;

class PriorityQueue {
private:
  vector<pair<float, int>> heap;

  void heapifyUp(int index) {
    while (index > 0) {
      int parent = (index - 1) / 2;
      if (heap[index].first < heap[parent].first) {
        swap(heap[index], heap[parent]);
        index = parent;
      } else {
        break;
      }
    }
  }

  void heapifyDown(int index) {
    int size = heap.size();
    while (index < size) {
      int left = 2 * index + 1;
      int right = 2 * index + 2;
      int smallest = index;

      if (left < size && heap[left].first < heap[smallest].first)
        smallest = left;
      if (right < size && heap[right].first < heap[smallest].first)
        smallest = right;

      if (smallest != index) {
        swap(heap[index], heap[smallest]);
        index = smallest;
      } else {
        break;
      }
    }
  }

public:
  PriorityQueue() {}

  void push(pair<float, int> element) {
    heap.push_back(element);
    heapifyUp(heap.size() - 1);
  }

  pair<float, int> top() { return heap[0]; }

  void pop() {
    if (!heap.empty()) {
      heap[0] = heap.back();
      heap.pop_back();
      heapifyDown(0);
    }
  }

  bool empty() { return heap.empty(); }
};

#endif
