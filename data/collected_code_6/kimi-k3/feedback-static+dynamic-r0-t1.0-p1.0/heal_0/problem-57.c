#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_desc(const void *a, const void *b) {
    return (*(const int *)b - *(const int *)a);
}

long long largest_number_from_digits(int digits[], int n) {
    if (digits == NULL || n <= 0) {
        return -1;
    }
    
    for (int i = 0; i < n; i++) {
        if (digits[i] < 0 || digits[i] > 9) {
            return -1;
        }
    }
    
    qsort(digits, (size_t)n, sizeof(int), compare_desc);
    
    long long result = 0;
    for (int i = 0; i < n; i++) {
        if (result > (9223372036854775807LL - digits[i]) / 10) {
            return -1;
        }
        result = result * 10 + digits[i];
    }
    
    return result;
}

int main(void) {
    int digits[] = {5, 4, 2, 8, 1, 9};
    int n = (int)(sizeof(digits) / sizeof(digits[0]));
    
    long long result = largest_number_from_digits(digits, n);
    
    if (result == -1) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("Largest number: %lld\n", result);
    
    return EXIT_SUCCESS;
}