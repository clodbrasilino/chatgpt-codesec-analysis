#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_k_length_words(const char *str, int k) {
    char *result = NULL;
    size_t result_len = 0;
    const char *p = str;
    size_t next_token_pos;

    while ((next_token_pos = strcspn(p, " ")) != 0) {
        size_t token_len = (size_t)(memchr(p, ' ', next_token_pos) ? next_token_pos : strlen(p));

        if (token_len != (size_t)k) {
            char *new_result = realloc(result, result_len + token_len + 1);
            if (new_result) {
                result = new_result;
                if (result_len > 0) {
                    result[result_len++] = ' ';
                }
                memcpy(result + result_len, p, token_len);
                result_len += token_len;
            } else {
                free(result);
                return NULL;
            }
        }

        p += next_token_pos + (p[next_token_pos] == ' ');
    }

    if (result) {
        result[result_len] = '\0';
    } else {
        result = strdup("");
    }

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