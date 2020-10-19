/**
 * This program simlates a program that processes list of jobs in parallel.
 * @file job_queue.cpp
 * @author Bhed Kumar Kushwaha
 * @version 1.0
 **/
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using std::cin;
using std::cout;
using std::pair;
using std::pop_heap;
using std::push_heap;
using std::vector;

/**
 * sturct to define how comparisons will be performed in heap for pair of int
 * and long long int.
 **/
struct comp {
    bool operator()(const pair<int, long long> &i,
                    const pair<int, long long> &j) {
        if (i.second == j.second) {
            return i.first > j.first;
        } else {
            return i.second > j.second;
        }
    }
};

class JobQueue {
   private:
    int num_workers_;
    vector<int> jobs_;

    vector<int> assigned_workers_;
    vector<long long> start_times_;

    void WriteResponse() const {
        for (int i = 0; i < jobs_.size(); ++i) {
            cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
        }
    }

    void ReadData() {
        int m;
        cin >> num_workers_ >> m;
        jobs_.resize(m);
        for (int i = 0; i < m; ++i) cin >> jobs_[i];
    }

    void AssignJobs() {
        vector<pair<int, long long>> heap;
        int i{}, job_ind{};
        while ((i < num_workers_) && (job_ind < (int)jobs_.size())) {
            assigned_workers_.push_back(i);
            start_times_.push_back(0);

            if (jobs_[job_ind] != 0) {
                heap.push_back(std::make_pair(i, jobs_[job_ind]));
                push_heap(heap.begin(), heap.end(), comp());
                i++;
            }
            job_ind++;
        }

        while (job_ind < (int)jobs_.size()) {
            int worker{heap.front().first};
            long long start_time{heap.front().second};

            assigned_workers_.push_back(worker);
            start_times_.push_back(start_time);
            if (jobs_[job_ind] != 0) {
                pop_heap(heap.begin(), heap.end(), comp());

                heap[num_workers_ - 1].first = worker;
                heap[num_workers_ - 1].second = start_time + jobs_[job_ind];
                push_heap(heap.begin(), heap.end(), comp());
            }
            job_ind++;
        }
    }

   public:
    void Solve() {
        ReadData();
        AssignJobs();
        WriteResponse();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    JobQueue job_queue;
    job_queue.Solve();
    return 0;
}
