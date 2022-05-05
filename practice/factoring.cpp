#include<iostream>
#include<cmath>


void factor(int n, int* arr, int idx, int lo)
{
    std::cout << "factor(" << n << ", arr, " << idx << ',' << lo << ")\n";
    if (n==0 || n==1)
    {
        arr[idx] = n;
        return;
    }
    else
    {
        if (n%2==0)
        {
            arr[idx] = 2;
            factor(n/2, arr, idx+1, lo);
            return;
        }
        for (int i{lo}; i<sqrt(n)+1; i+=2)
        {
            if (n%i==0)
            {
                arr[idx] = i;
                factor(n/i, arr, idx+1, i);
                return;
            }
        }
        arr[idx] = n;
    }
}