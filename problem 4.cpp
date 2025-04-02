#include <iostream>
#include <algorithm>
#include <chrono>
#include <type_traits>
#include <fstream>

using namespace std;

ifstream file("testcases.txt");

template<typename T>
class SortingSystem {
    T *data;
    int size;

    void mergeSortLinker() {
        mergeSort(0, size - 1);
    }

    void quickSortLinker() {
        quick(0, size - 1);
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

    void insertion();

    void selection();

    void bubble();

    void shell();

    void mergeSort(int l, int r) {
        if (l < r) {
            int middle = l + (r - l) / 2;
            mergeSort(l, middle);
            mergeSort(middle + 1, r);
            merge(l, middle, r);
            cout << "\nSorted Data: ";
            display();
        }
    }

    void quick(int left, int right) {
        if (left < right) {
            int j = partition(left, right);
            quick(left, j - 1);
            quick(j + 1, right);
        }
        cout << "Sorted Data: ";
        display();
    }

    void count() {
        cout << "Sorting using Count Sort: " << endl;
        if (size <= 1) return;
        T Max = *max_element(data, data + size);

        T *aux = new T[Max + 1]();
        T *sorted = new T[size];

        cout << "\n How many times occurred: " << endl;
        for (int i = 0; i < size; i++) {
            aux[data[i]]++;
            cout << "iteration " << i << ": -> Aux array [ ";
            for (int j = 1; j <= Max; j++) {
                cout << aux[j] << " ";
            }
            cout << "]" << endl;
        }
        cout << "\n Cumulative sums: " << endl;
        for (int i = 2; i <= Max; i++) {
            aux[i] = aux[i] + aux[i - 1];
            cout << "iteration " << i - 1 << ": -> Aux array [ ";
            for (int j = 1; j <= Max; j++) {
                cout << aux[j] << " ";
            }
            cout << "]" << endl;
        }
        cout << "\n Sorted array: " << endl;
        for (int i = size - 1; i >= 0; i--) {
            sorted[aux[data[i]]] = data[i];
            aux[data[i]]--;
            cout << "iteration " << size - i << ": [ ";
            for (int j = 1; j <= size; j++) {
                cout << sorted[j] << " ";
            }
            cout << "]" << endl;
        }
        delete[] aux;
        delete[] sorted;
        cout << "\nSorted Data: [";
        for (int i = 1; i <= size; i++) {
            cout << sorted[i] << " ";
        }
        cout << " ]";
    }

    void radix() {
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
        display();
    }

    void bucket() {
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
            sort(buckets[i], buckets[i] + bucketSizes[i]); // USE MANUAL SORT
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
        display();
    }

    void merge(int left, int mid, int right) {
        int firstSize = mid - left + 1;
        int secSize = right - mid;

        T *leftarr = new T[firstSize];
        T *rightarr = new T[secSize];

        cout << "Split array into left and right arrays:" << endl;
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

        int i = 0, j = 0, k = left;
        while (i < firstSize && j < secSize) {
            if (leftarr[i] <= rightarr[j]) {
                data[k] = leftarr[i++];
            } else {
                data[k] = rightarr[j++];
            }
            cout << "Iteration " << k - left + 1 << " -> data: ";
            display();
            cout << endl;
            k++;
        }

        while (i < firstSize) {
            data[k] = leftarr[i++];
            cout << "Iteration " << k - left + 1 << " -> data: ";
            display();
            cout << endl;
            k++;
        }
        while (j < secSize) {
            data[k] = rightarr[j++];
            cout << "Iteration " << k - left + 1 << " -> data: ";
            display();
            cout << endl;
            k++;
        }
        delete[] leftarr;
        delete[] rightarr;
    }

    int partition(int low, int high) {
        T pivot = data[low];
        int i = low;
        int j = high + 1;
        while (i < j) {
            do {
                i++;
            } while (data[i] <= pivot);
            do {
                j--;
            } while (data[j] > pivot);
            if (i < j) {
                swap(data[i], data[j]);
            }
        }

        swap(data[low], data[j]);

        cout << "Pivot: " << pivot << " -> ";
        cout << "[";
        for (int k = 0; k < j; ++k) {
            if (k > 0) cout << ", ";
            cout << data[k];
        }
        cout << "] " << data[j] << " [";
        for (int k = j + 1; k < size; ++k) {
            if (k > j + 1) cout << ", ";
            cout << data[k];
        }
        cout << "]\n";

        return j;
    }

    void display() {
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
        int choice;
        cout
                << "\nSorting Algorithm:\n 1. Insertion Sort\n 2. Selection Sort\n 3. Bubble Sort\n 4. Shell Sort\n 5. Merge Sort\n 6. Quick Sort\n 7. Count Sort (Only for integers)\n 8. Radix Sort (Only for integers)\n 9. Bucket Sort "
                << endl;
        file >> choice;
        cout << "Chosen Sorting Algorithm: " << choice << endl;
        switch (choice) {
            case 1:
                cout << "Sorting using Insertion Sort... " << endl;
                cout << "Initial data: ";
                display();
                cout << endl;
                break;
            case 2:
                cout << "Sorting using Selection Sort... " << endl;
                cout << "Initial data: ";
                display();
                cout << endl;
                break;
            case 3:
                cout << "Sorting using Bubble Sort... " << endl;
                cout << "Initial data: ";
                display();
                cout << endl;
                break;
            case 4:
                cout << "Sorting using Shell Sort... " << endl;
                cout << "Initial data: ";
                display();
                cout << endl;
                break;
            case 5:
                cout << "Sorting using Merge Sort... " << endl;
                cout << "Initial data: ";
                display();
                cout << endl;
                measureSortTime(&SortingSystem::mergeSortLinker);
                break;
            case 6:
                cout << "Sorting using Quick Sort... " << endl;
                cout << "Initial data: ";
                display();
                cout << endl;
                measureSortTime(&SortingSystem::quickSortLinker);
                break;
            case 7:
                if constexpr (std::is_integral<T>::value) {
                    cout << "Sorting using Count Sort... " << endl;
                    cout << "Initial data: ";
                    display();
                    cout << endl;
                    measureSortTime(&SortingSystem::count);
                } else {
                    cout << "Count Sort is not available for this type.\n";
                }
                break;
            case 8:
                if constexpr (std::is_integral<T>::value) {
                    cout << "Sorting using Radix Sort... " << endl;
                    cout << "Initial data: ";
                    display();
                    cout << endl;
                    measureSortTime(&SortingSystem::radix);

                } else {
                    cout << "Radix Sort is not available for this type.\n";
                }

                break;
            case 9:
                if constexpr (std::is_floating_point<T>::value) {
                    cout << "Sorting using Bucket Sort... " << endl;
                    cout << "Initial data: ";
                    display();
                    cout << endl;
                    measureSortTime(&SortingSystem::bucket);
                } else if constexpr (std::is_integral<T>::value) {
                    cout << "Sorting using Bucket Sort... " << endl;
                    cout << "Initial data: ";
                    display();
                    cout << endl;
                    measureSortTime(&SortingSystem::bucket);
                } else {
                    cout << "Bucket Sort is not available for this type.\n";
                }

                break;


        }


    }
};

int main() {
    cout << "\t\t\t\t\t\t\t\t Welcome to Sorting Algorithms program " << endl;

    if (!file) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    while (true) {
        int dataSize, type;
        file >> dataSize;
        cout << "Please enter the data size: " << dataSize << endl;


        cout << "Choose the data type: \n 1.Integer \n 2.Float \n 3.String \n 4.Char" << endl;
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
                float *arr = new float[dataSize];
                for (int i = 0; i < dataSize; i++) {
                    file >> arr[i];
                    cout << "Enter data " << i + 1 << ": " << arr[i] << endl;
                }
                SortingSystem<float> data(arr, dataSize);
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
