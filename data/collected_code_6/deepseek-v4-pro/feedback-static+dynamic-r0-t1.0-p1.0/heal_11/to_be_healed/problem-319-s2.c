#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define ERROR_BUFFER_SIZE 256
#define MAX_WORD_LENGTH 255
#define MAX_INPUT_SIZE 65536

void find_five_char_words(const char *input) {
    regex_t regex;
    regmatch_t match;
    const char *pattern = "\\b[a-zA-Z]{5}\\b";
    
    int result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result != 0) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char error_buffer[ERROR_BUFFER_SIZE] = {0};
        regerror(result, &regex, error_buffer, ERROR_BUFFER_SIZE);
        fprintf(stderr, "Regex compilation failed: %s\n", error_buffer);
        return;
    }

    const char *cursor = input;
    size_t input_length = strnlen(input, MAX_INPUT_SIZE);
    if (input_length >= MAX_INPUT_SIZE) {
        fprintf(stderr, "Input too long\n");
        regfree(&regex);
        return;
    }
    
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
        if (cursor_offset > input_length) {
            break;
        }
        
        size_t remaining = input_length - cursor_offset;
        if ((size_t)match.rm_so > remaining || (size_t)match.rm_eo > remaining) {
            break;
        }
        
        char *word = (char *)malloc(word_length + 1);
        if (word == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            regfree(&regex);
            return;
        }
        
        const char *src = cursor + match.rm_so;
        size_t bytes_to_copy = word_length;
        size_t max_src_bytes = input + input_length - src;
        
        if (bytes_to_copy > max_src_bytes) {
            bytes_to_copy = max_src_bytes;
        }
        
        /* Possible weaknesses found:
         *  outer condition: bytes_to_copy<=word_length
         */
        if (src != NULL && bytes_to_copy > 0 && bytes_to_copy <= word_length) {
            /* Possible weaknesses found:
             *  identical inner condition: bytes_to_copy<=word_length
             *  Identical inner 'if' condition is always true. [identicalInnerCondition]
             */
            if (bytes_to_copy <= word_length) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(word, src, bytes_to_copy);
            }
            word[bytes_to_copy] = '\0';
        } else {
            word[0] = '\0';
        }
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
    
    if (input == NULL) {
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     *  Assuming that condition 'read>0' is not redundant
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    if (read > 0 && (size_t)read <= MAX_INPUT_SIZE) {
        /* Possible weaknesses found:
         *  Assignment 'len=(unsigned long)read', assigned value is greater than 0
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        size_t len = (size_t)read;
        /* Possible weaknesses found:
         *  Condition 'len>0' is always true
         *  Condition 'len>0' is always true [knownConditionTrueFalse]
         */
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
            len--;
        }
        if (len > 0) {
            find_five_char_words(input);
        } else {
            fprintf(stderr, "Empty input\n");
        }
    } else if (read == 0) {
        fprintf(stderr, "Empty input\n");
    } else {
        fprintf(stderr, "Input exceeds maximum allowed size\n");
    }
    
    free(input);
    return EXIT_SUCCESS;
}