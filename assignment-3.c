#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

// Structure to hold thread parameters and results
typedef struct {
    long long low;           // Starting number for this thread
    long long high;          // Ending number for this thread
    int thread_id;          // Thread identifier
    long long sum;          // Sum of primes found by this thread
    int count;             // Count of primes found by this thread
} thread_data;

// Function to check if a number is prime
int is_prime(long long n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;

    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return 0;
        }
    }
    return 1;
}

// Thread function to find primes in a range
void* find_primes(void* arg) {
    thread_data* data = (thread_data*)arg;
    data->sum = 0;
    data->count = 0;

    printf("Thread # %d is finding primes from low = %lld to high = %lld\n", 
           data->thread_id, data->low, data->high);

    // Find primes in the range and calculate sum
    for (long long i = data->low; i < data->high; i++) {
        if (is_prime(i)) {
            data->sum += i;
            data->count++;
        }
    }

    printf("Thread # %d Sum is %lld, Count is %d\n", 
           data->thread_id, data->sum, data->count);

    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <num_threads> <max_number>\n", argv[0]);
        return 1;
    }

    // Parse command line arguments
    int num_threads = atoi(argv[1]);
    long long max_number = atoll(argv[2]);

    if (num_threads < 1 || max_number < 1) {
        printf("Invalid arguments\n");
        return 1;
    }

    // Create arrays for thread management
    pthread_t* threads = malloc(num_threads * sizeof(pthread_t));
    thread_data* thread_args = malloc(num_threads * sizeof(thread_data));

    // Calculate range size for each thread
    long long range_size = max_number / num_threads;

    // Create threads
    for (int i = 0; i < num_threads; i++) {
        thread_args[i].thread_id = i;
        thread_args[i].low = i * range_size;
        
        // For last thread, ensure we go up to max_number
        if (i == num_threads - 1) {
            thread_args[i].high = max_number;
        } else {
            thread_args[i].high = (i + 1) * range_size;
        }

        pthread_create(&threads[i], NULL, find_primes, &thread_args[i]);
    }

    // Wait for all threads to complete
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Calculate grand totals
    long long grand_sum = 0;
    int grand_count = 0;
    for (int i = 0; i < num_threads; i++) {
        grand_sum += thread_args[i].sum;
        grand_count += thread_args[i].count;
    }

    printf("\n\tGRAND SUM IS %lld, COUNT IS %d\n", grand_sum, grand_count);

    // Clean up
    free(threads);
    free(thread_args);

    return 0;
}
