#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_WORD_LEN 256

bool word_contains_z(const char *word, size_t max_len)
{
    if (word == NULL || max_len == 0) {
        return false;
    }

    size_t len = 0;

    while (len < max_len && word[len] != '\0') {
        len++;
    }

    if (len == 0 || len == max_len) {
        return false;
    }

    for (size_t i = 0; i < len; i++) {
        if (word[i] == 'z' || word[i] == 'Z') {
            return true;
        }
    }

    return false;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LEN];

    printf("Enter a word: ");

    if (fgets(word, sizeof(word), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    size_t len = strcspn(word, "\n");
    word[len] = '\0';

    if (word_contains_z(word, sizeof(word))) {
        printf("The word contains 'z'.\n");
    } else {
        printf("The word does not contain 'z'.\n");
    }

    return EXIT_SUCCESS;
}