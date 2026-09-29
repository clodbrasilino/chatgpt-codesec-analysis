#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_MATCHES 100
#define MAX_WORD_LEN 6
#define ERROR_BUFFER_SIZE 256
#define MAX_INPUT_LEN 4096

void find_words(const char *str) {
    regex_t regex;
    regmatch_t matches[1];
    const char *pattern = "\\b[a-zA-Z]{3,5}\\b";
    int ret;
    char *copy;
    size_t len;
    int count = 0;
    size_t offset = 0;

    if (str == NULL) {
        fprintf(stderr, "Invalid input string\n");
        return;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        char *error_buffer = (char *)malloc(ERROR_BUFFER_SIZE);
        if (error_buffer == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return;
        }
        regerror(ret, &regex, error_buffer, ERROR_BUFFER_SIZE);
        fprintf(stderr, "Regex compilation failed: %s\n", error_buffer);
        free(error_buffer);
        return;
    }

    len = strnlen(str, MAX_INPUT_LEN);
    if (len == 0 || len >= MAX_INPUT_LEN) {
        fprintf(stderr, "Invalid string length\n");
        regfree(&regex);
        return;
    }

    copy = (char *)malloc(len + 1);
    if (copy == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        regfree(&regex);
        return;
    }

    snprintf(copy, len + 1, "%s", str);

    printf("Words with 3, 4, or 5 characters:\n");

    while (offset < len && count < MAX_MATCHES) {
        ret = regexec(&regex, copy + offset, 1, matches, 0);
        
        if (ret == REG_NOMATCH) {
            break;
        } else if (ret != 0) {
            char *error_buffer = (char *)malloc(ERROR_BUFFER_SIZE);
            if (error_buffer != NULL) {
                regerror(ret, &regex, error_buffer, ERROR_BUFFER_SIZE);
                fprintf(stderr, "Regex execution failed: %s\n", error_buffer);
                free(error_buffer);
            } else {
                fprintf(stderr, "Regex execution failed\n");
            }
            break;
        }

        if (matches[0].rm_so != -1) {
            size_t word_len = matches[0].rm_eo - matches[0].rm_so;
            char *word = (char *)malloc(word_len + 1);
            
            if (word == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                break;
            }
            
            if (word_len > 0 && word_len < MAX_WORD_LEN) {
                size_t copy_len = word_len;
                if (copy_len > 0 && copy_len <= word_len) {
                    strncpy(word, copy + offset + matches[0].rm_so, copy_len);
                    word[copy_len] = '\0';
                    printf("%s\n", word);
                    count++;
                }
            }
            
            free(word);
            offset += matches[0].rm_eo;
        } else {
            break;
        }
    }

    if (count == 0) {
        printf("No matching words found.\n");
    }

    free(copy);
    regfree(&regex);
}

int main(void) {
    const char *test_string = "The quick brown fox jumps over the lazy dog near the river bank";
    
    find_words(test_string);
    
    return 0;
}