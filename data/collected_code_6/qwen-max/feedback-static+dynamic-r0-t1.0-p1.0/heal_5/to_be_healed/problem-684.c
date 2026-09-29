#include <stdio.h>
#include <string.h>

int count_char_in_repeated_string(const char *str, size_t str_len, int repeat_count, char c) {
    if (str == NULL || str_len == 0 || repeat_count <= 0) {
        return 0;
    }
    int total_length = (int)(str_len * repeat_count);
    int count = 0;

    for (int i = 0; i < total_length; ++i) {
        if (str[i % str_len] == c) {
            ++count;
        }
    }

    return count;
}

int main() {
    const char *input_str = "hello";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input_str);
    int repeat_times = 3;
    char target_char = 'l';

    int result = count_char_in_repeated_string(input_str, input_len, repeat_times, target_char);
    printf("Count of '%c' in the repeated string: %d\n", target_char, result);

    return 0;
}