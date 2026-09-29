#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void find_five_char_words(const char *input) {
    regex_t regex;
    regmatch_t match;
    const char *pattern = "\\b[a-zA-Z]{5}\\b";
    int result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result != 0) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char error_buffer[256];
        regerror(result, &regex, error_buffer, sizeof(error_buffer));
        fprintf(stderr, "Regex compilation failed: %s\n", error_buffer);
        return;
    }

    const char *cursor = input;
    while (regexec(&regex, cursor, 1, &match, 0) == 0) {
        size_t word_length = match.rm_eo - match.rm_so;
        if (word_length > 255) {
            fprintf(stderr, "Word length exceeds maximum allowed\n");
            regfree(&regex);
            return;
        }
        char *word = (char *)malloc(word_length + 1);
        if (word == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            regfree(&regex);
            return;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(word, cursor + match.rm_so, word_length);
        word[word_length] = '\0';
        printf("%s\n", word);
        free(word);
        cursor += match.rm_eo;
    }

    regfree(&regex);
}

int main(void) {
    char *input = NULL;
    size_t buffer_size = 0;
    printf("Enter a string: ");
    if (getline(&input, &buffer_size, stdin) == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return EXIT_FAILURE;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_length = strlen(input);
    if (input_length > 0 && input[input_length - 1] == '\n') {
        input[input_length - 1] = '\0';
    }

    find_five_char_words(input);
    free(input);

    return EXIT_SUCCESS;
}