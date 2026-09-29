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
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char error_buffer[ERROR_BUFFER_SIZE];
        regerror(ret, &regex, error_buffer, sizeof(error_buffer));
        fprintf(stderr, "Regex compilation failed: %s\n", error_buffer);
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
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char error_buffer[ERROR_BUFFER_SIZE];
            regerror(ret, &regex, error_buffer, sizeof(error_buffer));
            fprintf(stderr, "Regex execution failed: %s\n", error_buffer);
            break;
        }

        if (matches[0].rm_so != -1) {
            size_t word_len = matches[0].rm_eo - matches[0].rm_so;
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char word[MAX_WORD_LEN];
            
            if (word_len > 0 && word_len < sizeof(word)) {
                size_t copy_len = (word_len < sizeof(word) - 1) ? word_len : sizeof(word) - 1;
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(word, copy + offset + matches[0].rm_so, copy_len);
                word[copy_len] = '\0';
                printf("%s\n", word);
                count++;
            }
            
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