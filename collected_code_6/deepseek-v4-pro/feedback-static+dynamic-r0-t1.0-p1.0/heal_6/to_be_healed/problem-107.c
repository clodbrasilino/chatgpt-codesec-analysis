#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

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
    
    if (len == size - 1 && buffer[len] == '\0' && buffer[len - 1] != '\n') {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        return 1;
    }
    
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    
    return 1;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char start_input[256];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char end_input[256];
    
    printf("Enter start hex value: ");
    if (!read_input_line(start_input, sizeof(start_input))) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    printf("Enter end hex value: ");
    if (!read_input_line(end_input, sizeof(end_input))) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    long long count = count_hex_numbers_in_range(start_input, end_input);
    
    if (count < 0) {
        fprintf(stderr, "Invalid input values\n");
        return 1;
    }
    
    printf("Count of hex numbers in range: %lld\n", count);
    
    return 0;
}