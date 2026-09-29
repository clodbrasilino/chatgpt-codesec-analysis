#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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
    size_t capacity = 256;
    char *buffer = (char *)malloc(capacity);
    
    if (buffer == NULL) {
        return 1;
    }

    size_t length = 0;
    int c;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = fgetc(stdin)) != EOF && c != '\n') {
        if (length >= capacity - 1) {
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 1;
            }
            size_t new_capacity = capacity * 2;
            char *new_buffer = (char *)realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 1;
            }
            buffer = new_buffer;
            capacity = new_capacity;
        }
        buffer[length++] = (char)c;
    }

    if (length == 0 && c == EOF) {
        free(buffer);
        return 1;
    }

    buffer[length] = '\0';

    long long int result = calculate_ascii_sum(buffer);
    printf("%lld\n", result);

    free(buffer);
    return 0;
}