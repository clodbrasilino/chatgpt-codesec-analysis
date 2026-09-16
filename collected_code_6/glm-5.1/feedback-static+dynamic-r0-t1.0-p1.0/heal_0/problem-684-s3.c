#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

size_t count_char_in_repeated_string(const char *str, size_t str_len, char c, size_t repeat_count) {
    if (str == NULL || str_len == 0) {
        return 0;
    }

    size_t count = 0;
    for (size_t i = 0; i < str_len; i++) {
        if (str[i] == c) {
            count++;
        }
    }

    return count * repeat_count;
}

int main(void) {
    const char *str = "abc";
    size_t str_len = strlen(str);
    char target = 'a';
    size_t repeat_count = 10;

    size_t result = count_char_in_repeated_string(str, str_len, target, repeat_count);

    printf("%zu\n", result);

    return 0;
}