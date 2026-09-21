#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_k_length_words(const char *str, int k) {
    if (str == NULL || k <= 0) return NULL;

    size_t str_len = strlen(str);
    char *result = malloc(1);
    if (result == NULL) return NULL;
    result[0] = '\0';
    size_t result_len = 0;

    const char *p = str;
    size_t next_token_pos;

    while ((next_token_pos = strcspn(p, " ")) != 0) {
        size_t token_len = (p[next_token_pos] == ' ') ? next_token_pos : str_len - (p - str);

        if (token_len != (size_t)k) {
            size_t new_len = result_len + token_len + 1;
            char *new_result = realloc(result, new_len);
            if (new_result == NULL) {
                free(result);
                return NULL;
            }
            result = new_result;
            if (result_len > 0 && result_len < new_len - 1)
                result[result_len++] = ' ';
            memcpy(result + result_len, p, token_len);
            result_len += token_len;
        }

        p += next_token_pos + (p[next_token_pos] == ' ');
        if (p - str >= str_len) break;
    }

    result[result_len] = '\0';

    return result;
}

int main() {
    const char str[] = "This is a test string with some words of length four";
    int k = 4;
    char *new_str = remove_k_length_words(str, k);
    if (new_str) {
        printf("%s\n", new_str);
        free(new_str);
    }
    return 0;
}