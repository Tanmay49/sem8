#include<iostream>
#include<vector>
#include<omp.h>

using namespace std;
void sbs(vector<int> arr){
    int it=arr.size()-1;
    for (int i=0;i<=it;i++){
        for(int j=0;j<=it-i;j++){
            if(arr[j]>arr[j+1]){
                swap(arr[j],arr[j+1]);
            }
        }
    }
    // for (int i=0;i<arr.size();i++){
    //     cout<<arr[i]<<" ";
    // }
}
void bs(vector<int> arr){
    int it=arr.size()-1;
    #pragma omp parallel
    for (int i=0;i<=it;i++){
        #pragma omp for
        for(int j=0;j<=it-i;j++){
            if(arr[j]>arr[j+1]){
                swap(arr[j],arr[j+1]);
            }
        }
    }

    // for (int i=0;i<arr.size();i++){
    //     cout<<arr[i]<<" ";
    // }
    // cout<<endl;
}

void merge(vector<int> &arr,int start,int end,int mid){
    vector<int> L;
    vector<int> R;

    for(int i=start;i<=mid;i++){
        L.push_back(arr[i]);
    }    
    for(int i=mid+1;i<=end;i++){
        R.push_back(arr[i]);
    }    
    int i=0;
    int j=0;
    int k=start;
    while(i<L.size()&& j< R.size()){
        if(L[i]<=R[j]){
            arr[k]=L[i];
            i++;
        }else{
            arr[k]=R[j];
            j++;
        }
        k++;
    }
    while(i<L.size()){
        arr[k]=L[i];
        i++;
        k++;
    }
    while(j<R.size()){
        arr[k]=R[j];
        j++;
        k++;
    }
    
}
void ms(vector<int> &arr,int start,int end){
    if(start<end){
        int mid=(start+end)/2;
        ms(arr,start,mid);
        ms(arr,mid+1,end);
        merge(arr,start,end,mid);
    }
}
int main(){
    int N=50000;
    vector<int> arr;
    vector<int> arr_cp;
    for(int i=0;i<N;i++){
        arr.push_back(rand()%N);
    }
    // arr_cp=arr;
    // for(iter=arr.begin();iter!=arr.end();iter++){
    //     cout<<*iter<<endl;
    // }
    // for (int i=0;i<arr.size();i++){
    //     cout<<arr[i]<<" ";
    // }

    cout<<endl;
    // ms(arr,0,arr.size()-1);
    // for (int i=0;i<arr.size();i++){
    //     cout<<arr[i]<<" ";
    // }
    // vector<int>::iterator iter;
    double start=omp_get_wtime();
    sbs(arr);
    double end=omp_get_wtime();
    cout<<"Sequential bs"<<end-start<<endl;
    
    cout<<endl;

    // for (int i=0;i<arr.size();i++){
    //     cout<<arr[i]<<" ";
    // }
    cout<<endl;
    start=omp_get_wtime();
    bs(arr);
    end=omp_get_wtime();
    cout<<"Parallel bs"<<end-start<<endl;
        

    return 0;
}