#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

unsigned long long sum_of_fourth_powers(int n) {
    if (n <= 0) {
        return 0;
    }
    
    unsigned long long sum = 0;
    for (int i = 1; i <= n; i++) {
        unsigned long long fourth = (unsigned long long)i * i * i * i;
        unsigned long long prev = sum;
        sum += fourth;
        if (sum < prev) {
            return ULLONG_MAX;
        }
    }
    return sum;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[16] = {0};
    int c;
    size_t i = 0;
    
    printf("Enter a natural number: ");
    
    while (i < sizeof(input) - 1) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = getchar();
        if (c == EOF) {
            fprintf(stderr, "Error reading input\n");
            return 1;
        }
        if (c == '\n') {
            break;
        }
        input[i++] = (char)c;
    }
    input[i] = '\0';
    
    if (c != '\n') {
        int discard;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((discard = getchar()) != '\n' && discard != EOF) {
        }
        fprintf(stderr, "Invalid input. Input too long.\n");
        return 1;
    }
    
    if (i == 0) {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
        return 1;
    }
    
    for (size_t j = 0; j < i; j++) {
        if (input[j] < '0' || input[j] > '9') {
            fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
            return 1;
        }
    }
    
    char *endptr;
    errno = 0;
    unsigned long long value = strtoull(input, &endptr, 10);
    
    if (errno == ERANGE || value > 1000) {
        fprintf(stderr, "Invalid input. Number out of range (0-1000).\n");
        return 1;
    }
    
    if (endptr == input || *endptr != '\0') {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
        return 1;
    }
    
    int n = (int)value;
    unsigned long long result = sum_of_fourth_powers(n);
    
    if (result == ULLONG_MAX) {
        fprintf(stderr, "Overflow occurred during calculation.\n");
        return 1;
    }
    
    printf("Sum of fourth powers from 1 to %d: %llu\n", n, result);
    
    return 0;
}