#include <stdio.h>
#include <string.h>

int count_char_in_repeated_string(const char *str, int repeat_count, char c) {
    size_t len = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (str && (len = strlen(str)) > 0) {
        int total_length = (int)(len * repeat_count);
        int count = 0;

        for (int i = 0; i < total_length; ++i) {
            if (str[i % len] == c) {
                ++count;
            }
        }

        return count;
    }
    return 0;
}

int main() {
    const char *input_str = "hello";
    int repeat_times = 3;
    char target_char = 'l';

    int result = count_char_in_repeated_string(input_str, repeat_times, target_char);
    printf("Count of '%c' in the repeated string: %d\n", target_char, result);

    return 0;
}