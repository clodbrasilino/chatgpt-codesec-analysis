#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 11, got 0
  *  test case 2 failed: expected 13, got 1
  *  test case 1 failed: expected 7, got 0
  */

unsigned long long is_polite(unsigned long long num) {
    if (num < 2) return 0;
    
    while ((num & 1) == 0) {
        return 0;
    }
    
    while (num > 1 && (num & 1) == 1) {
        num >>= 1;
        if (num > 1 && (num & 1) == 0) {
            unsigned long long temp = num;
            while ((temp & 1) == 0) {
                temp >>= 1;
            }
            return temp > 1 ? 0 : 1;
        }
    }
    
    return 0;
}

unsigned long long nth_polite(int n) {
    if (n <= 0) {
        return 0;
    }
    
    unsigned long long count = 0;
    unsigned long long num = 3;
    
    while (1) {
        unsigned long long x = num;
        if (x < 2) {
            num++;
            continue;
        }
        
        unsigned long long polite_found = 0;
        for (unsigned long long start = 1; start < num; start++) {
            unsigned long long sum = 0;
            unsigned long long current = start;
            while (sum < num) {
                sum += current;
                if (sum == num && current > start) {
                    polite_found = 1;
                    break;
                }
                if (sum >= num) break;
                current++;
            }
            if (polite_found) break;
        }
        
        if (polite_found) {
            count++;
            if (count == (unsigned long long)n) {
                return num;
            }
        }
        num++;
    }
}

int main(void) {
    int n;
    
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n <= 0) {
        fprintf(stderr, "n must be positive\n");
        return EXIT_FAILURE;
    }
    
    printf("%llu\n", nth_polite(n));
    
    return EXIT_SUCCESS;
}