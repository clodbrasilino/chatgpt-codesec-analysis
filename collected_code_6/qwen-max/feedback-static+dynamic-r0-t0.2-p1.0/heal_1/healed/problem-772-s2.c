#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_k_length_words(const char *str, int k) {
    size_t len = strlen(str);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) return NULL;
    char *write_ptr = result;
    const char *read_ptr = str;
    while (*read_ptr) {
        const char *start_word = read_ptr;
        while (*read_ptr && *read_ptr != ' ') read_ptr++;
        if (read_ptr - start_word != k) {
            while (start_word != read_ptr) *write_ptr++ = *start_word++;
        }
        if (*read_ptr) *write_ptr++ = *read_ptr++;
    }
    *write_ptr = '\0';
    return result;
}

int main() {
    char str[] = "This is a test string with some words of length five";
    int k = 5;
    char *result = remove_k_length_words(str, k);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else {
        printf("Memory allocation failed\n");
    }
    return 0;
}