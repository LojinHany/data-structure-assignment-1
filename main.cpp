#include <iostream>
//Selection Sort
using namespace std;
template <class T>
void selectionSort(T arr[] , int size){
    for(int i=0; i<size-1; i++){
        int least=i;
        for(int j=i+1; j<size; j++){
                if(arr[j]< arr[least]){
                    least=j;
                }
        }
        T temp=arr[i];
        arr[i]=arr[least];
        arr[least]=temp;
    }
}

int main()
{
    int arr[] = {5,7,2,4,9,1};
    selectionSort(arr,6);
    for (int i=0; i<6; i++) {
        cout <<arr[i]<<" ";
    }
    cout<<endl;

    return 0;
}
