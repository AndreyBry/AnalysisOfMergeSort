#ifndef A2_ARRAYGENERATOR_H
#define A2_ARRAYGENERATOR_H

#include <cstdint>
#include <vector>
#include <random>
#include <algorithm>

class ArrayGenerator {
public:
    ArrayGenerator(size_t minSize, size_t maxSize, size_t step, int minNumber, int maxNumber) {
        _minSize = minSize;
        _maxSize = maxSize;
        _currentSize = minSize;
        _step = step;
        _minNumber = minNumber;
        _maxNumber = maxNumber;

        fillArrays();
    }

    std::vector<int> nextRandomArray() {
        if (_currentSize > _maxSize) {
            return {};
        }
        std::vector<int> result(_randomArray.begin(), _randomArray.begin() + _currentSize);
        _currentSize += _step;
        return result;
    }

    std::vector<int> nextBackSortedArray() {
        if (_currentSize > _maxSize) {
            return {};
        }
        std::vector<int> result(_backSortedArray.begin(), _backSortedArray.begin() + _currentSize);
        _currentSize += _step;
        return result;
    }

    std::vector<int> nextAlmostSortedArray() {
        if (_currentSize > _maxSize) {
            return {};
        }
        std::vector<int> result(_almostSortedArray.begin(), _almostSortedArray.begin() + _currentSize);
        _currentSize += _step;
        return result;
    }

    void reset() {
        _currentSize = _minSize;
    }

private:
    size_t _minSize;
    size_t _maxSize;
    size_t _currentSize;
    size_t _step;
    int _minNumber;
    int _maxNumber;

    std::vector<int> _randomArray;
    std::vector<int> _backSortedArray;
    std::vector<int> _almostSortedArray;

    void fillArrays() {
        _randomArray = getRandomArray();

        _backSortedArray = _randomArray;
        std::sort(_backSortedArray.begin(), _backSortedArray.end());
        _almostSortedArray = _backSortedArray;

        std::reverse(_backSortedArray.begin(), _backSortedArray.end());
        shuffleArray(_almostSortedArray);
    }

    void shuffleArray(std::vector<int>& array) const {
        std::mt19937 gen(42);
        std::uniform_int_distribution<int> int_dist(0, _maxSize - 1);
        for (size_t i = 0; i < _maxSize / 20; ++i) {
            int first = int_dist(gen);
            int second = int_dist(gen);
            std::swap(array[first], array[second]);
        }
    }

    std::vector<int> getRandomArray() const {
        std::mt19937 gen(42);
        std::uniform_int_distribution<int> int_dist(_minNumber, _maxNumber);
        std::vector<int> randomArray(_maxSize);
        for (size_t i = 0; i < _maxSize; ++i) {
            randomArray[i] = int_dist(gen);
        }
        return randomArray;
    }
};


#endif //A2_ARRAYGENERATOR_H