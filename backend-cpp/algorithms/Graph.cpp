#include "Graph.h"
#include <iostream>
#include <stdexcept>
#include <limits>
#include <cmath>
#include <algorithm>

// Include Haversine.h is sufficient, but re-include <cmath> for safety
// We rely on Haversine::calculateDistance here, so the Haversine class must be properly defined.

// --- Constructor ---
Graph::Graph(const std::string& graph_path) {
    // STUB: Initialize graph structure
    std::cout << "Graph initialized. Attempting to load: " << graph_path << std::endl;
    loadGraph(graph_path);
}

// --- loadGraph Definition ---
void Graph::loadGraph(const std::string& graph_path) {
    // STUB: Mock loading data from a file (e.g., graph_data.json)
    std::cout << "STUB: Graph data loaded (using mock/minimal data)." << std::endl;
    // Add minimal node data to prevent errors in findNearestNode
    nodes[1] = {1, 18.5200, 73.8400}; // Pune City Centre mock node
    nodes[2] = {2, 18.5150, 73.8350}; // Nearby node
    
    // Add minimal edge data (if needed for Dijkstra stub)
    adj_list[1].push_back({2, 1.0}); 
}

// --- findNearestNode Definition ---
int Graph::findNearestNode(double lat, double lon) {
    // STUB: Minimal logic - should use Haversine, but a mock is safer for now
    if (nodes.empty()) return -1;
    
    double min_dist_sq = std::numeric_limits<double>::max();
    int closest_node_id = -1;

    // Use a simplified distance check here (Euclidean on lat/lon, much faster than Haversine 
    // for a simple stub, though Haversine is required for the final version).
    // For now, we'll just check against the mock nodes:
    
    for (const auto& pair : nodes) {
        double dist = Haversine::calculateDistance(lat, lon, pair.second.lat, pair.second.lon);
        if (dist < min_dist_sq) {
             min_dist_sq = dist;
             closest_node_id = pair.first;
        }
    }

    return closest_node_id; 
}

// --- dijkstra Definition (Private) ---
std::vector<int> Graph::dijkstra(int start_node_id, int end_node_id) {
    // STUB: This is the core algorithm. Return a hardcoded path.
    std::vector<int> path;
    path.push_back(start_node_id);
    if (start_node_id != end_node_id) {
        // Mock a route through node 2, then to the end node
        if (start_node_id == 1 && end_node_id == 2) {
             path.push_back(2);
        }
        path.push_back(end_node_id);
    }
    return path;
}

// --- convertPathToCoords Definition ---
std::vector<std::pair<double, double>> Graph::convertPathToCoords(const std::vector<int>& path_nodes) {
    // STUB: Look up the lat/lon for the node IDs
    std::vector<std::pair<double, double>> coords;
    for (int id : path_nodes) {
        if (nodes.count(id)) {
            coords.push_back({nodes.at(id).lat, nodes.at(id).lon});
        }
    }
    return coords;
}

// --- findShortestPath Definition (Public Interface) ---
std::vector<std::pair<double, double>> Graph::findShortestPath(double start_lat, double start_lon, double end_lat, double end_lon) {
    // 1. Find the nearest graph nodes
    int start_node = findNearestNode(start_lat, start_lon);
    int end_node = findNearestNode(end_lat, end_lon);

    if (start_node == -1 || end_node == -1) {
        // Return an empty path if nodes aren't found
        return {}; 
    }
    
    // 2. Execute Dijkstra's on the core graph
    std::vector<int> path_nodes = dijkstra(start_node, end_node);
    
    // 3. Convert the resulting node sequence into a list of coordinates
    return convertPathToCoords(path_nodes);
}