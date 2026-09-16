#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_prime(long long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

long long get_nth_nsw_prime(int n) {
    if (n <= 0) return -1;
    
    int count = 0;
    long long p0 = 1;
    long long p1 = 1;
    long long p = 1;
    
    int index = 1;
    
    while (true) {
        if (index > 1) {
            p = 2 * p1 + p0;
            p0 = p1;
            p1 = p;
        }
        
        if (is_prime(p)) {
            count++;
            if (count == n) {
                return p;
            }
        }
        index++;
    }
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    int n = atoi(argv[1]);
    if (n <= 0) {
        fprintf(stderr, "Please provide a positive integer.\n");
        return EXIT_FAILURE;
    }
    
    long long result = get_nth_nsw_prime(n);
    if (result == -1) {
        fprintf(stderr, "Error calculating the NSW prime.\n");
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}