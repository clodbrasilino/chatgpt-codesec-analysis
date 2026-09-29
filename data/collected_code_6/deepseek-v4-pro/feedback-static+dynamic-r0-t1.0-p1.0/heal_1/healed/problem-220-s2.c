#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int replace_chars(char *str, size_t size, unsigned int n) {
    unsigned int count = 0;
    char *p = str;
    
    while (*p != '\0' && count < n) {
        if (*p == ' ' || *p == ',' || *p == '.') {
            *p = ':';
            count++;
        }
        p++;
    }
    return 0;
}

int main(void) {
    char *str = NULL;
    size_t len = 0;
    ssize_t read;
    long temp_n;
    unsigned int n;
    char *endptr;

    printf("Enter a string: ");
    read = getline(&str, &len, stdin);
    if (read == -1) {
        free(str);
        return 1;
    }
    if (read > 0 && str[read - 1] == '\n') {
        str[read - 1] = '\0';
    }

    printf("Enter maximum replacements: ");
    if (fgets(str, len, stdin) == NULL) {
        free(str);
        return 1;
    }

    errno = 0;
    temp_n = strtol(str, &endptr, 10);
    if ((errno == ERANGE && (temp_n == LONG_MAX || temp_n == LONG_MIN))
        || (errno != 0 && temp_n == 0)
        || endptr == str
        || *endptr != '\0'
        || temp_n < 0
        || temp_n > UINT_MAX) {
        free(str);
        return 1;
    }
    n = (unsigned int)temp_n;

    if (read > 0) {
        replace_chars(str, (size_t)read, n);
        printf("Result: %s\n", str);
    }

    free(str);
    return 0;
}