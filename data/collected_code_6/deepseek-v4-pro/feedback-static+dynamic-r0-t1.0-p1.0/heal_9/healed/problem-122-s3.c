#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool is_smart_number(long long num) {
    int count = 0;
    long long temp = num;
    
    if (num < 2) {
        return false;
    }
    
    if (temp % 2 == 0) {
        count++;
        while (temp % 2 == 0) {
            temp /= 2;
        }
    }
    
    for (long long i = 3; i * i <= temp; i += 2) {
        if (temp % i == 0) {
            count++;
            if (count > 3) {
                return false;
            }
            while (temp % i == 0) {
                temp /= i;
            }
        }
    }
    
    if (temp > 1) {
        count++;
    }
    
    return count == 3;
}

static int count_distinct_prime_factors(long long num) {
    int count = 0;
    long long temp = num;
    
    if (temp % 2 == 0) {
        count++;
        while (temp % 2 == 0) {
            temp /= 2;
        }
    }
    
    for (long long i = 3; i * i <= temp; i += 2) {
        if (temp % i == 0) {
            count++;
            while (temp % i == 0) {
                temp /= i;
            }
        }
    }
    
    if (temp > 1) {
        count++;
    }
    
    return count;
}

static void extract_three_smallest_primes(long long num, int *p1, int *p2, int *p3) {
    *p1 = 0;
    *p2 = 0;
    *p3 = 0;
    long long temp = num;
    
    if (temp % 2 == 0) {
        *p1 = 2;
        while (temp % 2 == 0) {
            temp /= 2;
        }
    }
    
    for (long long i = 3; i * i <= temp; i += 2) {
        if (temp % i == 0) {
            if (*p1 == 0) {
                *p1 = (int)i;
            } else if (*p2 == 0) {
                *p2 = (int)i;
            } else if (*p3 == 0) {
                *p3 = (int)i;
                return;
            }
            while (temp % i == 0) {
                temp /= i;
            }
        }
    }
    
    if (temp > 1) {
        if (*p1 == 0) {
            *p1 = (int)temp;
        } else if (*p2 == 0) {
            *p2 = (int)temp;
        } else if (*p3 == 0) {
            *p3 = (int)temp;
        }
    }
}

static long long cube(long long x) {
    return x * x * x;
}

long long find_nth_smart_number(int n) {
    if (n <= 0) {
        return -1;
    }
    
    long long candidate = 30;
    int found = 0;
    
    if (n == 1) return 30;
    found = 1;
    candidate = 31;
    
    while (found < n) {
        int p1, p2, p3;
        long long minimal = 0;
        
        if (count_distinct_prime_factors(candidate) == 3) {
            extract_three_smallest_primes(candidate, &p1, &p2, &p3);
            minimal = cube((long long)p1) * (long long)p2 * (long long)p3;
        }
        
        if (minimal == candidate) {
            found++;
        }
        candidate++;
    }
    
    return candidate - 1;
}

int main(void) {
    int n;
    
    printf("Enter n to find the nth smart number: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n <= 0) {
        printf("n must be a positive integer\n");
        return EXIT_FAILURE;
    }
    
    long long result = find_nth_smart_number(n);
    printf("The %dth smart number is: %lld\n", n, result);
    
    return EXIT_SUCCESS;
}