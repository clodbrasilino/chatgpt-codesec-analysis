#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 50

char* remove_duplicates(const char *input) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char words[MAX_WORDS][MAX_WORD_LENGTH + 1] = {0};
    int word_count = 0;
    const char *token;
    char *output = NULL;
    size_t total_length = 0;

    token = strtok((char *)input, " ");
    while (token && word_count < MAX_WORDS) {
        int i;
        for (i = 0; i < word_count; i++) {
            if (strcmp(words[i], token) == 0) {
                break;
            }
        }
        if (i == word_count) {
            size_t length = strnlen(token, MAX_WORD_LENGTH);
            if (length < MAX_WORD_LENGTH) {
                /* Possible weaknesses found:
                 * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                 */
                strncpy(words[word_count], token, length);
                words[word_count][length] = '\0';
                word_count++;
                total_length += length + 1;
            }
        }
        token = strtok(NULL, " ");
    }

    total_length--;
    output = (char *)malloc(total_length + 1);
    if (output == NULL) {
        return NULL;
    }

    char *temp_output = output;
    for (int i = 0; i < word_count; i++) {
        size_t length = strnlen(words[i], MAX_WORD_LENGTH);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(temp_output, words[i], length);
        temp_output += length;
        *temp_output++ = ' ';
    }
    if (word_count > 0) {
        *(temp_output - 1) = '\0';
    }

    return output;
}

int main() {
    const char *input = "Python Exercises Practice Solution Python";
    char *result = remove_duplicates(input);

    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    return 0;
}