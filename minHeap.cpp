#include <iostream>
#include <vector>
using namespace std;

// min heap -> parent will always be smaller than children
//  properties -> complete binary tree
//  since complete bt, array representation can be used as insertion will always be at end
//  if i is the index of node
//  left child index -> 2i+1     right child index ->2i+2        parent index ->(i-1)/2

class MinHeap
{
private:
    vector<int> heap;
    void swap(int a, int b);

public:
    void insert(int val);
    int minElem();
};

void MinHeap::swap(int a, int b)
{
    // swaps a and b elements in heap array
    int temp{heap.at(a)};
    heap.at(a) = heap.at(b);
    heap.at(b) = temp;
    return;
}

int MinHeap::minElem()
{
    for (const auto &val : heap)
    {
        cout << val << " ";
    }
    cout << endl;
    return heap.size() == 0 ? -1 : heap.at(0);
}

void MinHeap::insert(int val)
{
    // insert the element at end of array (bottom left of tree)
    heap.push_back(val);
    int n{(int)heap.size()};

    // compare elem to parent, if elem < parent, swap them, repeat until elem >=parent, or root is reached
    if (n == 0)
        return;

    // index of currently inserted elem
    int curr{n - 1};
    int parent{(curr - 1) / 2};
    while (curr > 0 && (heap.at(curr) < heap.at(parent)))
    {
        swap(curr, parent);
        // shift current pointer to the new current (as curr got swapped with parent)
        curr = parent;
        parent = (curr - 1) / 2;
    }
    return;
}

int main()
{
    MinHeap h;
    vector<int> vals{50, 40, 30, 20, 35, 10, 12, 7};
    for (const auto &val : vals)
        h.insert(val);

    cout << h.minElem() << endl;

    system("pause");
    return 0;
}
