#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT_SIZE 1024

unsigned long long count_substrings(const char *str, size_t max_len)
{
    size_t len;

    if (str == NULL) {
        return 0ULL;
    }

    len = strnlen(str, max_len);

    return ((unsigned long long)len * (unsigned long long)(len + 1U)) / 2ULL;
}

int main(void)
{
    char *buffer;
    char *newline;
    unsigned long long result;

    buffer = calloc(MAX_INPUT_SIZE, sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Error: memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Enter a string: ");

    if (fgets(buffer, MAX_INPUT_SIZE, stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    buffer[MAX_INPUT_SIZE - 1] = '\0';

    newline = strchr(buffer, '\n');
    if (newline != NULL) {
        *newline = '\0';
    }

    result = count_substrings(buffer, MAX_INPUT_SIZE);

    printf("Number of non-empty substrings: %llu\n", result);

    free(buffer);

    return EXIT_SUCCESS;
}