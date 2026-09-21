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
    const size_t guard_limit = (size_t)MAX_INPUT_SIZE * 1024U;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
        guard++;
    } while (ch != '\n' && ch != EOF && guard < guard_limit);
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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