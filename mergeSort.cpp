#include <iostream>
#include <vector>
using namespace std;

// given two adjacent sorted subarrays of array, merge them into 1 sorted subarray
// start and end are given, first array ends at mid, second array starts and mid+1
void mergeSortedArr(vector<int> &arr, int start, int end)
{
    vector<int> sorted;

    int mid{(end + start) / 2};

    int i1{start}, i2{mid + 1};
    while (i1 <= mid && i2 <= end)
    {
        if (arr.at(i1) < arr.at(i2))
        {
            sorted.push_back(arr.at(i1));
            i1++;
        }
        else
        {
            sorted.push_back(arr.at(i2));
            i2++;
        }
    }

    while (i1 <= mid)
    {
        sorted.push_back(arr.at(i1));
        i1++;
    }
    while (i2 <= end)
    {
        sorted.push_back(arr.at(i2));
        i2++;
    }

    // copy sorted array elements into our array
    for (int i{0}; i < sorted.size(); i++)
    {
        arr.at(i + start) = sorted.at(i);
    }
}

void mergeSort(vector<int> &arr, int start, int end)
{
    cout << start << " " << end << endl;
    // start and end are needed to decide the part of array that is to be sorted in a particular recursion
    // base case (0 and 1 element array is always sorted)
    if (start >= end)
        return;

    // otherwise, split the array in left half and right half, sort these two arrays, and merge+return the two returned sorted left and right arrays
    int mid{(end + start) / 2};
    mergeSort(arr, start, mid);
    mergeSort(arr, mid + 1, end);

    mergeSortedArr(arr, start, end);
}

int main()
{
    vector<int> arr{3, 2, 1, 4, 5, 2, 3, 3, 1, 10};
    mergeSort(arr, 0, 9);
    for (const auto &num : arr)
    {
        cout << num << endl;
    }

    system("pause");
    return 0;
}
