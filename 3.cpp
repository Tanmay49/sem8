#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int arr_max(vector<int> arr)
{
    int maximum = arr[0];
    double start = omp_get_wtime();

#pragma omp parallel for reduction  (max:maximum)
    for (int i = 0; i < arr.size(); i++)
    {
        maximum = max(maximum, arr[i]);
    };
    double end = omp_get_wtime();
    cout << "Parallel Max Reduction" << end - start << endl;
    cout<<"Parallel Max Reduction"<<maximum;
    cout<<endl;

    return maximum;
}
int arr_max_seq(vector<int> arr)
{
    int maximum = arr[0];
    double start = omp_get_wtime();

    for (int i = 0; i < arr.size(); i++)
    {
        maximum = max(maximum, arr[i]);
    };
    double end = omp_get_wtime();
    cout << "Seq Max Reduction" << end - start << endl;
    cout<<"Seq Max Reduction"<<maximum;
    cout<<endl;

    return maximum;
}
int arr_min(vector<int> arr)
{
    int minimum = arr[0];
    double start = omp_get_wtime();

#pragma omp parallel for reduction  (min:minimum)
    for (int i = 0; i < arr.size(); i++)
    {
        minimum = min(minimum, arr[i]);
    };
    double end = omp_get_wtime();
    cout << "Parallel Min Reduction" << end - start << endl;
    cout<<"Parallel Min Reduction"<<minimum;
    cout<<endl;
    return minimum;
}
int arr_min_seq(vector<int> arr)
{
    int minimum = arr[0];
    double start = omp_get_wtime();
    for (int i = 0; i < arr.size(); i++)
    {
        minimum = min(minimum, arr[i]);
    };
    double end = omp_get_wtime();
    cout << "Seq Min Reduction" << end - start << endl;
    cout<<"Seq Min Reduction"<<minimum;
    cout<<endl;
    
    return minimum;
}

int arr_sum(vector<int> arr){
    int sum=0;
    double start = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < arr.size(); i++)
    {
        sum+=arr[i];
    }
    double end = omp_get_wtime();
    cout << "Sum Reduction" << end - start << endl;
    cout<<"Sum Reduction"<<sum;
    cout<<endl;
    return sum;

}
int arr_sum_seq(vector<int> arr){
    int sum=0;
    double start = omp_get_wtime();
    // #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < arr.size(); i++)
    {
        sum+=arr[i];
    }
    double end = omp_get_wtime();
    cout << "Seq Sum Reduction" << end - start << endl;
    cout<<"Seq Sum Reduction"<<sum;
    cout<<endl;
    return sum;

}
int arr_avg(vector<int> arr){
    int sum=arr_sum(arr);
    int avg=sum/arr.size();
    cout<<"Avg"<<avg<<endl;
    return avg ;
}
int main()

{
    int N = 90000000;
    vector<int> arr = {1, 2, 4, 5, 7, 2, 6,0};

    for (int i = 0; i < N; i++)
    {
        arr.push_back(rand() % 1000);
    }
    int maximum=arr_max(arr);
    int max_seq=arr_max_seq(arr);
    int min=arr_min(arr);
    int min_seq=arr_min_seq(arr);
    int sum=arr_sum(arr);
     sum=arr_sum_seq(arr);
     int avg=arr_avg(arr);

}
