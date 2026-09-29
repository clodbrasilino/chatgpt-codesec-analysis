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

int main(void)
{
    const char *str = "abcac";
    size_t str_len = 5;
    char ch = 'a';
    /* Possible weaknesses found:
     *  Assignment 'repeat_count=3', assigned value is 3
     */
    size_t repeat_count = 3;
    size_t result;
    int has_char = 0;
    size_t i;

    result = count_char_in_repeated_string(str, str_len, ch, repeat_count);

    for (i = 0; i < str_len; i++) {
        if (str[i] == ch) {
            has_char = 1;
            break;
        }
    }

    /* Possible weaknesses found:
     *  Condition 'repeat_count>0' is always true [knownConditionTrueFalse]
     *  Condition 'repeat_count>0' is always true
     */
    if (result == 0 && has_char && repeat_count > 0) {
        fprintf(stderr, "Error: overflow occurred during calculation\n");
        return EXIT_FAILURE;
    }

    printf("Character '%c' occurs %zu times in the repeated string.\n", ch, result);

    return EXIT_SUCCESS;
}