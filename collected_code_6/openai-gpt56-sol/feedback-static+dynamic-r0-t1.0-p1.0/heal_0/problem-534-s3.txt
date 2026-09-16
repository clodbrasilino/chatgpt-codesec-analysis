#include <stdio.h>
#include <string.h>
#include <stddef.h>

static int find_literal(const char *text, const char *pattern, size_t *position)
{
    const char *match;

    if (text == NULL || pattern == NULL || position == NULL) {
        return -1;
    }

    match = strstr(text, pattern);
    if (match == NULL) {
        return 0;
    }

    *position = (size_t)(match - text);
    return 1;
}

int main(void)
{
    const char text[] = "The quick brown fox jumps over the lazy dog.";
    const char pattern[] = "brown fox";
    size_t position = 0U;
    int result = find_literal(text, pattern, &position);

    if (result < 0) {
        fputs("Invalid argument.\n", stderr);
        return 1;
    }

    if (result == 0) {
        puts("Pattern not found.");
        return 0;
    }

    printf("Pattern found at index %zu.\n", position);
    return 0;
}