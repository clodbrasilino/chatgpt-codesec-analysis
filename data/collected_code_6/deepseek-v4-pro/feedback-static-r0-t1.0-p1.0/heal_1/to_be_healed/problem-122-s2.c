#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int is_smart_number(unsigned long long num) {
    int count = 0;
    unsigned long long temp = num;
    
    while (temp % 2 == 0) {
        count++;
        temp /= 2;
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
        }
        if (count < n) {
            if (num == ULLONG_MAX) {
                return 0;
            }
            num++;
        }
    }
    
    return num;
}

int main(void) {
    int n;
    
    printf("Enter n: ");
    /* Possible weaknesses found:
     *  Assuming that condition 'n<=0' is not redundant
     */
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    unsigned long long result = find_nth_smart_number(n);
    
    /* Possible weaknesses found:
     *  Condition 'n>0' is always true
     *  Condition 'n>0' is always true [knownConditionTrueFalse]
     */
    if (result == 0 && n > 0) {
        fprintf(stderr, "Result out of range\n");
        return 1;
    }
    
    printf("%llu\n", result);
    
    return 0;
}