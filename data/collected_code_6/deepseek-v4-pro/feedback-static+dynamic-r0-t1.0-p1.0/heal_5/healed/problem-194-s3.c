#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>

int octal_to_decimal(const char *octal_str, long *result) {
    if (octal_str == NULL || result == NULL || *octal_str == '\0') {
        return -1;
    }
    
    const char *p = octal_str;
    if (*p == '+' || *p == '-') {
        p++;
        if (*p == '\0') {
            return -1;
        }
    }
    
    for (const char *q = p; *q != '\0'; q++) {
        if (*q < '0' || *q > '7') {
            return -1;
        }
    }
    
    errno = 0;
    char *endptr;
    long value = strtol(octal_str, &endptr, 8);
    
    if (errno == ERANGE || endptr == octal_str || *endptr != '\0') {
        return -1;
    }
    
    *result = value;
    return 0;
}

int main(void) {
    char input[256];
    long decimal;
    
    printf("Enter an octal number: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    size_t len = strnlen(input, sizeof(input));
    int truncated = 0;
    
    if (len == sizeof(input) - 1 && input[len] != '\n' && input[len] != '\0') {
        truncated = 1;
    }
    
    if (truncated) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
        fprintf(stderr, "Invalid octal number\n");
        return 1;
    }
    
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
    }
    
    if (len == 0) {
        fprintf(stderr, "Invalid octal number\n");
        return 1;
    }
    
    if (octal_to_decimal(input, &decimal) != 0) {
        fprintf(stderr, "Invalid octal number\n");
        return 1;
    }
    
    printf("Decimal equivalent: %ld\n", decimal);
    
    return 0;
}