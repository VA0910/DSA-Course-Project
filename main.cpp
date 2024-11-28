// Authored by : Vaishnavi Agarwal

#include "Graph.h" // Manual graph implementation
#include "PriorityQueue.h" // Priority queue for graph, better in time complexity that is why used
#include <algorithm> // For basic functions like remove, reverse and erase
#include <iostream>
#include <limits>
#include <string>
#include <utility> // For easier acces to pair
#include <vector>

using namespace std;
const float Graph::FLT_MAX = std::numeric_limits<float>::infinity();
const float FLT_MAX = numeric_limits<float>::max();
const int MAX_PASSENGERS = 4;

struct Booking { // Booking defines each passenger booking
  int pickupNode;
  int dropNode;
  int passengerID;
  bool pickedUp;
  Booking(int pickup, int drop, int id)
      : pickupNode(pickup), dropNode(drop), passengerID(id), pickedUp(false) {}
};

struct Rickshaw { // Defining the rickshaw class
  int id;
  int currentLocation;
  int currentLoad;
  vector<Booking> bookings;
  vector<int> route;
  Rickshaw(int rickshawID, int startLocation)
      : id(rickshawID), currentLocation(startLocation), currentLoad(0) {}
};

// Graph as a 15 x 15 adjacency matrix
float graph[15][15];
vector<Rickshaw> rickshaws;

vector<string> nodeNames = {"Khokha Gate",
                            "Dhansiri Hostel",
                            "Umiam-Barak-Gaurang-Kameng-Manas Road",
                            "Lohit Hostel",
                            "Brahmaputra-Dihing-Kapili Junction",
                            "Disang Hostel",
                            "Market Complex-Shiv Mandir-Main Gate",
                            "Subansiri Hostel",
                            "Academic Complex : Core 1-4",
                            "Core 5",
                            "IITG Circle",
                            "New Sac",
                            "Old Sac",
                            "Hospital",
                            "Guest Houses"};
// Have clubbed the major regions of campus. for any igher number of node
// adjancency list might be more useful, due to time contraints i am switching
// to a 15x15 matrix for graph. Matric is also preferred since the data is not
// very sparse

void initializeGraph() {
  for (int i = 0; i < 15; i++) {
    for (int j = 0; j < 15; j++) {
      graph[i][j] = 0;
      // Initialize distances as 0, i.e. those which are not mentioned do not
      // need rikshaw travel. in campus everythiing is connected and none of it
      // requires inf distance
    }
  }
  graph[0][1] = 1;
  graph[0][2] = 0.5;
  graph[0][3] = 0.5;
  graph[0][4] = 0.5;
  graph[0][5] = 1.1;
  graph[0][6] = 2.6;
  graph[0][7] = 1.5;
  graph[0][8] = 1.7;
  graph[0][9] = 1.5;
  graph[0][10] = 1.7;
  graph[0][11] = 0.8;
  graph[0][12] = 1.1;
  graph[0][13] = 2;
  graph[0][14] = 2;
  graph[1][2] = 0.9;
  graph[1][3] = 0.5;
  graph[1][4] = 1;
  graph[1][5] = 1.2;
  graph[1][6] = 1.5;
  graph[1][7] = 1.1;
  graph[1][8] = 1.4;
  graph[1][9] = 1.7;
  graph[1][10] = 1.1;
  graph[1][12] = 0.7;
  graph[1][13] = 0.6;
  graph[1][14] = 0.7;
  graph[2][3] = 0.6;
  graph[2][4] = 0.6;
  graph[2][5] = 1;
  graph[2][6] = 1.7;
  graph[2][7] = 1.3;
  graph[2][8] = 1.6;
  graph[2][9] = 1.9;
  graph[2][10] = 1.6;
  graph[2][11] = 0.6;
  graph[2][12] = 0.9;
  graph[2][13] = 1.2;
  graph[2][14] = 1.4;
  graph[3][4] = 0.5;
  graph[3][5] = 0.6;
  graph[3][6] = 1.7;
  graph[3][7] = 1.3;
  graph[3][8] = 1.6;
  graph[3][9] = 1.9;
  graph[3][10] = 1.6;
  graph[3][11] = 0.6;
  graph[3][12] = 0.9;
  graph[3][13] = 1.2;
  graph[3][14] = 1.4;
  graph[4][5] = 0.5;
  graph[4][6] = 1.6;
  graph[4][7] = 1.1;
  graph[4][8] = 1.4;
  graph[4][9] = 1.7;
  graph[4][10] = 1.3;
  graph[4][11] = 0.9;
  graph[4][12] = 0.7;
  graph[4][13] = 1.5;
  graph[4][14] = 1.5;
  graph[5][6] = 2.3;
  graph[5][7] = 1.8;
  graph[5][8] = 1.3;
  graph[5][9] = 1.2;
  graph[5][10] = 1.5;
  graph[5][11] = 1.2;
  graph[5][12] = 1;
  graph[5][13] = 2.1;
  graph[5][14] = 2.1;
  graph[6][7] = 1.2;
  graph[6][8] = 1.1;
  graph[6][9] = 1.3;
  graph[6][10] = 1;
  graph[6][11] = 0.8;
  graph[6][12] = 1.1;
  graph[6][13] = 1.2;
  graph[6][14] = 1.7;
  graph[7][8] = 0.9;
  graph[7][9] = 1.2;
  graph[7][10] = 0.5;
  graph[7][11] = 0.6;
  graph[7][12] = 0.45;
  graph[7][13] = 0.7;
  graph[7][14] = 0.8;
  graph[8][11] = 1.1;
  graph[8][12] = 0.85;
  graph[8][13] = 1.2;
  graph[8][14] = 1.3;
  graph[9][10] = 0.7;
  graph[9][11] = 1.5;
  graph[9][12] = 1.2;
  graph[9][13] = 1.9;
  graph[9][14] = 1.9;
  graph[10][11] = 1.2;
  graph[10][12] = 0.65;
  graph[10][13] = 1.6;
  graph[10][14] = 1.2;
  graph[11][12] = 0.6;
  graph[11][13] = 0.6;
  graph[11][14] = 0.8;
  graph[12][13] = 1.2;
  graph[12][14] = 1.2;
  graph[13][14] = 0.35;

  // All distances according to google maps

  for (int i = 0; i < 15; i++) {
    for (int j = 0; j < 15; j++) {
      if (graph[i][j] != 0) {
        graph[j][i] = graph[i][j];
      }
    }
  }
}

void displayNodeList() { // Displaying the list of nodes for the user's
                         // reference
  cout << "List of Nodes:\n";
  for (int i = 0; i < nodeNames.size(); i++) {
    cout << i << " : " << nodeNames[i] << endl;
  }
}

// Find the shortest path between two nodes (Dijkstra's Algorithm)
vector<int> findShortestPath(Graph &graph, int start, int end) {
  int nodeCount = graph.numberNodes();
  vector<float> dist(nodeCount, Graph::FLT_MAX); // Distance vector
  vector<int> parent(nodeCount,
                     -1); // To reconstruct the path for displaying later

  dist[start] = 0;

  PriorityQueue pq;
  pq.push({0, start});

  while (!pq.empty()) {
    // Get the node with the smallest distance
    auto [currentDist, currentNode] = pq.top();
    pq.pop();

    // Skip if this path is no longer optimal
    if (currentDist > dist[currentNode])
      continue;

    // Iterate through neighbors of the current node
    for (auto &neighbor : graph.getNeighbors(currentNode)) {
      int neighborNode = neighbor.first;
      float edgeWeight = neighbor.second;

      float newDist = dist[currentNode] + edgeWeight;
      if (newDist < dist[neighborNode]) {
        dist[neighborNode] = newDist;
        parent[neighborNode] = currentNode;
        pq.push({newDist, neighborNode}); // Push the updated distance and node
      }
    }
  }

  // Reconstruct the shortest path from end to start
  vector<int> path;
  for (int v = end; v != -1; v = parent[v]) {
    path.push_back(v);
  }

  // Reverse the path to get it from start to end to display as route
  reverse(path.begin(), path.end());
  return path;
}

// Update Rickshaw Route
void updateRoute(Rickshaw &rickshaw) {
  vector<int> nodesToVisit;

  for (Booking &b : rickshaw.bookings) {
    if (!b.pickedUp) {
      nodesToVisit.push_back(b.pickupNode);
    }
    nodesToVisit.push_back(b.dropNode);
  }

  rickshaw.route.clear();
  int currentNode = rickshaw.currentLocation;

  while (!nodesToVisit.empty()) {
    int nextNode = -1;
    float minDist = FLT_MAX;

    for (int node : nodesToVisit) {
      if (graph[currentNode][node] < minDist) {
        minDist = graph[currentNode][node];
        nextNode = node;
      }
    }

    if (nextNode != -1) {
      rickshaw.route.push_back(nextNode);
      currentNode = nextNode;
      nodesToVisit.erase(
          remove(nodesToVisit.begin(), nodesToVisit.end(), nextNode),
          nodesToVisit.end());
    }
  }
}

// Book a passenger and assign to the nearest available rickshaw
void bookPassenger(int passengerID, int pickupNode, int dropNode) {
  Rickshaw *nearestRickshaw = nullptr;
  float minDistance = FLT_MAX;

  // Find the nearest available rickshaw with space i.e. cap<4
  for (Rickshaw &rickshaw : rickshaws) {
    if (rickshaw.currentLoad < MAX_PASSENGERS) {
      float distance = graph[rickshaw.currentLocation][pickupNode];
      if (distance < minDistance) {
        nearestRickshaw = &rickshaw;
        minDistance = distance;
      }
    }
  }

  // If a rickshaw was found, assign the passenger
  if (nearestRickshaw != nullptr) {
    nearestRickshaw->bookings.push_back(
        Booking(pickupNode, dropNode, passengerID));
    nearestRickshaw->currentLoad++;
    updateRoute(*nearestRickshaw); // Recalculate the rickshaw's route
    cout << "Passenger " << passengerID << " assigned to Rickshaw "
         << nearestRickshaw->id << endl;
  } else {
    cout << "No available rickshaw for Passenger " << passengerID << endl;
  }
}

// Simulate Rickshaw Movement
void simulateRickshawMovement() {
  for (Rickshaw &rickshaw : rickshaws) {
    if (!rickshaw.route.empty()) {
      int nextStop = rickshaw.route.front();
      rickshaw.route.erase(rickshaw.route.begin());
      rickshaw.currentLocation = nextStop;

      // Drop passengers
      for (auto it = rickshaw.bookings.begin();
           it != rickshaw.bookings.end();) {
        if (it->pickedUp && it->dropNode == nextStop) {
          cout << "Passenger " << it->passengerID << " dropped at Node "
               << nextStop << endl;
          rickshaw.currentLoad--;
          it = rickshaw.bookings.erase(it); // Remove completed booking
        } else {
          ++it;
        }
      }

      // Pick up passengers
      for (Booking &b : rickshaw.bookings) {
        if (!b.pickedUp && b.pickupNode == nextStop) {
          cout << "Passenger " << b.passengerID << " picked up at Node "
               << nextStop << endl;
          b.pickedUp = true;
        }
      }
    }
  }
}

// Display Current Rickshaws
void displayRickshaws() {
  for (Rickshaw &rickshaw : rickshaws) {
    cout << "Rickshaw ID: " << rickshaw.id
         << ", Current Location: " << nodeNames[rickshaw.currentLocation]
         << ", Passengers: " << rickshaw.currentLoad << ", Route: ";
    for (int node : rickshaw.route) {
      cout << nodeNames[node] << " -> ";
    }
    cout << "END" << endl;
  }
}

int main() {
  initializeGraph();

  int choice;
  while (true) {
    cout << "\nE-Rickshaw Transportation System for IITG\n";
    cout << "1. Register as a Driver\n";
    cout << "2. Book a Ride (Passenger)\n";
    cout << "3. Display Rickshaw Status\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
      int driverID, startLocation;
      cout << "Enter Driver ID: ";
      cin >> driverID;
      displayNodeList();
      cout << "Enter your starting location (Node ID): ";
      cin >> startLocation;
      if (startLocation >= 0 && startLocation < 15) {
        Rickshaw newRickshaw(driverID, startLocation);
        rickshaws.push_back(newRickshaw);
        cout << "Driver registered successfully!" << endl;
      } else {
        cout << "Invalid Node ID. Try again." << endl;
      }
    } else if (choice == 2) {
      int passengerID, pickupNode, dropNode;
      cout << "Enter Passenger ID: ";
      cin >> passengerID;
      displayNodeList();
      cout << "Enter Pickup Location (Node ID): ";
      cin >> pickupNode;
      cout << "Enter Drop Location (Node ID): ";
      cin >> dropNode;
      if (pickupNode >= 0 && pickupNode < 15 && dropNode >= 0 &&
          dropNode < 15) {
        bookPassenger(passengerID, pickupNode, dropNode);
        simulateRickshawMovement();
      } else {
        cout << "Invalid Node ID(s). Try again." << endl;
      }
    } else if (choice == 3) {
      displayRickshaws();
    } else if (choice == 4) {
      cout << "Exiting the system. Have a nice day!" << endl;
      break;
    } else {
      cout << "Invalid choice. Try again." << endl;
    }
  }

  return 0;
}
// End of code
