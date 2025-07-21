#include <iostream>
#include <cstdlib>
#include <chrono>
#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#include <psapi.h>
#else
#include <sys/resource.h>
#endif

#ifdef _WIN32
constexpr size_t total_bytes = 4L * GB;
#else
constexpr size_t total_bytes = 2L * GB;
#endif


void print_page_faults() {
#ifdef _WIN32
    PROCESS_MEMORY_COUNTERS counters;
    GetProcessMemoryInfo(GetCurrentProcess(), &counters, sizeof(counters));
    printf("Page Fault Count: %lu\n", counters.PageFaultCount);
    printf("Amount of virtual memory backed by swap: %lu\n", counters.PagefileUsage);
#else
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    printf("Minor Faults: %ld, Major Faults: %ld\n",
           usage.ru_minflt, usage.ru_majflt);
#endif
}

int main(){

    size_t size = total_bytes / sizeof(int);
    int* array = (int*)malloc(total_bytes);

    if (array == nullptr) {
        std::cerr << "Memory allocation failed" << std::endl;
        return 1;
    }

    // Sequential write
    for (size_t i = 0; i < size; i++) {
        array[i] = i;
    }

    // Sequential read
    long long sum = 0;
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    for(int j = 0; j < 10000; j++)
    {
        sum = 0; // Reset sum for each iteration
        for (size_t i = 0; i < size; i++) {
            sum += array[i];
        }
    }
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::nano> duration = end - start;
    std::cout << "Sequential read duration: " << duration.count() << " nanoseconds" << std::endl;

    // Random read
    srand(time(NULL));
    long long sum_random = 0;
    std::chrono::high_resolution_clock::time_point start_random = std::chrono::high_resolution_clock::now();
    for(int j = 0; j < 10000; j++)
    {
        sum_random = 0; 
        for (size_t i = 0; i < size; i++) {
            size_t index = rand() % size;
            sum_random += array[index];
        }
        
    }
    
    std::chrono::high_resolution_clock::time_point end_random = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::nano> duration_random = end_random - start_random;
    std::cout << "Random read duration: " << duration_random.count() << " nanoseconds" << std::endl;

    // Access triggers swap once RAM is exceeded
    for (size_t i = 0; i < 8L * 1024 * 1024 * 1024; i += 4096 / sizeof(int)) {
        array[i] = 42;  // Touch every 4KB page
    }
    print_page_faults();


    return 0;
}