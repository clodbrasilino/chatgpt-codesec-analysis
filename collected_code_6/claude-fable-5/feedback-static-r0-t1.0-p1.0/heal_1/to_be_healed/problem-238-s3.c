#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned long long count_substrings(const char *str)
{
    size_t len;

    if (str == NULL) {
        return 0ULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);

    return ((unsigned long long)len * (unsigned long long)(len + 1U)) / 2ULL;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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