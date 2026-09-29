#include <stdio.h>
#include <string.h>

int min_length_by_removing_char(const char *str, size_t str_len, char ch) {
    int count = 0;
    for (size_t i = 0; i < str_len; ++i) {
        if (str[i] == ch) {
            count++;
        }
    }
    return str_len - count;
}

int main() {
    const char *input = "example string";
    char remove_char = 'e';
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    int new_length = min_length_by_removing_char(input, input_len, remove_char);
    printf("New length: %d\n", new_length);
    return 0;
}