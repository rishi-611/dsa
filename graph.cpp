#include <iostream>
#include <list>
#include <vector>
#include <unordered_map>
#include <iterator>

using namespace std;

// undirected simple graph, represented as an adjacency list
class Graph
{
private:
    // map to store indices of each vertex in the adjacency list
    unordered_map<char, int> vertices;

    // a vector which stores pointers to lists, where each list stores characters
    vector<list<char> *> edges;

public:
    Graph(int);
    bool addVertex(char);
    bool addEdge(char, char);
};

Graph::Graph(int size = 10)
{
    edges.reserve(size);
}

bool Graph::addVertex(char l)
{
    // return false if vertex already present
    if (vertices.find(l) != vertices.end())
        return false;

    // create a list dynamically, and push its pointer into edges vector
    list<char> *vertex = new list<char>;
    edges.push_back(vertex);

    // store the index of the inserted vertex in vertices
    vertices[l] = edges.size() - 1;
    return true;
}

bool Graph::addEdge(char start, char end)
{
    // if any of the  vertices not found, return false
    if (vertices.find(start) == vertices.end() || vertices.find(end) == vertices.end())
        return false;

    // for both vertices, add the other vertex in the neighbours list of that vertex
    int startInd{vertices[start]}, endInd{vertices[end]};

    edges.at(startInd)->push_back(end);
    edges.at(endInd)->push_back(start);

    return true;
}

int main()
{
    Graph g;
    vector<char> vertices{'a', 'b', 'c', 'd', 'e'};
    vector<vector<char>> edges{{'a', 'b'}, {'a', 'c'}, {'a', 'd'}, {'b', 'd'}, {'d', 'e'}, {'e', 'c'}};

    for (const auto &l : vertices)
        cout << g.addVertex(l) << endl;

    cout << endl;

    for (const auto &edge : edges)
        cout << g.addEdge(edge[0], edge[1]) << endl;

    std::system("pause");
    return 0;
}
