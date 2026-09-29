#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

int is_demlo(int n)
{
    if (n <= 0) {
        return 0;
    }

    char buffer[16];
    int len = snprintf(buffer, sizeof(buffer), "%d", n);
    if (len < 0 || len >= (int)sizeof(buffer)) {
        return 0;
    }

    if (len % 2 == 0) {
        return 0;
    }

    int mid = len / 2;
    for (int i = 0; i < mid; i++) {
        if (buffer[i] != '1' + i) {
            return 0;
        }
    }
    for (int i = mid; i < len; i++) {
        if (buffer[i] != '1' + (len - 1 - i)) {
            return 0;
        }
    }

    return 1;
}

int main(void)
{
    char input[32];
    char *endptr;
    long val;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    val = strtol(input, &endptr, 10);
    
    if (errno == ERANGE || val > INT_MAX || val < INT_MIN) {
        return EXIT_FAILURE;
    }
    
    if (endptr == input) {
        return EXIT_FAILURE;
    }
    
    while (*endptr == ' ' || *endptr == '\t' || *endptr == '\n' || *endptr == '\r') {
        endptr++;
    }
    
    if (*endptr != '\0') {
        return EXIT_FAILURE;
    }

    if (is_demlo((int)val)) {
        printf("%d is a Demlo number\n", (int)val);
    } else {
        printf("%d is not a Demlo number\n", (int)val);
    }

    return EXIT_SUCCESS;
}