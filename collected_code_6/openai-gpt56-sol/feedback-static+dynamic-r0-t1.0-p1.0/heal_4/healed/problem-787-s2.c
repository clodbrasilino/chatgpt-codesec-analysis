#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool matches_pattern(const char *str, size_t length)
{
    static const char pattern[] = "abbb";
    const size_t pattern_length = sizeof pattern - 1U;

    return str != NULL &&
           length == pattern_length &&
           memcmp(str, pattern, pattern_length) == 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0U;
    const ssize_t count = getline(&input, &capacity, stdin);

    if (count < 0) {
        free(input);
        return 1;
    }

    size_t length = (size_t)count;

    if (length > 0U && input[length - 1U] == '\n') {
        input[--length] = '\0';
    }

    if (length > 0U && input[length - 1U] == '\r') {
        input[--length] = '\0';
    }

    puts(matches_pattern(input, length) ? "Match" : "No match");

    free(input);
    return 0;
}