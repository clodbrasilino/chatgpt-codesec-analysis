#include <stdio.h>
#include <string.h>
#include <ctype.h>

void move_numbers(char *str, size_t str_len) {
    char result[200 + 1] = "";
    char temp[200 + 1] = "";
    int j = 0, k = 0;

    for (size_t i = 0; i < str_len; i++) {
        if (isdigit(str[i])) {
            if (j < sizeof(result) - 1) {
                result[j++] = str[i];
            }
        } else {
            if (k < sizeof(temp) - 1) {
                temp[k++] = str[i];
            }
        }
    }

    temp[k] = '\0';
    result[j] = '\0';

    size_t temp_len = strlen(temp);
    size_t result_len = strlen(result);

    if (result_len + temp_len + 1 <= sizeof(result)) {
        strncat(result, temp, sizeof(result) - result_len - 1);
    }

    size_t final_len = strlen(result);
    if (final_len < str_len) {
        strncpy(str, result, str_len);
        str[str_len - 1] = '\0';
    }
}

int main() {
    char str[] = "a2b3c4d5e6";
    move_numbers(str, sizeof(str) - 1);
    printf("%s\n", str);
    return 0;
}