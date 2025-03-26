#include <iostream>
#include <algorithm>
#include <chrono>

using namespace std;

template<typename T>
class SortingSystem {
    T *data;
    int size;

    void mergeSortLinker() {
        mergeSort(0, size - 1);
    }

    void count(int place) {
        int aux[10] = {0};  // Counting array for digits 0-9
        int *sorted = new int[size]();  // Temporary sorted array
        //fill(sorted, sorted + size, 0);
        for (int i=0;i<size;i++){
            sorted[i]=0;
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
            cout << "iteration " << size - i << ": -> Sorted array [ ";
            for (int j = 1; j <= size; j++) {
                cout << sorted[j] << " ";
            }
            cout << "]" << endl;
        }
        // Step 4: Copy sorted array back to original array
        for (int i = 0; i < size; i++) {
            data[i] = sorted[i];
        }
        delete[] sorted;
    }

public:
    SortingSystem(T *arr, int n) : size(n) {
        data = new T[size];
        for (int i = 0; i < size; i++) {
            data[i] = arr[i]; // Copy array elements
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
            cout << "Sorted array after merging: ";
            display();
            cout << endl;
        }
    }

    void quick();

    void count() {
        cout << "Sorting using Count Sort: " << endl;
        if (size <= 1) return;
        T Max = *max_element(data, data + size);

        // Create auxiliary arrays dynamically
        T *aux = new T[Max + 1]();   // Initialized to 0
        T *sorted = new T[size];     // Sorted output array

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
            cout << "iteration " << size - i << ": -> Sorted array [ ";
            for (int j = 1; j <= size; j++) {
                cout << sorted[j] << " ";
            }
            cout << "]" << endl;
        }
        delete[] aux;
        delete[] sorted;
    }

    void radix() {
// Find the maximum number to determine the number of digits
        int maxNum = *max_element(data, data + size);

        // Perform Counting Sort for each digit place (1s, 10s, 100s, etc.)
        for (int exp = 1; maxNum / exp > 0; exp *= 10) {
            count(exp);

            // Print array after sorting each digit place
            cout << "After sorting with place " << exp << ": ";
            for (int i = 0; i < size; i++) {
                cout << data[i] << " ";
            }
            cout << endl;
        }
    }

    void bucket() {
        cout << "Sorting using Bucket Sort: " << endl;
        T Min = *min_element(data, data + size);
        T Max = *max_element(data, data + size);
        T singleBucketRange = (Max - Min) / size + 1;

        // Step 1: Create buckets (array of arrays)
        T **buckets = new T *[size];  // Array of pointers
        int *bucketSizes = new int[size](); // Initialize bucket sizes to 0
        // Allocate memory for each bucket
        for (int i = 0; i < size; i++) {
            buckets[i] = new T[size];  // Each bucket can hold up to `size` elements
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
            cout << "Iteration " << i + 1 << " -> Sorted Bucket " << i + 1 << "[ ";
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
                // Print array status after each merge step
                cout << "Iteration " << newindex << " -> Array [ ";
                for (int k = 0; k < size; k++) {
                    cout << data[k] << " ";
                }
                cout << "]" << endl;
            }
        }
        // Step 5: Free allocated memory
        for (int i = 0; i < size; i++) {
            delete[] buckets[i];
        }
        delete[] buckets;
        delete[] bucketSizes;
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

    void partition(int low, int high);

    void display() {
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
    }

    void measureSortTime(void (SortingSystem::*sortFunc)()) {
        auto start = chrono::high_resolution_clock::now();
        (this->*sortFunc)();
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> time = end - start;
        cout << "\n Sort Time = " << time.count() << endl << endl;

    }

    void showMenu() {
        cout
                << "\nSorting Algorithm:\n 1. Insertion Sort\n 2. Selection Sort\n 3. Bubble Sort\n 4. Shell Sort\n 5. Merge Sort\n 6. Quick Sort\n 7. Count Sort (Only for integers)\n 8. Radix Sort (Only for integers)\n 9. Bucket Sort "
                << endl;
        cout << "Please enter your choice(1-9): " << endl;
        int choice;
        cin >> choice;
        while (choice != 10) {
            switch (choice) {
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                case 5:
                    measureSortTime(&SortingSystem::mergeSortLinker);
                    break;
                case 6:
                    break;
                case 7:
                    measureSortTime(&SortingSystem::count);
                    break;
                case 8:
                    measureSortTime(&SortingSystem::radix);
                    break;
                case 9:
                    measureSortTime(&SortingSystem::bucket);
                    break;


            }
            cout << "Do you want to sort another dataset? (y/n):" << endl;
            char option;
            cin >> option;
            switch (option) {
                case 'y':
                    cout
                            << "\nSorting Algorithm:\n 1. Insertion Sort\n 2. Selection Sort\n 3. Bubble Sort\n 4. Shell Sort\n 5. Merge Sort\n 6. Quick Sort\n 7. Count Sort (Only for integers)\n 8. Radix Sort (Only for integers)\n 9. Bucket Sort "
                            << endl;
                    cout << "Please enter your choice(1-9): " << endl;
                    cin >> choice;
                    break;
                case 'n':
                    cout << "Thank you for using the sorting system! Goodbye!" << endl;
                    return;

            }

        }
    }
};

int main() {
    cout << "\t\t\t\t\t\t\t\t Welcome to Sorting Algorithms program " << endl;
    cout << "Please enter the data size: " << endl;
    int dataSize;
    cin >> dataSize;
    int *arr = new int[dataSize];
            for (int i = 0; i < dataSize; i++) {
                cout << "Enter data " << i + 1 << ": ";
                cin >> arr[i];
            }
            SortingSystem<int> s(arr, dataSize);
            cout << "Before Sorting: ";
            s.display();
            s.showMenu();
            delete[] arr;
//    cout << "Choose the data type: \n 1.Integer \n 2.Float \n 3.String \n 4.Char" << endl;
//    int type;
//    cin >> type;
//    switch (type) {
//        case 1: {
//            int *arr = new int[dataSize];
//            for (int i = 0; i < dataSize; i++) {
//                cout << "Enter data " << i + 1 << ": ";
//                cin >> arr[i];
//            }
//            SortingSystem<int> s(arr, dataSize);
//            cout << "Before Sorting: ";
//            s.display();
//            s.showMenu();
//            delete[] arr;
//            break;
//        }
//        case 2: {
//            float *arr = new float[dataSize];
//            for (int i = 0; i < dataSize; i++) {
//                cout << "Enter data " << i + 1 << ": ";
//                cin >> arr[i];
//            }
//            SortingSystem<float> s(arr, dataSize);
//            cout << "Before Sorting: ";
//            s.display();
//            s.showMenu();
//            delete[] arr;
//            break;
//        }
//        case 3: {
//            string *arr = new string[dataSize];
//            for (int i = 0; i < dataSize; i++) {
//                cout << "Enter data " << i + 1 << ": ";
//                cin >> arr[i];
//            }
//            SortingSystem<string> s(arr, dataSize);
//            cout << "Before Sorting: ";
//            s.display();
//            s.showMenu();
//            delete[] arr;
//            break;
//        }
//        case 4: {
//            char *arr = new char[dataSize];
//            for (int i = 0; i < dataSize; i++) {
//                cout << "Enter data " << i + 1 << ": ";
//                cin >> arr[i];
//            }
//            SortingSystem<char> s(arr, dataSize);
//            cout << "Before Sorting: ";
//            s.display();
//            s.showMenu();
//            delete[] arr;
//            break;
//        }
//
//    }



    return 0;
}
