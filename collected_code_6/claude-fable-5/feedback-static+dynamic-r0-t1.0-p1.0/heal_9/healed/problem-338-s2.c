#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

long count_substrings(const char *str, size_t max_len)
{
    long count;
    size_t len;
    size_t i;
    size_t j;

    if (str == NULL) {
        return -1L;
    }

    len = strnlen(str, max_len);
    if (len >= max_len) {
        return -1L;
    }

    count = 0L;

    for (i = 0U; i < len; i++) {
        for (j = i; j < len; j++) {
            if (str[i] == str[j]) {
                count++;
            }
        }
    }

    return count;
}

int main(void)
{
    char *buffer;
    long result;
    size_t len;

    buffer = (char *)calloc(BUFFER_SIZE, sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    buffer[BUFFER_SIZE - 1U] = '\0';

    len = strnlen(buffer, BUFFER_SIZE);
    if ((len > 0U) && (buffer[len - 1U] == '\n')) {
        buffer[len - 1U] = '\0';
    }

    result = count_substrings(buffer, BUFFER_SIZE);
    if (result < 0L) {
        fprintf(stderr, "Invalid input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    if (printf("%ld\n", result) < 0) {
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);
    return EXIT_SUCCESS;
}