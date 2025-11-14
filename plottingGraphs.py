import matplotlib.pyplot as plt
import pandas as pd
import numpy as np


def plotting():
    data1 = pd.read_csv("data/merge_sort_almost_sorted.csv")
    data2 = pd.read_csv("data/merge_insertion30_sort_almost_sorted.csv")
    # data3 = pd.read_csv("data/merge_insertion60_sort_almost_sorted.csv")

    plt.figure(figsize=(16, 10))
    plt.yscale('log')

    plt.plot(data1['Size'], data1['Time(microseconds)'], '-', label='Merge Sort', linewidth=2)
    plt.plot(data2['Size'], data2['Time(microseconds)'], '-', label='Merge+Insertion30 Sort', linewidth=2)
    # plt.plot(data3['Size'], data3['Time(microseconds)'], '-', label='Merge+Insertion60 Sort', linewidth=2)

    sizes = np.array(data1['Size'])
    n_log_n = sizes * np.log2(sizes)
    scale_factor = data1['Time(microseconds)'].iloc[-1] / n_log_n[-1]
    n_log_n_scaled = n_log_n * scale_factor
    plt.plot(sizes, n_log_n_scaled, 'k--', label='n log n', linewidth=2)

    plt.xlabel('Array Size')
    plt.ylabel('Time (microseconds)')
    plt.title('Merge Sort Performance')
    plt.legend(fontsize=12)
    plt.grid(True, alpha=0.3)
    plt.show()


def main():
    plotting()


if __name__ == '__main__':
    main()
