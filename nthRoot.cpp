#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int binarySearch(int n, int m, int start, int end)
{

    if (start > end || start < 0 || end > m)
        return -1;

    int mid{(end - start) / 2 + start};
    cout << "start: " << start << " mid: " << mid << " end: " << end << endl;

    // if mid ^n
    int midPowN{(int)pow(mid, n)};

    cout << "mid power: " << midPowN << endl;
    if (midPowN == m)
        return mid;

    // shrink to left array
    else if (midPowN > m)
        return binarySearch(n, m, start, mid - 1);
    else
        return binarySearch(n, m, mid + 1, end);
}

int NthRoot(int n, int m)
{
    // Code here.
    // find a number x such that x^n = m
    // only return num if its integer
    // vector<int> nums (m);
    // for (int i{1}; i <= m; i++) nums[i-1] = i; //nums from 1 to n array

    // binary search in this arrray to find num
    return binarySearch(n, m, 1, m);
}

int main()
{
    cout << NthRoot(2, 9) << endl;

    system("pause");
    return 0;
}