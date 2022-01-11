#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool isCellValid(vector<vector<int>> &m, int n, int row, int col)
{
    // check for out of bounds
    // check for blocked cell, or already visited cell
    if (row < 0 || col < 0 || row >= n || col >= n || m[row][col] == 0 || m[row][col] == 2)
        return false;

    return true;
}

void findPathHelper(vector<vector<int>> &m, int n, int row, int col, string &path, vector<string> &res)
{
    // base case=> invalid cell
    if (!isCellValid(m, n, row, col))
        return;
    // base case=> reached destination
    if (row == (n - 1) && col == (n - 1))
    {
        // append path to result
        res.push_back(path);
        return;
    }

    // mark the cell visited
    m[row][col] = 2;
    // move to next cells, while storing direction of movement in path

    path += "U";
    findPathHelper(m, n, row - 1, col, path, res);
    path.pop_back();

    path += "D";
    findPathHelper(m, n, row + 1, col, path, res);
    path.pop_back(); // backtrack as we come back from row below

    path += "L";
    findPathHelper(m, n, row, col - 1, path, res);
    path.pop_back();

    path += "R";
    findPathHelper(m, n, row, col + 1, path, res);
    path.pop_back();

    m[row][col] = 1; // backtrack to 1 so that next solution can be found
    return;
}
vector<string> findPath(vector<vector<int>> &m, int n)
{
    // DFS starting from  1st cell
    string path{""};
    vector<string> res;
    findPathHelper(m, n, 0, 0, path, res);
    return res;
}

int main()
{
    vector<vector<int>> m{{1, 1, 1, 1},
                          {1, 1, 1, 1},
                          {1, 1, 1, 1},
                          {1, 1, 1, 1}};

    int n{(int)m.size()};
    vector<string> paths{findPath(m, n)};
    for (auto path : paths)
        cout << path << " ";
    cout << endl;
    system("pause");
    return 0;
}