#include <stdio.h>
#include <string.h>
#include <ctype.h>

void move_numbers(char *str, size_t str_len) {
    char result[str_len + 1];
    char temp[str_len + 1];
    int j = 0, k = 0;

    for (size_t i = 0; i < str_len; i++) {
        if (isdigit(str[i])) {
            if (j < str_len) {
                result[j++] = str[i];
            }
        } else {
            if (k < str_len) {
                temp[k++] = str[i];
            }
        }
    }

    temp[k] = '\0';
    result[j] = '\0';

    size_t temp_len = strnlen(temp, str_len);
    size_t result_len = strnlen(result, str_len);

    if (result_len + temp_len + 1 <= str_len) {
        strncat(result, temp, str_len - result_len - 1);
    }

    size_t final_len = strnlen(result, str_len);
    if (final_len < str_len) {
        strncpy(str, result, str_len);
        str[str_len] = '\0';
    }
}

int main() {
    char str[] = "a2b3c4d5e6";
    move_numbers(str, sizeof(str) - 1);
    printf("%s\n", str);
    return 0;
}