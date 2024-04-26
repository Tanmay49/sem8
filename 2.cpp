#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>

using namespace std;
using namespace std::chrono;

// Sequential Bubble Sort
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Parallel Bubble Sort
void parallelBubbleSort(vector<int>& arr) {
    int n = arr.size();
    #pragma omp parallel
    {
        for (int i = 0; i < n - 1; ++i) {
            #pragma omp for
            for (int j = 0; j < n - i - 1; ++j) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
}

// Merge Function for Merge Sort
void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i) {
        L[i] = arr[l + i];
    }
    for (int j = 0; j < n2; ++j) {
        R[j] = arr[m + 1 + j];
    }

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
    
}

// Sequential Merge Sort
void mergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Parallel Merge Sort
void parallelMergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMergeSort(arr, l, m);
            #pragma omp section
            parallelMergeSort(arr, m + 1, r);
        }
        merge(arr, l, m, r);
    }
}

int main() {
    int n = 10; // Size of the array
    vector<int> arr={3,4,1,6,2,6,2,8,9,10};

    // Initialize array with random values

    vector<int> arr_copy(arr); // Copy of the array for comparison

    // Measure performance of Sequential Bubble Sort
    auto start = high_resolution_clock::now();
    bubbleSort(arr);
    auto end = high_resolution_clock::now();
    auto duration_bubble = duration_cast<milliseconds>(end - start);
    cout << "Sequential Bubble Sort Time: " << duration_bubble.count() << " milliseconds\n";

    
    // Measure performance of Parallel Bubble Sort
    start = high_resolution_clock::now();
    parallelBubbleSort(arr_copy);
    end = high_resolution_clock::now();
    auto duration_parallel_bubble = duration_cast<milliseconds>(end - start);
    cout << "Parallel Bubble Sort Time: " << duration_parallel_bubble.count() << " milliseconds\n";

    // Reset array
    arr_copy = arr;

    // Measure performance of Sequential Merge Sort
    start = high_resolution_clock::now();
    mergeSort(arr, 0, n - 1);
    end = high_resolution_clock::now();
    auto duration_merge = duration_cast<milliseconds>(end - start);
    cout << "Sequential Merge Sort Time: " << duration_merge.count() << " milliseconds\n";

    // Measure performance of Parallel Merge Sort
    start = high_resolution_clock::now();
    parallelMergeSort(arr_copy, 0, n - 1);
    end = high_resolution_clock::now();
    auto duration_parallel_merge = duration_cast<milliseconds>(end - start);
    cout << "Parallel Merge Sort Time: " << duration_parallel_merge.count() << " milliseconds\n";

    return 0;
}
