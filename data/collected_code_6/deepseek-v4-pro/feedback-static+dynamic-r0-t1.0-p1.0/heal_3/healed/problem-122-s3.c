#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool is_smart_number(long long num) {
    int count = 0;
    long long temp = num;
    
    for (long long i = 2; i * i <= temp; i++) {
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
    
    return count % 2 == 1;
}

long long find_nth_smart_number(int n) {
    if (n <= 0) {
        return -1;
    }
    
    long long candidate = 1;
    int found = 0;
    
    while (found < n) {
        if (is_smart_number(candidate)) {
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