#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

int count_digits(long long number) {
    int count = 0;
    
    if (number == 0) {
        return 1;
    }
    
    if (number < 0) {
        if (number == LLONG_MIN) {
            number = LLONG_MAX;
        } else {
            number = -number;
        }
    }
    
    while (number > 0) {
        number /= 10;
        count++;
    }
    
    return count;
}

int main(void) {
    char input[128];
    char *endptr;
    long long number;
    int digits;
    size_t len;
    int c;
    int too_long = 0;
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    len = strnlen(input, sizeof(input));
    if (len == sizeof(input)) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    if (len > 0 && input[len - 1] != '\n' && !feof(stdin)) {
        while ((c = getchar()) != '\n' && c != EOF) {
            too_long = 1;
        }
        if (too_long || c == EOF) {
            fprintf(stderr, "Input too long\n");
            return EXIT_FAILURE;
        }
    }
    
    errno = 0;
    number = strtoll(input, &endptr, 10);
    
    if (errno == ERANGE) {
        fprintf(stderr, "Number out of range\n");
        return EXIT_FAILURE;
    }
    
    if (endptr == input) {
        fprintf(stderr, "Invalid input: not a number\n");
        return EXIT_FAILURE;
    }
    
    while (isspace((unsigned char)*endptr)) {
        endptr++;
    }
    
    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input: trailing characters\n");
        return EXIT_FAILURE;
    }
    
    digits = count_digits(number);
    printf("%d\n", digits);
    
    return EXIT_SUCCESS;
}