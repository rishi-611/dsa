#include <iostream>
#include <vector>
using namespace std;

// return number of inversion pairs in an array such that
//  i < j && arr[1] > arr[j]
// merge sort array, but when merging left and right subarray, whenever right arr(i2) is inserted in merged array, increment count by number of elems after and equal to i1, since all numbers after this will be  >
// only increment when i2 is inserted, as we have to meet i < j condition too, and i2 represents right subarray

// given two adjacent sorted subarrays of array, merge them into 1 sorted subarray
// start and end are given, first array ends at mid, second array starts and mid+1
// returns count of invers pairs found during merging
int mergeSortedArr(vector<int> &arr, int start, int end)
{
    int count{};
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
            count += mid - i1 + 1;
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
    return count;
}

int mergeSort(vector<int> &arr, int start, int end)
{
    int count{};
    // start and end are needed to decide the part of array that is to be sorted in a particular recursion
    // base case (0 and 1 element array is always sorted)
    if (start >= end)
    {

        // otherwise, split the array in left half and right half, sort these two arrays, and merge+return the two returned sorted left and right arrays
        int mid{(end + start) / 2};
        count += mergeSort(arr, start, mid);
        count += mergeSort(arr, mid + 1, end);

        count += mergeSortedArr(arr, start, end);
    }

    return count;
}

int main()
{
    vector<int> arr{3, 2, 1};
    int pairs = mergeSort(arr, 0, 9);
    // for (const auto &num : arr)
    // {
    //     cout << num << endl;
    // }

    cout << "\n"
         << pairs << endl;

    system("pause");
    return 0;
}
