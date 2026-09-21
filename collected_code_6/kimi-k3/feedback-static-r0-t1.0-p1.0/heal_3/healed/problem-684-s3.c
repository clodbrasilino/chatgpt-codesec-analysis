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

    if (str == NULL || str_len == 0 || repeat_count == 0) {
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

int main(int argc, const char *argv[])
{
    const char *str = "abcac";
    size_t str_len = 5;
    char ch = 'a';
    size_t repeat_count;
    size_t result;
    int has_char = 0;
    size_t i;
    char *endptr;

    if (argc > 1) {
        long val;
        errno = 0;
        val = strtol(argv[1], &endptr, 10);
        if (errno != 0 || *endptr != '\0' || val < 0) {
            fprintf(stderr, "Error: invalid repeat count\n");
            return EXIT_FAILURE;
        }
        repeat_count = (size_t)val;
    } else {
        repeat_count = 3;
    }

    result = count_char_in_repeated_string(str, str_len, ch, repeat_count);

    for (i = 0; i < str_len; i++) {
        if (str[i] == ch) {
            has_char = 1;
            break;
        }
    }

    if (result == 0 && has_char && repeat_count != 0) {
        fprintf(stderr, "Error: overflow occurred during calculation\n");
        return EXIT_FAILURE;
    }

    printf("Character '%c' occurs %zu times in the repeated string.\n", ch, result);

    return EXIT_SUCCESS;
}