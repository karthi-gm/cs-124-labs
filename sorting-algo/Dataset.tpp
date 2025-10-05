#include <algorithm>


template <typename T>
Dataset<T>::Dataset(const T arr[], int n) {
    size = n;                   
    data = new T[size];         
    for (int i = 0; i < size; i++) {
        data[i] = arr[i];       
    }
    srand(time(nullptr));
}


template <typename T>
Dataset<T>::~Dataset() {
    delete[] data; 
}

template <typename T>
int Dataset<T>::selection_sort(bool reversed) {
    int swapCount = 0;


    for (int i = 0; i < size - 1; i++) {
        int targetIndex = i; 

        for (int j = i + 1; j < size; j++) {

            if ((!reversed && data[j] < data[targetIndex]) ||
                (reversed && data[j] > data[targetIndex])) {
                targetIndex = j; 
            }
        }

        // Rule: Always count this as a swap, even if i == targetIndex
        swap(data[i], data[targetIndex]);
        swapCount++;
    }

    return swapCount;
}

template <typename T>
int Dataset<T>::insertion_sort(bool reversed) {
    int shiftCount = 0; 

    
    for (int i = 1; i < size; i++) {
        T key = data[i];   
        int j = i - 1;      
       
        while (j >= 0 && ((!reversed && data[j] > key) ||
                          (reversed && data[j] < key))) {
            data[j + 1] = data[j]; 
            j--;
            shiftCount++;          
        }

        
        data[j + 1] = key;
    }

    return shiftCount;
}

template <typename T>
int Dataset<T>::bubble_sort(bool reversed) {
    int swapCount = 0; 
    bool swapped;

    // Outer loop: keep making passes through array
    for (int i = 0; i < size - 1; i++) {
        swapped = false;

        // Inner loop: compare adjacent pairs
        for (int j = 0; j < size - i - 1; j++) {
           
            if ((!reversed && data[j] > data[j + 1]) ||
                (reversed && data[j] < data[j + 1])) {
                swap(data[j], data[j + 1]); 
                swapCount++;                
                swapped = true;          
            }
        }

        
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
    
    if (left >= right) return 1;

    int mid = (left + right) / 2; // Find midpoint

    int count = 1;
    count += mergeSortHelper(left, mid, reversed);     // Left half
    count += mergeSortHelper(mid + 1, right, reversed); // Right half

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

    delete[] L;
    delete[] R;
}

template <typename T>
void Dataset<T>::shuffle() {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1); 
        swap(data[i], data[j]);   
    }
}

template <typename T>
void Dataset<T>::print() const {
    for (int i = 0; i < size; i++) {
        cout << data[i] << " ";
    }
    cout << endl;
}