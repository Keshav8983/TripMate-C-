// JourneyGenie.cpp
// __define-ocg__: JourneyGenie Trip Planner
#include <bits/stdc++.h>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include <string>
#include <sstream>

using namespace std;

struct Edge {
    string to;
    int distance;
    int time;
};

struct Node {
    string city;
    int distance;
    int time;
    bool operator>(const Node &other) const {
        return distance > other.distance;
    }
};

class JourneyGenie {
private:
    unordered_map<string, vector<Edge>> graph;

public:
    void loadRoutes(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "⚠️ Error: Could not open dataset file: " << filename << endl;
        system("pause"); // keeps console open
        exit(1);
    }
    string from, to;
    int distance, time;
    while (file >> from >> to >> distance >> time) {
        graph[from].push_back({to, distance, time});
        graph[to].push_back({from, distance, time});
    }
    file.close();
}


    void dijkstra(const string &source, const string &destination) {
        unordered_map<string, int> dist;
        unordered_map<string, string> prev;

        for (auto &node : graph) {
            dist[node.first] = numeric_limits<int>::max();
        }
        dist[source] = 0;

        priority_queue<Node, vector<Node>, greater<Node>> pq;
        pq.push({source, 0, 0});

        while (!pq.empty()) {
            Node u = pq.top();
            pq.pop();

            if (u.city == destination) break;

            for (auto &edge : graph[u.city]) {
                int newDist = dist[u.city] + edge.distance;
                if (newDist < dist[edge.to]) {
                    dist[edge.to] = newDist;
                    prev[edge.to] = u.city;
                    pq.push({edge.to, newDist, 0});
                }
            }
        }

        // Print path
        if (dist[destination] == numeric_limits<int>::max()) {
            cout << "No route found.\n";
            return;
        }

        vector<string> path;
        for (string at = destination; at != ""; at = prev[at]) {
            path.push_back(at);
            if (at == source) break;
        }
        reverse(path.begin(), path.end());

        cout << "Shortest Path from " << source << " to " << destination << ":\n";
        for (auto &city : path) cout << city << " ";
        cout << "\nDistance: " << dist[destination] << " km\n";
    }
};

// CLI
int main() {
    JourneyGenie app;
    app.loadRoutes("C:/Users/Keshav/OneDrive/Desktop/c++/JourneyGenie/routes.txt");

    cout << "====== JourneyGenie Trip Planner ======\n";
    string src, dest;
    cout << "Enter source city: ";
    cin >> src;
    cout << "Enter destination city: ";
    cin >> dest;

    app.dijkstra(src, dest);
    return 0;
}

