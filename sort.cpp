#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;
void sbs(vector<int> arr)
{
    int it = arr.size() - 1;
    for (int i = 0; i <= it; i++)
    {
        for (int j = 0; j < it - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
    // for (int i=0;i<arr.size();i++){
    //     cout<<arr[i]<<" ";
    // }
    // cout<<endl;
}
void bs(vector<int> arr)
{
    int it = arr.size() - 1;
    // #pragma omp parallel
    for (int i = 0; i <= it; i++)
    {
#pragma omp for
        for (int j = 0; j < it - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
// #pragma omp critical
                swap(arr[j], arr[j + 1]);
            }
        }
    }

    // for (int i=0;i<arr.size();i++){
    //     cout<<arr[i]<<" ";
    // }
    cout << endl;
}
void merge(vector<int> &arr, int start, int end, int mid)
{
    vector<int> L;
    vector<int> R;

    for (int i = start; i <= mid; i++)
    {
        L.push_back(arr[i]);
    }
    for (int i = mid + 1; i <= end; i++)
    {
        R.push_back(arr[i]);
    }

    int i = 0;
    int j = 0;
    int k = start;
    while (i < L.size() && j < R.size())
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i++];
        }
        else
        {
            arr[k] = R[j++];
        }
        k++;
    }
    while (i < L.size())
    {
        arr[k++] = L[i++];
    }

    while (j < R.size())
    {
        arr[k++] = R[j++];
    }
}
void ms(vector<int> &arr, int start, int end)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        ms(arr, start, mid);
        ms(arr, mid + 1, end);
        merge(arr, start, end, mid);
    }
}

void pms(vector<int> &arr, int start, int end)
{
    if (start < end)
    {
        int mid;
        mid = (start + end) / 2;
#pragma omp parallel sections
{
    #pragma omp section
    {
                pms(arr, start, mid);
    }
    #pragma omp section           
{                pms(arr, mid + 1, end);

}

}
    merge(arr, start, end, mid);

    }
}
int main()
{

    const int size = 5000000; // Size of the array
    vector<int> arr(size), arr_copy(size);

    // Initialize the array with random values
    for (int i = 0; i < size; ++i)
    {
        arr[i] = rand() % 1000;
        arr_copy[i] = arr[i];
    }

    double start = omp_get_wtime();
    // sbs(arr);
    double end = omp_get_wtime();
    cout << "Sequential bs" << end - start << endl;

    start = omp_get_wtime();
    bs(arr_copy);
    end = omp_get_wtime();
    cout << "Parallel bs" << end - start << endl;

    start = omp_get_wtime();
    ms(arr, 0, arr.size() - 1);
    end = omp_get_wtime();
    std::cout << "Sequential" << end - start << endl;
    // for(int i=0;i<arr.size();i++){
    //     cout<<arr[i]<<" ";
    // }
    start = omp_get_wtime();
    pms(arr_copy, 0, arr_copy.size() - 1);
    end = omp_get_wtime();
    std::cout << "Parallel" << end - start << endl;

    return 0;
}