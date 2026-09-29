#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

bool has_30_days(int month) {
    if (month < 1 || month > 12) {
        return false;
    }
    
    switch (month) {
        case 4:
        case 6:
        case 9:
        case 11:
            return true;
        default:
            return false;
    }
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char const * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <month_number>\n", argv[0]);
        return 1;
    }

    if (argv[1][0] == '\0') {
        fprintf(stderr, "Invalid input: empty string\n");
        return 1;
    }
    
    char *endptr;
    long month_long;
    
    errno = 0;
    month_long = strtol(argv[1], &endptr, 10);

    size_t arg_len = 0;
    while (argv[1][arg_len] != '\0') {
        arg_len++;
    }
    
    if (errno == ERANGE || month_long < INT_MIN || month_long > INT_MAX || *endptr != '\0' || endptr == argv[1] || (size_t)(endptr - argv[1]) != arg_len) {
        fprintf(stderr, "Invalid input: not a valid integer\n");
        return 1;
    }
    
    if (has_30_days((int)month_long)) {
        printf("1\n");
    } else {
        printf("0\n");
    }
    
    return 0;
}