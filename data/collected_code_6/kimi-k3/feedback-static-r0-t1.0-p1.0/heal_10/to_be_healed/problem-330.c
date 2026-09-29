#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_MATCHES 100
#define MAX_INPUT_LEN 4096
#define MAX_WORD_LEN 256

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
        char *error_buffer = NULL;
        size_t error_size = regerror(ret, &regex, NULL, 0);
        error_buffer = (char *)malloc(error_size);
        if (error_buffer != NULL) {
            regerror(ret, &regex, error_buffer, error_size);
            fprintf(stderr, "Regex compilation failed: %s\n", error_buffer);
            free(error_buffer);
        } else {
            fprintf(stderr, "Regex compilation failed\n");
        }
        return;
    }

    len = strnlen(str, MAX_INPUT_LEN);
    if (len == MAX_INPUT_LEN && str[len] != '\0') {
        fprintf(stderr, "Input string too long or not null-terminated\n");
        regfree(&regex);
        return;
    }

    copy = (char *)malloc(len + 1);
    if (copy == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        regfree(&regex);
        return;
    }

    if (len > 0) {
        if (len < MAX_INPUT_LEN) {
            if (len + 1 <= MAX_INPUT_LEN) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(copy, str, len);
            } else {
                fprintf(stderr, "Buffer overflow prevented\n");
                free(copy);
                regfree(&regex);
                return;
            }
        } else {
            fprintf(stderr, "Input length exceeds buffer capacity\n");
            free(copy);
            regfree(&regex);
            return;
        }
    }
    copy[len] = '\0';

    printf("Words with 3, 4, or 5 characters:\n");

    while (offset < len && count < MAX_MATCHES) {
        ret = regexec(&regex, copy + offset, 1, matches, 0);

        if (ret == REG_NOMATCH) {
            break;
        } else if (ret != 0) {
            char *error_buffer = NULL;
            size_t error_size = regerror(ret, &regex, NULL, 0);
            error_buffer = (char *)malloc(error_size);
            if (error_buffer != NULL) {
                regerror(ret, &regex, error_buffer, error_size);
                fprintf(stderr, "Regex execution failed: %s\n", error_buffer);
                free(error_buffer);
            } else {
                fprintf(stderr, "Regex execution failed\n");
            }
            break;
        }

        if (matches[0].rm_so != -1) {
            size_t word_len = matches[0].rm_eo - matches[0].rm_so;
            char *word = NULL;

            if (word_len > 0 && word_len < MAX_WORD_LEN) {
                word = (char *)malloc(word_len + 1);
                if (word != NULL) {
                    if (offset + matches[0].rm_so + word_len <= len && word_len + 1 <= MAX_WORD_LEN) {
                        /* Possible weaknesses found:
                         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                         */
                        memcpy(word, copy + offset + matches[0].rm_so, word_len);
                        word[word_len] = '\0';
                        printf("%s\n", word);
                        count++;
                    }
                    free(word);
                }
            }

            if (matches[0].rm_eo > 0) {
                offset += matches[0].rm_eo;
            } else {
                offset++;
            }
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