#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected True, got <no output>
  *  test case 1 failed: expected False, got <no output>
  *  test case 2 failed: expected False, got <no output>
  */

bool is_word_present(const char *sentence, const char *word) {
    if (sentence == NULL || word == NULL) {
        return false;
    }

    size_t sentence_len = strlen(sentence);
    size_t word_len = strlen(word);

    if (word_len == 0) {
        return false;
    }

    char *copy = (char *)malloc(sentence_len + 1);
    if (copy == NULL) {
        return false;
    }

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