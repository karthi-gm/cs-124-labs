#ifndef DATASET_H
#define DATASET_H

#include <iostream>
#include <cstdlib>
#include <ctime>   
using namespace std; 

// Template class Dataset
// This class can store any type T (int, double, string)
template <typename T>
class Dataset {
private:
    T* data;   // Pointer to dynamically allocated array
    int size;  // Number of elements in the dataset

    // Private helper for merge sort recursion
    int mergeSortHelper(int left, int right, bool reversed);

    // Private helper that merges two sorted halves
    void merge(int left, int mid, int right, bool reversed);

public:
    // Constructor: makes a deep copy of an input array
    Dataset(const T arr[], int n);

    // Destructor: cleans up dynamically allocated memory
    ~Dataset();

    // Sorting algorithms (all return an operation count)
    int selection_sort(bool reversed);  
    int insertion_sort(bool reversed);  
    int bubble_sort(bool reversed);     
    int merge_sort(bool reversed);      

    // Shuffle elements randomly (Fisher-Yates shuffle)
    void shuffle();

    // Print dataset to console
    void print() const;
};


#include "Dataset.tpp"

#endif