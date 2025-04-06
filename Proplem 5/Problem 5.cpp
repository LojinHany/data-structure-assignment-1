#include <iostream>
#include <fstream>
#include <string>
using namespace std;

ifstream inputFile("C:\\Users\\Nour\\CLionProjects\\Assignment_1_DataStructures\\input.txt");

template<typename T>
class StatisticalCalculation {
private:
    T *data;
    int size;

    int partition(T arr[], int low, int high) {
        T pivot = arr[low];
        int i = low;
        int j = high + 1;

        while (true) {
            do { i++; } while (i <= high && arr[i] < pivot);
            do { j--; } while (arr[j] > pivot);

            if (i >= j) break;

            T temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }

        T temp = arr[low];
        arr[low] = arr[j];
        arr[j] = temp;
        return j;
    }

    void QuickSort(T arr[], int low, int high) {
        if (low < high) {
            int j = partition(arr, low, high);
            QuickSort(arr, low, j - 1);
            QuickSort(arr, j + 1, high);
        }
    }

public:
    StatisticalCalculation() {}

    ~StatisticalCalculation() { delete[] data; }

    void inputData() {
        if (!inputFile) {
            cout << "Error: Could not open file 'input.txt'!" << endl;
            return;
        }
        inputFile >> size;
        data = new T[size];

        cout << "Attached data: [";
        for (int i = 0; i < size; i++) {
            inputFile >> data[i];
            cout << data[i] << " ";
        }
        cout << "]\n\n";
    }

    void sort() {
        QuickSort(data, 0, size - 1);
    }

    void displayArray() {
        sort();
        cout << "Sorted Array: ";
        for (int i = 0; i < size; i++) cout << data[i] << " ";
        cout << endl;
    }

    T findMin() {
        T minValue = data[0];
        for (int i = 0; i < size; i++) {
            if (data[i] < minValue)
                minValue = data[i];
        }
        return minValue;
    }

    T findMax() {
        T maxValue = data[0];
        for (int i = 0; i < size; i++) {
            if (data[i] > maxValue)
                maxValue = data[i];
        }
        return maxValue;
    }

    double findMean() {
        if constexpr (is_same<T, string>::value || is_same<T, char>::value) {
            cout << "Mean not available for strings or characters.\n";
            return 0;
        } else {
            double sum = 0;
            for (int i = 0; i < size; i++)
                sum += data[i];
            return sum / size;
        }
    }


    T findSummation() {
        if constexpr (is_same<T, string>::value) {
            string result = "";
            for (int i = 0; i < size; i++)
                result += data[i];
            return result;
        } else if constexpr (is_same<T, char>::value) {
            cout << "Summation not available for characters.\n";
            return 0;
        } else {
            T sum = 0;
            for (int i = 0; i < size; i++)
                sum += data[i];
            return sum;
        }
    }


    T findMedian() {
        sort();
        if constexpr (is_same<T, string>::value || is_same<T, char>::value) {
            return data[size / 2]; // Middle element for string/char
        } else {
            if (size % 2 == 0)
                return (data[size / 2 - 1] + data[size / 2]) / 2.0;
            else
                return data[size / 2];
        }
    }


    void statsMenu(StatisticalCalculation<T> &stats, bool isString = false) {
        int choice;
        do {
            cout << "\nSelect a Statistical Calculation:\n"
                 << " 1. Sort & display\n"
                 << " 2. Find Minimum\n"
                 << " 3. Find Maximum\n"
                 << " 4. Find Mean\n"
                 << " 5. Find Median\n"
                 << " 6. Find Summation\n"
                 << " 7. Exit\n"
                 << "Enter your choice (1-7): ";
            cin >> choice;

            switch (choice) {
                case 1:
                    stats.sort();
                    stats.displayArray();
                    break;
                case 2:
                    cout << "Minimum: " << stats.findMin() << "\n";
                    break;
                case 3:
                    cout << "Maximum: " << stats.findMax() << "\n";
                    break;
                case 4:
                    cout << "Mean: " << stats.findMean() << "\n";
                    break;
                case 5:

                    cout << "Median: " << stats.findMedian() << "\n";
                    break;
                case 6:
                    cout << "Summation: " << stats.findSummation() << "\n";
                    break;
                case 7:
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Invalid choice! Try again.\n";
            }
        } while (choice != 7);
    }
};
    template <typename T>
    void selectDataType() {
        int type;
        cout << "Choose the data type:\n1. Integer\n2. Double\n3. String\n4. Char\nChoice: ";
        cin >> type;

        if (type == 1) {
            StatisticalCalculation<int> stats;
            stats.inputData();
            stats.statsMenu(stats);
        } else if (type == 2) {
            StatisticalCalculation<double> stats;
            stats.inputData();
            stats.statsMenu(stats);
        } else if (type == 3) {
            StatisticalCalculation<string> stats;
            stats.inputData();
            stats.statsMenu(stats, true);
        } else if (type == 4) {
            StatisticalCalculation<char> stats;
            stats.inputData();
            stats.statsMenu(stats, true);
        } else {
            cout << "Invalid type selection!\n";
        }
    }

int main() {
    selectDataType<int>();
    return 0;
}
