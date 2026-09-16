#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned long long count_substrings(const char *str)
{
    size_t len;

    if (str == NULL) {
        return 0ULL;
    }

    len = strlen(str);

    return ((unsigned long long)len * (unsigned long long)(len + 1U)) / 2ULL;
}

int main(void)
{
    char buffer[1024];
    char *newline;
    unsigned long long result;

    printf("Enter a string: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input\n");
        return EXIT_FAILURE;
    }

    newline = strchr(buffer, '\n');
    if (newline != NULL) {
        *newline = '\0';
    }

    result = count_substrings(buffer);

    printf("Number of non-empty substrings: %llu\n", result);

    return EXIT_SUCCESS;
}