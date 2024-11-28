// Manual implementation of Graph
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Graph {
private:
  int size;                              // Number of nodes
  vector<vector<float>> adjacencyMatrix; // Adjacency matrix

public:
  static const float FLT_MAX; // Maximum distance (infinity)

  // Constructor
  Graph(int nodes)
      : size(nodes), adjacencyMatrix(nodes, vector<float>(nodes, FLT_MAX)) {}

  // Get neighbors of a node
  vector<pair<int, float>> getNeighbors(int node) const {
    vector<pair<int, float>> neighbors;
    for (int i = 0; i < size; i++) {
      if (adjacencyMatrix[node][i] != FLT_MAX) {
        neighbors.push_back({i, adjacencyMatrix[node][i]});
      }
    }
    return neighbors;
  }

  // Get the number of nodes
  int numberNodes() const { return size; }
};

#endif
