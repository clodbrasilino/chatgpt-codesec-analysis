#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define ERROR_BUFFER_SIZE 256
#define MAX_WORD_LENGTH 255

void find_five_char_words(const char *input) {
    regex_t regex;
    regmatch_t match;
    const char *pattern = "\\b[a-zA-Z]{5}\\b";
    
    int result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result != 0) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char error_buffer[ERROR_BUFFER_SIZE];
        regerror(result, &regex, error_buffer, ERROR_BUFFER_SIZE);
        fprintf(stderr, "Regex compilation failed: %s\n", error_buffer);
        return;
    }

    const char *cursor = input;
    size_t input_length = strnlen(input, MAX_WORD_LENGTH * 100);
    
    while (regexec(&regex, cursor, 1, &match, 0) == 0) {
        if (match.rm_so < 0 || match.rm_eo < 0 || match.rm_eo <= match.rm_so) {
            break;
        }
        
        size_t word_length = (size_t)(match.rm_eo - match.rm_so);
        if (word_length > MAX_WORD_LENGTH) {
            fprintf(stderr, "Word length exceeds maximum allowed\n");
            regfree(&regex);
            return;
        }
        
        size_t cursor_offset = (size_t)(cursor - input);
        if (cursor_offset + (size_t)match.rm_eo > input_length) {
            break;
        }
        
        char *word = (char *)malloc(word_length + 1);
        if (word == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            regfree(&regex);
            return;
        }
        
        size_t available = input_length - (cursor_offset + (size_t)match.rm_so);
        /* Possible weaknesses found:
         *  to_copy is assigned '(word_length<available)?word_length:available' here.
         */
        size_t to_copy = (word_length < available) ? word_length : available;
        /* Possible weaknesses found:
         *  Condition 'to_copy<=word_length' is always false
         *  Condition 'to_copy<=word_length' is always false [knownConditionTrueFalse]
         */
        if (to_copy > 0 && to_copy <= word_length) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(word, cursor + match.rm_so, to_copy);
        }
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
    if (read > 0 && (size_t)read <= buffer_size && input[read - 1] == '\n') {
        input[read - 1] = '\0';
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (read > 1) {
            read--;
        }
    }

    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    if (read > 0 && (size_t)read <= buffer_size) {
        find_five_char_words(input);
    }
    
    free(input);
    return EXIT_SUCCESS;
}