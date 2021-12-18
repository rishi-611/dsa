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
    void heapify(int);

public:
    MinHeap(int);
    void insert(int val);
    int getMin();
    void pop();
};

// constructor
MinHeap::MinHeap(int defaultSize = 10)
{
    // allocate this much memory for vector to start with
    heap.reserve(defaultSize);
}

// swaps two elements of heap
void MinHeap::swap(int a, int b)
{
    // swaps a and b elements in heap array
    int temp{heap.at(a)};
    heap.at(a) = heap.at(b);
    heap.at(b) = temp;
    return;
}

// for a given node, bubbles it down such that property of heap is recovered
void MinHeap::heapify(int i)
{
    int curr{i}, left{2 * i + 1}, right{2 * i + 2};

    // while curr is not the minimum of curr, left, right and curr is not a leaf node (no left or right), keep swapping curr with min
    while ((left < heap.size() && right < heap.size()))
    {
        int minIndex = heap.at(curr) < heap.at(left) ? (heap.at(curr) < heap.at(right) ? curr : right) : (heap.at(left) < heap.at(right) ? left : right);
        // if current is less than its left and right, heap property is already achieved
        if (minIndex == curr)
            return;
        // otherwise swap curr with min
        swap(curr, minIndex);

        curr = minIndex;
        left = 2 * curr + 1;
        right = 2 * curr + 2;
    }
}

int MinHeap::getMin()
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

void MinHeap::pop()
{
    // if we just delete the root node, it will split the tree in two halves and and we'll have to shift all other elems
    // so we first swap root with last elem, remove the last element ( hence min elem removed )
    // then we bubble down the new topmost element, while bubbling up new minimum element, so that min heap property is regained
    if (heap.size() == 0)
        return;

    swap(0, heap.size() - 1);
    heap.pop_back();
    heapify(0);
}

int main()
{
    MinHeap h;
    vector<int> vals{50, 40, 30, 20, 35, 10, 12, 7};
    for (const auto &val : vals)
        h.insert(val);

    cout << h.getMin() << endl;

    h.pop();
    cout << h.getMin() << endl;
    h.pop();
    cout << h.getMin() << endl;
    h.pop();
    cout << h.getMin() << endl;

    system("pause");
    return 0;
}
