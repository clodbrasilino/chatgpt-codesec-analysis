#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

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
    
    long start_val = strtol(start, &endptr_start, 16);
    long end_val = strtol(end, &endptr_end, 16);
    
    if (endptr_start == NULL || endptr_end == NULL || 
        *endptr_start != '\0' || *endptr_end != '\0') {
        return 0;
    }
    
    if (start_val > end_val) {
        return 0;
    }
    
    long diff = end_val - start_val;
    if (diff > INT_MAX - 1) {
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
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(start, argv[1], sizeof(start) - 1);
        start[sizeof(start) - 1] = '\0';
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(end, argv[2], sizeof(end) - 1);
        end[sizeof(end) - 1] = '\0';
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