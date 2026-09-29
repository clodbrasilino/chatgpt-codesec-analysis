#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool is_word_present(const char *sentence, const char *word) {
    if (sentence == NULL || word == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t sentence_len = strlen(sentence);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t word_len = strlen(word);

    if (word_len == 0) {
        return false;
    }

    char *copy = (char *)malloc(sentence_len + 1);
    if (copy == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, sentence, sentence_len + 1);

    char *token = strtok(copy, " \t\n\r.,!?;:\"'");
    bool found = false;

    while (token != NULL) {
        if (strcmp(token, word) == 0) {
            found = true;
            break;
        }
        token = strtok(NULL, " \t\n\r.,!?;:\"'");
    }

    free(copy);
    copy = NULL;

    return found;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s \"<sentence>\" \"<word>\"\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (is_word_present(argv[1], argv[2])) {
        printf("Word is present.\n");
    } else {
        printf("Word is not present.\n");
    }

    return EXIT_SUCCESS;
}