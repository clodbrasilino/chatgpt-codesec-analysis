#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_prime(long long int n) {
    if (n <= 1) {
        return false;
    }
    if (n <= 3) {
        return true;
    }
    if (n % 2 == 0 || n % 3 == 0) {
        return false;
    }
    for (long long int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

long long int get_nsw_sequence(int n) {
    if (n < 0) {
        return -1; 
    }
    if (n == 0) {
        return 1;
    }
    if (n == 1) {
        return 1;
    }
    long long int s0 = 1;
    long long int s1 = 1;
    long long int s_n = 0;
    for (int i = 2; i <= n; i++) {
        s_n = 2 * s1 + s0;
        s0 = s1;
        s1 = s_n;
    }
    return s_n;
}

long long int nth_nsw_prime(int n) {
    if (n <= 0) {
        return -1; 
    }
    int count = 0;
    int i = 0;
    while (1) {
        long long int nsw = get_nsw_sequence(i);
        if (nsw < 0) {
            return -1; 
        }
        if (is_prime(nsw)) {
            count++;
            if (count == n) {
                return nsw;
            }
        }
        i++;
    }
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000003,time:4663,execs:125,op:havoc,rep:1; likely memory-safety defect
  */

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        return EXIT_FAILURE;
    }
    
    if (n <= 0) {
        return EXIT_FAILURE;
    }

    long long int result = nth_nsw_prime(n);
    if (result == -1) {
        return EXIT_FAILURE;
    }

    printf("%lld\n", result);
    return EXIT_SUCCESS;
}