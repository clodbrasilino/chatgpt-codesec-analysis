#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

#define INPUT_BUFFER_SIZE 64

static bool safe_strlen(const char *str, size_t maxlen, size_t *out_len) {
    size_t i;
    
    if (str == NULL || out_len == NULL) {
        return false;
    }
    
    for (i = 0; i < maxlen; i++) {
        if (str[i] == '\0') {
            *out_len = i;
            return true;
        }
    }
    
    return false;
}

uint64_t carol_number(uint64_t n) {
    if (n == 0 || n > 31) {
        return UINT64_MAX;
    }
    
    uint64_t power = 1ULL << n;
    uint64_t temp = power - 1;
    
    if (temp != 0 && temp > UINT64_MAX / temp) {
        return UINT64_MAX;
    }
    
    return temp * temp - 2;
}

int main(void) {
    char input[INPUT_BUFFER_SIZE];
    char *endptr;
    uint64_t n;
    size_t len;
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    if (!safe_strlen(input, sizeof(input), &len)) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    if (len > 0 && input[len - 1] != '\n' && !feof(stdin)) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }
    
    if (len == 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    n = strtoull(input, &endptr, 10);
    
    if (errno != 0 || endptr == input || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n == 0 || n > 31) {
        fprintf(stderr, "Input out of valid range\n");
        return EXIT_FAILURE;
    }
    
    uint64_t result = carol_number(n);
    
    if (result == UINT64_MAX) {
        fprintf(stderr, "Overflow occurred\n");
        return EXIT_FAILURE;
    }
    
    printf("%" PRIu64 "\n", result);
    
    return EXIT_SUCCESS;
}