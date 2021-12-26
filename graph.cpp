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

    // a vector which stores pointers to lists, where each list stores characters (adjacency list)
    vector<list<char> *> edges;

    // helper method to find index of a node in adjacency list
    int getIndex(char);

    // helper method, that takes in a character, stores it in result vector, and does the recursively does the same for all its neighbours
    void dfsHelper(char node, vector<char> &nodes, unordered_map<char, bool> &);
    void bfsHelper(char node, vector<char> &nodes, unordered_map<char, bool> &);

public:
    Graph(int);
    bool addVertex(char);
    bool addEdge(char, char);
    vector<char> dfs(char);
    vector<char> bfs(char);
};

Graph::Graph(int size = 10)
{
    edges.reserve(size);
}

int Graph::getIndex(char node)
{
    if (vertices.find(node) == vertices.end())
        return -1;

    return vertices[node];
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
    // otherwise, for both vertices, add the other vertex in the neighbours list of that vertex
    int startInd{getIndex(start)}, endInd{getIndex(end)};

    if (startInd < 0 || endInd < 0)
        return false;

    edges.at(startInd)->push_back(end);
    edges.at(endInd)->push_back(start);

    return true;
}

void Graph::dfsHelper(char node, vector<char> &nodes, unordered_map<char, bool> &visited)
{
    int nodeInd{getIndex(node)};

    // base case
    // if node already visited, exit
    if (visited.find(node) != visited.end())
        return;

    // if given vertex is not found, return
    if (nodeInd < 0 || nodeInd >= edges.size())
        return;

    // recursice case-> print the node, mark it visited
    nodes.push_back(node);
    visited[node] = true;

    // and then traverse through its adjacent nodes list, and for each node in the list, call this function
    for (auto it{edges.at(nodeInd)->begin()}; it != edges.at(nodeInd)->end(); it++)
    {
        dfsHelper(*it, nodes, visited);
    }
}

// DEPTH FIRST TRAVERSAL
//  from a given character (node), traverse with depth first approach
//  return a vector of all traversed nodes
vector<char> Graph::dfs(char node)
{
    // stores resultant vector
    vector<char> nodes;

    // stores list of nodes that have been already visited
    unordered_map<char, bool> visited;
    dfsHelper(node, nodes, visited);

    return nodes;
}

void Graph::bfsHelper(char node, vector<char> &nodes, unordered_map<char, bool> &visited)
{
    int nodeInd{getIndex(node)};

    // base case
    // if node already visited, exit
    if (visited.find(node) != visited.end())
        return;

    // if given vertex is not found, return
    if (nodeInd < 0 || nodeInd >= edges.size())
        return;

    // recursice case-> print the node, mark it visited
    nodes.push_back(node);
    visited[node] = true;

    // and then traverse through its adjacent nodes list, and for each node in the list, call this function
    for (auto it{edges.at(nodeInd)->begin()}; it != edges.at(nodeInd)->end(); it++)
    {
        bfsHelper(*it, nodes, visited);
    }
}

// BREADTH FIRST TRAVERSAL
// from a given character (node), traverse with depth first approach
// return a vector of all traversed nodes
vector<char> Graph::bfs(char node)
{
    // stores resultant vector
    vector<char> nodes;

    // stores list of nodes that have been already visited
    unordered_map<char, bool> visited;
    bfsHelper(node, nodes, visited);

    return nodes;
}

int main()
{
    Graph g;

    // test case 1
    //  vector<char> vertices{'a', 'b', 'c', 'd', 'e'};
    //  vector<vector<char>> edges{{'a', 'b'}, {'a', 'c'}, {'a', 'd'}, {'b', 'd'}, {'d', 'e'}, {'e', 'c'}};

    // test case 2
    vector<char> vertices{'a', 'b', 'c', 'd', 'e', 'f'};
    vector<vector<char>> edges{{'a', 'b'}, {'a', 'c'}, {'b', 'd'}, {'c', 'e'}, {'d', 'e'}, {'d', 'f'}};

    std::cout << "inserting vertices" << endl;
    for (const auto &l : vertices)
        std::cout << g.addVertex(l) << endl;

    std::cout << endl;

    std::cout << "inserting edges" << endl;
    for (const auto &edge : edges)
        std::cout << g.addEdge(edge[0], edge[1]) << endl;

    std::cout << endl;

    char node{'a'};
    std::cout << "dfs traversal from node: " << node << endl;
    vector<char> allNodes{g.dfs(node)};
    for (const auto &l : allNodes)
        std::cout << l << " ";
    std::cout << endl;

    std::system("pause");
    return 0;
}
