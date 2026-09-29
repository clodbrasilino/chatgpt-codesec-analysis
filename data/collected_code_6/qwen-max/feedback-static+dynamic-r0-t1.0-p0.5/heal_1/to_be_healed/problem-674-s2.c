#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 100

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LENGTH];
} Word;

typedef struct {
    Word words[MAX_WORDS];
    int count;
} WordList;

void init_word_list(WordList *list) {
    list->count = 0;
}

bool add_word(WordList *list, const char *word) {
    if (list->count >= MAX_WORDS) {
        return false;
    }
    for (int i = 0; i < list->count; ++i) {
        if (strcmp(list->words[i].word, word) == 0) {
            return false;
        }
    }
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(list->words[list->count].word, word, MAX_WORD_LENGTH);
    list->count++;
    return true;
}

char *remove_duplicates(const char *input) {
    WordList list;
    init_word_list(&list);

    const char *token;
    const char *context = NULL;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    char *result = (char *)malloc(input_len + 1);
    if (!result) {
        return NULL;
    }
    result[0] = '\0';

    /* Possible weaknesses found:
     *  passing argument 3 of 'strtok_r' from incompatible pointer type [-Wincompatible-pointer-types]
     */
    token = strtok_r((char *)input, " ", &context);
    while (token) {
        if (add_word(&list, token)) {
            /* Possible weaknesses found:
             * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
             */
            strcat(result, token);
            /* Possible weaknesses found:
             * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). Risk is low because the source is a constant character. (risk 1, buffer)
             */
            strcat(result, " ");
        }
        /* Possible weaknesses found:
         *  passing argument 3 of 'strtok_r' from incompatible pointer type [-Wincompatible-pointer-types]
         */
        token = strtok_r(NULL, " ", &context);
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (result[strlen(result) - 1] == ' ') {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        result[strlen(result) - 1] = '\0';
    }

    return result;
}

int main() {
    const char *input = "this is a test this is only a test";
    char *output = remove_duplicates(input);
    if (output) {
        printf("%s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }
    return 0;
}