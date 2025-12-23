#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <atomic>

void compute_fibonacci(unsigned long long& local_count, std::atomic<bool>& stop_flag) {
    unsigned long long prev = 0, curr = 1, next;

    while (!stop_flag.load()) {
        next = prev + curr;
        prev = curr;
        curr = next;
        local_count++; // Increment the local counter
    }
}

int main() {
    using namespace std;
    using namespace chrono;

    const int num_threads = thread::hardware_concurrency(); // Get the number of available threads
    vector<thread> threads;
    vector<unsigned long long> local_counts(num_threads, 0); // Local counters for each thread
    atomic<bool> stop_flag(false);                          // Flag to signal threads to stop

    // Start the timer
    auto start = high_resolution_clock::now();

    // Launch threads
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(compute_fibonacci, ref(local_counts[i]), ref(stop_flag));
    }

    // Let the threads run for 1 second
    this_thread::sleep_for(seconds(1));

    // Signal threads to stop
    stop_flag.store(true);

    // Join all threads
    for (auto& t : threads) {
        t.join();
    }

    // Aggregate the results from all threads
    unsigned long long total_count = 0;
    for (const auto& local_count : local_counts) {
        total_count += local_count;
    }

    // Output the result
    cout << "Computed " << total_count << " Fibonacci numbers in 1 second using "
        << num_threads << " threads." << endl;

    return 0;
}// g++ -O3 -march=native multithreadfastfibo.cpp -o multithreadfastfibo is the command used to compile this code to enable it to acheive tens of billions of fibonacci numbers from few hundred millions
// The code is a multithreaded Fibonacci number generator that computes Fibonacci numbers in parallel using multiple threads.