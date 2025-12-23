Multi-Threaded Fibonacci Benchmark
A high-performance C++ tool designed to measure CPU throughput by calculating Fibonacci sequences across all available hardware threads.

🚀 Overview
This program stress-tests your processor by spawning a thread for every logical core detected on your system. Each thread iteratively calculates Fibonacci numbers for exactly one second. The final output provides the total number of iterations completed, serving as a raw indicator of your CPU's multi-threaded performance.

Key Features
Hardware Awareness: Automatically detects the number of logical CPU cores using std::thread::hardware_concurrency().

Thread Safety: Utilizes std::atomic<bool> for clean, synchronized thread termination.

High Precision: Uses the <chrono> library for accurate 1-second timing.

Zero Contention: Each thread increments its own local counter to avoid "false sharing" and atomic bottlenecks during the computation phase.

🛠 Prerequisites
To compile and run this code, you will need:

A C++ compiler that supports C++11 or higher (e.g., g++, clang++, or MSVC).

A system that supports multi-threading (Linux, macOS, or Windows).

🏗 Compilation
Use the following command to compile the program.

Note: It is crucial to use the -O3 optimization flag; otherwise, the performance will be significantly lower, and the compiler may not optimize the arithmetic loops.

Using G++ (Linux/macOS)
Bash

g++ -O3 -pthread -o fib_benchmark main.cpp
Using Clang
Bash

clang++ -O3 -pthread -o fib_benchmark main.cpp
🏃 Usage
Once compiled, simply run the executable:

Bash

./fib_benchmark
Example Output
Plaintext

Computed 1450283940 Fibonacci numbers in 1 second using 16 threads.
🔬 How It Works
Initialization: The program determines how many threads your CPU supports.

Parallel Execution: It launches a vector of threads, each running an iterative Fibonacci loop.

Local Counting: To maximize speed, each thread updates its own unsigned long long counter in memory.

Signal & Join: After 1000ms, the main thread sets an atomic stop_flag to true. All threads exit their loops and join the main thread.

Aggregation: The results from all individual counters are summed and displayed.

⚠️ Important Considerations
Integer Overflow: The Fibonacci numbers themselves will eventually overflow unsigned long long. However, since this is a benchmark for iterations and not mathematical verification, the overflow does not impact the performance metrics.

Thermal Throttling: Running this repeatedly on a laptop or poorly cooled system may result in lower scores as the CPU reduces clock speeds to manage heat.
