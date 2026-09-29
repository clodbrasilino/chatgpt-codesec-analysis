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
    char buffer[MAX_INPUT_SIZE];
    char *newline;
    unsigned long long result;

    printf("Enter a string: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    newline = strchr(buffer, '\n');
    if (newline != NULL) {
        *newline = '\0';
    } else {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
    }

    result = count_substrings(buffer, sizeof(buffer));

    printf("Number of non-empty substrings: %llu\n", result);

    return EXIT_SUCCESS;
}