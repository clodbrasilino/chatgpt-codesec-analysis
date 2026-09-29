#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT_SIZE 1024

static unsigned long long count_substrings(const char *str, size_t max_len)
{
    size_t len;

    if (str == NULL) {
        return 0ULL;
    }

    len = strnlen(str, max_len);

    return ((unsigned long long)len * (unsigned long long)(len + 1U)) / 2ULL;
}

static void flush_stdin(void)
{
    int ch;
    size_t guard = 0;

    do {
        ch = getchar();
        guard++;
    } while (ch != '\n' && ch != EOF && guard < (size_t)-1);
}

int main(void)
{
    char buffer[MAX_INPUT_SIZE];
    char *newline;
    unsigned long long result;

    memset(buffer, 0, sizeof(buffer));

    printf("Enter a string: ");

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    newline = memchr(buffer, '\n', sizeof(buffer));
    if (newline != NULL) {
        *newline = '\0';
    } else {
        flush_stdin();
    }

    result = count_substrings(buffer, sizeof(buffer));

    printf("Number of non-empty substrings: %llu\n", result);

    return EXIT_SUCCESS;
}