#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* remove_k_length_words(char *str, int k) {
    int total_len = strlen(str);
    char *result = (char*)malloc(total_len + 1);
    if (!result) return NULL;
    result[0] = '\0';

    int i = 0, j = 0;
    char *res_pos = result;

    while (i < total_len) {
        j = i;
        while (j < total_len && str[j] != ' ') j++;
        int word_len = j - i;
        if (word_len != k) {
            strncpy(res_pos, str + i, word_len);
            res_pos += word_len;
            if (j < total_len) *res_pos++ = ' ';
        }
        i = j + 1;
    }

    *res_pos = '\0';
    free(str);
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