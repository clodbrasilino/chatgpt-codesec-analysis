#include <stdio.h>
#include <string.h>
#include <stdlib.h>

size_t count_char_in_repeated_string(const char *str, char ch, size_t repeat_count)
{
    size_t len;
    size_t char_count = 0;
    size_t i;
    size_t total_count;

    if (str == NULL) {
        return 0;
    }

    len = strlen(str);

    if (len == 0 || repeat_count == 0) {
        return 0;
    }

    for (i = 0; i < len; i++) {
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
    char ch = 'a';
    size_t repeat_count = 3;
    size_t result;

    result = count_char_in_repeated_string(str, ch, repeat_count);

    if (result == 0 && strchr(str, ch) != NULL && repeat_count > 0) {
        fprintf(stderr, "Error: overflow occurred during calculation\n");
        return EXIT_FAILURE;
    }

    printf("Character '%c' occurs %zu times in the repeated string.\n", ch, result);

    return EXIT_SUCCESS;
}