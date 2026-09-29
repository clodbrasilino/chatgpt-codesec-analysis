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
        char error_buffer[ERROR_BUFFER_SIZE];
        regerror(result, &regex, error_buffer, ERROR_BUFFER_SIZE - 1);
        error_buffer[ERROR_BUFFER_SIZE - 1] = '\0';
        fprintf(stderr, "Regex compilation failed: %s\n", error_buffer);
        return;
    }

    const char *cursor = input;
    size_t input_length = strnlen(input, MAX_INPUT_SIZE - 1);
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
        if (cursor_offset > input_length || (size_t)match.rm_eo > input_length - cursor_offset) {
            break;
        }
        
        char *word = (char *)malloc(word_length + 1);
        if (word == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            regfree(&regex);
            return;
        }
        
        if (word_length > 0 && cursor + match.rm_so + word_length <= input + input_length) {
            memcpy(word, cursor + match.rm_so, word_length);
            word[word_length] = '\0';
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
        free(input);
        return EXIT_FAILURE;
    }
    
    if (read > 0) {
        size_t len = (size_t)read;
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
            len--;
        }
        if (len > 0 && len < MAX_INPUT_SIZE) {
            find_five_char_words(input);
        }
    }
    
    free(input);
    return EXIT_SUCCESS;
}