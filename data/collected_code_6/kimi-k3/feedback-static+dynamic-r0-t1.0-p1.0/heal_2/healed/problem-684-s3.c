#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

size_t count_char_in_repeated_string(const char *str, size_t str_len, char ch, size_t repeat_count)
{
    size_t char_count = 0;
    size_t i;
    size_t total_count;

    if (str == NULL) {
        return 0;
    }

    if (str_len == 0 || repeat_count == 0) {
        return 0;
    }

    for (i = 0; i < str_len; i++) {
        if (str[i] == ch) {
            char_count++;
        }
    }

    if (char_count > 0 && repeat_count > SIZE_MAX / char_count) {
        return 0;
    }

    total_count = char_count * repeat_count;

    return total_count;
}

int main(void)
{
    const char str[] = "abcac";
    size_t str_len = sizeof(str) - 1;
    char ch = 'a';
    size_t repeat_count = 3;
    size_t result;

    if (repeat_count == 0) {
        fprintf(stderr, "Error: repeat_count must be greater than zero\n");
        return EXIT_FAILURE;
    }

    result = count_char_in_repeated_string(str, str_len, ch, repeat_count);

    if (result == 0 && memchr(str, ch, str_len) != NULL) {
        fprintf(stderr, "Error: overflow occurred during calculation\n");
        return EXIT_FAILURE;
    }

    printf("Character '%c' occurs %zu times in the repeated string.\n", ch, result);

    return EXIT_SUCCESS;
}