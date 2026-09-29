#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(copy, sentence);

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

    return found;
}

int main(int argc, char const * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s \"<sentence>\" \"<word>\"\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (is_word_present(argv[1], argv[2])) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return EXIT_SUCCESS;
}