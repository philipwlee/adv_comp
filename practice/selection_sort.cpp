#include<iostream>
#include<utility>  // std::swap
#include<iterator> // std::size

void selection_sort()
{
    int arr[]{30, 50, 20, 10, 40};
    constexpr int n { static_cast<int>(std::size(arr))};

    for (int i{0}; i<n; i++) std::cout << arr[i] << ',';
    std::cout << '\n';

    for (int l{0}; l<n-1; l++)
    {
        int mindex{l};
        for (int r{l+1}; r<n; r++)
        {
            if (arr[r]<arr[mindex]) mindex=r;
        }
        std::swap(arr[l], arr[mindex]);
    }

    for (int i{0}; i<n; i++) std::cout << arr[i] << ',';
}
