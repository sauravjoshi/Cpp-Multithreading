# Cpp-Multithreading
- This repository contains multithreading codes for C++
- Includes the cases of Deadlocks and handling.
- Includes the famous Reader-Writer problem.
- Also contains concurrentInnerProduct of a large Vector using async tasks. 

## Analysis against different synchronization constructs
1. After running the Sum of a large Vector (100M), the analysis is done over the computation time for:
    - A single thread, using accumulate (STL), for-loop.
    - Just to check the comparison between mutexes and atomic, they are also run on a single thread. (Performance decay is understood).
    - The performance of the range-based for loop and the STL algorithm std::accumulate is comparable.
    - Atomics performs faster than mutexes.
    
2. Multithreading is then utilized to calculate the sum of the vector firstly using a shared Variable:
    - The use of a shared variable as the summation variable highlights the fact that synchronization is a costly operation and should be minimized whenever feasible.
3. Finally we utilize thread_local data and tasks to perform the summation, which gives us the best performance.
    - Code for these are included.
    - Despite the fact that each of the four threads can operate independently, the performance gain of using thread-local summation is only twice that of a single-threaded range-based for loop or std::accumulate.
    - The reason for this is the memory system bottleneck that doesn't allow data to be readily available to the CPU cores.
    
