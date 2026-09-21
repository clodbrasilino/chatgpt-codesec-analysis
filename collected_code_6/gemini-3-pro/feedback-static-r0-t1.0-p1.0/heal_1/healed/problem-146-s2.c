#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>

long long int calculate_ascii_sum(const char *str) {
    if (str == NULL) {
        return 0;
    }

    long long int total_ascii_value = 0;
    while (*str != '\0') {
        total_ascii_value += (unsigned char)*str;
        str++;
    }

    return total_ascii_value;
}

int main(void) {
    char *buffer = NULL;
    size_t bufsize = 0;

    if (getline(&buffer, &bufsize, stdin) == -1) {
        free(buffer);
        return 1;
    }

    size_t i = 0;
    while (buffer[i] != '\0') {
        if (buffer[i] == '\n') {
            buffer[i] = '\0';
            break;
        }
        i++;
    }

    long long int result = calculate_ascii_sum(buffer);
    printf("%lld\n", result);

    free(buffer);
    return 0;
}