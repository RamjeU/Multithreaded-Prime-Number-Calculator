# Multithreaded Prime Calculator

This program implements a high-performance prime number calculator that leverages multiple threads to parallelize the computation of prime numbers. It accepts a maximum number and thread count from the user, then divides the computational workload across the specified number of threads to efficiently calculate both the count and sum of all prime numbers up to the given maximum.

## Implementation Details

- Uses POSIX threads (pthreads) for parallel processing
- Implements optimized prime number detection algorithm
- Employs data parallelism by dividing number ranges across threads
- Handles large numbers (up to 1,000,000) using appropriate data types
- Thread-safe design with proper synchronization
- Combines results from all threads for final calculation

## Requirements

- GCC compiler
- POSIX threads library
- Math library

## Compilation

Compile the program using:
```bash
gcc -o assignment-3 assignment-3.c -pthread -lm
```

## Usage

Run the program with two command-line arguments:
```bash
./assignment-3 <num_threads> <max_number>
```

Where:
- `num_threads`: Number of threads to create for parallel processing
- `max_number`: Maximum number to check for primes (up to 1,000,000)

## Examples

1. Single thread, maximum number 25:
```bash
./assignment-3 1 25
```

2. Four threads, maximum number 25:
```bash
./assignment-3 4 25
```

3. Twenty-five threads, maximum number 100:
```bash
./assignment-3 25 100
```

## Output Format

The program outputs progress and results for each thread, followed by the grand totals. Example outputs:

### Single Thread (1 thread, max 25)
```
Thread # 0 is finding primes from low = 0 to high = 25 
Thread # 0 Sum is 100, Count is 9 

        GRAND SUM IS 100, COUNT IS 9
```

### Multiple Threads (4 threads, max 25)
```
Thread # 0 is finding primes from low = 0 to high = 7 
Thread # 0 Sum is 10, Count is 3 
Thread # 1 is finding primes from low = 7 to high = 14 
Thread # 1 Sum is 31, Count is 3 
Thread # 2 is finding primes from low = 14 to high = 21 
Thread # 2 Sum is 36, Count is 2 
Thread # 3 is finding primes from low = 21 to high = 25 
Thread # 3 Sum of is 23, Count is 1

        GRAND SUM IS 100, COUNT IS 9
```

## Technical Notes

- Thread ranges are calculated by dividing the maximum number by the thread count
- The last thread handles any remaining numbers if the division isn't even
- Results are accumulated using thread-safe techniques
- Uses long long data type for sums to handle large numbers
- Prime detection algorithm optimized for performance

## Performance Considerations

- More threads generally improve performance up to the number of available CPU cores
- Optimal thread count depends on the maximum number being processed
- Very small ranges with many threads may have overhead that outweighs benefits
- Memory usage scales linearly with thread count
