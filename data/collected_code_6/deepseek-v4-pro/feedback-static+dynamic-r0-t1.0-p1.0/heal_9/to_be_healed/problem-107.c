#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

#define MAX_INPUT_LENGTH 1024

static int is_hex_string(const char *str) {
    if (str == NULL || *str == '\0') {
        return 0;
    }
    
    const char *p = str;
    
    if (p[0] == '0' && (p[1] == 'x' || p[1] == 'X')) {
        p += 2;
        if (*p == '\0') {
            return 0;
        }
    }
    
    while (*p != '\0') {
        if (!isxdigit((unsigned char)*p)) {
            return 0;
        }
        p++;
    }
    
    return 1;
}

static int parse_hex_value(const char *str, unsigned long long *out_value) {
    if (str == NULL || out_value == NULL) {
        return 0;
    }
    
    const char *p = str;
    if (p[0] == '0' && (p[1] == 'x' || p[1] == 'X')) {
        p += 2;
    }
    
    char *endptr = NULL;
    errno = 0;
    unsigned long long value = strtoull(p, &endptr, 16);
    
    if (errno == ERANGE) {
        return 0;
    }
    
    if (endptr == p || *endptr != '\0') {
        return 0;
    }
    
    *out_value = value;
    return 1;
}

long long count_hex_numbers_in_range(const char *start_str, const char *end_str) {
    if (start_str == NULL || end_str == NULL) {
        return -1;
    }
    
    if (!is_hex_string(start_str) || !is_hex_string(end_str)) {
        return -1;
    }
    
    unsigned long long start_val = 0;
    unsigned long long end_val = 0;
    
    if (!parse_hex_value(start_str, &start_val) || !parse_hex_value(end_str, &end_val)) {
        return -1;
    }
    
    if (start_val > end_val) {
        unsigned long long temp = start_val;
        start_val = end_val;
        end_val = temp;
    }
    
    if (end_val > (unsigned long long)LLONG_MAX) {
        return -1;
    }
    
    unsigned long long range = end_val - start_val;
    if (range > (unsigned long long)LLONG_MAX - 1) {
        return -1;
    }
    
    return (long long)(range + 1);
}

static int read_input_line(char *buffer, size_t size) {
    if (buffer == NULL || size == 0) {
        return 0;
    }
    
    if (fgets(buffer, (int)size, stdin) == NULL) {
        return 0;
    }
    
    size_t len = strnlen(buffer, size);
    
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        return 1;
    }
    
    if (len == size - 1 && buffer[len - 1] != '\n') {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        return 1;
    }
    
    return 1;
}

int main(void) {
    char *start_input = (char *)calloc(MAX_INPUT_LENGTH, sizeof(char));
    char *end_input = (char *)calloc(MAX_INPUT_LENGTH, sizeof(char));
    
    if (start_input == NULL || end_input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(start_input);
        free(end_input);
        return 1;
    }
    
    printf("Enter start hex value: ");
    fflush(stdout);
    if (!read_input_line(start_input, MAX_INPUT_LENGTH)) {
        fprintf(stderr, "Error reading input\n");
        free(start_input);
        free(end_input);
        return 1;
    }
    
    size_t start_len = strnlen(start_input, MAX_INPUT_LENGTH);
    if (start_len >= MAX_INPUT_LENGTH - 1) {
        fprintf(stderr, "Input too long\n");
        free(start_input);
        free(end_input);
        return 1;
    }
    
    printf("Enter end hex value: ");
    fflush(stdout);
    if (!read_input_line(end_input, MAX_INPUT_LENGTH)) {
        fprintf(stderr, "Error reading input\n");
        free(start_input);
        free(end_input);
        return 1;
    }
    
    size_t end_len = strnlen(end_input, MAX_INPUT_LENGTH);
    if (end_len >= MAX_INPUT_LENGTH - 1) {
        fprintf(stderr, "Input too long\n");
        free(start_input);
        free(end_input);
        return 1;
    }
    
    long long count = count_hex_numbers_in_range(start_input, end_input);
    
    if (count < 0) {
        fprintf(stderr, "Invalid input values\n");
        free(start_input);
        free(end_input);
        return 1;
    }
    
    printf("Count of hex numbers in range: %lld\n", count);
    
    free(start_input);
    free(end_input);
    
    return 0;
}