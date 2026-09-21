#include <stdio.h>
#include <string.h>

int count_char_in_repeated_string(const char *str, int repeat_count, char c, size_t str_len) {
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
    int repeat_times = 3;
    char target_char = 'l';
    size_t input_len = strlen(input_str);

    int result = count_char_in_repeated_string(input_str, repeat_times, target_char, input_len);
    printf("Count of '%c' in the repeated string: %d\n", target_char, result);

    return 0;
}