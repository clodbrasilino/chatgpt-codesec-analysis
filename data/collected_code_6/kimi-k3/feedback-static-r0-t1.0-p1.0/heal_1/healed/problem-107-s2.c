#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

#define BUFFER_SIZE 64

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

int read_ull(const char *prompt, unsigned long long *value) {
    char buffer[BUFFER_SIZE];
    char *endptr;
    char *newline;
    
    if (value == NULL) {
        return -1;
    }
    
    printf("%s", prompt);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return -1;
    }
    
    newline = strchr(buffer, '\n');
    if (newline == NULL) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return -1;
    }
    
    errno = 0;
    *value = strtoull(buffer, &endptr, 10);
    if (errno == ERANGE || endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        return -1;
    }
    
    return 0;
}

int main(void) {
    unsigned long long start;
    unsigned long long end;
    unsigned long long count;
    
    if (read_ull("Enter start of range (decimal): ", &start) != 0) {
        fprintf(stderr, "Invalid start value\n");
        return EXIT_FAILURE;
    }
    
    if (read_ull("Enter end of range (decimal): ", &end) != 0) {
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