


#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <map>
#include <limits>
#include <string>
#include <cmath>
#include "Haversine.h" // Needed to calculate distance to nearest node

struct Node {
    int id;
    double lat, lon;
};

struct Edge {
    int target_node_id;
    double weight; // Distance (e.g., in meters or kilometers)
};

class Graph {
private:
    std::map<int, Node> nodes;
    std::map<int, std::vector<Edge>> adj_list;

public:
    // Constructor (Definition required in .cpp)
    Graph(const std::string& graph_path); 
    
    // Loads graph data from JSON file (Definition required in .cpp)
    void loadGraph(const std::string& graph_path);

    // Step 3: Finds the nearest road node to a given coordinate.
    int findNearestNode(double lat, double lon);
    
    // Executes Dijkstra's Algorithm and converts path to coordinates.
    // This is the main public routing interface.
    std::vector<std::pair<double, double>> findShortestPath(double start_lat, double start_lon, double end_lat, double end_lon);

private:
    // Core Dijkstra's Algorithm implementation.
    std::vector<int> dijkstra(int start_node_id, int end_node_id);
    
    // Converts the sequence of Node IDs from Dijkstra's to lat/lon pairs.
    std::vector<std::pair<double, double>> convertPathToCoords(const std::vector<int>& path_nodes);
    
    // Helper to retrieve Node coordinates
    const Node& getNode(int id) const;
};

#endif // GRAPH_H