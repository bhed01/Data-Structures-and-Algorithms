/**
 * The goal of this program is to simulate headsort algorithm and out the swaps
 * performed the process.
 * @file build_head.cpp
 * @author Bhed Kumar Kushwaha
 * @version 1.0
 **/
#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::make_pair;
using std::pair;
using std::swap;
using std::vector;

/**
 * Heap builder class for storing the heap and processing the input
 **/
class HeapBuilder {
   private:
    vector<int> data_;               /// to store the input array
    vector<pair<int, int> > swaps_;  /// to store the swaps performed

    /**
     * Prints the swaps performed on to the console.
     **/
    void WriteResponse() const {
        cout << swaps_.size() << "\n";
        for (int i = 0; i < swaps_.size(); ++i) {
            cout << swaps_[i].first << " " << swaps_[i].second << "\n";
        }
    }

    /**
     * Takes the input data from console and stores it into 'data_'.
     **/
    void ReadData() {
        int n;
        cin >> n;
        data_.resize(n);
        for (int i = 0; i < n; ++i) cin >> data_[i];
    }

    /**
     * Function to swap the node with it's left child and record the swap in
     *'swaps_'.
     **/
    void swap_left_child(long long i) {
        swap(data_[i], data_[2 * i + 1]);
        swaps_.push_back(std::make_pair(i, 2 * i + 1));
    }

    /**
     * Function to swap the node with it's right child and record the swap in
     *'swaps_'.
     **/
    void swap_right_child(long long i) {
        swap(data_[i], data_[2 * i + 2]);
        swaps_.push_back(std::make_pair(i, 2 * i + 2));
    }

    /**
     * Function to shift down the node to appropriate position.
     **/
    void ShiftDown(long long i) {
        if (2 * i + 2 <= data_.size() - 1) {
            int left_child = data_[2 * i + 1];
            int right_child = data_[2 * i + 2];
            if (data_[i] > left_child) {
                if (data_[i] > right_child) {
                    if (left_child > right_child) {
                        /**
                         * If data at node is greater than both child and left
                         * child is greater than right child.
                         * 1. swap node with right child
                         * 2. perform shift down on right child.
                         **/
                        swap_right_child(i);
                        ShiftDown(2 * i + 2);
                    } else {
                        /**
                         * If data at node is greater than both child and right
                         * child is greater than or equal to left child.
                         * 1. swap node with left child
                         * 2. perform shift down on left child.
                         **/
                        swap_left_child(i);
                        ShiftDown(2 * i + 1);
                    }
                } else {
                    /**
                     * If data at node is greater than left child but is smaller
                     * than right child.
                     * 1. swap node with left child
                     * 2. perform shift down on left child.
                     **/
                    swap_left_child(i);
                    ShiftDown(2 * i + 1);
                }
            } else {
                if (data_[i] > right_child) {
                    /**
                     * If data at node is smaller than left child but is greater
                     * than right child.
                     * 1. swap node with right child
                     * 2. perform shift down on right child.
                     **/
                    swap_right_child(i);
                    ShiftDown(2 * i + 2);
                }
            }
        } else if (2 * i + 1 <= data_.size() - 1) {
            int left_child = data_[2 * i + 1];
            if (data_[i] > left_child) {
                swap_left_child(i);
                ShiftDown(2 * i + 1);
            }
        }
    }

    /**
     * Function for generating the swaps.
     **/
    void GenerateSwaps() {
        swaps_.clear();
        for (long long i{(long long)data_.size() / 2 - 1}; i >= 0; i--) {
            ShiftDown(i);
        }
    }

   public:
    /**
     * Public member funtion to initaite the solving process.
     **/
    void Solve() {
        ReadData();
        GenerateSwaps();
        WriteResponse();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    HeapBuilder heap_builder;
    heap_builder.Solve();
    return 0;
}
