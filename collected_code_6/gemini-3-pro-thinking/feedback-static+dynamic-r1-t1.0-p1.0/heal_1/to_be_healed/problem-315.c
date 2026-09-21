#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *find_first_max_even_word(const char *str);

char *find_first_max_even_word(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t max_len = 0;
    const char *best_start = NULL;
    const char *current = str;

    while (*current != '\0') {
        while (*current != '\0' && isspace((unsigned char)*current)) {
            current++;
        }

        if (*current == '\0') {
            break;
        }

        const char *word_start = current;
        size_t word_len = 0;

        while (*current != '\0' && !isspace((unsigned char)*current)) {
            word_len++;
            current++;
        }

        if ((word_len % 2 == 0) && (word_len > max_len)) {
            max_len = word_len;
            best_start = word_start;
        }
    }

    if (max_len == 0 || best_start == NULL) {
        return NULL;
    }

    char *result = (char *)malloc(max_len + 1);
    if (result == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, best_start, max_len);
    result[max_len] = '\0';

    return result;
}

int main(void) {
    const char *text = "Write a carefully crafted sentence testing even words";
    char *result = find_first_max_even_word(text);

    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } 

    return 0;
}