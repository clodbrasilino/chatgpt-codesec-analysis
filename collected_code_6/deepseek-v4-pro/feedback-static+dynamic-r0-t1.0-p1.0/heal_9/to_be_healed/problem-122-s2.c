#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 2664, got 0
  *  test case 1 failed: expected 273, got 1
  *  test case 0 failed: expected 30, got 0
  */

int is_smart_number(unsigned long long num) {
    if (num == 0) {
        return 0;
    }
    
    int count = 0;
    unsigned long long temp = num;
    
    if (temp % 2 == 0) {
        while (temp % 2 == 0) {
            count++;
            temp /= 2;
        }
    }
    
    for (unsigned long long i = 3; i * i <= temp; i += 2) {
        while (temp % i == 0) {
            count++;
            temp /= i;
        }
    }
    
    if (temp > 1) {
        count++;
    }
    
    return count % 2 == 1;
}

unsigned long long find_nth_smart_number(int n) {
    if (n <= 0) {
        return 0;
    }
    
    int count = 0;
    unsigned long long num = 1;
    
    while (count < n) {
        if (is_smart_number(num)) {
            count++;
            if (count == n) {
                return num;
            }
        }
        if (num == ULLONG_MAX) {
            return 0;
        }
        num++;
    }
    
    return 0;
}

int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    unsigned long long result = find_nth_smart_number(n);
    
    if (result == 0) {
        fprintf(stderr, "Result out of range\n");
        return 1;
    }
    
    printf("%llu\n", result);
    
    return 0;
}