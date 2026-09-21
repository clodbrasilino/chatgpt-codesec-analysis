#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

unsigned long long sum_of_fourth_powers(int n) {
    if (n < 0) {
        return 0;
    }
    
    unsigned long long sum = 0;
    for (int i = 1; i <= n; i++) {
        unsigned long long term = (unsigned long long)i;
        unsigned long long fourth = term * term * term * term;
        
        if (fourth > ULLONG_MAX - sum) {
            return ULLONG_MAX;
        }
        
        sum += fourth;
    }
    return sum;
}

int main(void) {
    char *input = NULL;
    size_t len = 0;
    ssize_t nread;
    
    printf("Enter a natural number: ");
    nread = getline(&input, &len, stdin);
    
    if (nread == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    if (input_len > 0 && input[input_len - 1] == '\n') {
        input[input_len - 1] = '\0';
        input_len--;
    }
    
    if (input_len == 0) {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
        free(input);
        return 1;
    }
    
    char *endptr;
    errno = 0;
    long value = strtol(input, &endptr, 10);
    
    if (errno == ERANGE || value > 1000 || value < 0) {
        fprintf(stderr, "Invalid input. Number out of range.\n");
        free(input);
        return 1;
    }
    
    if (endptr == input || *endptr != '\0') {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
        free(input);
        return 1;
    }
    
    int n = (int)value;
    unsigned long long result = sum_of_fourth_powers(n);
    
    if (result == ULLONG_MAX) {
        fprintf(stderr, "Result overflow detected\n");
        free(input);
        return 1;
    }
    
    printf("Sum of fourth powers from 1 to %d: %llu\n", n, result);
    
    free(input);
    return 0;
}