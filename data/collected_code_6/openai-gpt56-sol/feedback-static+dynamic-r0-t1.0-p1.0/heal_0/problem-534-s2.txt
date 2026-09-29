#include <stdio.h>
#include <string.h>
#include <stddef.h>

static int find_literal(const char *text, const char *pattern, size_t *location)
{
    const char *match;

    if (text == NULL || pattern == NULL || location == NULL) {
        return -1;
    }

    match = strstr(text, pattern);
    if (match == NULL) {
        return 0;
    }

    *location = (size_t)(match - text);
    return 1;
}

int main(void)
{
    const char text[] = "The quick brown fox jumps over the lazy dog.";
    const char pattern[] = "brown fox";
    size_t location = 0;
    int result = find_literal(text, pattern, &location);

    if (result < 0) {
        fputs("Invalid argument.\n", stderr);
        return 1;
    }

    if (result == 0) {
        puts("Pattern not found.");
        return 0;
    }

    if (printf("Pattern found at index %zu.\n", location) < 0) {
        return 1;
    }

    return 0;
}