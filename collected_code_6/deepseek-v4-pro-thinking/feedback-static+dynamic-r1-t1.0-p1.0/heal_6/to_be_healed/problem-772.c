#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

void remove_words_of_length(char *str, size_t bufsize, int k) {
    if (str == NULL || bufsize == 0 || k <= 0) {
        return;
    }

    size_t i = 0, j = 0;
    int has_word = 0;

    while (i < bufsize && str[i] != '\0') {
        while (i < bufsize && str[i] != '\0' && isspace((unsigned char)str[i])) {
            i++;
        }
        if (i >= bufsize || str[i] == '\0') {
            break;
        }

        size_t word_start = i;
        size_t word_len = 0;

        while (i < bufsize && str[i] != '\0' && !isspace((unsigned char)str[i])) {
            i++;
            word_len++;
        }

        if (word_len != (size_t)k) {
            if (has_word) {
                if (j + 1 + word_len >= bufsize) {
                    break;
                }
                str[j++] = ' ';
            } else {
                if (j + word_len >= bufsize) {
                    break;
                }
            }
            memmove(str + j, str + word_start, word_len);
            j += word_len;
            has_word = 1;
        }
    }

    if (j < bufsize) {
        str[j] = '\0';
    } else {
        str[bufsize - 1] = '\0';
    }
}

int main(void) {
    const char sample[] = "This is a sample string with several words";
    int k = 2;
    size_t len = sizeof(sample);
    char *str = malloc(len);
    if (str == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(str, sample, len);

    printf("Original: %s\n", str);
    remove_words_of_length(str, len, k);
    printf("Modified: %s\n", str);

    free(str);
    return 0;
}