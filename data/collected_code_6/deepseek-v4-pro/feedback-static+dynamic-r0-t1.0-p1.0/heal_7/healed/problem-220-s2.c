#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

int replace_chars(char *str, size_t size, unsigned int n) {
    unsigned int count = 0;
    size_t i;

    if (str == NULL) {
        return -1;
    }

    for (i = 0; i < size && str[i] != '\0' && count < n; i++) {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '.') {
            str[i] = ':';
            count++;
        }
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
    char input_buf[64];

    printf("Enter a string: ");
    read = getline(&str, &len, stdin);
    if (read == -1) {
        free(str);
        return 1;
    }

    if (read > 0 && str[read - 1] == '\n') {
        str[read - 1] = '\0';
        read--;
    }

    printf("Enter maximum replacements: ");
    if (fgets(input_buf, sizeof(input_buf), stdin) == NULL) {
        free(str);
        return 1;
    }

    input_buf[strcspn(input_buf, "\n")] = '\0';

    errno = 0;
    temp_n = strtol(input_buf, &endptr, 10);
    if ((errno == ERANGE && (temp_n == LONG_MAX || temp_n == LONG_MIN))
        || (errno != 0 && temp_n == 0)
        || endptr == input_buf
        || *endptr != '\0'
        || temp_n < 0
        || temp_n > UINT_MAX) {
        free(str);
        return 1;
    }
    n = (unsigned int)temp_n;

    if (read > 0 && str[0] != '\0') {
        replace_chars(str, (size_t)read, n);
        printf("Result: %s\n", str);
    }

    free(str);
    return 0;
}