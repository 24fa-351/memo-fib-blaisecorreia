#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

unsigned long long int fib_i(unsigned long long int n) {
    if (n <= 1) return n;

    unsigned long long int prev1 = 0, prev2 = 1, current;
    for (unsigned long long int i = 2; i <= n; i++) {
        current = prev1 + prev2;
        prev1 = prev2;
        prev2 = current;
    }
    return current;
}

unsigned long long int fib_r(unsigned long long int n) {
    if (n <= 1) return n;
    return fib_r(n - 1) + fib_r(n - 2);
}

unsigned long long int fib_memo(unsigned long long int n, unsigned long long int *memo) {
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];  // Return cached result if available

    memo[n] = fib_memo(n - 1, memo) + fib_memo(n - 2, memo);  // Store result
    return memo[n];
}


unsigned long long int fib_wrapper(unsigned long long int n) {
    unsigned long long int *memo = (unsigned long long int *) malloc((n + 1) * sizeof(unsigned long long int));
    for (unsigned long long int i = 0; i <= n; i++) memo[i] = -1;  // Initialize memoization table
    unsigned long long int result = fib_memo(n, memo);
    free(memo);  // Free allocated memory
    return result;
}


unsigned long long int fib_with_func_ptr(unsigned long long int n, unsigned long long int (*fib_func)(unsigned long long int)) {
    return fib_func(n);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <integer> <r/i> <filename>\n", argv[0]);
        return 1;
    }

    unsigned long long int num1 = strtoull(argv[1], NULL, 10);

    
    FILE *file = fopen(argv[3], "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", argv[3]);
        return 1;
    }
    unsigned long long int num2;
    fscanf(file, "%llu", &num2);
    fclose(file);

    unsigned long long int N = num1 + num2;

    unsigned long long int result;
    clock_t start, end;
    double cpu_time_used;

    if (strcmp(argv[2], "i") == 0) {
        
        start = clock();
        result = fib_with_func_ptr(N, fib_i);  // Using function pointer for iterative version
        end = clock();
    } else if (strcmp(argv[2], "r") == 0) {
        
        start = clock();
        result = fib_with_func_ptr(N, fib_wrapper);  // Using function pointer for memoized version
        end = clock();
    } else {
        printf("Error: Invalid method. Use 'r' for recursive or 'i' for iterative.\n");
        return 1;
    }

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    
    printf("The %lluth Fibonacci number is: %llu\n", N, result);
    printf("Time taken: %f seconds\n", cpu_time_used);

    return 0;
}
