#include <algorithm> // for swap

// Constructor
// Purpose: Copy elements from input array into internal array
// Notes:
//   - We allocate new memory so changes to the dataset won't
//     affect the original array passed in.
template <typename T>
Dataset<T>::Dataset(const T arr[], int n) {
    size = n;                   // Store number of elements
    data = new T[size];         // Allocate new memory
    for (int i = 0; i < size; i++) {
        data[i] = arr[i];       // Deep copy each element
    }
    srand(time(nullptr));       // Seed random generator
}

// Destructor
// Purpose: Prevent memory leaks by releasing heap memory.
template <typename T>
Dataset<T>::~Dataset() {
    delete[] data; // Free dynamically allocated memory
}

template <typename T>
int Dataset<T>::selection_sort(bool reversed) {
    int swapCount = 0; // Count how many swaps happen

    // Outer loop: moves boundary between sorted/unsorted
    for (int i = 0; i < size - 1; i++) {
        int targetIndex = i; // Assume current index is min (or max)

        // Inner loop: find the min/max in the rest of array
        for (int j = i + 1; j < size; j++) {
            // If not reversed, look for smaller values
            // If reversed, look for larger values
            if ((!reversed && data[j] < data[targetIndex]) ||
                (reversed && data[j] > data[targetIndex])) {
                targetIndex = j; // Found new candidate
            }
        }

        // Swap the found element into correct position
        // Rule: Always count this as a swap, even if i == targetIndex
        swap(data[i], data[targetIndex]);
        swapCount++;
    }

    return swapCount;
}

template <typename T>
int Dataset<T>::insertion_sort(bool reversed) {
    int shiftCount = 0; // Count how many shifts happen

    // Start from second element (first element is trivially sorted)
    for (int i = 1; i < size; i++) {
        T key = data[i];    // The element we want to insert
        int j = i - 1;      // Index of last element in sorted portion

        // Move elements greater than (or smaller if reversed) key
        // to one position ahead to make space
        while (j >= 0 && ((!reversed && data[j] > key) ||
                          (reversed && data[j] < key))) {
            data[j + 1] = data[j]; // Shift element right
            j--;
            shiftCount++;          // Count each shift
        }

        // Place key into correct location
        // Final placement is NOT counted as a shift
        data[j + 1] = key;
    }

    return shiftCount;
}

template <typename T>
int Dataset<T>::bubble_sort(bool reversed) {
    int swapCount = 0; // Count swaps
    bool swapped;      // Track if a pass made changes

    // Outer loop: keep making passes through array
    for (int i = 0; i < size - 1; i++) {
        swapped = false; // Reset at start of pass

        // Inner loop: compare adjacent pairs
        for (int j = 0; j < size - i - 1; j++) {
            // If not reversed, swap if left > right
            // If reversed, swap if left < right
            if ((!reversed && data[j] > data[j + 1]) ||
                (reversed && data[j] < data[j + 1])) {
                swap(data[j], data[j + 1]); // Swap neighbors
                swapCount++;                // Count swap
                swapped = true;             // Mark that swap occurred
            }
        }

        // If no swaps in a pass, array is already sorted
        if (!swapped) break;
    }

    return swapCount;
}

template <typename T>
int Dataset<T>::merge_sort(bool reversed) {
    return mergeSortHelper(0, size - 1, reversed);
}


template <typename T>
int Dataset<T>::mergeSortHelper(int left, int right, bool reversed) {
    // Base case: single element is already sorted
    if (left >= right) return 1; // Count this call

    int mid = (left + right) / 2; // Find midpoint

    // Count = this call + recursive calls on halves
    int count = 1;
    count += mergeSortHelper(left, mid, reversed);     // Left half
    count += mergeSortHelper(mid + 1, right, reversed); // Right half

    // Merge the two sorted halves
    merge(left, mid, right, reversed);

    return count;
}

template <typename T>
void Dataset<T>::merge(int left, int mid, int right, bool reversed) {
    int n1 = mid - left + 1;  // Size of left half
    int n2 = right - mid;     // Size of right half

    // Create temp arrays
    T* L = new T[n1];
    T* R = new T[n2];

    // Copy data into temp arrays
    for (int i = 0; i < n1; i++) L[i] = data[left + i];
    for (int j = 0; j < n2; j++) R[j] = data[mid + 1 + j];

    // Merge back into main array
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if ((!reversed && L[i] <= R[j]) ||
            (reversed && L[i] >= R[j])) {
            data[k++] = L[i++];
        } else {
            data[k++] = R[j++];
        }
    }

    // Copy leftovers
    while (i < n1) data[k++] = L[i++];
    while (j < n2) data[k++] = R[j++];

    // Free temp arrays
    delete[] L;
    delete[] R;
}

// Shuffle (Fisher-Yates)
// Algorithm idea:
//   - For each index i from end to start,
//     pick random j in [0..i], then swap i and j.
template <typename T>
void Dataset<T>::shuffle() {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1); // Random index 0..i
        swap(data[i], data[j]);   // Swap into position
    }
}

// Print
// Purpose: Output contents of dataset to console.
template <typename T>
void Dataset<T>::print() const {
    for (int i = 0; i < size; i++) {
        cout << data[i] << " "; // Print each element
    }
    cout << endl;
}