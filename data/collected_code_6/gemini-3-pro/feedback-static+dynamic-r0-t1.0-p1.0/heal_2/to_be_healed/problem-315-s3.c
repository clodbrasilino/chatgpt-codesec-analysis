#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* find_first_max_even_word(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    size_t max_len = 0;
    size_t current_len = 0;
    const char* max_word_start = NULL;
    const char* current_word_start = NULL;

    size_t i = 0;
    while (1) {
        char c = str[i];
        if (c != '\0' && !isspace((unsigned char)c)) {
            if (current_len == 0) {
                current_word_start = &str[i];
            }
            current_len++;
        } else {
            if (current_len > 0) {
                if (current_len % 2 == 0 && current_len > max_len) {
                    max_len = current_len;
                    max_word_start = current_word_start;
                }
                current_len = 0;
            }
        }
        if (c == '\0') {
            break;
        }
        i++;
    }

    if (max_len == 0 || max_word_start == NULL) {
        return NULL;
    }

    char* result = (char*)malloc(max_len + 1);
    if (result == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, max_word_start, max_len);
    result[max_len] = '\0';

    return result;
}

int main(void) {
    const char* test_str = "This is a test sentence with some even length words";
    char* max_even_word = find_first_max_even_word(test_str);

    if (max_even_word != NULL) {
        printf("%s\n", max_even_word);
        free(max_even_word);
    } 

    return 0;
}