#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <sstream>
#include <queue>
#include <climits>

using namespace std;

// Structure to represent a hospital with ID and time
struct Hospital {
    int id;
    int time;
};

// Function to implement Dijkstra's algorithm
void dijkstra(vector<list<Hospital>>& graph, vector<int>& t, vector<int>& p) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Initialize t and p arrays
    fill(t.begin(), t.end(), INT_MAX);
    fill(p.begin(), p.end(), -1);

    // Start from UN center (id = 0)
    int source = 0;
    t[source] = 0;
    pq.push({ 0, source });

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (const Hospital& neighbor : graph[u]) {
            int v = neighbor.id;
            int time_to_v = neighbor.time;

            if (t[v] > t[u] + time_to_v) {
                t[v] = t[u] + time_to_v;
                p[v] = u;
                pq.push({ t[v], v });
            }
        }
    }
}

// Function to display optimal routes and times
void displayRoutes(vector<int>& t, vector<int>& p, int total_hospitals) {
    cout << "Optimal Routes and Times:" << endl;
    for (int i = 1; i <= total_hospitals; ++i) {
        cout << "To Hospital " << i << ": ";
        int current = i;
        while (current != 0) {
            cout << "H" << current;
            if (p[current] != 0) {
                cout << " <- ";
            }
            current = p[current];
        }
        cout << " (UN Center), Time: " << t[i] << " minutes" << endl;
    }
}

int main() {
    ifstream inputFile("C:/input/Hospitals.txt");
    if (!inputFile.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    int total_hospitals;
    inputFile >> total_hospitals;
    inputFile.ignore();  // Ignore the newline after reading total_hospitals

    vector<list<Hospital>> graph(total_hospitals + 1);
    vector<int> t(total_hospitals + 1);
    vector<int> p(total_hospitals + 1);

    // Input reachability information
    for (int i = 0; i <= total_hospitals; ++i) {
        string line;
        getline(inputFile, line);

        // Extract hospital id and time information
        size_t pos = line.find("H");
        while (pos != string::npos) {
            int hospital_id, time;
            sscanf_s(line.c_str() + pos, "H%d,%d", &hospital_id, &time);
            graph[i].push_back({ hospital_id, time });
            pos = line.find("H", pos + 1);
        }
    }

    inputFile.close();

    // Run Dijkstra's algorithm
    dijkstra(graph, t, p);

    // Display optimal routes and times
    displayRoutes(t, p, total_hospitals);

    return 0;
}
