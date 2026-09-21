#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define ERROR_BUFFER_SIZE 256

void find_five_char_words(const char *input) {
    regex_t regex;
    regmatch_t match;
    const char *pattern = "\\b[a-zA-Z]{5}\\b";
    /* Possible weaknesses found:
     *  The scope of the variable 'error_buffer' can be reduced. [variableScope]
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char error_buffer[ERROR_BUFFER_SIZE];
    
    int result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result != 0) {
        regerror(result, &regex, error_buffer, ERROR_BUFFER_SIZE - 1);
        error_buffer[ERROR_BUFFER_SIZE - 1] = '\0';
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
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t available = strlen(cursor + match.rm_so);
        size_t to_copy = (word_length < available) ? word_length : available;
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(word, cursor + match.rm_so, to_copy);
        word[to_copy] = '\0';
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
    ssize_t read = getline(&input, &buffer_size, stdin);
    if (read == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    if (read > 0 && input[read - 1] == '\n') {
        input[read - 1] = '\0';
    }

    find_five_char_words(input);
    free(input);

    return EXIT_SUCCESS;
}