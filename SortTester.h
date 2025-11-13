#ifndef PLOTTINGGRAPHS_PY_SORTTESTER_H
#define PLOTTINGGRAPHS_PY_SORTTESTER_H

#include <cstdint>
#include <vector>
#include <functional>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

#include "ArrayGenerator.h"

class SortTester {
public:
    void testSort(ArrayGenerator& arrayGenerator, const std::function<void(std::vector<int>&, size_t, size_t, size_t)>& algorithm,
                  const std::string& fileNamePrefix, size_t threshold = 1, size_t runs = 5) {
        // Random array
        while (true) {
            auto array = arrayGenerator.nextRandomArray();
            if (array.empty()) break;
            size_t time = takeAverageTime(array, algorithm, threshold=threshold, runs=runs);
            randomResults.emplace_back(array.size(), time);
        }

        arrayGenerator.reset();

        // Back sorted array
        while (true) {
            auto array = arrayGenerator.nextBackSortedArray();
            if (array.empty()) break;
            size_t time = takeAverageTime(array, algorithm, threshold=threshold, runs=runs);
            backSortedResults.emplace_back(array.size(), time);
        }

        arrayGenerator.reset();

        // Almost sorted array
        while (true) {
            auto array = arrayGenerator.nextAlmostSortedArray();
            if (array.empty()) break;
            size_t time = takeAverageTime(array, algorithm, threshold=threshold, runs=runs);
            almostSortedResults.emplace_back(array.size(), time);
        }

        arrayGenerator.reset();

        saveResultsToCSV(randomResults, "../data/" + fileNamePrefix + "_random.csv");
        saveResultsToCSV(backSortedResults, "../data/" + fileNamePrefix + "_back_sorted.csv");
        saveResultsToCSV(almostSortedResults, "../data/" + fileNamePrefix + "_almost_sorted.csv");
    }

    void reset() {
        randomResults.clear();
        backSortedResults.clear();
        almostSortedResults.clear();
    }

private:
    std::vector<std::pair<size_t, size_t>> randomResults;
    std::vector<std::pair<size_t, size_t>> backSortedResults;
    std::vector<std::pair<size_t, size_t>> almostSortedResults;

    static size_t takeAverageTime(std::vector<int>& array, const std::function<void(std::vector<int>&, size_t, size_t, size_t)>& algorithm,
                                  size_t threshold = 1, size_t runs = 5) {
        std::vector<size_t> times(runs);
        for (size_t i = 0; i < runs; ++i) {
            std::vector<int> copiedArray = array;
            auto start = std::chrono::high_resolution_clock::now();
            algorithm(copiedArray, 0, copiedArray.size() - 1, threshold);
            auto elapsed = std::chrono::high_resolution_clock::now() - start;
            size_t msec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
            times[i] = msec;
        }
        std::sort(times.begin(), times.end());
        return times[runs / 2];
    }

    static void saveResultsToCSV(const std::vector<std::pair<size_t, size_t>>& results, const std::string& filename) {
        std::ofstream file(filename);
        file << "Size,Time(microseconds)\n";
        for (const auto& [size, time] : results) {
            file << size << "," << time << "\n";
        }
        file.close();
    }
};

#endif //PLOTTINGGRAPHS_PY_SORTTESTER_H