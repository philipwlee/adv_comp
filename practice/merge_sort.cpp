#include<iostream>


class Print
{
public:
    Print() = default;

    static void int_arr(int arr[], size_t sz)
    {
        for (int i{0}; i<sz-1; ++i) std::cout << arr[i] << ", ";
        std::cout << arr[sz-1] << '\n';
    }
};

class MergeSort
{
public:
    MergeSort() = default;

    static void merge(int data[], int start, int mid, int end)
    {
        // build temp array to avoid modification of original contents
        int* temp = new int[end-start+1];

        // data[] = start <--right--> mid; mid+1 <--left--> end
        int ridx{start}, lidx{mid+1}, tidx{0};

        // go through the two subarrays and populate temp using the smaller values
        while (ridx<=mid && lidx<=end)
        {
            if (data[ridx]<data[lidx]) {temp[tidx] = data[ridx]; ++ridx;}
            else {temp[tidx] = data[lidx]; ++lidx;}
            ++tidx;
        }
        while (ridx<=mid) {temp[tidx] = data[ridx]; ++ridx; ++tidx;}
        while (lidx<=end) {temp[tidx] = data[lidx]; ++lidx; ++tidx;}

        // copy temp into data
        for (int i{start}; i<=end; ++i) data[i] = temp[i-start];
    }

    static void merge_sort(int data[], int start, int end)
    {
        if (start<end)
        {
            int mid{(start+end)/2};
            merge_sort(data, start, mid);
            merge_sort(data, mid+1, end);
            merge(data, start, mid, end);
        }
        // else nothing left to do.
    }
};

int merge_sort_main()
{
    int arr[]{5,8,1,0,9,3,6,2,4,7};
    Print::int_arr(arr, 10);
    MergeSort::merge_sort(arr, 0, 9);
    Print::int_arr(arr, 10);
}