// 9 Sorts Implementations
// There is an attached file containing 9 different testcases in order not to use cin or take input from user

#include <iostream>
#include <algorithm>
#include <chrono>
#include <type_traits>
#include <fstream>

using namespace std;

ifstream file("testcases.txt");
int decision;

template<typename T>
class SortingSystem {
    T *data;
    int size;

    // Function to check whether to use attached file or enter data manually
    int chooseAlgorithm(int choice) {
        cout
        << "\nSorting Algorithm:\n 1. Insertion Sort\n 2. Selection Sort\n 3. Bubble Sort\n 4. Shell Sort\n 5. Merge Sort\n 6. Quick Sort\n 7. Count Sort (Only for integers)\n 8. Radix Sort (Only for integers)\n 9. Bucket Sort "
        << endl;
        if (decision == 1) {
            file >> choice;
            cout << "Chosen Sorting Algorithm: " << choice << endl;
        } else if (decision == 2) {
            cout << "Please choose the sorting algorithm: " << endl;
            cin >> choice;
        }
        return choice;

    }

    void mergeSortLinker() {
        mergeSort(0, size - 1);
    }

    void quickSortLinker() {
        quickSort(0, size - 1);
        cout<<"\nSorted Data: ";
        displayData();
    }

    void count(int place) {
        int aux[10] = {0};
        int *sorted = new int[size]();
        for (int i = 0; i < size; i++) {
            sorted[i] = 0;
        }

        for (int i = 0; i < size; i++) {
            int digit = (data[i] / place) % 10;
            aux[digit]++;
        }
        for (int i = 1; i < 10; i++) {
            aux[i] += aux[i - 1];
        }
        for (int i = size - 1; i >= 0; i--) {
            int digit = (data[i] / place) % 10;
            sorted[aux[digit] - 1] = data[i];
            aux[digit]--;
            cout << "iteration " << size - i << ": [ ";
            for (int j = 1; j <= size; j++) {
                cout << sorted[j] << " ";
            }
            cout << "]" << endl;
        }
        for (int i = 0; i < size; i++) {
            data[i] = sorted[i];
        }
        delete[] sorted;
    }

public:
    SortingSystem(T *arr, int n) : size(n) {
        data = new T[size];
        for (int i = 0; i < size; i++) {
            data[i] = arr[i];
        }
    }

    ~SortingSystem() {
        delete[] data;
    }

    void insertionSort() {
        for (int i = 1, j; i < size; i++) {
            T temp = data[i];
            cout << "\nIteration " << i << ": Inserting " << temp << endl;

            for (j = i; j > 0 && temp < data[j - 1]; j--) {
                data[j] = data[j - 1];

                cout << "After shifting: [ ";
                for (int k = 0; k < size; k++) {
                    cout << data[k] << " ";
                }
                cout << "]" << endl;

            }
            data[j] = temp;

            cout << "Array after placing " << temp << " : [ ";
            for (int k = 0; k < size; k++) {
                cout << data[k] << " ";
            }
            cout << "]" << endl;
        }
        cout << "\nSorted Data: ";
        displayData();
    }

    void selectionSort() {
        for (int i = 0; i < size - 1; i++) {
            cout << "\nIteration " << i + 1 << ": Finding the smallest element from index " << i << " to " << size-1
                 << endl;
            int least = i;
            for (int j = i + 1; j < size; j++) {
                cout << "Comparing data[" << j << "] = " << data[j] << " with data[" << least << "] = " << data[least]
                     << endl;
                if (data[j] < data[least]) {
                    least = j;
                    cout << "Minimum found at index " << least << " (value: " << data[least] << ")" << endl;
                }
            }
            cout << "Swapping data[" << i << "] = " << data[i] << " with data[" << least << "] = " << data[least]
                 << endl;
            T temp = data[i];
            data[i] = data[least];
            data[least] = temp;
        }
        cout << "\nSorted Data: ";
        displayData();

    }

    void bubbleSort() {
        for (int i = 0; i < size - 1; i++) {
            bool swapped = false;
            cout << "\nIteration " << i + 1 << ": \n";
            for (int j = 0; j < size - i - 1; j++) {
                cout << "  Comparing data["<<j<<"]= "<< data[j] << " and data[" <<j+1<<"]= "<< data[j + 1];
                if (data[j] > data[j + 1]) {
                    T temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                    swapped = true;
                    cout << " -> swapped\n";
                } else {
                    cout << " -> no swap\n";
                }
            }
            cout << "  After iteration " << i + 1 << ": ";
            displayData();
            cout << endl;
            if (!swapped) {
                cout << "  No swaps in this iteration. Array is sorted early.\n";
                break;
            }
        }
        cout << "\nSorted Data: ";
        displayData();
    }

    void shellSort() {
        int count=1;
        for (int i = size / 2; i > 0; i /= 2) {
            cout << "\nIteration: " << count <<" Gap= "<<i<< endl;
            for (int k = i; k < size; k++) {
                T temp = data[k];
                int j = k;

                cout << "\nComparing and inserting data[" << k << "] = " << temp << endl;
                while (j >= i && temp < data[j - i]) {
                    cout << "Shifting data[" << j - i << "] = " << data[j - i]
                         << " to position " << j << endl;
                    data[j] = data[j - i];
                    j -= i;
                }

                data[j] = temp;
                cout << "Inserted temp = " << temp << " at position " << j << endl;

                cout << "Array after insertion: ";
                displayData();
                cout << endl;
            }
            count++;
        }

        cout << "\nSorted Data: ";
        displayData();
    }


    void mergeSort(int left, int right) {
        if (left >= right) {
            return;
        } else {
            int middle = (right + left) / 2;
            mergeSort(left, middle);
            mergeSort(middle + 1, right);
            merge(left, middle, right);
            cout << "\nSorted Data: ";
            displayData();
        }
    }

    void quickSort(int left, int right) {
        if (left < right) {
            int j = partition(left, right);
            quickSort(left, j - 1);
            quickSort(j + 1, right);
        }
        cout << "Sorted Data: ";
        displayData();
        cout << endl;
    }

    void countSort() {
        cout << "Sorting using Count Sort: " << endl;
        if (size <= 1) return;

        T Max = *max_element(data, data + size);

        T *aux = new T[Max + 1]();
        T *sorted = new T[size];

        cout << "\nHow many times each number occurred: " << endl;
        for (int i = 0; i < size; i++) {
            aux[data[i]]++;
            cout << "Iteration " << i << ": -> Aux array [ ";
            for (int j = 0; j <= Max; j++) {
                cout << aux[j] << " ";
            }
            cout << "]" << endl;
        }

        cout << "\nCumulative sums: " << endl;
        for (int i = 1; i <= Max; i++) {
            aux[i] += aux[i - 1];
            cout << "Iteration " << i << ": -> Aux array [ ";
            for (int j = 0; j <= Max; j++) {
                cout << aux[j] << " ";
            }
            cout << "]" << endl;
        }

        cout << "\nBuilding the sorted array: " << endl;
        for (int i = size - 1; i >= 0; i--) {
            sorted[aux[data[i]] - 1] = data[i];
            aux[data[i]]--;

            cout << "Iteration " << size - i << ": [ ";
            for (int j = 0; j < size; j++) {
                cout << sorted[j] << " ";
            }
            cout << "]" << endl;
        }

        cout << "\nSorted Data: [ ";
        for (int i = 0; i < size; i++) {
            cout << sorted[i] << " ";
        }
        cout << "]" << endl;

        delete[] aux;
        delete[] sorted;
    }

    void radixSort() {
        int maxNum = *max_element(data, data + size);

        for (int exp = 1; maxNum / exp > 0; exp *= 10) {
            count(exp);

            cout << "\nAfter sorting with place " << exp << ": ";
            for (int i = 0; i < size; i++) {
                cout << data[i] << " ";
            }
            cout << endl;
        }
        cout << "\nSorted Data: ";
        displayData();
    }

    void bucketSort() {
        T Min = *min_element(data, data + size);
        T Max = *max_element(data, data + size);
        T singleBucketRange = (Max - Min) / size + 1;

        T **buckets = new T *[size];
        int *bucketSizes = new int[size]();
        for (int i = 0; i < size; i++) {
            buckets[i] = new T[size];
        }
        cout << "\n Distribute items into buckets: " << endl;
        for (int i = 0; i < size; i++) {
            int bucketindex = (data[i] - Min) / singleBucketRange;
            bucketindex = min(bucketindex, size - 1);
            buckets[bucketindex][bucketSizes[bucketindex]++] = data[i];
            cout << "Iteration " << i + 1 << " -> Buckets: " << endl;
            for (int j = 0; j < size; j++) {
                cout << "Bucket " << j + 1 << "[ ";
                for (int k = 0; k < bucketSizes[j]; k++) {
                    cout << buckets[j][k] << " ";
                }
                cout << "]" << endl;
            }
        }
        cout << "Sort buckets: " << endl;
        for (int i = 0; i < size; i++) {

            // Insertion Sort for each bucket
            for (int j = 1; j < bucketSizes[i]; j++) {
                T key = buckets[i][j];
                int k = j - 1;
                while (k >= 0 && buckets[i][k] > key) {
                    buckets[i][k + 1] = buckets[i][k];
                    k--;
                }
                buckets[i][k + 1] = key;
            }
            cout << "Iteration " << i + 1 << " -> Sorted Bucket " << i + 1 << " [ ";
            for (int j = 0; j < bucketSizes[i]; j++) {
                cout << buckets[i][j] << " ";
            }
            cout << "]" << endl;
        }
        int newindex = 0;
        cout << "Merge buckets again: " << endl;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < bucketSizes[i]; j++) {
                data[newindex++] = buckets[i][j];
                cout << "Iteration " << newindex << ": [ ";
                for (int k = 0; k < size; k++) {
                    cout << data[k] << " ";
                }
                cout << "]" << endl;
            }
        }
        for (int i = 0; i < size; i++) {
            delete[] buckets[i];
        }
        delete[] buckets;
        delete[] bucketSizes;
        cout << "\nSorted Data: ";
        displayData();
    }

    void merge(int left, int mid, int right) {
        int firstSize = mid - left + 1;
        int secSize = right - mid;

        T *leftarr = new T[firstSize];
        T *rightarr = new T[secSize];

        cout << "\nSplit array into left and right arrays:" << endl;
        cout << "Left array [ ";
        for (int i = 0; i < firstSize; i++) {
            leftarr[i] = data[left + i];
            cout << leftarr[i] << " ";
        }
        cout << "]" << endl;
        cout << "Right array [ ";
        for (int i = 0; i < secSize; i++) {
            rightarr[i] = data[mid + 1 + i];
            cout << rightarr[i] << " ";
        }
        cout << "]" << endl;

        int i = 0, j = 0;
        int k = left;
        int iter = 1;  // Tracks merge steps, starting from 1

        while (i < firstSize && j < secSize) {
            if (leftarr[i] < rightarr[j]) {
                data[k++] = leftarr[i++];
            } else {
                data[k++] = rightarr[j++];
            }
            cout << "Iteration " << iter++ << " -> data: ";
            displayData();
            cout << endl;
        }

        while (i < firstSize) {
            data[k++] = leftarr[i++];
            cout << "Iteration " << iter++ << " -> data: ";
            displayData();
            cout << endl;
        }

        while (j < secSize) {
            data[k++] = rightarr[j++];
            cout << "Iteration " << iter++ << " -> data: ";
            displayData();
            cout << endl;
        }

        delete[] leftarr;
        delete[] rightarr;
    }

    int partition(int low, int high) {
        T x = data[low];
        int i = low;
        T left[high - low + 1], right[high - low + 1];
        int leftCount = 0, rightCount = 0;

        for (int j = low + 1; j <= high; ++j) {
            if (data[j] < x) {
                i++;
                T temp = data[i];
                data[i] = data[j];
                data[j] = temp;
            }
        }

        T temp = data[i];
        data[i] = data[low];
        data[low] = temp;

        for (int k = low; k < i; ++k) {
            left[leftCount++] = data[k];
        }
        for (int k = i + 1; k <= high; ++k) {
            right[rightCount++] = data[k];
        }

        cout << "Pivot: " << x << " -> [";
        for (int k = 0; k < leftCount; ++k) {
            cout << left[k];
            if (k < leftCount - 1) cout << ", ";
        }
        cout << "] " << data[i] << " [";
        for (int k = 0; k < rightCount; ++k) {
            cout << right[k];
            if (k < rightCount - 1) cout << ", ";
        }
        cout << "]" << endl;

        return i;
    }

    void displayData() {
        cout << "[ ";
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << "]";
    }

    void measureSortTime(void (SortingSystem::*sortFunc)()) {
        auto start = chrono::high_resolution_clock::now();
        (this->*sortFunc)();
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> time = end - start;
        cout << "\n Sort Time = " << time.count() << endl << endl;

    }

    void showMenu() {
        int choice = chooseAlgorithm(choice);
        switch (choice) {
            case 1:
                cout << "Sorting using Insertion Sort... " << endl;
                cout << "Initial data: ";
                displayData();
                cout << endl;
                measureSortTime(&SortingSystem::insertionSort);
                break;
            case 2:
                cout << "Sorting using Selection Sort... " << endl;
                cout << "Initial data: ";
                displayData();
                cout << endl;
                measureSortTime(&SortingSystem::selectionSort);
                break;
            case 3:
                cout << "Sorting using Bubble Sort... " << endl;
                cout << "Initial data: ";
                displayData();
                cout << endl;
                measureSortTime(&SortingSystem::bubbleSort);
                break;
            case 4:
                cout << "Sorting using Shell Sort... " << endl;
                cout << "Initial data: ";
                displayData();
                cout << endl;
                measureSortTime(&SortingSystem::shellSort);
                break;
            case 5:
                cout << "Sorting using Merge Sort... " << endl;
                cout << "Initial data: ";
                displayData();
                cout << endl;
                measureSortTime(&SortingSystem::mergeSortLinker);
                break;
            case 6:
                cout << "Sorting using Quick Sort... " << endl;
                cout << "Initial data: ";
                displayData();
                cout << endl;
                measureSortTime(&SortingSystem::quickSortLinker);
                break;
            case 7:
                if constexpr (is_integral<T>::value) {
                    cout << "Sorting using Count Sort... " << endl;
                    cout << "Initial data: ";
                    displayData();
                    cout << endl;
                    measureSortTime(&SortingSystem::countSort);
                } else {
                    cout << "Count Sort is not available for this type.\n";
                }
                break;
            case 8:
                if constexpr (is_integral<T>::value) {
                    cout << "Sorting using Radix Sort... " << endl;
                    cout << "Initial data: ";
                    displayData();
                    cout << endl;
                    measureSortTime(&SortingSystem::radixSort);

                } else {
                    cout << "Radix Sort is not available for this type.\n";
                }

                break;
            case 9:
                if constexpr (is_floating_point<T>::value) {
                    cout << "Sorting using Bucket Sort... " << endl;
                    cout << "Initial data: ";
                    displayData();
                    cout << endl;
                    measureSortTime(&SortingSystem::bucketSort);
                } else if constexpr (is_integral<T>::value) {
                    cout << "Sorting using Bucket Sort... " << endl;
                    cout << "Initial data: ";
                    displayData();
                    cout << endl;
                    measureSortTime(&SortingSystem::bucketSort);
                } else {
                    cout << "Bucket Sort is not available for this type.\n";
                }

                break;


        }


    }
};

int main() {
    cout << "\t\t\t\t\t\t\t\t Welcome to Sorting Algorithms program " << endl;
    cout << "Do you want to use testcase or in attached file or enter your own data? \n 1. Use file \n 2. Enter data "
         << endl;
    cin >> decision;
    // use the attached file
    if (decision == 1) {
        if (!file) {
            cerr << "Error opening file!" << endl;
            return 1;
        }
        int count = 1; // counter to print the testcase number based on the attached file

        while (true) {
            int dataSize, type;
            file >> dataSize;
            cout << "\n\n  TESTCASE " << count << endl << endl;
            cout << "Please enter the data size: " << dataSize << endl;


            cout << "Choose the data type: \n 1.Integer \n 2.Double \n 3.String \n 4.Char" << endl;
            file >> type;
            cout << "Chosen type: " << type << endl;
            switch (type) {
                case 1: {
                    int *arr = new int[dataSize];
                    for (int i = 0; i < dataSize; i++) {
                        file >> arr[i];
                        cout << "Enter data " << i + 1 << ": " << arr[i] << endl;
                    }
                    SortingSystem<int> data(arr, dataSize);
                    data.showMenu();
                    delete[] arr;
                    break;
                }
                case 2: {
                    double *arr = new double[dataSize];
                    for (int i = 0; i < dataSize; i++) {
                        file >> arr[i];
                        cout << "Enter data " << i + 1 << ": " << arr[i] << endl;
                    }
                    SortingSystem<double> data(arr, dataSize);
                    data.showMenu();
                    delete[] arr;
                    break;
                }
                case 3: {
                    string *arr = new string[dataSize];
                    for (int i = 0; i < dataSize; i++) {
                        file >> arr[i];
                        cout << "Enter data " << i + 1 << ": " << arr[i] << endl;
                    }
                    SortingSystem<string> data(arr, dataSize);
                    data.showMenu();
                    delete[] arr;
                    break;
                }
                case 4: {
                    char *arr = new char[dataSize];
                    for (int i = 0; i < dataSize; i++) {
                        file >> arr[i];
                        cout << "Enter data " << i + 1 << ": " << arr[i] << endl;
                    }
                    SortingSystem<char> data(arr, dataSize);
                    data.showMenu();
                    delete[] arr;
                    break;
                }

            }
            count++;
            cout << "Do you want to sort another dataset? (y/n):" << endl;
            char option;
            file >> option;
            cout << "Chosen Option: " << option << endl;
            if (option == 'n') {
                cout << "Thank you for using the sorting system! Goodbye!" << endl;
                return 0;
            }

        }


    }
    // Enter Data Manually
    else {
        while (true) {
            int dataSize, type;
            cout << "Please enter the data size: " << endl;
            cin >> dataSize;

            cout << "Choose the data type: \n 1.Integer \n 2.Double \n 3.String \n 4.Char" << endl;
            cin >> type;
            switch (type) {
                case 1: {
                    int *arr = new int[dataSize];
                    for (int i = 0; i < dataSize; i++) {
                        cout << "Enter data " << i + 1 << ": ";
                        cin >> arr[i];
                    }
                    SortingSystem<int> data(arr, dataSize);
                    data.showMenu();
                    delete[] arr;
                    break;
                }
                case 2: {
                    double *arr = new double[dataSize];
                    for (int i = 0; i < dataSize; i++) {
                        cout << "Enter data " << i + 1 << ": ";
                        cin >> arr[i];
                    }
                    SortingSystem<double> data(arr, dataSize);
                    data.showMenu();
                    delete[] arr;
                    break;
                }
                case 3: {
                    string *arr = new string[dataSize];
                    for (int i = 0; i < dataSize; i++) {
                        cout << "Enter data " << i + 1 << ": ";
                        cin >> arr[i];
                    }
                    SortingSystem<string> data(arr, dataSize);
                    data.showMenu();
                    delete[] arr;
                    break;
                }
                case 4: {
                    char *arr = new char[dataSize];
                    for (int i = 0; i < dataSize; i++) {
                        cout << "Enter data " << i + 1 << ": ";
                        cin >> arr[i];
                    }
                    SortingSystem<char> data(arr, dataSize);
                    data.showMenu();
                    delete[] arr;
                    break;
                }

            }
            cout << "Do you want to sort another dataset? (y/n):" << endl;
            char option;
            cin >> option;
            if (option == 'n') {
                cout << "Thank you for using the sorting system! Goodbye!" << endl;
                return 0;
            }

        }

    }
}
