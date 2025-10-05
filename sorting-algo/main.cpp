#include "Dataset.h"
#include <iostream>
using namespace std;

int main() {
    const int SIZE = 10;
    int arr[SIZE] = {};
    
    // Seed the random number generator with the current time
    srand(time(nullptr));
    
    for (int i = 0; i < SIZE; i++)
    {
        // Assigns random number between 1-100 to array element
        arr[i] = (rand() % 100) + 1;
    }

    // Original dataset
    Dataset<int> ds(arr, SIZE);
    cout << "Original: ";
    ds.print();

    // Selection Sort ascending
    Dataset<int> ds1(arr, SIZE);          // fresh copy
    int swaps = ds1.selection_sort(false);
    cout << "Selection Sort ascending: ";
    ds1.print();
    cout << "Swaps = " << swaps << endl;

    // Insertion Sort descending
    Dataset<int> ds2(arr, SIZE);
    int shifts = ds2.insertion_sort(true);
    cout << "Insertion Sort descending: ";
    ds2.print();
    cout << "Shifts = " << shifts << endl;

    // Bubble Sort ascending
    Dataset<int> ds3(arr, SIZE);
    int bubSwaps = ds3.bubble_sort(false);
    cout << "Bubble Sort ascending: ";
    ds3.print();
    cout << "Swaps = " << bubSwaps << endl;

    // Merge Sort descending
    Dataset<int> ds4(arr, SIZE);
    int mergeCalls = ds4.merge_sort(true);
    cout << "Merge Sort descending: ";
    ds4.print();
    cout << "Recursive calls = " << mergeCalls << endl;

    // Shuffle
    Dataset<int> ds5(arr, SIZE);
    cout << "Before shuffle: ";
    ds5.print();
    ds5.shuffle();
    cout << "After shuffle: ";
    ds5.print();

    return 0;
}