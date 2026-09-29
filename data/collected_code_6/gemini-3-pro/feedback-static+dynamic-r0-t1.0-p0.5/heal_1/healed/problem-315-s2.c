#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* find_first_max_even_word(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    int max_len = 0;
    int current_len = 0;
    const char* max_word_start = NULL;
    const char* current_word_start = NULL;
    const char* p = str;

    while (*p != '\0') {
        if (isalpha((unsigned char)*p)) {
            if (current_len == 0) {
                current_word_start = p;
            }
            current_len++;
        } else {
            if (current_len > 0 && current_len % 2 == 0) {
                if (current_len > max_len) {
                    max_len = current_len;
                    max_word_start = current_word_start;
                }
            }
            current_len = 0;
        }
        p++;
    }

    if (current_len > 0 && current_len % 2 == 0) {
        if (current_len > max_len) {
            max_len = current_len;
            max_word_start = current_word_start;
        }
    }

    if (max_word_start == NULL) {
        return NULL;
    }

    char* result = (char*)malloc((max_len + 1) * sizeof(char));
    if (result == NULL) {
        return NULL;
    }

    memcpy(result, max_word_start, max_len);
    result[max_len] = '\0';

    return result;
}

int main(void) {
    const char* text = "This is a test string with some even length words";
    char* max_even_word = find_first_max_even_word(text);

    if (max_even_word != NULL) {
        printf("%s\n", max_even_word);
        free(max_even_word);
    } else {
        printf("\n");
    }

    return 0;
}