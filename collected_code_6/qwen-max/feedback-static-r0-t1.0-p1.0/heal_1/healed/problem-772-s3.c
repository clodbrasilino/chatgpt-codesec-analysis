#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* remove_k_length_words(const char *str, int k) {
    size_t len = strlen(str);
    char *result = (char*)malloc(len + 1);
    if (!result) return NULL;
    result[0] = '\0';

    const char *p = str;
    while (*p) {
        const char *start = p;
        while (*p && *p != ' ') p++;
        size_t word_len = p - start;
        if (word_len != k) {
            size_t new_len = strlen(result) + word_len + (p < str + len ? 1 : 0);
            if (new_len > len + 1) {
                free(result);
                return NULL;
            }
            strcat(result, start);
            if (p < str + len && *p == ' ') {
                strcat(result, " ");
            }
        }
        p += (p < str + len && *p == ' ') ? 1 : 0;
    }

    return result;
}

int main() {
    char str[] = "this is a test string with some words of length four and five";
    int k = 4;
    char *result = remove_k_length_words(str, k);
    if (result) {
        printf("%s\n", result);
        free(result);
    }
    return 0;
}