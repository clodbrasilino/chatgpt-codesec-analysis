#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int count_char_in_repeated_string(const char *str, int repeat_count, char c) {
    if (str == NULL || !*str) {
        return 0;
    }
    size_t len = strlen(str);
    int total_length = (int)(len * repeat_count);
    int count = 0;

    for (int i = 0; i < total_length; ++i) {
        if (str[i % len] == c) {
            ++count;
        }
    }

    return count;
}

int main() {
    const char *input_str = "hello";
    int repeat_times = 3;
    char target_char = 'l';

    int result = count_char_in_repeated_string(input_str, repeat_times, target_char);
    printf("Count of '%c' in the repeated string: %d\n", target_char, result);

    return 0;
}