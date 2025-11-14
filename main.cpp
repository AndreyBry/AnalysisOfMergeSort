#include "ArrayGenerator.h"
#include "SortTester.h"

void insertionSort(std::vector<int>& array, size_t left, size_t right) {
    for (size_t i = left + 1; i < right + 1; ++i) {
        int key = array[i];
        size_t j = i;
        for (; j >= left + 1 && key < array[j - 1]; --j) {
            array[j] = array[j - 1];
        }
        array[j] = key;
    }
}

void merge(std::vector<int>& array, size_t left, size_t mid, size_t right) {
    std::vector<int> result(right - left + 1);
    size_t curIndex = 0;
    size_t l = left;
    size_t r = mid + 1;
    while (l <= mid || r <= right) {
        if (l <= mid && (r > right || array[l] <= array[r])) {
            result[curIndex++] = array[l++];
        } else {
            result[curIndex++] = array[r++];
        }
    }
    for (size_t i = 0; i < result.size(); ++i) {
        array[left + i] = result[i];
    }
}

void mergeSort(std::vector<int>& array, size_t left, size_t right, size_t threshold=1) {
    if (right - left + 1 > threshold) {
        size_t mid = (left + right) / 2;
        mergeSort(array, left, mid);
        mergeSort(array, mid + 1, right);
        merge(array, left, mid, right);
    }
}

void mergeInsertionSort(std::vector<int>& array, size_t left, size_t right, size_t threshold=1) {
    if (right - left + 1 > threshold) {
        size_t mid = (left + right) / 2;
        mergeInsertionSort(array, left, mid, threshold);
        mergeInsertionSort(array, mid + 1, right, threshold);
        merge(array, left, mid, right);
    } else {
        insertionSort(array, left, right);
    }
}

int main() {
    ArrayGenerator arrayGenerator(500, 100000, 100, 0, 6000);
    SortTester sortTester;
    sortTester.testSort(arrayGenerator, mergeSort, "merge_sort");
    sortTester.reset();
    sortTester.testSort(arrayGenerator, mergeInsertionSort, "merge_insertion15_sort", 15);
    sortTester.reset();
    sortTester.testSort(arrayGenerator, mergeInsertionSort, "merge_insertion30_sort", 30);
    sortTester.reset();
    sortTester.testSort(arrayGenerator, mergeInsertionSort, "merge_insertion60_sort", 60);
    return 0;
}
