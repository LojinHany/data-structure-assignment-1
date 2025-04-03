#include <iostream>
#include <fstream>
using namespace std;

template<typename T>

class StatisticalCalculation{
private:

    T* data;            // Dynamically allocated array for sorting data
    int size;           // Number of elements in the array

    // QuickSort Algorithm
    int partition(T arr[] ,int low , int high){
        T pivot = arr[low];
        int i= low;
        int j= high;
        while(i < j){
            do {i++;} while (arr[i] <= pivot);
            do {j--;} while (arr[j] > pivot);
            if (i < j) swap(arr[i], arr[j]);

        }
        swap(arr[low], arr[j]);
        return j;
    }
    void QuickSort(T A[],int low , int high){
        if(low < high){
            int j = partition(A,low , high);
            QuickSort(A,low,j);
            QuickSort(A, j+1,high);
        }
    }
public:

    StatisticalCalculation(){}

    ~StatisticalCalculation(){delete[] data;}

    void inputData() {
        ifstream inputFile("C:/Users/Nour/CLionProjects/Assignment_1_DataStructures/input.txt");
        if (!inputFile) {
            cout << "Error: Could not open file 'input.txt'!" << endl;
            return;
        }

        inputFile >> size;
        data = new T[size];
        for (int i = 0; i < size; i++) {
            inputFile >> data[i];
        }

        inputFile.close();
    }

    void sort(){
        QuickSort(data,0,size);
    }

    void displayArray() {
        sort();
        cout << "Sorted Array: "<<endl;
        for (int i = 0; i < size; i++){
            cout << data[i] << " ";
        }
        cout << endl;
    }

    T findMedian() {
        sort();
        if (size % 2 == 0) {
            return (data[size / 2 - 1] + data[size / 2]) / 2.0;
        } else {
            return data[size / 2];
        }
    }

    T findMin() {
        T minValue = data[0];
        for (int i = 0; i < size; i++){
            if(data[i] < minValue)
                minValue = data[i];
        }
        return minValue;
    }

    T findMax() {
        T maxValue = data[0];
        for(int i = 0; i < size;i++){
            if(data[i] > maxValue)
                maxValue = data[i];
        }
        return maxValue;
    }

    double findMean() {
        double sum = 0;
        for (int i = 0; i < size;i++){
            sum += data[i];
        }
        return sum/size;
    }

    T findSummation() {
        T sum = 0;
        for(int i = 0;i < size;i++){
            sum += data[i];
        }
        return sum;
    }

    void statisticsMenu() {
        int choice;
        do{
            cout << "Select a Statistical Calculation:"
                 << "\n 1. Sort & display"
                 << "\n 2. Find Minimum"
                 << "\n 3. Find Maximum"
                 << "\n 4. Find Mean"
                 << "\n 5. Find Median"
                 << "\n 6. Find Summation"
                 << "\n 7. Exit"
                 << "\n Enter your choice (1-7): " << endl;
            cin >> choice;

            switch (choice){
                case 1: sort(); displayArray();
                    break;
                case 2: cout << "Minimum: " << findMin() << endl;
                    break;
                case 3: cout << "Maximum: " << findMax() << endl;
                    break;
                case 4: cout << "Mean: " << findMean() << endl;
                    break;
                case 5: cout << "Median: " << findMedian() << endl;
                    break;
                case 6: cout << "Summation: " << findSummation() << endl;
                    break;
                case 7: cout << "Exit" << endl;
                    break;
                default: cout << "Invalid choice! Please Enter a choice between 1 - 7." << endl;
            }
        } while (choice != 7);
    }
};


int main() {

    StatisticalCalculation<int> stats;
    stats.inputData();
    stats.statisticsMenu();

    return 0;
}
