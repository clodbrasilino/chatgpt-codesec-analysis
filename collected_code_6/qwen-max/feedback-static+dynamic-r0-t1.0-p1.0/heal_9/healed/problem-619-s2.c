#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void move_numbers(char *str, size_t str_len) {
    char *result = malloc(str_len + 1);
    if (result == NULL) return;
    char *temp = malloc(str_len + 1);
    if (temp == NULL) {
        free(result);
        return;
    }
    int j = 0, k = 0;

    for (size_t i = 0; i < str_len; i++) {
        if (isdigit((unsigned char)str[i]) && j < str_len) {
            result[j++] = str[i];
        } else if (k < str_len) {
            temp[k++] = str[i];
        }
    }

    temp[k] = '\0';
    result[j] = '\0';

    if (j + k + 1 <= str_len) {
        strncat(result, temp, str_len - j);
    }

    size_t final_len = strlen(result);
    if (final_len < str_len) {
        memmove(str, result, final_len);
        str[final_len] = '\0';
    } else {
        snprintf(str, str_len + 1, "%.*s", (int)str_len, result);
    }

    free(result);
    free(temp);
}

int main() {
    char str[] = "a2b3c4d5e6";
    move_numbers(str, sizeof(str) - 1);
    printf("%s\n", str);
    return 0;
}