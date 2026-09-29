#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int count_hexadecimal_numbers(unsigned long long start, unsigned long long end, unsigned long long *count) {
    if (count == NULL) {
        return -1;
    }
    
    if (start > end) {
        return -1;
    }
    
    if (start == 0 && end == ULLONG_MAX) {
        return -1;
    }
    
    *count = end - start + 1;
    return 0;
}

int main(void) {
    char start_buffer[32];
    char end_buffer[32];
    char *endptr;
    unsigned long long start;
    unsigned long long end;
    unsigned long long count;
    
    printf("Enter start of range (decimal): ");
    if (fgets(start_buffer, sizeof(start_buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    start = strtoull(start_buffer, &endptr, 10);
    if (errno == ERANGE || endptr == start_buffer || (*endptr != '\n' && *endptr != '\0')) {
        fprintf(stderr, "Invalid start value\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter end of range (decimal): ");
    if (fgets(end_buffer, sizeof(end_buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    end = strtoull(end_buffer, &endptr, 10);
    if (errno == ERANGE || endptr == end_buffer || (*endptr != '\n' && *endptr != '\0')) {
        fprintf(stderr, "Invalid end value\n");
        return EXIT_FAILURE;
    }
    
    if (count_hexadecimal_numbers(start, end, &count) != 0) {
        fprintf(stderr, "Invalid range\n");
        return EXIT_FAILURE;
    }
    
    printf("Count of hexadecimal numbers in range [%llu, %llu]: %llu\n", start, end, count);
    printf("Hexadecimal range: [0x%llX, 0x%llX]\n", start, end);
    
    return EXIT_SUCCESS;
}