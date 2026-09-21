#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>

int is_hex_number(const char *str) {
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

int count_hex_numbers_in_range(const char *start, const char *end) {
    if (start == NULL || end == NULL) {
        return 0;
    }
    
    if (!is_hex_number(start) || !is_hex_number(end)) {
        return 0;
    }
    
    char *endptr_start = NULL;
    char *endptr_end = NULL;
    
    errno = 0;
    long start_val = strtol(start, &endptr_start, 16);
    if (errno == ERANGE || endptr_start == NULL || *endptr_start != '\0') {
        return 0;
    }
    
    errno = 0;
    long end_val = strtol(end, &endptr_end, 16);
    if (errno == ERANGE || endptr_end == NULL || *endptr_end != '\0') {
        return 0;
    }
    
    if (start_val > end_val) {
        return 0;
    }
    
    unsigned long diff = (unsigned long)(end_val - start_val);
    if (diff > (unsigned long)(INT_MAX - 1)) {
        return INT_MAX;
    }
    
    return (int)diff + 1;
}

int main(int argc, const char *argv[]) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char start[101];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char end[101];
    
    if (argc == 3) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len_start = strlen(argv[1]);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len_end = strlen(argv[2]);
        
        if (len_start >= sizeof(start) || len_end >= sizeof(end)) {
            printf("Input too long\n");
            return 1;
        }
        
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(start, argv[1], len_start + 1);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(end, argv[2], len_end + 1);
    } else {
        printf("Enter start hexadecimal number: ");
        if (fgets(start, sizeof(start), stdin) == NULL) {
            return 1;
        }
        start[strcspn(start, "\n")] = '\0';
        
        printf("Enter end hexadecimal number: ");
        if (fgets(end, sizeof(end), stdin) == NULL) {
            return 1;
        }
        end[strcspn(end, "\n")] = '\0';
    }
    
    int count = count_hex_numbers_in_range(start, end);
    
    if (count == 0 && strcmp(start, end) != 0) {
        printf("Invalid input or range\n");
        return 1;
    }
    
    printf("Number of hexadecimal values in range [%s, %s]: %d\n", start, end, count);
    
    return 0;
}